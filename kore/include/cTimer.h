/*
 *  cTimer.h
 *  Kore-Engine
 *
 *  Description: Holds the timer class
 *
 *  Created by Sean Chapel on 2/5/06
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#ifndef TIMER
#define TIMER

#include "globals.h"

namespace Kore
{

	class cTimer
	{
		public:
			/// Default Constructor
			cTimer();

			/// Default Destructor
			~cTimer();
			
			/// Sets the ammount of time till the time triggers (in milliseconds)
			void SetInterval(Uint32 Interval);

			/// Resets the timer
			void Reset();

			/// Tells if the timer has past the interval given
			bool TimeUp();

		private:

			Uint32 m_LastTime;	/**< Holds when the timer was last reset/created	*/
			Uint32 m_Interval;	/**< Holds how long the interval till timer triggers 	*/
	};
}

#endif
