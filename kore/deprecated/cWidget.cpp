
/**
 *  File: cWidget.h
 *  Project: Kore-Engine
 *
 *  Description: This file contains defination of a widget
 *
 *  Created by Sean Chapel on 2/15/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#include "cWidget.h"
#include "cGraphics.h"
#include "Singleton.h"

namespace Kore
{
	//
	// default constructor
	//
	cWidget::cWidget()
	{
		m_HasParent = false;
		m_Parent = NULL;
	    m_TextFocus = false;
	    Singleton<cWidgetManager>::GetSingletonPtr()->RegisterWidget(this);

		m_X = 0;
		m_Y = 0;
		m_Width = 10;
		m_Height = 10;
	}

	//
	// Set width
	/// @param width a int
	///
	void cWidget::SetWidth(int width)
	{
		m_Width = width;
	}

	//
	// default destructor
	//
	cWidget::~cWidget()
	{
	    Delete();
	}

	//
	// Tells if the widget has a parent or not
	/// @return if the widget has a parent or not
	///
	bool cWidget::HasParent()
	{
		return m_HasParent;
	}

	//
	// Sets the parent to the widget
	/// @param container a cContainer pointer
	///
	void cWidget::SetParent(cWidget* container)
	{
		if(!container->isContainer())
		{
			return;
		}

		if(container != NULL)
		{
			m_HasParent = true;
		}
		else
		{
			m_HasParent = false;
		}

		m_Parent = container;
	}

	//
	// Get Width
	/// @return width of the widget
	///
	int cWidget::GetWidth()
	{
		return m_Width;
	}

	//
	// Set Height
	/// @param height a int
	//
	void cWidget::SetHeight(int height)
	{
		m_Height = height;
	}

	//
	// Get Height
	/// @return height of the widget
	///
	int cWidget::GetHeight()
	{
		return m_Height;
	}

	//
	// Set X coordinate
	/// @param x a int
	///
	void cWidget::SetX(int x)
	{
		m_X = x;
	}

	//
	// Get X coordinate
	/// @return x cooridnate
	///
	int cWidget::GetX()
	{
		return m_X;
	}

	//
	// Set Y coordinate
	/// @param y a int
	///
	void cWidget::SetY(int y)
	{
		m_Y = y;
	}

	//
	// Get Y coordinate
	/// @return y cooridnate
	///
	int cWidget::GetY()
	{
		return m_Y;
	}

	//
	// Tells the widget where the mouse clicked
	/// @param x a int
	/// @param y a int
	/// @param button a int
	///
	void cWidget::MouseClicked(int x, int y, int button)
	{
		if((x >= m_X) && (x <= (m_X + m_Width)))
		{
			if((y >= m_Y) && (y <= (m_Y + m_Height)))
			{
				Logic();
			}
		}
	}

		//
	// Mouse button released
	/// @param button
	///
	void cWidget::MouseReleased(int button)
	{
	}

	//
	// Mouse moved
	/// @param x a int
	/// @param y a int
	///
	void cWidget::MouseMoved(int x, int y)
	{
	}


	//
	// Returns if the widget is a container
	/// @return if the widget is a container
	///
	bool cWidget::isContainer()
	{
		return false;
	}

	//
	// Set Y coordinate
	/// @param Name a std::String
	///
	void cWidget::SetId(std::string Name)
	{
		m_Name = Name;
	}

	//
	// Get Y coordinate
	/// @return the widgets id
	///
	std::string cWidget::GetId()
	{
		return	m_Name;
	}

    //
	// Deletes the wdiget
	//
	void cWidget::Delete()
	{
		Singleton<cWidgetManager>::GetSingletonPtr()->UnRegisterWidget(this);
	}

	//
	// Has text input focus
	/// @return if the widget has focus for text input or not
	///
    bool cWidget::HasTextFocus()
    {
        return m_TextFocus;
    }

    //
    // make the widget have focus for text input
    /// @param hasFocus a bool
    ///
    void cWidget::TextFocus(bool hasFocus)
    {
        m_TextFocus = hasFocus;

        if( m_TextFocus == true )
        {
            Singleton<cWidgetManager>::GetSingletonPtr()->SetTextFocus(this);
        }
        else
        {
            Singleton<cWidgetManager>::GetSingletonPtr()->SetTextFocus(NULL);
        }
    }

    //
    // handle input from the keyboard
    /// @param key an eKey
    ///
    void cWidget::HandleTextInput(eKey key)
    {
    }



    //
    // Default Constructor
    //
    cWidgetManager::cWidgetManager()
    {
        m_TextFocusWidget = NULL;
    }

    //
    // Default Destructor
    //
    cWidgetManager::~cWidgetManager()
    {
        for(uint i = 0; i < m_Widgets.size(); i++)
        {
            UnRegisterWidget(m_Widgets[i]);
        }
    }

    //
    // Sets the text input focus to the widget
    /// @param widget a cWidget pointer
    void cWidgetManager::SetTextFocus(cWidget* widget)
    {
        if( m_TextFocusWidget != NULL)
        {
            m_TextFocusWidget->m_TextFocus = false;
        }
        if( widget != NULL)
        {
            widget->m_TextFocus = true;
        }

        m_TextFocusWidget = widget;
    }

    //
    // Gets a pointer to the widget that has focus
    /// @return a cWidget pointer to the widget in focus
    cWidget* cWidgetManager::GetTextFocus()
    {
       return m_TextFocusWidget;
    }

    //
    // Mouse Clicked
    /// @param x a int
    /// @param y a int
    /// @param button a int
    ///
    void cWidgetManager::MouseClicked(int x, int y, int button)
    {
        for(uint i = 0; i < m_Widgets.size(); i++)
        {
			if(!m_Widgets[i]->HasParent())
			{
				m_Widgets[i]->MouseClicked(x, y, button);
			}
        }
    }

	//
	// Mouse button released
	/// @param button
	///
	void cWidgetManager::MouseReleased(int button)
	{
		for(uint i = 0; i < m_Widgets.size(); i++)
        {
			if(!m_Widgets[i]->HasParent())
			{
				m_Widgets[i]->MouseReleased(button);
			}
        }
	}

	//
	// Mouse moved
	/// @param x a int
	/// @param y a int
	///
	void cWidgetManager::MouseMoved(int x, int y)
	{
		for(uint i = 0; i < m_Widgets.size(); i++)
        {
			if(!m_Widgets[i]->HasParent())
			{
				m_Widgets[i]->MouseMoved(x, y);
			}
        }
	}

	//
	// updates all widgets
	//
	void cWidgetManager::Update()
	{
		for(uint i = 0; i < m_Widgets.size(); i++)
		{
			if(!m_Widgets[i]->HasParent())
			{
				m_Widgets[i]->Draw();
			}
		}
	}

    //
    // Registers a widget for management
    /// @param Widget a cWidget pointer
    ///
    void cWidgetManager::RegisterWidget(cWidget* Widget)
    {
        m_Widgets.push_back(Widget);
    }

    //
    // Removes a widget from management
    /// @param Widget a cWidget pointer
    ///
    void cWidgetManager::UnRegisterWidget(cWidget* Widget)
    {
        int place = -1;

		//lets find where the texture is in the vector
		for( uint i = 0; i < m_Widgets.size(); i++)
		{
			if( m_Widgets[i] == Widget )
			{
				place = i;
			}
		}

		//if its not registed then do nothing
		if(place == -1)
		{
			return;
		}

		//if the place is at the end just remove the texture
		if( (place + 1) == (int)m_Widgets.size())
		{
			m_Widgets.erase( m_Widgets.begin() + place);
		}
		else // move the last place to the empty slot and remove the last one element
		{
			m_Widgets[place] = m_Widgets[ m_Widgets.size() - 1 ];
			m_Widgets.erase( m_Widgets.begin() + place);
		}

		delete Widget;
    }
}
