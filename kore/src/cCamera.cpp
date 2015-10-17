	/**
	*  File: cCamera.cpp
	*  Project: Kore-Engine
	*
	*  Description: This file defines what the view sees, ie the camera
	*
	*  Created by Sean Chapel on 1/21/06.
	*  Copyright 2006 Seoushi Games. All rights reserved.
	*
	*/
	
	#include "cCamera.h"
	
	namespace Kore
	{
	//
	// Default Constructor
	//
	cCamera::cCamera()
	{
		m_Xpos = 0;
		m_Ypos = 0;
	}
	
	//
	// Default Destructor
	//
	cCamera::~cCamera()
	{
	}
	
	//
	// Moves the camera by x and y units
	/// @param x a GLfloat
	/// @param y a GLfloat
	///
	void cCamera::Move(GLfloat x, GLfloat y)
	{
		m_Xpos -= x;
		m_Ypos -= y;
	}
	
	//
	// Sets the absolute position of the camera
	/// @param x a GLfloat
	/// @param y a GLfloat
	///
	void cCamera::SetPosition(GLfloat x, GLfloat y)
	{
		m_Xpos = -x;
		m_Ypos = -y;
	}
	
	//
	// Returns the x cooridinate of the camera
	/// @return X position of the camera
	///
	GLfloat cCamera::GetXposition()
	{
		return m_Xpos;
	}
	
	//
	// Returns the y cooridinate of the camera
	/// @return Y position of the camera
	///
	GLfloat cCamera::GetYposition()
	{
		return m_Ypos;
	}
}
