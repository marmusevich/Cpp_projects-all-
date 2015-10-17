/**
 *  File: cWidget.h
 *  Project: Kore-Engine
 *
 *  Description: This file contains the manager for everything gui related
 *
 *  Created by Sean Chapel on 2/15/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */ 


#include "cGuiManager.h"
#include "cWidget.h"
#include "GuiTypes.h"
#include "cContainer.h"

namespace Kore
{
	//
    // Default Constructor
    //
    cGuiManager::cGuiManager()
    {
        m_TextFocusWidget = NULL;
    }

    //
    // Default Destructor
    //
    cGuiManager::~cGuiManager()
    {
		/*
		//delete all widgets
		for( std::list< cWidget* >::iterator itr = m_Widgets.begin(); itr != m_Widgets.end(); itr++)
		{
			delete (*itr);
		}

		m_Containers.clear();
		m_KeyListeners.clear();
		m_MouseListeners.clear();
		m_Widgets.clear();
		*/
    }

	//
	// updates all widgets
	//
	void cGuiManager::Update()
	{
		for( std::list< cContainer* >::iterator itr = m_Containers.begin(); itr != m_Containers.end(); itr++)
		{
			//only draw top level containers
			if(!(*itr)->HasParent())
			{
				(*itr)->Draw();
			}
		}
	}

	//
	// Handles mouse input
	/// @param event a eMouseEvent
	/// @param x a int
	/// @param y a int
	/// @param button a iny
	///
	bool cGuiManager::HandleMouseEvent(eMouseEvent event, int x, int y, int button)
	{
		bool handled = false;

		for( std::list< cWidget* >::iterator itr = m_MouseListeners.begin(); itr != m_MouseListeners.end(); itr++ )
		{
			switch( event )
			{
				case MOUSEDOWN:
					handled = (*itr)->m_MouseListener->MouseClicked(x, y, button);
					break;
				case MOUSEUP:
					handled = (*itr)->m_MouseListener->MouseReleased(x, y, button);
					break;
				case MOUSEMOVE:
					handled = (*itr)->m_MouseListener->MouseMoved(x, y);
					break;
			}
		}

		return handled;
	}

	//
	// Handles Keyboard input
	/// @param event a eKeyEvent
	/// @param key a eKey 
	bool cGuiManager::HandleKeyEvent(eKeyEvent event, eKey key)
	{
		bool handled = false;

		for( std::list< cWidget* >::iterator itr = m_KeyListeners.begin(); itr != m_KeyListeners.end(); itr++)
		{
			switch( event )
			{
				case KEYDOWN:
					handled = (*itr)->m_KeyListener->KeyPressed(key);
					break;
				case KEYUP:
					handled = (*itr)->m_KeyListener->KeyReleased(key);
					break;
			}
		}

		return handled;
	}

    //
    // Registers a widget for management
    /// @param Widget a cWidget pointer
    ///
    void cGuiManager::RegisterWidget(cWidget* Widget)
    {
        m_Widgets.push_back(Widget);
    }

	//
    // Registers a container for management
    /// @param container a cContainer pointer
    ///
    void cGuiManager::RegisterContainer(cContainer* container)
    {
			m_Containers.push_back(container);
    }

	//
    // UnRegisters a container from management
    /// @param container a cContainer pointer
    ///
    void cGuiManager::UnRegisterContainer(cContainer* container)
    {
		for( std::list< cContainer* >::iterator itr = m_Containers.begin(); itr != m_Containers.end(); itr++)
		{
			if((*itr) == container)
			{
				m_Containers.erase(itr);
				break;
			}
		}
    }


    //
    // Removes a widget from management
    /// @param Widget a cWidget pointer
    ///
    void cGuiManager::UnRegisterWidget(cWidget* Widget)
    {
		/*
		bool foundWidget = false;

		for( std::list< cWidget* >::iterator itr = m_Widgets.begin(); itr != m_Widgets.end(); itr++)
		{
			if( (*itr) == Widget )
			{
				foundWidget = true;
				m_Widgets.erase(itr);

				if(Widget->IsContainer())
				{
					for( std::list< cWidget* >::iterator conItr = m_Containers.begin(); conItr != m_Containers.end(); conItr++)
					{
						m_Containers.erase(conItr);
					}
				}

				if(Widget->HasKeyListener())
				{
					for( std::list< cWidget* >::iterator keyItr = m_KeyListeners.begin(); keyItr != m_KeyListeners.end(); keyItr++)
					{
						m_KeyListeners.erase(keyItr);
					}
				}

				if(Widget->HasMouseListener())
				{
					for( std::list< cWidget* >::iterator mosItr = m_MouseListeners.begin(); mosItr != m_MouseListeners.end(); mosItr++)
					{
						m_MouseListeners.erase(mosItr);
					}
				}

				break;
			}
		}

		if(foundWidget)
		{
			delete Widget;
		}

		*/
    }
};