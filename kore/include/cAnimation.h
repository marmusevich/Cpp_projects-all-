/**
 *  File: cAnimation.h
 *  Project: Kore-Engine
 *
 *  Description: This file contains the definations of animations
 *		and its friend the manager.
 *
 *  Created by Sean Chapel on 1/21/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#ifndef ANIMATION
#define ANIMATION

#include "globals.h"
#include "GraphicTypes.h"
#include "cTextureManager.h"

namespace Kore
{
	///
	/// The animation class holds an animation and all the commands to
	/// manipulate it
	///
	class cAnimation
	{
		friend class cAnimationManager;

		private:
				cTexture* m_Texture;		    /**< Holds a cTexture for the animation to use 				*/
				std::vector< sRect > m_Frames;  /**< Holds the sections of the texture for the animation 	*/

				uint m_CurrentFrame;		    /**< The current frame of the animation						*/

				Uint32 m_LastUpdate;			/**< The last time the animation was update					*/
				Uint32 m_Fps;					/**< The number of frames per second						*/

				bool m_Paused;					/**< Tells if the animation is playing or not				*/
				bool m_IsDone;					/**< Tells if the animation is done playing or not				*/
				int m_Repeations;				/**< The number of times to repeat the animation			*/

		public:
				/// Default Constructor
				cAnimation(cTexture* Texture = NULL);
				/// Default Destructor
				~cAnimation();

				/// Deletes the animation
				void Delete();

				/// Updates the animation
				void Update();
				/// Pauses the animation
				void Pause();
				/// Returns bool of if the animation has terminated.
				bool IsDone();
				/// Resumes an animation from being paused
				void Resume();
				/// Resets the animation to the first frame
				void Reset();
				/// Sets the current frame of the animation
				void JumpToFrame(uint Frame);

				/// Sets the number of times to repeat
				void SetRepeations(int Repeations);

				/// Sets the cTexture to be used
				void SetTexture(cTexture* Texture);
				/// Sets all the sections of the animation
				void SetFrames(std::vector< sRect > Frames);
				/// Adds a frame to the end of the animation
				void AddFrame(sRect Frame);
				/// Removes all frames
				void ClearFrames();

				/// Sets the frames per second
				void SetFps(Uint32 Fps);

				/// Draws the current frame of the animation
				void Draw(GLfloat x, GLfloat y, GLfloat Scale = 1, GLfloat Rotation= 0, GLfloat Red = 1, GLfloat Green = 1, GLfloat Blue = 1, GLfloat Alpha = 1);

				/// Returns the number of frames
				uint GetFrameCount();

				/// Returns the current rect
				sRect* GetRect();

				/// Returns the texture used
				cTexture* GetTexture();
	};
}

#endif
