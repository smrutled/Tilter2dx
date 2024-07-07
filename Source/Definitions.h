//
//  Definitions.h
//  Tilter2dx
//
//  Created by Sean on 4/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#ifndef Tilter2d_Definitions_h
#define Tilter2d_Definitions_h
#include "axmol.h"
using namespace ax;

#define RATIO 32.0f
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define ENT_BALL 1
#define ENT_ENDZONE 2
#define ENT_HOLE 3
#define ENT_THRUSTER 4
#define ENT_ANTIACCEL 5
#define ENT_BLOCK 6


// Global properties
inline float designWidth{480};
inline float designHeight{320};
inline float factorX{};
inline float factorY{};
inline float scaledWidth{};
inline float scaledHeight{};
inline float screenWidth{};
inline float screenHeight{};
inline int currentLevel{};
inline int backgroundMusicId;


enum _entityCategory {
	BOUNDARY = 0x0001,
	A_BALL = 0x0002,
	A_SENSOR = 0x0004
};


#endif





