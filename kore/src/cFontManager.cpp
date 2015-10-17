/**
 *  File: cFontManager.cpp
 *  Project: Kore-Engine
 *
 *  Description: This file contains everything font related
 *
 *  Created by Sean Chapel on 1/21/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#include "cFontManager.h"
#include "SDL_rwops_zzip.h"
#include "cFontManager.h"
#include "cGraphics.h"
#include "cCamera.h"
#include "Singleton.h"

using namespace std;

namespace Kore
{
	//
	// Default constructor
	/// @params Filename a std::string
	cFont::cFont(std::string Filename)
	{
		m_Static = true;

		if(Filename != "")
		{
			Load(Filename);
		}
		else
		{
			m_Font = NULL;
		}
	}

	//
	// Default destructor
	//
	cFont::~cFont()
	{
		delete m_Font;
		//Delete();
	}

	//
	// Loads a font from a zip
	/// @param Filename a std::string
	///
	bool cFont::LoadFromZip(std::string Filename)
	{
		std::string mode = "rb";

		//zziplib specific code
		ZZIP_FILE* fp = zzip_fopen(Filename.c_str(),0);

		//holds the file data
		char buf[17];

		//length of the file
		int len = 0;

		//stores the files data
		unsigned char data[200000];

		if (!fp)
		{
			cout << "Error loading font from zip '" << Filename << "' " << endl;
			return false;
		}
		else
		{
			int n;

			// read chunks of 16 bytes into buf
			while (0 < (n = zzip_read(fp, buf, 16)))
			{
				if( len + n > 200000 )
				{
					cout << "Font file is bigger than the buffer, change the size in cFontManager.cpp" << endl;
					return false;
				}

				for(int i = 0; i < n; i++)
				{
					data[len + i] = (unsigned char) buf[i];
				}

				len += n;
			}
		}

		zzip_file_close (fp);

		m_Font = new FTGLPixmapFont( data, len );

		if( m_Font->Error() )
		{
			cout << "Error loading font from zip '" << Filename << "' " << m_Font->Error() <<  " " << len << endl;
			delete m_Font;
			m_Font = NULL;

			return false;
		}
		else
		{
			//set a default size
			m_Font->FaceSize(20);
			Singleton<cFontManager>::GetSingletonPtr()->RegisterFont(this);
		}

		return true;
	}


	//
	// Loads a font from a file
	/// @param Filename a std::string
	///
	bool cFont::Load(std::string Filename)
	{
		m_Font = new FTGLPixmapFont( Filename.c_str() );

		if( m_Font->Error() )
		{
			cout << "Error loading Font '" << Filename << "'" << endl;
			delete m_Font;
			m_Font = NULL;
		}
		else
		{
			//set a default size
			m_Font->FaceSize(20);
			Singleton<cFontManager>::GetSingletonPtr()->RegisterFont(this);
		}

		return true;
	}

	//
	// Unregisters the font and deletes it from memory
	//
	void cFont::Delete()
	{
		Singleton<cFontManager>::GetSingletonPtr()->UnRegisterFont(this);
	}

	//
	// Draws text on the screen given the parameters
	/// @param Text a std::string
	/// @param X a GLfloat
	/// @param Y a GLfloat
	/// @param Red a GLfloat
	/// @param Green a GLfloat
	/// @param Blue a GLfloat
	/// @param Alpha a GLfloat
	///
	void cFont::Draw(std::string Text, GLfloat X, GLfloat Y, GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha)
	{
		//do nothing if the font isn't setup
		if( m_Font == NULL)
		{
			return;
		}

		glLoadIdentity();

		//move with the camera if needed
		if( ! m_Static )
		{
			X = Singleton<cCamera>::GetSingletonPtr()->GetXposition() + X;
			Y = Singleton<cCamera>::GetSingletonPtr()->GetYposition() + Y;
		}

		std::string tempStr;

		//fix bug in ftgl when part of the text is offscreen nothing draws
		while( (X < 0) && (Text.length() != 0))
		{
			tempStr = Text[0];
			X += GetWidth(tempStr);
			Text = Text.substr(1,Text.length());
		}

		glColor4f(Red, Green, Blue, Alpha);
		glRasterPos2i( (int)X, (int)Y);

		glPushMatrix();

		m_Font->Render(Text.c_str());

		glPopMatrix();
	}

	//
	// Sets the font's face size
	/// @param Size a uint
	///
	void cFont::SetSize(uint Size)
	{
		if(m_Font == NULL)
		{
			return;
		}

		m_Font->FaceSize(Size);

		m_FaceSize = Size;
	}

	//
	// Sets if the text moves with the camera or not, default is true
	/// @param Static a bool
	///
	void cFont::SetStatic(bool Static)
	{
		m_Static = Static;
	}

	//
	// returns the height of the font
	/// @return Width of the string
	///
    GLfloat cFont::GetHeight()
    {
        return (GLfloat) m_Font->LineHeight();
    }

    //
    // returns the width of the string
    /// @param text a std::string
    /// @return width of the string
    ///
    GLfloat cFont::GetWidth(std::string text)
    {
        return (GLfloat) m_Font->Advance(text.c_str());
    }




	///////////////////////////////////////////////
	// Start Font Manager Code
	///////////////////////////////////////////////


	//
	// Default constructor
	//
	cFontManager::cFontManager()
	{
		m_Fonts.clear();
	}

	//
	// Default destructor
	//
	cFontManager::~cFontManager()
	{
		DeleteFonts();
		m_Fonts.clear();
	}

	//
	// Deletes all fonts form memory
	//
	void cFontManager::DeleteFonts()
	{
		for(uint i = 0; i < m_Fonts.size(); i++)
		{
			delete m_Fonts[i];
		}
	}

	//
	// Adds a font to the manager
	//
	void cFontManager::RegisterFont(cFont* Font)
	{
		//don't add nulls
		if( Font == NULL)
		{
			return;
		}

		//check to see if its already loaded in the manager
		for(uint i = 0; i < m_Fonts.size(); i++)
		{
			if( Font->m_Font == m_Fonts[i]->m_Font )
			{
				return;
			}
		}

		//add the font to management
		m_Fonts.push_back(Font);
	}

	//
	// Removes a font from the manager and deletes it from memory
	//
	void cFontManager::UnRegisterFont(cFont* Font)
	{
		//don't add nulls
		if( Font == NULL)
		{
			return;
		}

		int place = -1;

		//check to see if its loaded in the manager
		for(uint i = 0; i < m_Fonts.size(); i++)
		{
			if( Font->m_Font == m_Fonts[i]->m_Font )
			{
				place = (int)i;
				break;
			}
		}

		//abort if not found
		if( place == -1 )
		{
			return;
		}

		//if the place is at the end of the vector just delete it
		if( (place + 1) == (int)m_Fonts.size() )
		{
			delete m_Fonts[place];
			m_Fonts.erase(m_Fonts.begin() + place);
		}
		else // we need to have the font swap places with the last element
		{
			delete m_Fonts[place];
			m_Fonts[place] = m_Fonts[ m_Fonts.size() ];
			m_Fonts.erase(m_Fonts.end());
		}
	}
}
