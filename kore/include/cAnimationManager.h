	/**
	*  File: cAnimationManager.h
	*  Project: Kore-Engine
	*
	*  Description: This file contains defines the animation manager
	*
	*  Created by Sean Chapel on 1/21/06.
	*  Copyright 2006 Seoushi Games. All rights reserved.
	*
	*/

	#ifndef ANIMMAN
	#define ANIMMAN

	#include "globals.h"
	#include "cAnimation.h"

	namespace Kore
	{
	///
	/// This class manages all animations
	///
	class cAnimationManager
	{
		friend class cAnimation;

		public:
				/// Default constructor
				cAnimationManager();
				/// Default destructor
				~cAnimationManager();

				/// Deletes all animations
				void DeleteAll();
				/// Pauses all animations
				void PauseAll();
				/// Updates all animations
				void UpdateAll();
				/// Resumes all animations
				void ResumeAll();
				/// Resets all animations
				void ResetAll();

		private:
				/// Registers an animation to be managed
				void RegisterAnimation(cAnimation* Animation);

				/// Removes an animation from being managed
				void UnRegisterAnimation(cAnimation* Animation);

				std::vector< cAnimation* > m_Animations; 	/**< Holds all the animations to be managed 	*/
	};
}

#endif
