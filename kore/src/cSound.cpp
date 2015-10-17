/**
 *  File: cSound.cpp
 *  Project: Kore-Engine
 *
 *  Description: This file contains the definition of a sound
 *
 *  Created by Sean Chapel on 1/26/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#include "cSound.h"
#include "cSoundManager.h"
#include "Singleton.h"
#include "SDL_rwops_zzip.h"

namespace Kore
{
	//
	// Default constructor
	/// @param Filename a std::string
	///
	cSound::cSound(std::string Filename)
	{
		m_Sound = NULL;
		m_Filename = Filename;

		if(Filename != "")
		{
			Load(Filename);
		}
	}

	//
	// Default destructor
	//
	cSound::~cSound()
	{
		if( m_Sound != NULL )
		{
			Mix_FreeChunk( m_Sound );
		}
	}

	//
	// Loads a file
	/// @param Filename a std::string
	/// @return Success or failure
	///
	bool cSound::Load(std::string Filename)
	{
		m_Sound = Mix_LoadWAV_RW(SDL_RWFromFile(Filename.c_str(), "rb"), 1);

		if( m_Sound == NULL )
		{
			std::cout << "Failed to load sound " << Filename << std::endl;
			return false;
		}

		m_Filename = Filename;

		Singleton<cSoundManager>::GetSingletonPtr()->RegisterSound(this);

		return true;
	}

	//
	// Loads a file from a zip
	/// @param Filename a std::string
	/// @return Success or failure
	///
	bool cSound::LoadFromZip(std::string Filename)
	{
		std::string mode = "rb";

		SDL_RWops* WavData = SDL_RWFromZZIP(Filename.c_str(), mode.c_str());

		m_Sound = Mix_LoadWAV_RW(WavData, 1);

		if( m_Sound == NULL )
		{
			std::cout << "Failed to load sound from zip" << Filename << std::endl;
			return false;
		}

		m_Filename = Filename;

		Singleton<cSoundManager>::GetSingletonPtr()->RegisterSound(this);

		return true;
	}

	//
	// Delete the sound
	//
	void cSound::Delete()
	{
		Singleton<cSoundManager>::GetSingletonPtr()->UnRegisterSound(this);
	}

	//
	// Plays the sound
	/// @param Repeats a uint
	///
	void cSound::Play(uint Repeats)
	{
		if( m_Sound == NULL )
		{
			return;
		}

		if( Mix_PlayChannel(-1, m_Sound, Repeats) == -1)
		{
			std::cout << "Failed to play sound " << m_Filename << " " << Mix_GetError() << std::endl;
		}
	}

}
