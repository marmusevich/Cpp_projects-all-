/**
 *  File: cSoundManager.h
 *  Project: Kore-Engine
 *
 *  Description: This file defines the sound manager
 *
 *  Created by Sean Chapel on 1/26/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */


#ifndef SOUNDMAN
#define SOUNDMAN

#include "globals.h"
#include "cMusic.h"
#include "cSound.h"


namespace Kore
{
	///
	/// This class manages sounds and music
	///
	class cSoundManager
	{
		friend class cMusic;
		friend class cSound;
	
		public:
				/// Default constructor
				cSoundManager();
				/// Default destructor
				~cSoundManager();
	
				/// Deletes all sounds
				void DeleteAllSounds();
				/// Sets the volume of the sounds
				void SetSoundVolume(int Volume);
				/// Returns the volume of the sounds
				int GetSoundVolume();
	
				/// Deletes all music
				void DeleteAllMusic();
				/// Stops the music
				void StopMusic();
				/// Pauses the music
				void PauseMusic();
				/// Resumes the music from a pause
				void ResumeMusic();
	
				/// Set music volume
				void SetMusicVolume(int Volume);
				/// Returns the volume of the music
				int GetMusicVolume();
	
		private:
				/// Registers a sound to be managed
				void RegisterSound(cSound* Sound);
				/// Removes a sound from being managed
				void UnRegisterSound(cSound* Sound);
	
				/// Registers music to be managed
				void RegisterMusic(cMusic* Music);
				/// Removes a sound from being managed
				void UnRegisterMusic(cMusic* Music);
	
				std::vector< cSound* > m_Sounds; 	/**< Holds all the sounds to be managed 	*/
				std::vector< cMusic* > m_Music; 	/**< Holds all the music to be managed		*/
				int m_SoundVolume;			/**< Stores the volume of the sound effects	*/
				int m_MusicVolume;			/**< Stores the volume of the music		*/
	};
}

#endif
