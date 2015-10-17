/*
 *  cContainer.h
 *  Kore-Engine
 *
 *  Description: A container holds widgets
 *
 *  Created by Sean Chapel on 2/27/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#ifndef CONTAINER
#define CONTAINER

#include "globals.h"
#include "cWidget.h"

namespace Kore
{
	class cContainer : public cWidget
	{
		public:
			/// Default constructor
			cContainer();
			/// Default destructor
			virtual ~cContainer();

			/// Adds a widget to the container
			void Add(cWidget* widget);
			/// Removes a widget from the container
			void Remove(cWidget* widget);
			/// Draws the container and all widgets
			virtual void Draw();
			/// Does the logic for all widgets
			virtual void Logic();
			/// When a mouse is clicked on the container
			virtual void MouseClicked(int x, int y, int button);
			/// Returns if the widget is a container
			bool isContainer();

			/// Get X coordinate
			virtual int GetX();
			/// Get Y coordinate
			virtual int GetY();

		private:
			std::list< cWidget* > m_Widgets;
	};
}

#endif