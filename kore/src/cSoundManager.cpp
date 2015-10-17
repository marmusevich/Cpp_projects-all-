/**
 *  File: cSoundManager.cpp
 *  Project: Kore-Engine
 *
 *  Description: This file defines the sound manager
 *
 *  Created by Sean Chapel on 1/26/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#include "cSoundManager.h"

namespace Kore
{
	//
	// Default constructor
	//
	cSoundManager::cSoundManager()
	{
		//setup SDL_mixer
		int audio_rate = 22050;
		Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
		int audio_channels = 2;
		int audio_buffers = 4096;
	
		SDL_Init(SDL_INIT_AUDIO);
	
		if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
		{
			std::cout << "Unable to open audio" << std::endl;
			SDL_Quit();
		}
	}
	
	//
	// Default destructor
	//
	cSoundManager::~cSoundManager()
	{
		DeleteAllSounds();
		DeleteAllMusic();
		Mix_CloseAudio();
	}
	
	//
	// Deletes all sounds
	//
	void cSoundManager::DeleteAllSounds()
	{
		for(uint i = 0; i < m_Sounds.size(); i++)
		{
			delete m_Sounds[i];
		}
	
		m_Sounds.clear();
	}
	
	//
	// Deletes all music
	//
	void cSoundManager::DeleteAllMusic()
	{
		StopMusic();
	
		for(uint i = 0; i < m_Music.size(); i++)
		{
			delete m_Music[i];
		}
	
		m_Music.clear();
	}
	
	//
	// Stops the music
	//
	void cSoundManager::StopMusic()
	{
		if( Mix_PlayingMusic() == 1)
		{
			Mix_HaltMusic();
		}
	}
	
	//
	// Sets the musics volume
	/// @param Volume a int
	/// Volume ranges from 1 to 128
	///
	void cSoundManager::SetMusicVolume(int Volume)
	{
		if( Volume > 128 )
		{
			Volume = 128;
		}
		if( Volume < 0 )
		{
			Volume = 0;
		}
	
		Mix_VolumeMusic(Volume);
	
		m_MusicVolume = Volume;
	}
	
	//
	// Sets the volume of the sounds
	/// @param Volume a int
	/// Volume ranges from 1 to 128
	///
	void cSoundManager::SetSoundVolume(int Volume)
	{
		if( Volume > 128 )
		{
			Volume = 128;
		}
		if( Volume < 0 )
		{
			Volume = 0;
		}
		
		Mix_Volume( -1, Volume);
		m_SoundVolume = Volume;
	}
	
	//
	// Returns the volume of the music
	/// @return The volume of the music
	/// Volume ranges from 1 to 128
	///
	int cSoundManager::GetMusicVolume()
	{
		return m_MusicVolume;
	}
	
	//
	// Returns the volume of the sounds
	/// @return The volume of the sound effects
	/// Volume ranges from 1 to 128
	///
	int cSoundManager::GetSoundVolume()
	{
		return m_SoundVolume;
	}
	
	
	//
	// Registers a sound to be managed
	/// @param Sound a cSound pointer
	///
	void cSoundManager::RegisterSound(cSound* Sound)
	{
		m_Sounds.push_back(Sound);
	}
	
	//
	// Removes a sound from being managed
	/// @param Sound a cSound pointer
	///
	void cSoundManager::UnRegisterSound(cSound* Sound)
	{
		int place = -1;
	
		for(uint i = 0; i < m_Sounds.size(); i++)
		{
			if(m_Sounds[i] == Sound)
			{
				place = i;
				break;
			}
		}
	
		if(place != -1)
		{
			m_Sounds.erase( m_Sounds.begin() + place );
		}
		
		delete Sound;
	}
	
	//
	// Registers music to be managed
	/// @param Music a cMusic pointer
	void cSoundManager::RegisterMusic(cMusic* Music)
	{
		m_Music.push_back(Music);
	}
	
	//
	// Removes a sound from being managed
	/// @param Music a cMusic pointer
	void cSoundManager::UnRegisterMusic(cMusic* Music)
	{
		int place = -1;
	
		for(uint i = 0; i < m_Music.size(); i++)
		{
			if(m_Music[i] == Music)
			{
				place = i;
				break;
			}
		}
	
		if(place != -1)
		{
			m_Music.erase( m_Music.begin() + place );
		}
		
		delete Music;
	}
}
