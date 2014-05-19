///
/// \file Targets.h
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#ifndef TARGETS_H
#define TARGETS_H

#include "Settings.h"
#include "StringFunc.h"
#include <string>
#include <map>
#include <vector>

//using namespace std;

class Targets
{
public:
    class Target
    {
    public:
        float x;
        float y;
        float theta; ///< (-pi, pi] -> orientation at the target
        Target() :
            x(0.0),
            y(0.0),
            theta(0.0)
        {
        }

        std::string toString()
        {
            return "x:" + StringFunc::numToString(x) + " y:" + StringFunc::numToString(y) + " orientation:" + StringFunc::numToString(theta);
        }
    };


private:
    Target          _targets[NUM_TARGETS];                              ///< list of x, y and theta of targets
    uint            _sequenceNumbers[NUM_SUBJECTS][NUM_TARGETS];		///< A mapping from target index to sequence #
    uint            _sequenceNumbersAlt[NUM_SUBJECTS][NUM_TARGETS];		///< A mapping from target index to alternate sequence #
    uint            _targetNumbers[NUM_SUBJECTS][NUM_SEQUENCES];		///< A mapping from sequence # to target index
    uint            _symmetricIndices[NUM_TARGETS];						///< A mapping of symmetric targets

public:
    ///
    /// \brief reads all files and initalises structures
    ///
    void initialiseTargets();

    ///
    /// \brief gets sequence numbers corresponding to the target
    /// \param subjectNumber: subject #
    /// \param targetNumber: target #
    /// \result one or two sequence #s corresponding to the target #
    ///
    std::vector<uint> getSequenceNumbers(uint subjectNumber, uint targetNumber);

    ///
    /// \brief gets the target index for
    /// \param subjectNumber: subject #
    /// \param sequenceNumber: sequence #
    /// \result target # corresponding to the sequence # for subject #
    ///
    uint getTargetNumber(uint subjectNumber, uint sequenceNumber);

    ///
    /// \brief returns the target details
    /// \param targetNumber: target #
    /// \return Target details containing x, y and theta
    Target getTarget(uint targetNumber);

    ///
    /// \brief returns the target details
    /// \param subjectNumber: subject #
    /// \param sequenceNumber: sequence #
    /// \return Target corresponding to subject # and sequence #
    Target getTargetFromSequenceNum(uint subjectNumber, uint sequenceNumber);

    ///
    /// \brief get the index of symmetric target
    /// \param targetNumber: target #
    /// \return target # symmetric to input target #
    uint getSymmetricTarget(uint targetNumber);

}; // end of class Targets
#endif
