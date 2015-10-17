/*
 *  Engine.cpp
 *  Kore-Engine
 *
 *  Description: Links all the parts of the engine together
 *
 *  Created by Sean Chapel on 2/27/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */


#include "Engine.h"


namespace Kore
{
    Engine::Engine()
    {
        Initalize();
    }

    Engine::~Engine()
    {
        Shutdown();
    }

    void Engine::Initalize()
    {
        Sounds      = Singleton<cSoundManager>::GetSingletonPtr();
        Animations  = Singleton<cAnimationManager>::GetSingletonPtr();
        Textures    = Singleton<cTextureManager>::GetSingletonPtr();
        Fonts       = Singleton<cFontManager>::GetSingletonPtr();
        Camera      = Singleton<cCamera>::GetSingletonPtr();
        Graphics    = Singleton<cGraphics>::GetSingletonPtr();
        Input       = Singleton<cInput>::GetSingletonPtr();
    }

    void Engine::Shutdown()
    {
    }

}
