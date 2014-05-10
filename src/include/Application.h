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

#include <vector>

using namespace std;

///
/// \class Application
/// \brief Main Application for handling subjects, etc.
///
class Application
{
    vector<Subject *>       _subjects;  ///< All subjects
    Targets                 _targets;   ///< Target data structure

public:
    Application();
    void initialiseSubjects();
};


#endif // APPLICATION_H
