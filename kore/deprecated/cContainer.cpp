/*
 *  cContainer.cpp
 *  Kore-Engine
 *
 *  Description: A container holds widgets
 *
 *  Created by Sean Chapel on 2/27/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */


#include "cContainer.h"
#include "cGraphics.h"
#include "Singleton.h"

namespace Kore
{
	//
	// Default constructor
	//
	cContainer::cContainer()
	{
	}

	//
	// Default destructor
	//
	cContainer::~cContainer()
	{
		/*
		for(std::list< cWidget* >::iterator itr = m_Widgets.begin(); itr != m_Widgets.end(); itr++)
		{
			if( (*itr) != NULL)
			{
				(*itr)->SetParent(NULL);
			}
		}
		*/
		

		m_Widgets.clear();
	}

	//
	// Returns if the widget is a container
	/// @return if the widget is a container
	///
	bool cContainer::isContainer()
	{
		return true;
	}

	//
	// Adds a widget to the container
	/// @param widget a cWidget pointer
	///
	void cContainer::Add(cWidget* widget)
	{
		bool WidgetExists = 0;
		
		for(std::list< cWidget* >::iterator itr = m_Widgets.begin(); itr != m_Widgets.end(); itr++)
		{
			if((*itr) == widget)
			{
				WidgetExists = 1;
			}
		}

		if(!WidgetExists)
		{
			widget->SetParent(this);
			m_Widgets.push_back(widget);
		}
	}

	//
	// Get Y coordinate
	/// @return y cooridnate
	///
	int cContainer::GetY()
	{
		GLfloat p_y = 0.0f;

		if(m_Parent != NULL)
		{
			p_y = (GLfloat)m_Parent->GetY();
		}

		return m_Y + p_y;
	}

	//
	// Get X coordinate
	/// @return x cooridnate
	///
	int cContainer::GetX()
	{
		GLfloat p_x = 0.0f;;

		if(m_Parent != NULL)
		{
			p_x = (GLfloat)m_Parent->GetX();
		}

		return m_X + p_x;
	}

	//
	// Removes a widget to the container
	/// @param widget a cWidget pointer
	///
	void cContainer::Remove(cWidget* widget)
	{
		for(std::list< cWidget* >::iterator itr = m_Widgets.begin(); itr != m_Widgets.end(); itr++)
		{
			if((*itr) == widget)
			{
				(*itr)->SetParent(NULL);
				m_Widgets.erase(itr);
				break;
			}
		}
	}

	//
	// Draws the container and all widgets
	//
	void cContainer::Draw()
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
		ClippingArea.Top = (GLfloat)(m_Y + m_Height + p_y + 1);
		ClippingArea.Right = (GLfloat)(m_X + m_Width + p_x + 1);
		ClippingArea.Left = (GLfloat)(m_X + p_x);

		graphics->PushClippingArea(ClippingArea);

		//draw the surrounding box
		graphics->DrawFilledRectangle((GLfloat)m_X + p_x, (GLfloat)m_Y + p_y, (GLfloat)m_Width, (GLfloat)m_Height, (GLfloat)0.3f, (GLfloat)0.3f, (GLfloat)0.3f, (GLfloat)1.0f);

		//draw all widgets
		for(std::list< cWidget* >::iterator itr = m_Widgets.begin(); itr != m_Widgets.end(); itr++)
		{
			(*itr)->Draw();
		}

		//draw the outline
		graphics->DrawRectangle((GLfloat)m_X + p_x, (GLfloat)m_Y + p_y, (GLfloat)m_Width, (GLfloat)m_Height, (GLfloat)0.0f, (GLfloat)0.0f, (GLfloat)0.0f, (GLfloat)1.0f);

		graphics->PopClippingArea();
	}

	//
	// When a mouse is clicked on the container
	/// @param x a int
	/// @param y a int
	/// @param button a int
	///
	void cContainer::MouseClicked(int x, int y, int button)
	{
		if((x >= m_X) && (x <= (m_X + m_Width)))
		{
			if((y >= m_Y) && (y <= (m_Y + m_Height)))
			{
				Logic();

				//send click events to all childern
				for(std::list< cWidget* >::iterator itr = m_Widgets.begin(); itr != m_Widgets.end(); itr++)
				{
					(*itr)->MouseClicked(x - m_X, y - m_Y, button);
				}
			}
		}
	}

	//
	// Does the logic for all widgets
	//
	void cContainer::Logic()
	{
	}

}