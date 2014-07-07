///
/// \file Targets.cpp
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#include "Targets.h"
#include "StringFunc.h"
#include <fstream>
#include <iostream>

void Targets::initialiseTargets() {
    std::string targetDirectory = "..//data//targets//";
    std::ifstream fTargets(targetDirectory + "targets_ordered.txt");
	uint targetIndex = 0;
    while(!fTargets.eof()) 	{
        fTargets >> _targets[targetIndex].x >> _targets[targetIndex].y >> _targets[targetIndex].theta;
		targetIndex++;
		if(targetIndex == NUM_TARGETS)
			break;
	}
	fTargets.close();

    std::ifstream fSymmetricTargets(targetDirectory + "symmetric_targets.txt");
	targetIndex = 0;
	while(!fSymmetricTargets.eof())	{
        fSymmetricTargets >> _symmetricIndices[targetIndex];
        //symmetricIndices[targetIndex]; // indices start at 1
		targetIndex++;
		if(targetIndex == NUM_TARGETS)
			break;
	}
	fSymmetricTargets.close();

	for(uint subjectNumber = 0; subjectNumber < NUM_SUBJECTS; subjectNumber++)	{
        std::ifstream fSubject(targetDirectory + "targets_rev_index_" + StringFunc::numToString(subjectNumber + 1) + ".txt");
		targetIndex = 0;
        while(!fSubject.eof()) {
			uint index1, index2;
			fSubject >> index1 >> index2;
            _sequenceNumbers[subjectNumber][targetIndex] = index1; // indices start at 0
            _sequenceNumbersAlt[subjectNumber][targetIndex] = index2; // indices start at 0
			
			if(index1 > 0)
                _targetNumbers[subjectNumber][index1 - 1] = targetIndex + 1; // target #s start at 1
			if(index2 > 0)
                _targetNumbers[subjectNumber][index2 - 1] = targetIndex + 1;

			targetIndex++;
			if(targetIndex == NUM_TARGETS)
				break;
		}
		fSubject.close();
	}

    if(DEBUG) {
        std::cout << "Targets::initialiseTargets(): Targets initialised!" << std::endl;
    }
}

std::vector<uint> Targets::getSequenceNumbers(uint subjectNumber, uint targetNumber) {
    std::vector<uint> indices;
    if(subjectNumber > 0 && subjectNumber <= NUM_SUBJECTS && targetNumber > 0 && targetNumber <= NUM_TARGETS) {
        uint index1 = _sequenceNumbers[subjectNumber - 1][targetNumber - 1];
        uint index2 = _sequenceNumbersAlt[subjectNumber - 1][targetNumber - 1];
		if(index1 > 0)
			indices.push_back(index1);
		if(index2 > 0)
			indices.push_back(index2); // 0 isn't a valid index
    } else {
        std::cerr << "getSequenceNumbers(): Subject # or Target # out of range!" << std::endl;
	}
	return indices;
}

uint Targets::getTargetNumber(uint subjectNumber, uint sequenceNumber) {
	uint index = 0; // invalid index
	if(subjectNumber > 0 && subjectNumber <= NUM_SUBJECTS && sequenceNumber > 0 && sequenceNumber <= NUM_SEQUENCES)	{
        index = _targetNumbers[subjectNumber - 1][sequenceNumber - 1];
    } else {
        std::cerr << "getTargetNumber(): Subject # or Sequence # out of range!" << std::endl;
	}
	return index;
}

Targets::Target Targets::getTarget(uint targetNumber) {
    if(targetNumber > 0 && targetNumber <= NUM_TARGETS) {
        return _targets[targetNumber - 1];
    } else {
        std::cerr << "getTarget(): target # out of range!" << std::endl;
		return Target();
	}
}

Targets::Target Targets::getTargetFromSequenceNum(uint subjectNumber, uint sequenceNumber) {
	return getTarget(getTargetNumber(subjectNumber, sequenceNumber));
}

uint Targets::getSymmetricTarget(uint targetNumber) {
    if(targetNumber > 0 && targetNumber <= NUM_TARGETS) {
        return _symmetricIndices[targetNumber - 1];
    } else {
        std::cerr << "getSymmetricTarget(): target # out of range!" << std::endl;
		return 0;
	}
}
