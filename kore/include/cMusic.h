/**
 *  File: cMusic.h
 *  Project: Kore-Engine
 *
 *  Description: This file contains the definition of music
 *
 *  Created by Sean Chapel on 1/26/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#ifndef MUSIC
#define MUSIC

#include "globals.h"


namespace Kore
{
	///
	/// This class holds music
	///
	class cMusic
	{
		friend class cSoundManager;
	
		public:
				/// Default constructor
				cMusic(std::string Filename = "");
				/// Default destructor
				~cMusic();
	
				/// Loads a File From a zip
				bool LoadFromZip(std::string Filename);
	
				/// Loads a file
				bool Load(std::string Filename);
				/// Delete the music
				void Delete();
				/// Plays the music
				void Play(int Repeats = 0);
	
		private:
			/// Turns off the m_Playing flag
			void StopPlaying();
	
			Mix_Music* 	m_Music;	/**< Holds the sound data			*/
			std::string 	m_Filename;	/**< Holds the name of the file			*/
	};
}

#endif
