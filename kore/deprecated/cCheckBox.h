
/**
 *  File: cCheckBox.h
 *  Project: Kore-Engine
 *
 *  Description: This file contains defination of a check box
 *
 *  Created by Sean Chapel on 2/15/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#ifndef CHECKBOX
#define CHECKBOX


#include "cWidget.h"
#include "cFontManager.h"
#include "cTextureManager.h"
#include "GraphicTypes.h"


namespace Kore
{
	class cCheckBox : public cWidget
	{
		public:
				/// default constructor
				cCheckBox();

 				/// alternative constructor
 				cCheckBox(cFont* font, std::string caption, bool checked=false);

				/// default destructor
				virtual	~cCheckBox();

				/// returns if the checkbox is marked or not
				virtual bool IsMarked();

 				///	Checks if the CheckBox is marked.
				virtual void SetMarked(bool marked);

 				///	Gets the caption
				virtual std::string GetCaption();

 				///	Sets the CheckBox caption.
				virtual void SetCaption(std::string caption);

				/// Sets the font
				virtual void SetFont(cFont* font);

				/// Draws the checkbox
				virtual void Draw();

				/// virtual logic when clicked function
				virtual void Logic();

		protected:

					std::string	m_Caption;		/**< The text next to the checkbox							*/
					cFont*		m_Font;			/**< The font for the caption								*/
					bool		m_Checked;		/**< Holds if the checkbox is checked or not				*/
	};

}

#endif


