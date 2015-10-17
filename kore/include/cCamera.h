/**
 *  File: cCamera.h
 *  Project: Kore-Engine
 *
 *  Description: This file contains defination of a camera
 *
 *  Created by Sean Chapel on 1/21/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#ifndef CAMERA
#define CAMERA

#include "globals.h"

namespace Kore
{
	///
	/// The camera handles what the view is looking at
	///
	class cCamera
	{
		public:
				/// Default Constructor
				cCamera();
				/// Default Destructor
				~cCamera();
	
				/// Moves the camera by x and y units
				void Move(GLfloat x, GLfloat y);
				/// Sets the absolute position of the camera
				void SetPosition(GLfloat x, GLfloat y);
	
				/// Returns the x cooridinate of the camera
				GLfloat GetXposition();
				/// Returns the y  cooridinate of the camera
				GLfloat GetYposition();
		private:
				GLfloat m_Xpos;		/**< The x position of the camera 	*/
				GLfloat m_Ypos;		/**< The y position of the camera 	*/
	};
}

#endif
