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

#include "cWindow.h"
#include "cGraphics.h"
#include "cContainer.h"

namespace Kore
{
	//
	// Default Constructor
	//
	cWindow::cWindow()
	{
		m_TitleHeight = 20;
		m_Movable = false;
		m_Button = 0;
		m_Title = "Window";
		m_Font = NULL;
		m_Content = NULL;
	}

	/// Default Destructor
	cWindow::~cWindow()
	{
		m_Content->SetParent(NULL);
	}

	//
	// Draws the window
	//
	void cWindow::Draw()
	{
		cGraphics* graphics = Singleton< cGraphics >::GetSingletonPtr();

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
		ClippingArea.Top = (GLfloat)(m_Y + m_Height + p_y);
		ClippingArea.Right = (GLfloat)(m_X + m_Width + p_x);
		ClippingArea.Left = (GLfloat)(m_X + p_x);

		graphics->PushClippingArea(ClippingArea);

		//draw the surrounding box
		graphics->DrawFilledRectangle((GLfloat)m_X, (GLfloat)m_Y, (GLfloat)m_Width, (GLfloat)m_Height, (GLfloat)0.3f, (GLfloat)0.3f, (GLfloat)0.3f, (GLfloat)1.0f);

		//draw the content
		if(m_Content != NULL)
		{
			m_Content->Draw();
		}

		//draw the outline
		graphics->DrawRectangle((GLfloat)m_X, (GLfloat)m_Y, (GLfloat)m_Width, (GLfloat)m_Height, (GLfloat)0.0f, (GLfloat)0.0f, (GLfloat)0.0f, (GLfloat)1.0f);

		graphics->PopClippingArea();

		//draw the titlebar
		GLfloat x, y, height, width;
		x = m_X + p_x;
		y = m_Y + p_y + m_Height;
		width = (GLfloat)m_Width;
		height = (GLfloat)m_TitleHeight;


		ClippingArea.Bottom = (GLfloat)y;
		ClippingArea.Top = (GLfloat)(y + height + 1);
		ClippingArea.Right = (GLfloat)(x + width + 1);
		ClippingArea.Left = (GLfloat)x;

		graphics->PushClippingArea(ClippingArea);

		//draw the surrounding box
		graphics->DrawFilledRectangle((GLfloat)x, (GLfloat)y, (GLfloat)width, (GLfloat)height, (GLfloat)0.7f, (GLfloat)0.7f, (GLfloat)0.7f, (GLfloat)1.0f);


		//draw the window title
		if(m_Font != NULL)
		{
			m_Font->Draw(m_Title, (x + 2), (y + 2), 0, 0, 0);
		}

		//draw the outline
		graphics->DrawRectangle((GLfloat)x, (GLfloat)y, (GLfloat)width, (GLfloat)height, (GLfloat)0.0f, (GLfloat)0.0f, (GLfloat)0.0f, (GLfloat)1.0f);

		graphics->PopClippingArea();
	}

	//
	// Does the logic for all widgets
	//
	void cWindow::Logic()
	{
	}

	//
	// Sets the font
	/// @param font a cFont pointer
	///
	void cWindow::SetFont(cFont* font)
	{
		m_Font = font;

		if(font != NULL)
		{
			m_TitleHeight = (int)font->GetHeight();
		}
	}

	//
	// Sets the title
	/// @param title a std::string
	///
	void cWindow::SetTitle(std::string title)
	{
		m_Title = title;
	}

	//
	// Sets the content of the window
	/// @param widget a cWidget pointer
	void cWindow::SetContent(cWidget* widget)
	{
		if(m_Content != NULL)
		{
			m_Content->SetParent(NULL);
		}

		m_Content = widget;

		if(m_Content != NULL)
		{
			m_Content->SetParent(this);

			m_Width = m_Content->GetWidth();
			m_Height = m_Content->GetHeight();
		}
	}

	//
	// Returns if the window is movable or not
	/// @return if the window is movable
	///
	bool cWindow::IsMovable()
	{
		return m_Movable;
	}

	//
	// When a mouse is clicked on the container
	/// @param x a int
	/// @param y a int
	/// @param button a int
	///
	void cWindow::MouseClicked(int x, int y, int button)
	{
		//if content was clicked
		if((x >= m_X) && (x <= (m_X + m_Width)))
		{
			if((y >= m_Y) && (y <= (m_Y + m_Height)))
			{
				Logic();

				//send click events to child
				m_Content->MouseClicked(x - m_X, y - m_Y, button);
			}
		}

		//if titlebar was clicked
		if((x >= m_X) && (x <= (m_X + m_Width)))
		{
			if((y >= (m_Y + m_Height)) && (y <= (m_Y + m_Height + m_TitleHeight)))
			{
				sPoint point;
				point.x = (GLfloat)(x - m_X);
				point.y = (GLfloat)(y - m_Y);

				m_ClickedPoint = point;
				m_Movable = true;
				m_Button = button;
			}
		}
	}

	//
	// Tells when the mouse button was release
	/// @param button a int
	///
	void cWindow::MouseReleased(int button)
	{
		if(m_Button = button)
		{
			m_Movable = false;
		}
	}

	//
	// Tells when the mouse was moved
	/// @param x a int
	/// @param y a int
	///
	void cWindow::MouseMoved(int x, int y)
	{
		if(!m_Movable)
		{
			return;
		}

		/*
		//make sure it doesn't go too far left
		if((x - m_ClickedPoint.x) <= 0)
		{
			return;
		}
		//make sure it doesn't go too far up
		if((y - m_ClickedPoint.y) <= 0)
		{
			return;
		}
		*/

		m_X = (int)(x - m_ClickedPoint.x);
		m_Y = (int)(y - m_ClickedPoint.y);
	}

	//
	// Returns if the widget is a container
	/// @return is the widget is a container
	///
	bool cWindow::isContainer()
	{
		return true;
	}
}