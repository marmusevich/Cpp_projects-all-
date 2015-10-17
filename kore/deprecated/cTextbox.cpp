
/**
 *  File: cTextbox.cpp
 *  Project: Kore-Engine
 *
 *  Description: This file contains defination of a textbox
 *
 *  Created by Sean Chapel on 2/15/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

 #include "cTextbox.h"
 #include "cGraphics.h"
 #include "Singleton.h"
 #include "cContainer.h"

namespace Kore
{
    //
    // default constructor
    //
    cTextbox::cTextbox()
    {
        m_Text = "";
        m_Font = NULL;
        m_Width = 75;
        m_Height = 20;

        m_InputTimer.SetInterval(100);
        m_InputTimer.Reset();
    }


    //
    // default destructor
    //
    cTextbox::~cTextbox()
    {
    }

    //
    // sets the font to use for drawing
    /// @param font a cFont pointer
    ///
    void cTextbox::SetFont(cFont* font)
    {
        m_Font = font;

		if(font != NULL)
		{
			m_Height = (int)font->GetHeight();
		}
    }

    //
    // virtual draw function
    //
    void cTextbox::Draw()
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

		sRect ClippingArea;
		ClippingArea.Bottom = (GLfloat)(m_Y + p_y);
		ClippingArea.Top = (GLfloat)(m_Y + m_Height + p_y + 1);
		ClippingArea.Right = (GLfloat)(m_X + m_Width + p_x + 1);
		ClippingArea.Left = (GLfloat)(m_X + p_x);

		graphics->PushClippingArea(ClippingArea);

        //draw the input box
        graphics->DrawFilledRectangle((GLfloat)(m_X + p_x), (GLfloat)(m_Y + p_y), (GLfloat)m_Width, (GLfloat)m_Height, (GLfloat)1.0f, (GLfloat)1.0f, (GLfloat)1.0f);

        GLfloat x, y, width;

        x = (GLfloat)(m_X + 2);
        y = (GLfloat)(m_Y + 2);

        width = m_Font->GetWidth(m_Text) + 2;

		std::string text = m_Text;

        if(width >= m_Width)
        {
			//fix to chop of the string when its offscreen
			text = "";

			for(int i = (int)m_Text.length(); i >= 0; i--)
			{
				text = m_Text[i] + text;

				if(m_Font->GetWidth(text) >= m_Width)
				{
					break;
				}
			}

			text = text.substr(0, text.length() - 3);
        }

        //draw the text
        m_Font->Draw(text, (p_x + x), (p_y + y + 4), 0, 0, 0);

        graphics->DrawRectangle((GLfloat)(m_X + p_x), (GLfloat)(m_Y + p_y), (GLfloat)m_Width, (GLfloat)m_Height, (GLfloat)m_TextFocus, (GLfloat)0.0f, (GLfloat)0.0f);

		graphics->PopClippingArea();
    }

    //
    // virtual logic when clicked function
    //
    void cTextbox::Logic()
    {
        TextFocus( true );
    }

    //
	// Tells the widget where the mouse clicked
	/// @param x a int
	/// @param y a int
	///
	void cTextbox::MouseClicked(int x, int y, int button)
	{
	    bool clicked = false;

		if((x >= m_X) && (x <= (m_X + m_Width)))
		{
			if((y >= m_Y) && (y <= (m_Y + m_Height)))
			{
			    clicked = true;
				Logic();
			}
		}

		if(!clicked)
		{
		    TextFocus( false );
		}
	}

    //
    // handles text input
    /// @param key an eKey
    ///
    void cTextbox::HandleTextInput(eKey key)
	{
		//check timer
        if(!m_InputTimer.TimeUp())
        {
            return;
        }
        else
		{
            m_InputTimer.Reset();
		}

		//handle backspace/delete
        if( ((key == KEY_BACKSPACE) || (key == KEY_DELETE) ) && (m_Text.length() != 0))
        {
			m_Text = m_Text.erase(m_Text.length() - 1);
        }

		if( (m_Text.length() >= 256))
        {
            return;
        }

        // handle normal input
        if( (key >= KEY_SPACE) && (key <= KEY_z) )
        {
            m_Text += (char) key;
        }
    }

    //
    // returns the string in the textbox
    /// @return te text entered in the box
    ///
    std::string cTextbox::GetText()
    {
        return m_Text;
    }

    //
    // clears the text in the box
    //
    void cTextbox::ClearText()
    {
        m_Text = "";
    }

}
