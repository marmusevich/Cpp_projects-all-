/**
 *  File: cSound.h
 *  Project: Kore-Engine
 *
 *  Description: This file contains the definition of a sound
 *
 *  Created by Sean Chapel on 1/26/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#ifndef SOUND
#define SOUND

#include "globals.h"


namespace Kore
{
	///
	/// This class holds a sound
	///
	class cSound
	{
		friend class cSoundManager;
	
		public:
				/// Default constructor
				cSound(std::string Filename = "");
				/// Default destructor
				~cSound();
	
				/// Loads a file from a zip
				bool LoadFromZip(std::string Filename);
				/// Loads a file
				bool Load(std::string Filename);
				/// Delete the sound
				void Delete();
				/// Plays the sound
				void Play(uint Repeats = 0);
	
		private:
			Mix_Chunk* 	m_Sound;	/**< Holds the sound data		*/
			std::string 	m_Filename;	/**< Holds the name of the file		*/
	};
}

#endif
