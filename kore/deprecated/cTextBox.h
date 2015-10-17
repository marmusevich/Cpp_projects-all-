
/**
 *  File: cTextbox.h
 *  Project: Kore-Engine
 *
 *  Description: This file contains defination of a textbox
 *
 *  Created by Sean Chapel on 2/15/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#ifndef TEXTBOX
#define TEXTBOX


#include "cWidget.h"
#include "cFontManager.h"
#include "cTimer.h"

namespace Kore
{
     class cTextbox : public cWidget
     {
		public:
				/// default constructor
				cTextbox();

				/// virtual destructor
				virtual ~cTextbox();

				/// virtual draw function
				virtual void Draw();

				/// virtual logic when clicked function
				virtual void Logic();

				/// handles text input
				virtual void HandleTextInput(eKey key);

				/// returns the string in the textbox
				virtual std::string GetText();

				/// clears the text in the box
				virtual void ClearText();

				/// sets the font to use for drawing
				virtual void SetFont(cFont* font);

				/// Tells the widget where the mouse clicked
                virtual void MouseClicked(int x, int y, int button);

		protected:
				std::string m_Text;		 /**<	the text in the box	            */
				cFont* m_Font;           /**<    Font to use for the textbox     */
				cTimer m_InputTimer;     /**<    Used to slow down input         */
     };
}

#endif
