/*
 *  cWindow.h
 *  Kore-Engine
 *
 *  Description: A dragable window
 *
 *  Created by Sean Chapel on 3/01/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#include "cWidget.h"
#include "cFontManager.h"
#include "GraphicTypes.h"
#include "Singleton.h"

#ifndef CWINDOW
#define CWINDOW

namespace Kore
{
	class cWindow : public cWidget
	{
		public:
			/// Default Constructor
			cWindow();
			/// Default Destructor
			virtual ~cWindow();
			/// Draws the window
			virtual void Draw();
			/// Does the logic for all widgets
			virtual void Logic();
			/// Sets the font
			virtual void SetFont(cFont* font);
			/// Sets the title
			virtual void SetTitle(std::string title);
			/// Sets the content of the window
			virtual void SetContent(cWidget* widget);
			/// Returns if the window is movable or not
			virtual bool IsMovable();
			/// When a mouse is clicked on the container
			virtual void MouseClicked(int x, int y, int button);
			/// Tells when the mouse button was release
			virtual void MouseReleased(int button);
			/// Tells when the mouse was moved
			virtual void MouseMoved(int x, int y);
			/// Returns if the widget is a container
			bool isContainer();

		private:

			int m_Button;				/**< Holds the mosue button that clicked the window	*/
			sPoint m_ClickedPoint;		/**< Holds the point where window was clicked		*/
			bool m_Movable;				/**< Holds if the window is in drag mode			*/
			std::string m_Title;		/**< The Windows Title								*/
			cFont* m_Font;				/**< The font used									*/
			cWidget* m_Content;			/**< The content of the window						*/
			int m_TitleHeight;			/**< The height of the title bar					*/
	};
}

#endif