/*
 *  globals.h
 *  Kore-Engine
 *
 *  Created by Sean Chapel on 11/15/05.
 *  Copyright 2005 Seoushi Games. All rights reserved.
 *
 */

#ifndef GLOBALS
#define GLOBALS

// for use or rwops in sdl_mixer
#define USE_RWOPS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <list>
#include <map>
#include <stack>

#ifdef WIN32
#include <windows.h>
#endif

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include <GL/gl.h>
#include <GL/glu.h>

#ifndef WIN32
#include <GL/glext.h>
#endif

#define uint unsigned int

#endif
