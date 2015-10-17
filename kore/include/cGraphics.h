/**
 *  File: cGraphics.h
 *  Project: Kore-Engine
 *
 *  Description: This file contains handles all the graphic subsystems and
 *		basic window management.
 *
 *  Created by Sean Chapel on 1/21/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#include "globals.h"
#include "GraphicTypes.h"

#ifndef GRAPHICS
#define GRAPHICS

namespace Kore
{
	///
	/// A class to contain all graphic subsystems
	///
	class cGraphics
	{
		friend class cTextureManager;

		public:
			/// Default Constructor
			cGraphics();
			/// Default Destructor
			~cGraphics();

			/// Intializes all a window for creation
			bool Initialize(int Width = 640, int Height = 480, int Bpp = 32, std::string WindowTitle = "");
			/// kills all graphic subsystems
			void Shutdown();

			/// Clears the screen with a grey color
			void ClearScreen();
			/// Flips backbuffer to the screen
			void SwapBuffers();

			/// Creates a window for drawing
			bool MakeWindow();

			/// Resizes the window
			void ResizeWindow(int width, int height);
			/// Toggles if the window is fullscreen or not
			void ToggleFullScreen();

			/// Returns the width of the drawing area
			int GetWidth();

			/// Returns the height of the drawing area
			int GetHeight();

            /// Draws an empty Rectangle
			void DrawRectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat red = 0, GLfloat green = 0, GLfloat blue = 0, GLfloat alpha = 1);

			/// Draws an filled rectangle
			void DrawFilledRectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat red = 0, GLfloat green = 0, GLfloat blue = 0, GLfloat alpha = 1);

			/// Draws a line
			void DrawLine(GLfloat x, GLfloat y, GLfloat x2, GLfloat y2, GLfloat red = 0, GLfloat green = 0, GLfloat blue = 0, GLfloat alpha = 1);

			/// returns the current texture in memory
			GLuint GetCurrentTexture();

			/// Set the current texture in memory
			void SetCurrentTexture(GLuint texture);

			/// Pushes a clipping area on the stack for drawing
			void PushClippingArea(sRect);

			/// Pops a clipping area off the stack
			void PopClippingArea();

		protected:
			/// intializes opengl for 2d drawing
			void InitGl();

			bool m_Loaded;			/**< Tells if the graphics core was successfully loaded	*/
			int m_Width;			/**< Stores the width of the drawing area		*/
			int m_Height;			/**< Stores the height of the drawing area		*/
			int m_Bpp;			/**< Stores the bits per pixel of the screen		*/
			std::string m_WindowTitle;	/**< Stores the title of the window			*/
			bool m_FullScreen;		/**< Tells if the window id fullscreen or not		*/

			SDL_Surface* m_Surface;		/**< Stores the drawing surface				*/
			Uint32 m_SdlFlags;		/**< Stores the drawing surface's capabilities		*/

			GLuint m_CurrentTexture; 	/**< contains the current texture that is in graphics memory	*/

			std::stack< sRect > m_ClippingArea;
	};
}

#endif
