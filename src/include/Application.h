///
/// \file C3DReader.h
/// \brief
/// \author PISUPATI Phanindra
/// \date 03.04.2014
///
///

#ifndef APPLICATION_H
#define APPLICATION_H
#include "Settings.h"
#include "Subject.h"
#include "Targets.h"
#include "PlotInterface.h"

#include <vector>
#include <string>
#include <memory>

///
/// \class Application
/// \brief Main Application for handling subjects, etc.
///
class Application : public QObject
{
Q_OBJECT

public:
    ///
    /// \brief Constructor
    ///
    Application();
    ///
    /// \brief Destructor
    ///
    ~Application();
    ///
    /// \brief initialiseSubjects: initialises subjects, sequences and target structures
    /// \param readFromFile: if false, initialise all sequences, otherwise read from files
    ///
    void initialiseSubjects(bool readFromFile);
    uint getSequenceNumber(uint subjectNumber, uint targetNumber);
    uint getTargetNumber(uint subjectNumber, uint sequenceNumber);

public slots:
    void clearAllPlots();
    void plotTrajectory(uint subjectNumber, uint sequenceNumber);
    void showClickedPoint(uint plotId, Point2d point);

private:
    std::vector<std::unique_ptr<Subject> >          _subjects;      ///< All subjects
    std::shared_ptr<Targets>                        _targets;       ///< Target data structure
    std::string                                     _sequenceDir;   ///< S
    PlotInterface                                   _plotInterface;

signals:
    void pointClicked(uint, float, float);
};


#endif // APPLICATION_H
