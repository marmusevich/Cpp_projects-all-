/*
 *  cTimer.cpp
 *  Kore-Engine
 *
 *  Description: Holds the timer class
 *
 *  Created by Sean Chapel on 2/5/06
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#include "cTimer.h"

namespace Kore
{
	//
	// Default Constructor
	//
	cTimer::cTimer()
	{
		m_Interval = 10000;
		Reset();
	}

	//
	// Default Destructor
	//
	cTimer::~cTimer()
	{
	}
	
	//
	// Sets the ammount of time till the time triggers (in milliseconds)
	/// @param Interval a Uint32
	///
	void cTimer::SetInterval(Uint32 Interval)
	{
		m_Interval = Interval;
		Reset();
	}

	//
	// Resets the timer
	//
	void cTimer::Reset()
	{
		m_LastTime = SDL_GetTicks();
	}

	//
	// Tells if the timer has past the interval given
	/// @return If the timer has reached the interval or not
	///
	bool cTimer::TimeUp()
	{
		if( (SDL_GetTicks() - m_LastTime) > m_Interval )
		{
			return true;
		}

		return false;
	}
}
