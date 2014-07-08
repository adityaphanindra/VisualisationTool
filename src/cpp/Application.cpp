///
/// \file Application.cpp
/// \brief
/// \author PISUPATI Phanindra
/// \date 03.04.2014
///
#include "Application.h"
#include "TextReader.h"

#ifndef LOAD_ALL_SEQUENCES
#define LOAD_ALL_SEQUENCES 0
#endif

// --------------------------------------------------------- Public functions
Application::Application() :
    QObject(nullptr),
    _targets(std::shared_ptr<Targets>(new Targets())),
    _trajectoryType(TrajectoryType::NORMAL)
{
    QObject::connect(&_plotInterface, SIGNAL(pointClicked(uint, Point2d)), this, SLOT(showClickedPoint(uint, Point2d)));
}

Application::~Application() {
    _subjects.clear();
}

// --------------------------------------------------------- Public functions
void Application::initialiseSubjects(bool readFromFile) {
    _targets->initialiseTargets();

    if(!readFromFile) {
        for(uint i = 0; i < NUM_SUBJECTS; i++) {
            _subjects.push_back(std::unique_ptr<Subject>(new Subject(i + 1, _targets))); // subject numbers start at 1 instead of 0
        }

        if(LOAD_ALL_SEQUENCES) {
            std::unique_ptr<TextReader> textReader = std::unique_ptr<TextReader>(new TextReader(NUM_MARKERS));
            for(uint i = 0; i < NUM_SUBJECTS; i++) {
                _subjects[i]->calibrate();
                for(uint j = 0; j < NUM_SEQUENCES; j++) {
                    _subjects[i]->initialiseSequence(*textReader, j + 1); // sequence numbers start at 1 instead of 0
                    _subjects[i]->computeTrajectories(j + 1);
                    std::shared_ptr<Trajectory> trajectory = _subjects[i]->getTrajectory(j + 1);
                    std::cout << "Plot #: " << _plotInterface.plotTrajectory(trajectory) << std::endl;
                }
            }
        }
    } else  {
    //TODO
    }
}

uint Application::getSequenceNumber(uint subjectNumber, uint targetNumber) {
    return _targets->getSequenceNumbers(subjectNumber, targetNumber)[0]; // TODO: modify this to send both sequencenumbers
}

uint Application::getTargetNumber(uint subjectNumber, uint sequenceNumber) {
    return _targets->getTargetNumber(subjectNumber, sequenceNumber);
}

// --------------------------------------------------------- Public slots
void Application::clearAllPlots() {
    _plotInterface.clearAll();
}

void Application::plotTrajectory(uint subjectNumber, uint sequenceNumber) {
    std::unique_ptr<TextReader> textReader = std::unique_ptr<TextReader>(new TextReader(NUM_MARKERS));
    _subjects[subjectNumber-1]->initialiseSequence(*textReader, sequenceNumber); // sequence numbers start at 1 instead of 0
    _subjects[subjectNumber-1]->computeTrajectories(sequenceNumber);
    std::shared_ptr<Trajectory> trajectory = _subjects[subjectNumber-1]->getTrajectory(sequenceNumber, _trajectoryType);
    if(DEBUG)
        std::cout << "Application::plotTrajectory(): Plot #: " << _plotInterface.plotTrajectory(trajectory) << std::endl;
    else
        _plotInterface.plotTrajectory(trajectory);
}

void Application::showClickedPoint(uint plotId, Point2d point) {
    emit pointClicked(plotId, point.x, point.y);
}

void Application::changePlotType(PlotType plotType) {
    _plotInterface.setPlotType(plotType);
}

void Application::enableOrientation(bool enable) {
    _plotInterface.enableOrientation(enable);
}

void Application::fixTarget(bool enable) {
    if(enable)
        _trajectoryType = TrajectoryType::TARGET_FIXED;
    else
        _trajectoryType = TrajectoryType::NORMAL;
}

void Application::fixSource(bool enable) {
    if(enable)
        _trajectoryType = TrajectoryType::SOURCE_FIXED;
    else
        _trajectoryType = TrajectoryType::NORMAL;
}
