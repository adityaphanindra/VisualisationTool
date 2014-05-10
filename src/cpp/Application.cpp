///
/// \file Application.cpp
/// \brief
/// \author PISUPATI Phanindra
/// \date 03.04.2014
///
#include "Application.h"

// --------------------------------------------------------- Public functions
Application::Application()
{
}

// --------------------------------------------------------- Public functions
void Application::initialiseSubjects()
{
    for(uint i = 0; i < NUM_SUBJECTS; i++)
    {
        _subjects.push_back(new Subject(i + 1));
    }

    for(uint i = 0; i < NUM_SUBJECTS; i++)
    {
        _subjects[i]->calibrate();
    }

    _targets.initialiseTargets();
}
