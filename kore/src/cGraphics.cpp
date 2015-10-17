/**
 *  File: cGraphics.cpp
 *  Project: Kore-Engine
 *
 *  Description: This file contains handles all the graphic subsytems and
 *		basic window management.
 *
 *  Created by Sean Chapel on 1/21/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#include "cGraphics.h"
#include "Singleton.h"
#include "cTextureManager.h"
#include "globals.h"
#include "cCamera.h"
#include "Singleton.h"

using namespace std;

namespace Kore
{
	//
	// Default constructor
	//
	cGraphics::cGraphics()
	{
		glScissor(0, 0, m_Width, m_Height);
		m_Loaded = false;
	}

	//
	// Default destructor
	//
	cGraphics::~cGraphics()
	{
		Shutdown();
	}

	//
	// Sets up a windows properties
	/// must be called before CreateWindow towork properly
	/// @param Width a int
	/// @param Height a int
	/// @param Bpp a int
	/// @param WindowTitle a std::string
	bool cGraphics::Initialize(int Width, int Height, int Bpp, std::string WindowTitle)
	{
		m_Width = Width;
		m_Height = Height;
		m_Bpp = Bpp;
		m_WindowTitle = WindowTitle;
		m_FullScreen = false;
		m_Surface = NULL;

		//if we reinitalize then reload the textures
		if(m_Loaded)
		{
			Singleton<cTextureManager>::GetSingletonPtr()->ReloadTextures();
		}

		m_Loaded = true;

		return 1;
	}

	//
	// Creates a window from drawing on
	/// Intialize must be called first and a window must be created
	/// before you can use any drawing functions
	/// @return Success or failure
	///
	bool cGraphics::MakeWindow()
	{
		//initalize SDL
		if ( SDL_Init(SDL_INIT_VIDEO) != 0 )
		{
			cout << "Unable to initialize SDL: " << SDL_GetError() << endl;
			exit(1);
		}

		m_SdlFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE | SDL_RESIZABLE;
		m_FullScreen = false;

		const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();

		if (videoInfo->hw_available)
		{
			m_SdlFlags |= SDL_HWSURFACE;
		}
		else
		{
			m_SdlFlags |= SDL_SWSURFACE;
		}

		// This checks if hardware blits can be done
		if ( videoInfo->blit_hw )
		{
			m_SdlFlags |= SDL_HWACCEL;
		}

		// Sets up OpenGL double buffering
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

		//kill sdl on exiting
		atexit(SDL_Quit);

		//create the surface
		m_Surface = SDL_SetVideoMode(m_Width, m_Height, m_Bpp, m_SdlFlags);

		if ( m_Surface == NULL)
		{
			cout << "Video mode set failed: " << SDL_GetError() << endl;
			SDL_Quit();
		}

		InitGl();

		//set the window title
		SDL_WM_SetCaption(m_WindowTitle.c_str(), NULL);

		return 1;
	}

	//
	// Resizes the window to the given size
	/// @param width a int
	/// @param height a int
	///
	void cGraphics::ResizeWindow(int width, int height)
	{
		// Protect against a divide by zero
		if ( height == 0 )
		{
			height = 1;
		}

		//resize sdl surface
		m_Surface = SDL_SetVideoMode( width, height, m_Bpp, m_SdlFlags );

		if (m_Surface == NULL)
		{
			cout << "Could not get a surface after resize: " << SDL_GetError() << endl;
			exit(1);
		}

        //reinitalize opengl
		InitGl();

		//reload textures
		Singleton<cTextureManager>::GetSingletonPtr()->ReloadTextures();
	}

	//
	// Returns the width of the drawing area
	/// @return Width of the drawing area
	///
	int cGraphics::GetWidth()
	{
		return m_Width;
	}

	//
	// Returns the height of the drawing area
	/// @return Height of the drawing area
	///
	int cGraphics::GetHeight()
	{
		return m_Height;
	}

	//
	// internal function to setup opengl's othomode
	//
	void cGraphics::InitGl()
	{
		glShadeModel( GL_SMOOTH );
		glClearColor( 0.5f, 0.5f, 0.5f, 0.0f );
		glClearDepth( 0.0f );
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable( GL_DEPTH_TEST );
		glDepthFunc( GL_ALWAYS );
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

		glDisable(GL_LIGHTING);

		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_SCISSOR_TEST);

		//setup ortho mode
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		glOrtho(0, (GLfloat)m_Width, 0, (GLfloat)m_Height, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
	}

	//
	// Turns fullscreen on or off
	//
	void cGraphics::ToggleFullScreen()
	{
		m_FullScreen = !m_FullScreen;


		if(m_Surface != NULL)
		{
			SDL_WM_ToggleFullScreen(m_Surface);

			if (!m_FullScreen)
			{
				SDL_ShowCursor(SDL_ENABLE);
			}
			else
			{
				SDL_ShowCursor(SDL_DISABLE);
			}
		}
	}

    //
	// Draws an empty Rectangle
	/// @param x a GLfloat
	/// @param y a GLfloat
	/// @param width a GLfloat
	/// @param height a GLfloat
	/// @param red a GLfloat
	/// @param green a GLfloat
	/// @param blue a GLfloat
	/// @param alpha a GLfloat
	///
    void cGraphics::DrawRectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
    {
		glPushMatrix();

		glLoadIdentity();
		glTranslatef(Singleton<cCamera>::GetSingletonPtr()->GetXposition() + x, Singleton<cCamera>::GetSingletonPtr()->GetYposition() + y, 0.0);
        
        glBegin(GL_LINE_LOOP);
			glColor4f(red, green, blue, alpha);
            glVertex2f(x,y);
			glVertex2f(x + width,y + height);
			glVertex2f(x,y + height);
            glVertex2f(x + width,y);
        glEnd();

		glPopMatrix();
    }

    //
    // Draws an filled rectangle
    /// @param x a GLfloat
	/// @param y a GLfloat
	/// @param width a GLfloat
	/// @param height a GLfloat
	/// @param red a GLfloat
	/// @param green a GLfloat
	/// @param blue a GLfloat
	/// @param alpha a GLfloat
	///
    void cGraphics::DrawFilledRectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
    {
        glColor4f(red, green, blue, alpha);

        glBegin(GL_QUADS);
            glVertex3f(x,y,0);
            glVertex3f(x + width,y,0);
            glVertex3f(x + width,y + height,0);
            glVertex3f(x,y + height,0);
        glEnd();
    }

    //
    // Draws a line
    /// @param x a GLfloat
	/// @param y a GLfloat
	/// @param width a GLfloat
	/// @param height a GLfloat
	/// @param red a GLfloat
	/// @param green a GLfloat
	/// @param blue a GLfloat
	/// @param alpha a GLfloat
	///
    void cGraphics::DrawLine(GLfloat x, GLfloat y, GLfloat x2, GLfloat y2, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
    {
        glColor4f(red, green, blue, alpha);

        glBegin(GL_LINES);
            glVertex3f(x, y, 0);
            glVertex3f(x2, y2, 0);
        glEnd();
    }

	//
	// Flips the screen from the backbuffer to the screen
	//
	void cGraphics::SwapBuffers()
	{
		SDL_GL_SwapBuffers();
	}

	//
	// clears the screen with a grey color
	//
	void cGraphics::ClearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	//
	// Kills all graphic subsystems
	//
	void cGraphics::Shutdown()
	{
	}

	//
	// returns the current texture in memory
	/// @return the current texture
	///
	GLuint cGraphics::GetCurrentTexture()
	{
		return m_CurrentTexture;
	}

	//
	// set the current texture in memory
	/// @param texture a Gluint
	///
	void cGraphics::SetCurrentTexture(GLuint texture)
	{
		m_CurrentTexture = texture;
	}

	//
	// Pushes a clipping area on the stack for drawing
	/// @param area a sRect
	///
	void cGraphics::PushClippingArea(sRect area)
	{
		sRect newArea;
		sRect currentArea;

		//get the current clipping area
		if(!m_ClippingArea.empty())
		{
			currentArea = m_ClippingArea.top();
		}
		else
		{
			sRect fullArea;
			fullArea.Bottom = (GLfloat) 0;
			fullArea.Top = (GLfloat)m_Height;
			fullArea.Left = (GLfloat)0;
			fullArea.Right = (GLfloat)m_Width;

			currentArea = fullArea;
		}

		//make the new clipping area
		//bottom
		if(currentArea.Bottom > area.Bottom)
		{
			newArea.Bottom = currentArea.Bottom;
		}
		else
		{
			newArea.Bottom = area.Bottom;
		}

		//top
		if(currentArea.Top < area.Top)
		{
			newArea.Top = currentArea.Top;
		}
		else
		{
			newArea.Top = area.Top;
		}

		//left
		if(currentArea.Left > area.Left)
		{
			newArea.Left = currentArea.Left;
		}
		else
		{
			newArea.Left = area.Left;
		}

		//right
		if(currentArea.Right < area.Right)
		{
			newArea.Right = currentArea.Right;
		}
		else
		{
			newArea.Right = area.Right;
		}


		m_ClippingArea.push(newArea);

		glScissor((GLsizei)newArea.Left, (GLsizei)newArea.Bottom, (GLint)(newArea.Right - newArea.Left), (GLint)(newArea.Top - newArea.Bottom));
	}

	/// Pops a clipping area off the stack
	void cGraphics::PopClippingArea()
	{
		sRect newArea;

		m_ClippingArea.pop();

		if(m_ClippingArea.empty())
		{
			sRect fullArea;
			fullArea.Bottom = (GLfloat)0;
			fullArea.Top = (GLfloat)m_Height;
			fullArea.Left = (GLfloat)0;
			fullArea.Right = (GLfloat)m_Width;

			newArea = fullArea;
		}
		else
		{
			newArea = m_ClippingArea.top();
		}

		glScissor((GLsizei)newArea.Left, (GLsizei)newArea.Bottom, (GLint)(newArea.Right - newArea.Left), (GLint)(newArea.Top - newArea.Bottom));
	}
}
