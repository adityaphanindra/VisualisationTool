///
/// \file Subject.h
/// \brief
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#ifndef SUBJECT_H
#define SUBJECT_H

#include "Settings.h"
#include "StringFunc.h"
#include "TextReader.h"
#include "Sequence.h"
#include "Targets.h"

#include <string>
#include <memory>

///
/// \class Subject
/// \brief Subject Class
///
class Subject
{
public:
    ///
    /// \struct Thresholds for the subject
    ///
    struct Thresholds
    {
        float speedCutoff;				///< max speed allowed
        float rotSpeedCutoff;			///< max rotation speed allowed
        float stepSizeThreshold;		///< step size threshold (# frames)
        float speedThreshold;			///< speed threshold
        float rotSpeedThreshold;		///< rotation speed threshold

        Thresholds() :
            speedCutoff(50),
            rotSpeedCutoff(0.02),
            stepSizeThreshold(50),
            speedThreshold(436.8 / FRAME_RATE),
            rotSpeedThreshold(0.008)
        {
        }

        std::string toString()
        {
            return StringFunc::numToString(speedCutoff) + " "  +
                    StringFunc::numToString(rotSpeedCutoff) + " "  +
                    StringFunc::numToString(stepSizeThreshold) + " "  +
                    StringFunc::numToString(speedThreshold) + " "  +
                    StringFunc::numToString(rotSpeedThreshold);
        }
    };



private:
    uint                                                    _subjectNumber; 			///< subject number
    std::string                                             _c3dDirectory;				///< c3d directory
    std::string                                             _saveDirectory;             ///< directory where intermediate files are saved
    std::string                                             _txtDirectory;              ///< txt directory
    Thresholds                                              _thresholds;				///< thresholds
    std::shared_ptr<Sequence::CalibrationCorrection>        _calibrationCorrection;		///< calibration correction
    std::vector<std::unique_ptr<Sequence> >                 _sequences;                 ///<
    std::shared_ptr<Targets>                                _targets;
public:
    ///
    /// \brief Constructor
    /// \param subjectNumber: subject number
    /// \param targets: pointer to targets object, including all info about all targets
    ///
    Subject(uint subjectNumber, std::shared_ptr<Targets> targets);

    ///
    /// \brief set the thresholds for the subject
    /// \param thresholds: thresholds to determine the steps
    ///
    void setThresholds(Thresholds thresholds);

    ///
    /// \brief read the calibration files and store the corrections
    ///
    void calibrate();

    ///
    /// \brief saveCalibration: saves the calibration correction of the subject in a file
    ///
    inline void saveCalibration();

    void initialiseAllSequences();
    ///
    /// \brief initialiseSequence
    /// \param textReader
    /// \param sequenceNumber
    ///
    void initialiseSequence(TextReader& textReader, uint sequenceNumber);

    void computeTrajectories(uint sequenceNumber);

    std::shared_ptr<Trajectory> getTrajectory(uint sequenceNumber, TrajectoryType trajectoryType = TrajectoryType::NORMAL);
private:
};


#endif
