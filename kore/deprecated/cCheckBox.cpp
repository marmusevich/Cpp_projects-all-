
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


#include "cCheckBox.h"
#include "Singleton.h"
#include "cGraphics.h"
#include "cContainer.h"

namespace Kore
{

	//
	// default constructor
	//
	cCheckBox::cCheckBox()
	{
		m_Font = NULL;

		m_Width = 15;
		m_Height = 15;

		m_Checked = false;
	}

	//
	// alternative constructor
	//
	cCheckBox::cCheckBox(cFont* font, std::string caption, bool checked)
	{
		m_Font = font;
		m_Caption = caption;

	}

	//
	// default destructor
	//
	cCheckBox::~cCheckBox()
	{
	}

	//
	/// @return if the checkbox is marked or not
	///
	bool cCheckBox::IsMarked()
	{
	    return m_Checked;
	}


    //
	//	Checks if the CheckBox is marked.
	/// @param marked a bool
	///
	void cCheckBox::SetMarked(bool marked)
	{
	    m_Checked = marked;
	}

    //
	//	Gets the caption
	/// @return the id of the widget
	///
	std::string cCheckBox::GetCaption()
	{
	    return m_Caption;
	}

    //
	//	Sets the CheckBox caption.
	/// @param caption a std::string
	///
	void cCheckBox::SetCaption(std::string caption)
	{
	    m_Caption = caption;
	}

    //
	// Sets the font
	/// @param font a cFont pointer
	///
	void cCheckBox::SetFont(cFont* font)
	{
	    m_Font = font;
	}

    //
	// Draws the checkbox
	/// @param red a GLfloat
	/// @param green a GLfloat
	/// @param blue a GLfloat
	/// @param alpha a GLfloat
	///
	void cCheckBox::Draw ()
	{
		cGraphics* graphics = Singleton<cGraphics>::GetSingletonPtr();

		GLfloat p_x, p_y;

		if(m_Parent != NULL)
		{
			p_x = (GLfloat)m_Parent->GetX();
			p_y = (GLfloat)m_Parent->GetY();
		}
		else
		{
			p_x = 0.0f;
			p_y = 0.0f;
		}

	    //draw inner white part
	    graphics->DrawFilledRectangle((GLfloat)(m_X + p_x), (GLfloat)(m_Y + p_y), (GLfloat)m_Width, (GLfloat)m_Height, 1, 1, 1);

	    //draw black border arround it
	    graphics->DrawRectangle((GLfloat)(m_X + p_x), (GLfloat)(m_Y + p_y), (GLfloat)m_Width, (GLfloat)m_Height);

	    if(m_Checked)
	    {
	        // draw two lines to make it thicker
	        graphics->DrawLine((GLfloat)(m_X + 4 + p_x), (GLfloat)(m_Y + 7 + p_y), (GLfloat)(m_X + 9 + p_x), (GLfloat)(m_Y + 3 + p_y), (GLfloat)1.0f, (GLfloat)0.0f, (GLfloat)0.0f);
	        graphics->DrawLine((GLfloat)(m_X + 9 + p_x), (GLfloat)(m_Y + 3 + p_y), (GLfloat)(m_X + 18 + p_x), (GLfloat)(m_Y + 19 + p_y), (GLfloat)1.0f, (GLfloat)0.0f, (GLfloat)0.0f);

	        graphics->DrawLine( (GLfloat)(m_X + 4 + p_x), (GLfloat)(m_Y + 6 + p_y), (GLfloat)(m_X + 9 + p_x), (GLfloat)(m_Y + 2 + p_y), (GLfloat)1.0f, (GLfloat)0.0f, (GLfloat)0.0f);
	        graphics->DrawLine( (GLfloat)(m_X + 9 + p_x), (GLfloat)(m_Y + 2 + p_y), (GLfloat)(m_X + 17 + p_x), (GLfloat)(m_Y + 18 + p_y), (GLfloat)1.0f, (GLfloat)0.0f, (GLfloat)0.0f);
	    }

	    m_Font->Draw(m_Caption, (GLfloat) (m_X + m_Width + 5 + p_x), (GLfloat)(m_Y + p_y));
    }


    //
    // Does simple logic when clicked
    //
    void cCheckBox::Logic()
    {
        //toggle if its checked or not
        m_Checked = !m_Checked;
    }
}
