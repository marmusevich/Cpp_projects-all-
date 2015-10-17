/**
 *  File: cFontManager.h
 *  Project: Kore-Engine
 *
 *  Description: This file contains everything font related
 *
 *  Created by Sean Chapel on 1/21/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#ifndef FONTMAN
#define FONTMAN

#include "globals.h"
#include "FTGLPixmapFont.h"


namespace Kore
{
	///
	/// Holds all the information about a font and its functions
	///
	class cFont
	{
		friend class cFontManager;

		public:
			/// Default Constructor
			cFont(std::string Filename = "");
			/// Default Destructor
			~cFont();

			/// Loads a font from a zip
			bool LoadFromZip(std::string Filename);
			/// Loads a font from file
			bool Load(std::string Filename);
			/// Deletes a font from memory
			void Delete();

			/// Draws a font
			void Draw(std::string Text, GLfloat X, GLfloat Y, GLfloat Red = 1, GLfloat Green = 1, GLfloat Blue = 1, GLfloat Alpha = 1);
			/// Sets the face size of the font
			void SetSize(uint Size);
			/// Sets if the font moves with the camera
			void SetStatic( bool Static);

			/// returns the height of the font
			GLfloat GetHeight();
			/// returns the width of the string
			GLfloat GetWidth(std::string text);

		private:
			FTFont* m_Font;	/**< Stores the font				*/
			bool m_Static;	/**< Tells if the font moves with the camera 	*/
			int m_FaceSize; /**< Stores the size of the font		*/
	};

	///
	/// This class manages all fonts
	///
	class cFontManager
	{
		friend class cFont;

		public:
			/// Default Constructor
			cFontManager();
			/// Default Destructor
			~cFontManager();

			/// Deletes all fonts from memory
			void DeleteFonts();

		private:
			/// Registers a font for management
			void RegisterFont(cFont* Font);
			/// Removes a font from management
			void UnRegisterFont(cFont* Font);

			std::vector< cFont* > m_Fonts;	/**< Pointers to all the managed fonts */
	};
}

#endif
