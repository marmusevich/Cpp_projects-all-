
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

#include "globals.h"
#include "keys.h"
//#include "cContainer.h"

#ifndef WIDGET
#define WIDGET

namespace Kore
{
	//added so cCotainer won't recursivley bomb
	class cContainer;

     class cWidget
     {
        friend class cWidgetManager;

		public:
				/// default constructor
				cWidget();

				/// virtual destructor
				virtual ~cWidget();

				/// virtual draw function
				virtual void Draw() = 0;

				/// virtual logic when clicked function
				virtual void Logic() = 0;

				/// Set width
				virtual void SetWidth(int width);

				/// Get Width
				virtual int GetWidth();

				/// Set Height
				virtual void SetHeight(int height);

				/// Get Height
				virtual int GetHeight();

				/// Set X coordinate
				virtual void SetX(int x);

				/// Get X coordinate
				virtual int GetX();

				/// Set Y coordinate
				virtual void SetY(int y);

				/// Get Y coordinate
				virtual int GetY();

				/// Tells the widget where the mouse clicked
				virtual void MouseClicked(int x, int y, int button);

				/// Mouse button released
				virtual void MouseReleased(int button);

				/// Mouse moved
				virtual void MouseMoved(int x, int y);

				/// Set the Id
				virtual void SetId(std::string Name);

				/// Get the Id
				virtual std::string GetId();

                /// Deletes the widget
                virtual void Delete();

                /// Has text input focus
                virtual bool HasTextFocus();

                /// make the widget have focus for text input
                virtual void TextFocus(bool hasFocus);

                /// handle input from the keyboard
                virtual void cWidget::HandleTextInput(eKey key);

				/// Returns if the widget is a container
				virtual bool isContainer();

				/// Sets the parent to the widget
				void SetParent(cWidget* container);

				/// Tells if the widget has a parent or not
				bool cWidget::HasParent();

		protected:
				std::string m_Name;		/**<	ID or name of the widget	                */
				int m_X;				/**<	X coordinate				                */
				int m_Y;				/**<	Y coordinate				                */
				int m_Width;			/**<	Width of the widget			                */
                int m_Height;			/**<	Height of the widget		                */
				bool m_TextFocus;		/**<    If the widget has text input focus or not   */

				bool m_HasParent;		/**< If the widget has a parent or not				*/
				cWidget*	m_Parent;	/**< The widgets parent								*/
     };

    ///
	/// This class manages all widgets
	///
	class cWidgetManager
	{
		friend class cWidget;

		public:
			/// Default Constructor
			cWidgetManager();
			/// Default Destructor
			~cWidgetManager();

			/// updates all widgets
			void Update();

			/// Mouse button clicked
			void MouseClicked(int x, int y, int button);

			/// Mouse button released
			void MouseReleased(int button);

			/// Mouse moved
			void MouseMoved(int x, int y);

            /// Gets a pointer to the widget that has focus
            cWidget* GetTextFocus();

		protected:
            /// Sets the text input focus to the widget
            void SetTextFocus(cWidget* widget);

			/// Registers a widget for management
			void RegisterWidget(cWidget* Widget);
			/// Removes a widget from management
			void UnRegisterWidget(cWidget* Widget);

			std::vector< cWidget* > m_Widgets;	/**< Holds all widgets that are managed	        */
			cWidget* m_TextFocusWidget;         /**< Holds the widget that has text input focus */
	};
}

#endif
