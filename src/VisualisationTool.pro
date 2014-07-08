#-------------------------------------------------
#
# Project created by QtCreator 2014-05-04T21:01:48
#
#-------------------------------------------------

QT       += core gui widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4):

QMAKE_CXXFLAGS += -std=c++11

TARGET = VisualisationTool
TEMPLATE = app

DEPENDENCY_DIR = ../dep
EIGEN_DIR = /usr/local/include/eigen3/

SOURCES += main.cpp\
    mainwindow.cpp \
    $${DEPENDENCY_DIR}/qcustomplot/qcustomplot.cpp \
    cpp/C3DReader.cpp \
    cpp/MarkerData.cpp \
    cpp/Sequence.cpp \
    cpp/StringFunc.cpp \
    cpp/Subject.cpp \
    cpp/Targets.cpp \
    cpp/Tools.cpp \
    cpp/Application.cpp \
    cpp/Trajectory.cpp \
    cpp/TextReader.cpp \
    cpp/PlotInterface.cpp

HEADERS  += mainwindow.h \
    $${DEPENDENCY_DIR}/qcustomplot/qcustomplot.h \
    include/Application.h \
    include/C3DReader.h \
    include/MarkerData.h \
    include/Sequence.h \
    include/Settings.h \
    include/StringFunc.h \
    include/Subject.h \
    include/Targets.h \
    include/Tools.h \
    include/Trajectory.h \
    $${DEPENDENCY_DIR}/uuc3dlib/include/basic_io.hpp \
    $${DEPENDENCY_DIR}/uuc3dlib/include/overview.hpp \
    $${DEPENDENCY_DIR}/uuc3dlib/include/skeleton_info.hpp \
    $${DEPENDENCY_DIR}/uuc3dlib/include/subjects.hpp \
    $${DEPENDENCY_DIR}/uuc3dlib/include/targetver.h \
    $${DEPENDENCY_DIR}/uuc3dlib/include/uuc3d.hpp \
    $${DEPENDENCY_DIR}/alglib/include/ \
    include/TextReader.h \
    include/PlotInterface.h
    include/Application.h


INCLUDEPATH += $${DEPENDENCY_DIR}/uuc3dlib/include \
		include \
		$${DEPENDENCY_DIR}/qcustomplot \
		$${EIGEN_DIR}

LIBS += -L$${DEPENDENCY_DIR}/uuc3dlib/lib/

LIBS += -luuc3d

FORMS += mainwindow.ui
