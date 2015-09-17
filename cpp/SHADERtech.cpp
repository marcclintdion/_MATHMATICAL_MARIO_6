

void Dot3shader( void )
{
   

}

int LoadGLTextureBMP(char *textureFileName, char *normalMapFileName, GLuint &textureMapID, GLuint &normalMapID)                                 
{
    AUX_RGBImageRec *pTextureImage = auxDIBImageLoad(textureFileName);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glGenTextures( 1, &textureMapID);

		glBindTexture( GL_TEXTURE_2D,  textureMapID );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST );
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
		
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pTextureImage->sizeX, pTextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage->data);
        
        if( pTextureImage ) 
        {      // Release all data, since OpenGL holds its own copy of the textures
	           if( pTextureImage->data )
		       free( pTextureImage->data );
		       free( pTextureImage );
        }
     /////////////////////////////////_______________________LOAD___BMP__TEXTURE_MAPS_______________________LOAD___BMP__TEXTURE_MAPS	
	AUX_RGBImageRec *pTextureImage2 = auxDIBImageLoad(normalMapFileName);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glGenTextures( 1, &normalMapID );
        glBindTexture( GL_TEXTURE_2D, normalMapID);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );		

		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST );

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pTextureImage2->sizeX, pTextureImage2->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage2->data);

        if( pTextureImage2 ) 
        {    // Release all data, since OpenGL holds its own copy of the textures
	         if( pTextureImage2->data )
		     free( pTextureImage2->data );
		     free( pTextureImage2 );
        }
}

int LoadGLTextureBMP_single(char *textureFileName, GLuint &textureMapID) 
{    
   	AUX_RGBImageRec *pTextureImage = auxDIBImageLoad(textureFileName);

	   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);glGenTextures( 1, &textureMapID);

		glBindTexture( GL_TEXTURE_2D,  textureMapID );

		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
		
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pTextureImage->sizeX, pTextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage->data);
		
		if( pTextureImage ) 
        {       // Release all data, since OpenGL holds its own copy of the textures
	            if( pTextureImage->data )
	            free( pTextureImage->data );
	            free( pTextureImage );
        }
}

int LoadGLTextureTGA(char *textureFileName, GLuint &textureMapID)                                 
 {
    
    tgaImageFile tgaImage;
    tgaImage.load( textureFileName );
 
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures( 1, &textureMapID );
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, textureMapID );
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    gluBuild2DMipmaps(GL_TEXTURE_2D, tgaImage.m_texFormat, tgaImage.m_nImageWidth, tgaImage.m_nImageHeight, tgaImage.m_texFormat,  GL_UNSIGNED_BYTE, tgaImage.m_nImageData);

//-----------------------------------------------------------------------------
//           Name: ogl_alpha_blending_texture.cpp
//         Author: Kevin Harris
//  Last Modified: 03/25/05
return 0;
}
int LoadGLTextureTGA(char *textureFileName, char *normalMapFileName, GLuint &textureMapID, GLuint &normalMapID) 
{
      tgaImageFile tgaImage;
      tgaImage.load( textureFileName );
      
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);     
      glGenTextures( 1, &textureMapID );
      glEnable( GL_TEXTURE_2D );
      glBindTexture( GL_TEXTURE_2D, textureMapID );
      glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	  glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST );
	  glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
      gluBuild2DMipmaps(GL_TEXTURE_2D, tgaImage.m_texFormat, tgaImage.m_nImageWidth, 
                                       tgaImage.m_nImageHeight, tgaImage.m_texFormat, 
                                       GL_UNSIGNED_BYTE, tgaImage.m_nImageData);

      tgaImageFile tgaImage2;
      tgaImage2.load( textureFileName );
      
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);   
      glGenTextures( 1, &normalMapID );
      glEnable( GL_TEXTURE_2D );
      glBindTexture( GL_TEXTURE_2D, normalMapID );
      glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	  glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST );
	  glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
      gluBuild2DMipmaps(GL_TEXTURE_2D, tgaImage2.m_texFormat, tgaImage2.m_nImageWidth, 
                                      tgaImage2.m_nImageHeight, tgaImage2.m_texFormat, 
                                      GL_UNSIGNED_BYTE, tgaImage2.m_nImageData);    

  return 0;
}



void PerformFrameStartSetup(void)
{   
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
      
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glAlphaFunc(GL_GREATER,0.1f);
                             
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glAlphaFunc(GL_GREATER,0.1f);
}
