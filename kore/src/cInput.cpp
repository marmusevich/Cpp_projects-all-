/*
 *  cInput.h
 *  Kore-Engine
 *
 *  Description: Holds all the input core
 *
 *  Created by Sean Chapel on 2/1/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#include "cInput.h"
#include "cGraphics.h"
#include "Singleton.h"

namespace Kore
{
	//
	// Default Constructor
	//
	cInput::cInput()
	{
	}

	//
	// Default Destructor
	//
	cInput::~cInput()
	{
	}

	//
	// Tells if a key is inbetween being pressed and released
	//
	bool cInput::IsKeyHeld(eKey Key)
	{
		if(m_Keystates[Key] == 'h')
		{
			return true;
		}

		return false;
	}

	//
	// Tells if a key is pressed
	bool cInput::IsKeyDown(eKey Key)
	{
		if(m_Keystates[Key] == 'd')
		{
			return true;
		}

		return false;
	}

	//
	// Tells if a key is released
	//
	bool cInput::IsKeyUp(eKey Key)
	{
		if(m_Keystates[Key] == 'u')
		{
			return true;
		}

		return false;
	}

	//
	// Updates keyboard events
	/// @returns True is returned on an Exit key being pressed (ctrl+c, window being closed)
	/// Note: this also handles basic window events
	///
	bool cInput::Update()
	{
		SDL_Event event;
		std::vector< eKey > keys;

		//cGuiManager* Gui = Singleton<cGuiManager>::GetSingletonPtr();

		while ( SDL_PollEvent( &event ) )
		{
			switch( event.type )
			{
				case SDL_VIDEORESIZE:
					//Singleton<cGraphics>::GetSingletonPtr()->ResizeWindow( event.resize.w, event.resize.h );
					break;
				case SDL_QUIT:
					return true;
					break;
				case SDL_KEYDOWN:
					m_Keystates[event.key.keysym.sym] = 'd';
					keys.push_back((eKey)event.key.keysym.sym);
					break;
				case SDL_KEYUP:
					m_Keystates[event.key.keysym.sym] = 'u';
					keys.push_back((eKey)event.key.keysym.sym);
					break;
                case SDL_MOUSEMOTION:
                    m_MouseX = event.motion.x;
                    m_MouseY = Singleton<cGraphics>::GetSingletonPtr()->GetHeight() - event.motion.y;
                    break;
                case SDL_MOUSEBUTTONUP:
						//do input core stuff here
                    break;
                case SDL_MOUSEBUTTONDOWN:
						//do input core stuff here
                    break;
				default:
					break;
			}
		}

		//check to see if any keys haven't been released but were press
		// ie being held

		for( std::map<int, char>::iterator itr = m_Keystates.begin(); itr != m_Keystates.end(); itr++)
		{
			//put no status flag
			if( itr->second == 'u' )
			{
				bool keyFound = false;
				for(int i = 0; i < keys.size(); i++)
				{
					if(keys[i] == itr->first)
					{
						keyFound = true;
						break;
					}
				}

				if( !keyFound )
				{
					itr->second = 'n';
				}
			}
			else if( itr->second == 'd')
			{
				bool keyFound = false;
				for(int i = 0; i < keys.size(); i++)
				{
					if(keys[i] == itr->first)
					{
						keyFound = true;
						break;
					}
				}

				if( !keyFound )
				{
					itr->second = 'h';
				}
			}
		}

		return false;
	}
}
