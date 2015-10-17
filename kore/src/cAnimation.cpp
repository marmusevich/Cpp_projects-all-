/**
 *  File: cAnimation.cpp
 *  Project: Kore-Engine
 *
 *  Description: This file contains graphics code for animations
 *		and the animation manager
 *
 *  Created by Sean Chapel on 1/21/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#include "cAnimation.h"
#include "Singleton.h"
#include "cAnimationManager.h"

namespace Kore
{
	//
	// Default Constructor
	/// @param Texture a cTexture pointer
	///
	cAnimation::cAnimation(cTexture* Texture)
	{
		//setup sane defaults
		m_Texture = Texture;

		m_Frames.clear();

		m_CurrentFrame = 0;

		m_LastUpdate = SDL_GetTicks();
		m_Fps = 5;

		m_Paused = false;
		m_IsDone = false;
		m_Repeations = 0;

		Singleton<cAnimationManager>::GetSingletonPtr()->RegisterAnimation(this);
	}

	//
	// Default Destructor
	//
	cAnimation::~cAnimation()
	{
	}

	//
	// Deletes the animation
	//
	void cAnimation::Delete()
	{
		Singleton<cAnimationManager>::GetSingletonPtr()->UnRegisterAnimation(this);
	}

	//
	// Updates the animation
	//
	void cAnimation::Update()
	{
		//if the animation is paused or not loaded skip updating
		if( (m_Paused == true) || (m_Texture == NULL) || ( m_Frames.size() == 0) )
		{
			return;
		}

		//find out if enough time has passed
		if( 1000/m_Fps < (SDL_GetTicks() - m_LastUpdate) )
		{
			m_CurrentFrame++;
			m_LastUpdate = SDL_GetTicks();

			//if we reached the end
			if(m_CurrentFrame >= m_Frames.size())
			{
				//if not going for infinitey then set the reps one less
				if( m_Repeations != -1 )
				{
					//if there are no reps left then pause the animation
					if( m_Repeations == 0)
					{
						m_IsDone = true;
						m_Paused = true;
					}
					else //handle it normaly
					{
						m_Repeations--;
					}
				}

				m_CurrentFrame = 0;
			}
		}
	}

	//
	// Pauses the animation
	//
	void cAnimation::Pause()
	{
		m_Paused = true;
	}

	//
	// Returns bool if animation is done or not
	/// @return Bool saying if the animation is done or not.
	bool cAnimation::IsDone()
	{
		return m_IsDone;
	}

	//
	// Resumes an animation from being paused
	//
	void cAnimation::Resume()
	{
		m_Paused = false;
		m_LastUpdate = SDL_GetTicks();
	}

	//
	// Resets the animation to the first frame
	//
	void cAnimation::Reset()
	{
		m_CurrentFrame = 0;
		m_LastUpdate = SDL_GetTicks();
	}

	//
	// Sets the current frame of the animation
	//
	void cAnimation::JumpToFrame(uint Frame)
	{
		//only set if the frame is in range
		if(Frame < m_Frames.size())
		{
			m_CurrentFrame = Frame;
			m_LastUpdate = SDL_GetTicks();
		}
	}

	//
	// Sets the number of times to repeat
	/// any negitive number set the animation to loop infinitly
	/// @param Repeations a integer argument.
	///
	void cAnimation::SetRepeations(int Repeations)
	{
		m_Repeations = Repeations;
	}

	//
	// Sets the cTexture to be used
	/// @param Texture a cTexture pointer.
	///
	void cAnimation::SetTexture(cTexture* Texture)
	{
		m_Texture = Texture;
	}

	//
	// Sets all the sections of the animation
	/// @param Frames a vector of sRect
	///
	void cAnimation::SetFrames(std::vector< sRect > Frames)
	{
		m_Frames = Frames;
	}

	//
	// Adds a frame to the end of the animation
	/// @param Frame a sRect
	///
	void cAnimation::AddFrame(sRect Frame)
	{
		m_Frames.push_back(Frame);
	}

	//
	// Removes all frames
	///
	void cAnimation::ClearFrames()
	{
		m_Frames.clear();
	}

	//
	// Sets the frames per second
	/// @param Fps a Uint32
	///
	void cAnimation::SetFps(Uint32 Fps)
	{
		m_Fps = Fps;
	}

	//
	// Draws the current frame of the animation
	/// @param x a GLfloat
	/// @param y a GLfloat
	/// @param Scale a GLfloat
	/// @param Rotation a GLfloat
	/// @param Red a GLfloat
	/// @param Green a GLfloat
	/// @param Blue a GLfloat
	/// @param Alpha a GLfloat
	///
	void cAnimation::Draw(GLfloat x, GLfloat y, GLfloat Scale, GLfloat Rotation, GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha)
	{
		//only draw if the texture has been set
		if(m_Texture != NULL)
		{
			m_Texture->DrawSection(x, y, &m_Frames[m_CurrentFrame], Scale, Rotation, Red, Green, Blue, Alpha);
		}
	}

	//
	// Returns the number of frames
	/// @return The Number of Frames
	uint cAnimation::GetFrameCount()
	{
		return (uint)m_Frames.size();
	}

	//
	// Returns the current rect
	sRect* cAnimation::GetRect()
	{
		return &m_Frames[m_CurrentFrame];
	}

	/// Returns the texture used
	cTexture* cAnimation::GetTexture()
	{
		return m_Texture;
	}
}
