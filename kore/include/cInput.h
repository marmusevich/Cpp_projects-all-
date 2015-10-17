/*
 *  cInput.h
 *  Kore-Engine
 *
 *  Description: Holds all the input core
 *
 *  Created by Sean Chapel on 2/1/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#ifndef CINPUT
#define CINPUT

#include "keys.h"
#include "globals.h"

namespace Kore
{

	class cInput
	{
		public:
			/// Default Constructor
			cInput();

			/// Default Destructor
			~cInput();

			/// Tells if a key is inbetween being pressed and released
			bool IsKeyHeld(eKey Key);

			/// Tells if a key is pressed
			bool IsKeyDown(eKey Key);

			/// Tells if a key is released
			bool IsKeyUp(eKey Key);

			/// Updates keyboard events
			bool Update();

		private:

			std::map<int, char> m_Keystates;	/**< Holds the state of the keys */
			int m_MouseX;
			int m_MouseY;
			std::vector< char > m_MouseButtons;
	};
}

#endif
