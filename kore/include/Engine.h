/*
 *  Engine.h
 *  Kore-Engine
 *
 *  Description: Links all the parts of the engine together
 *
 *  Created by Sean Chapel on 2/27/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */


#include "cAnimationManager.h"
#include "cTextureManager.h"
#include "cFontManager.h"
#include "cSoundManager.h"
#include "cCamera.h"
#include "cGraphics.h"
#include "cInput.h"
#include "Singleton.h"


#ifndef ENGINE
#define ENGINE

namespace Kore
{
    class Engine
    {
        public:
                Engine();
                ~Engine();

                void Initalize();
                void Shutdown();

                cSoundManager*      Sounds;
                cAnimationManager*  Animations;
                cTextureManager*    Textures;
                cFontManager*       Fonts;
                cCamera*            Camera;
                cGraphics*          Graphics;
                cInput*	            Input;
    };
}

#endif
