/**
 *  File: cTextureManager.h
 *  Project: Kore-Engine
 *
 *  Description: This file contains all the texture functions
 *
 *  Created by Sean Chapel on 1/21/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#ifndef TEXTURE
#define TEXTURE

#include "globals.h"
#include "GraphicTypes.h"


namespace Kore
{
	///
	/// The texture class
	///
	class cTexture
	{
		friend class cTextureManager;
	
		public:
			/// Default Constructor
			cTexture();
			/// Constructor that loads a texture
			cTexture(std::string filename);
			/// Default Destructor
			~cTexture();
	
			/// Returns the texture width
			GLfloat GetWidth();
			/// Returns the texture height
			GLfloat GetHeight();
	
			/// Loads a texture
			void Load(std::string filename, bool LoadCollision = true);
	
			/// Loads file from a zip file
			void LoadFromZip(std::string filename);
	
			/// Deletes the texture
			void Delete();
			/// Reloads the texture
			void Reload();

			/// Returns the pixel data
			std::vector< std::vector< bool > >* GetPixels();
	
			/// Draws the whole texture
			void Draw(GLfloat X, GLfloat Y, GLfloat Scale = 1, GLfloat Rotatation = 0, GLfloat red = 1, GLfloat green = 1, GLfloat blue = 1, GLfloat alpha = 1);
	
			/// Draws a section of the texture
			void DrawSection(GLfloat X, GLfloat Y, sRect* Box, GLfloat Scale = 1, GLfloat Rotation = 0, GLfloat red = 1, GLfloat green = 1, GLfloat blue = 1, GLfloat alpha = 1);
		
		protected:
			/// Internal function to setup drawing
			void InitializeDraw(GLfloat Scale, GLfloat Rotation, GLfloat X, GLfloat Y, sRect* rect);
	
			/// Internal function for loading a texture from a surface
			void MakeTexture(SDL_Surface* Surface, bool LoadCollision = true);
	
			GLuint m_Texture;								/**< Holds the texture data										  */
			std::vector< std::vector< bool > > m_PixelOn;	/**< Holds the pixel data, if a pixel is not transparent it is on */
			std::string m_Filename;							/**< Holds the filename of the texture	                          */
			GLfloat m_Width;								/**< Stores the width of the texture	                          */
			GLfloat m_Height;								/**< Stores the height of the texture							  */
	};
	
	///
	/// This class manages all textures
	///
	class cTextureManager
	{
		friend class cTexture;
	
		public:
			/// Default Constructor
			cTextureManager();
			/// Default Destructor
			~cTextureManager();
	
			/// Reloads all textures
			void ReloadTextures();
			/// Deletes all textures
			void DeleteTextures();
	
		protected:
			/// Registers a texture for management
			void RegisterTexture(cTexture* Texture);
			/// Removes a texture from management
			void UnRegisterTexture(cTexture* Texture);
	
			std::vector< cTexture* > m_Textures;	/**< Holds all textures that are managed	*/
	};
}

#endif
