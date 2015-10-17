/**
 *  File: cMusic.cpp
 *  Project: Kore-Engine
 *
 *  Description: This file contains the definition of music
 *
 *  Created by Sean Chapel on 1/26/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#include "cMusic.h"
#include "cSoundManager.h"
#include "Singleton.h"
#include "SDL_rwops_zzip.h"


namespace Kore
{
	//
	// Default constructor
	/// @param Filename a std::string
	///
	cMusic::cMusic(std::string Filename)
	{
		m_Music = NULL;
		m_Filename = Filename;

		if(Filename != "")
		{
			Load(Filename);
		}
	}

	//
	// Default destructor
	//
	cMusic::~cMusic()
	{
		Singleton<cSoundManager>::GetSingletonPtr()->StopMusic();
		Mix_FreeMusic(m_Music);
	}

	//
	// Loads a File From a zip
	/// @param Filename a std::string
	/// @return Success or failure
	///
	bool cMusic::LoadFromZip(std::string Filename)
	{
		std::string mode = "rb";

		SDL_RWops* MusicData = SDL_RWFromZZIP(Filename.c_str(), mode.c_str());

		m_Music = Mix_LoadMUS_RW(MusicData);

		if(m_Music == NULL)
		{
			std::cout << "Failed to load music from zip" << Filename << std::endl;
			return false;
		}

		m_Filename = Filename;
		Singleton<cSoundManager>::GetSingletonPtr()->RegisterMusic(this);

		return true;
	}

	//
	// Loads a file
	/// @param Filename a std::string
	/// @return Success or failure
	///
	bool cMusic::Load(std::string Filename)
	{
		m_Music = Mix_LoadMUS(Filename.c_str());

		if(m_Music == NULL)
		{
			std::cout << "Failed to load music " << Filename << std::endl;
			return false;
		}

		m_Filename = Filename;
		Singleton<cSoundManager>::GetSingletonPtr()->RegisterMusic(this);

		return true;
	}

	//
	// Delete the music
	//
	void cMusic::Delete()
	{
		if(m_Music == NULL)
		{
			return;
		}

		Singleton<cSoundManager>::GetSingletonPtr()->StopMusic();

		Mix_FreeMusic( m_Music );

		Singleton<cSoundManager>::GetSingletonPtr()->UnRegisterMusic(this);
	}

	//
	// Plays the music
	/// @param Repeats a int
	/// -1 is infinite looping
	///
	void cMusic::Play(int Repeats)
	{
		if(m_Music == NULL)
		{
			return;
		}

		Singleton<cSoundManager>::GetSingletonPtr()->StopMusic();

		Mix_PlayMusic(m_Music, Repeats);
	}
}
