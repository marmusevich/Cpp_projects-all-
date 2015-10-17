/**
 *  File: GraphicTypes.h
 *  Project: Kore-Engine
 *
 *  Description: This file contains everything animation related
 *
 *
 *  Created by Sean Chapel on 1/21/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#include "globals.h"
#include "cAnimationManager.h"
#include "cGraphics.h"

namespace Kore
{
	//
	// Default constructor
	//
	cAnimationManager::cAnimationManager()
	{
		m_Animations.clear();
	}

	//
	// Default destructor
	//
	cAnimationManager::~cAnimationManager()
	{
	DeleteAll();
	}

	//
	// Deletes all animations
	//
	void cAnimationManager::DeleteAll()
	{
		for(uint i = 0; i < m_Animations.size(); i++)
		{
			if( m_Animations[i] != NULL )
			{
				delete m_Animations[i];
			}
		}

		m_Animations.clear();
	}

	//
	// Pauses all animations
	//
	void cAnimationManager::PauseAll()
	{
		for (uint i = 0; i < m_Animations.size(); i++)
		{
			m_Animations[i]->Pause();
		}
	}

	//
	// Updates all animations
	//
	void cAnimationManager::UpdateAll()
	{
		for (uint i = 0; i < m_Animations.size(); i++)
		{
			m_Animations[i]->Update();
		}
	}

	//
	// Resumes all animations
	//
	void cAnimationManager::ResumeAll()
	{
		for (uint i = 0; i < m_Animations.size(); i++)
		{
			m_Animations[i]->Resume();
		}
	}

	//
	// Resets all animations
	//
	void cAnimationManager::ResetAll()
	{
		for (uint i = 0; i < m_Animations.size(); i++)
		{
			m_Animations[i]->Reset();
		}
	}

	//
	// Adds an animation to the manager
	/// @param Animation a cAnimation pointer
	///
	void cAnimationManager::RegisterAnimation(cAnimation* Animation)
	{
		//add the texture to the vector
		m_Animations.push_back(Animation);
	}

	//
	// Remove an animation from the manager
	/// @param Animation a cAnimation pointer
	///
	void cAnimationManager::UnRegisterAnimation(cAnimation* Animation)
	{
		int place = -1;

		//lets find where the animation is in the vector
		for( uint i = 0; i < m_Animations.size(); i++)
		{
			if( m_Animations[i]->m_Texture == Animation->m_Texture )
			{
				place = i;
			}
		}

		//if its not registed then do nothing
		if(place == -1)
		{
			return;
		}

		//if the place is at the end just remove the animation
		if( (place + 1) == (int)m_Animations.size())
		{
			m_Animations.erase( m_Animations.begin() + place);
		}
		else // move the last place to the empty slot and remove the last one element
		{
			m_Animations[place] = m_Animations[ m_Animations.size() - 1 ];
			m_Animations.erase( m_Animations.begin() + place);
		}

		delete Animation;
	}
}
