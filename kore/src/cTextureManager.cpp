/**
 *  File: cTextureManager.cpp
 *  Project: Kore-Engine
 *
 *  Description: This file contains all the texture functions
 *
 *  Created by Sean Chapel on 1/21/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#include "cTextureManager.h"
#include "cGraphics.h"
#include "cCamera.h"
#include "GraphicTypes.h"
#include "SDL_rwops_zzip.h"
#include "Singleton.h"

using namespace std;

namespace Kore
{
	//
	// Default contructor
	//
	cTexture::cTexture()
	{
		m_Width = 0;
		m_Height = 0;
		m_Texture = 0;
		m_Filename = "";
	}

	//
	// Constructor that loads a file
	/// @param Filename a std::string
	cTexture::cTexture(std::string Filename)
	{
		Load(Filename);
	}

	//
	// Default destructor
	//
	cTexture::~cTexture()
	{
		Delete();
	}

	//
	// Returns the width of the texture
	/// @return The width of the texture
	///
	GLfloat cTexture::GetWidth()
	{
		return m_Width;
	}

	//
	// Returns the height of the texture
	/// @return the height of the texture
	///
	GLfloat cTexture::GetHeight()
	{
		return m_Height;
	}


	//
	// Loads file from a zip file
	/// @param filename s std::string
	/// Note: format is packname/filename,
	///	 a packfile can not have directories within it
	void cTexture::LoadFromZip(std::string filename)
	{
		string mode = "rb";

		SDL_RWops* ImageData = SDL_RWFromZZIP(filename.c_str(), mode.c_str());

		if(ImageData == NULL)
		{
			cout << "Failed to load the image from zip: " << filename << endl;
			return;
		}

		SDL_Surface* Surface = IMG_Load_RW(ImageData, 0);
		SDL_FreeRW(ImageData);

		m_Filename = filename;
		MakeTexture(Surface);
	}

	//
	// Loads the texture to memory
	/// @param filename a std::string
	///
	void cTexture::Load(std::string filename, bool LoadCollision)
	{
		//load the image from a file via sdl_img
		SDL_Surface* Surface = IMG_Load(filename.c_str());

		if(Surface == NULL)
		{
			cout << "Failed to load the image: " << filename << ", Error: " << SDL_GetError() << endl;
			return;
		}

		m_Filename = filename;
		MakeTexture(Surface, LoadCollision);
	}

	//
	// Internal function for loading a texture from a surface
	/// @param Surface a SDL_Surface pointer
	///
	void cTexture::MakeTexture(SDL_Surface* Surface, bool LoadCollision)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT,4);

		glGenTextures(1,&m_Texture);
		glBindTexture(GL_TEXTURE_2D,m_Texture);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		SDL_PixelFormat *fmt = Surface->format;

		//setup all the information
		m_Width = (GLfloat)Surface->w;
		m_Height = (GLfloat)Surface->h;

		//setup the pixel data (used for collisions)
		if( LoadCollision )
		{
			SDL_LockSurface(Surface);
			Uint32* sur_pixels = (Uint32*) Surface->pixels;
			Uint32 pixel;
			SDL_UnlockSurface(Surface);

			SDL_PixelFormat* format = Surface->format;
			Uint32 temp;
			Uint8 alpha;

			std::vector< bool > pixTemp;

			for(int x = 0; x < (int)m_Width; x++)
			{
				pixTemp.push_back(false);
			}

			for(int y = 0; y < (int)m_Height; y++)
			{
				m_PixelOn.push_back(pixTemp);
			}
			
			pixel = *(sur_pixels++);

			for(int y = 0; y < (int)m_Height; y++)
			{
				for(int x = 0; x < (int)m_Width; x++)
				{
					temp = pixel & format->Amask;
					temp = temp >> fmt->Ashift;
					temp = temp << fmt->Aloss;
					alpha = (Uint8) temp;

					if(alpha >= 200)
					{
						m_PixelOn[y][x] = true;
					}

					pixel = *(sur_pixels++);
				}
			}

			//flip rows so it's represented right in memory
			vector<vector<bool>> colTmp;
			for(int y = m_Height - 1; y >= 0; y--)
			{
				colTmp.push_back(m_PixelOn[y]);
			}

			m_PixelOn.clear();
			m_PixelOn = colTmp;
		}


		//if there is alpha
		if (fmt->Amask)
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,m_Width,m_Height,GL_RGBA,GL_UNSIGNED_BYTE,Surface->pixels);
		}
		else // no alpha
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,m_Width,m_Height,GL_RGB,GL_UNSIGNED_BYTE,Surface->pixels);
		}

		//free the image
		SDL_FreeSurface(Surface);

		Singleton<cTextureManager>::GetSingletonPtr()->RegisterTexture(this);
	}

	//
	// Deletes the texture
	//
	void cTexture::Delete()
	{
// this line has a BUG fix it!
		Singleton<cTextureManager>::GetSingletonPtr()->UnRegisterTexture(this);
	}

	//
	// Reloads the texture
	//
	void cTexture::Reload()
	{
		//only reload if it's a real file
		if(m_Filename != "")
		{
			LoadFromZip(m_Filename);
		}
	}

	//
	// Moves the camera, binds the texture if nessiary and does scaling/rotation
	/// @param Scale a GLfloat
	/// @param Rotation a GLfloat
	/// @param X a GLfloat
	/// @param Y a GLfloat
	///
	void cTexture::InitializeDraw(GLfloat Scale, GLfloat Rotation, GLfloat X, GLfloat Y, sRect* rect)
	{
		cGraphics* graphics = Singleton<cGraphics>::GetSingletonPtr();

		//check if the right texture is bound
		if( graphics->GetCurrentTexture() != m_Texture)
		{
			//bind texture
			glBindTexture(GL_TEXTURE_2D, m_Texture);

			//set graphics varible
			graphics->SetCurrentTexture(m_Texture);
		}

		//scale the points if needed
		glLoadIdentity();
		if(Rotation != 0)
		{/*
			GLfloat x, y;
			x = ((rect->Right - rect->Left)/2)   * m_Width;
			y = ((rect->Top   - rect->Bottom)/2) * m_Height;

			glTranslatef(-x ,-y, 0.0f);
			glRotatef(Rotation,0.0f,0.0f,1.0f);
			//glTranslatef(x, y, 0.0f);*/
		}
		glTranslatef(Singleton<cCamera>::GetSingletonPtr()->GetXposition() + X, Singleton<cCamera>::GetSingletonPtr()->GetYposition() + Y, 0.0f);
		if(Rotation != 0)
		{
			GLfloat x, y;
			x = ((rect->Right - rect->Left)/2)   * m_Width;
			y = ((rect->Top   - rect->Bottom)/2) * m_Height;

			glTranslatef(x ,y, 0.0f);
			glRotatef(Rotation,0.0f,0.0f,1.0f);
			glTranslatef(-x ,-y, 0.0f);
		}
		glScaled(Scale, Scale, 0);
	}

	//
	/// Returns the pixel data
	/// @return 
	///
	std::vector< std::vector< bool > >* cTexture::GetPixels()
	{
		return &m_PixelOn;
	}

	//
	// Draws the whole texture
	/// @param X a GLfloat
	/// @param Y a GLfloat
	/// @param Scale a GLfloat
	/// @param Rotation a GLfloat
	/// @param red a GLfloat
	/// @param green a GLfloat
	/// @param blue a GLfloat
	/// @param alpha a GLfloat
	///
	void cTexture::Draw(GLfloat X, GLfloat Y, GLfloat Scale, GLfloat Rotation, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
	{
		glPushMatrix();
		sRect rect;
		rect.Bottom = 0.0f;
		rect.Top = 1.0f;
		rect.Right = 1.0f;
		rect.Left = 0.0f;

		InitializeDraw(Scale, Rotation, X, Y, &rect);

		//draw the quad
		glBegin(GL_QUADS);
			//bottom-left vertex (corner)
			glColor4f(red, green, blue, alpha);
			glTexCoord2f(0 , 0);
			glVertex2f(0, m_Height);

			//bottom-right vertex (corner)
			glTexCoord2f(1, 0);
			glVertex2f(m_Width, m_Height);

			//top-right vertex (corner)
			glTexCoord2f(1, 1);
			glVertex2f(m_Width, 0);

			//top-left vertex (corner)
			glTexCoord2f(0, 1);
			glVertex2f(0, 0);

		glEnd();

		//reset the color
		glColor3f(1.0f, 1.0f, 1.0f);

		glPopMatrix();
	}

	//
	// Draws a section of a texture
	/// @param X a GLfloat
	/// @param Y a GLfloat
	/// @param Box a sRect pointer
	/// @param Scale a GLfloat
	/// @param Rotation a GLfloat
	/// @param red a GLfloat
	/// @param green a GLfloat
	/// @param blue a GLfloat
	/// @param alpha a GLfloat
	///
	void cTexture::DrawSection(GLfloat X, GLfloat Y, sRect* Box, GLfloat Scale, GLfloat Rotation, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
	{
		glPushMatrix();

		InitializeDraw(Scale, Rotation, X, Y, Box);

		//width for drawing
		GLfloat box_width = m_Width * (Box->Right - Box->Left);
		GLfloat box_height = m_Height * (Box->Top - Box->Bottom);

		GLfloat box_top = 1.0f - Box->Top;
		GLfloat box_bottom  = 1.0f - Box->Bottom;

		//draw the quad
		glBegin(GL_QUADS);
			//bottom-left vertex (corner)
			glColor4f(red, green, blue, alpha);
			glTexCoord2f(Box->Left , box_bottom);
			glVertex2f(0, 0);

			//bottom-right vertex (corner)
			glTexCoord2f(Box->Right , box_bottom);
			glVertex2f(box_width, 0);

			//top-right vertex (corner)
			glTexCoord2f(Box->Right , box_top);
			glVertex2f(box_width, box_height);

			//top-left vertex (corner)
			glTexCoord2f(Box->Left, box_top);
			glVertex2f(0, box_height);

		glEnd();

		//reset the color
		glColor3f(1.0f, 1.0f, 1.0f);

		glPopMatrix();
	}

	//////////////////////////////////////////////////////////////
	//	start texture manager code
	//////////////////////////////////////////////////////////////

	//
	// Default Constructor
	//
	cTextureManager::cTextureManager()
	{
		m_Textures.clear();
	}

	//
	// Default Destructor
	//
	cTextureManager::~cTextureManager()
	{
		DeleteTextures();
	}

	//
	// Reloads all textures
	//
	void cTextureManager::ReloadTextures()
	{
		//reload all textures
		for( uint i = 0; i < m_Textures.size(); i++)
		{
			m_Textures[i]->Reload();
		}
	}

	//
	// Deletes all textures
	//
	void cTextureManager::DeleteTextures()
	{
		//delete all textures
		for( uint i = 0; i < m_Textures.size(); i++)
		{
			m_Textures[i]->Delete();
		}
	}

	//
	// Registers a texture for management
	//
	void cTextureManager::RegisterTexture(cTexture* Texture)
	{
		//check to see if the texture isn't actually just been reloaded
		for( uint i = 0; i < m_Textures.size(); i++)
		{
			if( m_Textures[i]->m_Texture == Texture->m_Texture )
			{
				return;
			}
		}

		//add the texture to the vector
		m_Textures.push_back(Texture);
	}

	//
	// Removes a texture from the texture manager
	//
	void cTextureManager::UnRegisterTexture(cTexture* Texture)
	{
		int place = -1;

		//lets find where the texture is in the vector
		for( uint i = 0; i < m_Textures.size(); i++)
		{
			if( m_Textures[i]->m_Texture == Texture->m_Texture )
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
		if( (place + 1) == (int)m_Textures.size())
		{
			m_Textures.erase( m_Textures.begin() + place);
		}
		else // move the last place to the empty slot and remove the last one element
		{
			m_Textures[place] = m_Textures[ m_Textures.size() - 1 ];
			m_Textures.erase( m_Textures.begin() + place);
		}

		delete Texture;
	}
}
