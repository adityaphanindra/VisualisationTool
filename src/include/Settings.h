///
/// \file Settings.h
/// \brief
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#ifndef SETTINGS_H
#define SETTINGS_H

typedef unsigned int uint;

#ifndef DEBUG
#define DEBUG 1
#endif

#ifndef PI
#define PI 3.1415927
#endif

#define NUM_MARKERS     19
#define	NUM_SUBJECTS    20
#define NUM_SEQUENCES   386
#define NUM_TARGETS     359
#define NUM_SESSIONS    4
#define FRAME_RATE      480
#define NORMALISATION_HEIGHT 1860

// Butterworth Filter parameters
#define BUTTERWORTH_FREQUENCY   5

enum BodyParts {LEFT_FOOT = 0,
                RIGHT_FOOT = 1,
                PELVIS = 2
               };
enum FootMarkers {FOOT_LEFT = 0,
                  FOOT_TOP = 1,
                  FOOT_RIGHT = 2,
                  FOOT_BOTTOM = 3
                 };
enum PelvisMarkers {PELVIS_LEFT = 0,
                    PELVIS_RIGHT = 1
                   };
enum AllMarkers {LEFT_LEFT_MARKER = 0,
                 LEFT_TOP_MARKER = 1,
                 LEFT_RIGHT_MARKER = 2,
                 LEFT_BOTTOM_MARKER = 3,
                 RIGHT_LEFT_MARKER = 6,
                 RIGHT_TOP_MARKER = 7,
                 RIGHT_RIGHT_MARKER = 8,
                 RIGHT_BOTTOM_MARKER = 9,
                 PELVIS_LEFT_MARKER = 12,
                 PELVIS_RIGHT_MARKER = 13,
                 SHOULDER_LEFT = 14,
                 SHOULDER_RIGHT = 15,
                 HEAD_LEFT = 16,
                 HEAD_CENTRE = 17,
                 HEAD_RIGHT = 18
                };

enum InterpolationType {CUBIC_INTERPOLATION = 0,
                         LINEAR_INTERPOLATION = 1
                        };

enum PlotType {SCATTER = 0,
               LINE = 1
              };

enum TrajectoryType {NORMAL = 0,
                     TARGET_FIXED = 1,
                     SOURCE_FIXED = 2
                    };

#endif
