////////////________#pragma comment(lib, "Opengl32.lib")


#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <process.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <iostream.h>

//using namespace std;    ////_____used for string objects

#include <GL/gl.h>
#include <GL/glu.h>
#include "cpp/headerFiles/glaux.h"
#include <fstream.h>


#include "cpp/headerFiles/tga.h"

#include <math.h>


bool over = false;


//====================================================================================================================================

bool keys[256], keypressed[256];
bool active     = true;
bool fullscreen = true;

bool firstFrameSwitch = true;
float gameStart = 0.0f;

DWORD GLOBAL_TIME;

DWORD inTheBeginning = 0;
DWORD frameStart = 0;
DWORD frameEnd = 0;


int numberOfCollisionObjects = 50;

float left_edge [100];
float right_edge[100];
float lower_edge[100];
float upper_edge[100];

float X1, X2, Y1, Y2;

float   X3[100];
float   X4[100];
float   Y3[100];
float   Y4[100];

float   planeX3_inner[100];   ////left edge
float   planeX3_outer[100];   ////left edge
float   planeX4_inner[100];   ////right edge
float   planeX4_outer[100];   ////right edge
float   planeY3_inner[100];   ////bottom edge
float   planeY3_outer[100];   ////bottom edge
float   planeY4_inner[100];   ////top edge
float   planeY4_outer[100];   ////top edge

                             

void SetupCollision(void);
void CollisionCheck_LEFT(float X1, float Y1, float X2, float Y2);
void CollisionCheck_RIGHT(float X1, float Y1, float X2, float Y2);
void CollisionCheck_UP(float X1, float Y1, float X2, float Y2);
void CollisionCheck_DOWN(float X1, float Y1, float X2, float Y2);

int collisionObjectIdentifier = 0;

GLfloat MarioPositionX        = 0.0f;
GLfloat MarioPositionY        =-1.7f;
GLfloat MarioPositionZ        = 0.0f;
GLfloat THETA                 = 0.0f;
GLfloat gravity               = 0.00f;
bool    onGround              = true;
bool    MarioCanMoveRIGHT     = true;
bool    MarioIsStoppingRIGHT    = true;
float   MarioStopCountRIGHT     = 0.0f;
float   MarioStopCountPhaseOutRIGHT  = 0.0f;
bool    MarioCanMoveLEFT      = true;
bool    MarioIsStoppingLEFT   = true;
float   MarioStopCountLEFT    = 0.0f;
float   MarioStopCountPhaseOutLEFT   = 0.0f;
bool    MarioCanMoveDOWN      = false;
bool    MarioCanMoveUP        = false;
bool    MarioIsJumping        = false;
bool    MarioJumpReset        = false;
bool    spaceBarIsPressed     = false;        
GLfloat jumpDisplacement      = 0.0f;
GLfloat jumpVelocity          = 0.0f;

bool    showCollision         = true;
bool    resetCollision        = false;

GLfloat mainGearRotation         =  0.0f;
GLfloat mainGearLowerPosition[]  = {5.0f,  -2.47f, 0.0f};
GLfloat mainGearMiddlePosition[] = {5.0f, -1.27f, 0.0f};
GLfloat mainGearUpperPosition[]  = {5.0f, -0.05f, 0.0f};
GLfloat armsPosition[]           = {0.0f,  0.0f,  0.28f};

GLfloat   mainPosition[]    = {0.0f, 0.0f, -7.2f};
float     adjustCollision[] = {0.0f, 0.0f,  0.0f};

float page_03_Position[]  = { 10.5f,   0.0f, 0.0f};
float pg3_boxA_Position[] = {-2.3f,  -1.3f, 0.0f};
float pg3_boxB_Position[] = {-0.75f, -0.5f, 0.0f};
float pg3_boxC_Position[] = { 0.75f, -1.3f, 0.0f};
float pg3_boxD_Position[] = { 2.3f,  -0.5f, 0.0f};
float pg3_sawA_Position[] = { -1.3f,  1.3f, 0.0f};
float sawBladeRotation    = 0.0f;
float swingArmRotation    = 0.0;
float swingForward        = true;
float pg3_sineIncrement   = 0.0f;
float pg3b_sineIncrement  = 0.0f;
float pg3_blockMoveTemp   = 0.0f;

float   page_04_Position[] = {17.5f, 0.0f, 0.0f};
float   movepg4Tex         = 0.0f;
float   pg4_movePistons    = 0.0f;
bool    movePistonsForward = true;
float   pg4_sinIncrement   = 0.0f;

float positionObject[]  = {0.0f, 0.0f, 0.0f};

float   page_05_Position[]     = { 23.5f, 0.0f, 0.0f};
GLfloat pg5_blockMiddleUpper[] = { 0.0f,  0.0f, 0.0f};
GLfloat pg5_blockMiddleLower[] = { 0.0f, -1.0f, 0.0f};
GLfloat pg5_blockLeftUpper[]   = {-1.5f,  0.5f, 0.0f};
GLfloat pg5_blockLeftLower[]   = {-1.5f, -0.5f, 0.0f};
GLfloat pg5_blockRightUpper[]  = { 1.5f,  0.5f, 0.0f};
GLfloat pg5_blockRightLower[]  = { 1.5f, -0.5f, 0.0f};
GLfloat movePg5_pistons        =   0.0f;
bool    pg5_pistonsFORWARD     =   true;


float page_06_Position[]  = { 28.5f,   0.0f, 0.0f};
float movepg6Tex = 0.0f;
float wheelsRotation = 0.0f;

struct Vertex
{
	float tu, tv;                                    
	float r, g, b;                                  
	float x, y, z;                                   
}; 
struct Texture
{
    float u, v;                                   
};
struct Normals
{
    float r, g, b;                                   
}; 
struct Vertices
{
    float x, y, z;                                   
}; 


ofstream out("frameRate.cpp");
float frameNumber = 0.0f;

    float lightX =  1.7f;
     float lightY  =  3.5f;
       float lightZ  = -21.8f;   
         float lightPosition[] = { lightX, lightY, lightZ};
           float quadraticAttenuation = 0.0072;            


GLuint    textureMap[1];
GLuint    normalMap[1];

GLuint    clouds_1[4];
GLuint    bricksTexture[1];
GLuint    bricksEdges[1];
GLuint    MarioTexture[1];
GLuint    turnStill[7];
GLuint    pg3_pistons[7];
GLuint    pg4_textures[7];

GLuint    pg5_textures[7];
GLuint    pg6_textures[7];




#include <math.h>








GLuint	filter;	


HDC	hDC = NULL;
  HGLRC hRC = NULL;
    HWND hWnd = NULL;
      HINSTANCE hInstance = NULL;



int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

      void render(void);
        void Init(void);
          void shutDown(void);
            void initShader(void);
                void ProcessKeyboard();
                 
                    int  LoadGLTextureBMP(char *textureFileName, char *normalMapFileName, GLuint &textureMapID, GLuint &normalMapID);
                    int  LoadGLTextureBMP_single(char *textureFileName, GLuint &textureMapID);                           
                    int  LoadGLTextureTGA(char *textureFileName, GLuint &textureMapID);
                    int  LoadGLTextureTGA(char *textureFileName, char *normalMapFileName, GLuint &textureMapID, GLuint &normalMapID) ;  
                    void runNmapShader_1(int numTriangles, const GLvoid *ArrayName, GLuint texMap);
                         


void Dot3shader( void );

#include "cpp/winInit.cpp"
#include "cpp/SHADERtech.cpp"
        

void PerformFrameStartSetup(void);
void printNumbers(float InputValue);
#include "CPP/CHARACTER_FONTS/DisplayFloat_3Dfont.cpp"

#include "models/clouds/clouds_01/clouds_1a.cpp"
#include "models/clouds/clouds_01/clouds_1b.cpp"
#include "models/clouds/clouds_01/clouds_1c.cpp"
#include "models/clouds/clouds_01/clouds_1d.cpp"

#include "models/bricks/bricks.cpp"
#include "models/bricks/bricksLeftEdge.cpp"
#include "models/bricks/bricksRightEdge.cpp"

#include "models/Mario/Mario.cpp"

#include "models/turnStill/gearLower.cpp"
#include "models/turnStill/arms.cpp"

#include "models/pg3/pg3_Box.cpp"
#include "models/pg3/pg3_piston.cpp"
#include "models/pg3/sawBlade.cpp"
#include "models/pg3/sawBladeArm.cpp"

#include "models/pg4/conveyorBelt.cpp"
#include "models/pg4/cylinder.cpp"
#include "models/pg4/pg4_piston.cpp"
#include "models/pg4/pg4_block.cpp"
#include "models/pg4/pg4_spikes1.cpp"
#include "models/pg4/pg4_spikes2.cpp"
#include "models/pg4/pg4_spikes3.cpp"
#include "models/pg4/pg4_spikes4.cpp"
#include "models/pg4/pg4_spikes5.cpp"


#include "models/pg5/pg5_box.cpp"
#include "models/pg5/pg5_piston.cpp"

#include "models/pg6/pg6_conveyorBelt_A.cpp"
#include "models/pg6/pg6_conveyorBelt_B.cpp"
#include "models/pg6/pg6_conveyorBelt_C.cpp"
#include "models/pg6/pg6_wheels.cpp"


void render(void)//////////////////////_______RENDER_____RENDER____RENDER_______RENDER_____RENDER____RENDER_______RENDER_____RENDER____RENDER
{    
   PerformFrameStartSetup();
   //glDisable(GL_DEPTH_TEST);
   
   glPushMatrix();
     glTranslatef(mainPosition[0], mainPosition[1], mainPosition[2]);
     glTranslatef(0.0f, 1.5f, 0.0f);
     glScalef(2.0f, 1.0f, 1.0f);
         glEnable(GL_BLEND);
         glBindTexture(GL_TEXTURE_2D, clouds_1[0]);
         glInterleavedArrays( GL_T2F_N3F_V3F, 0, clouds_1a);                        
         glDrawArrays( GL_TRIANGLES, 0, 6);      
             glBindTexture(GL_TEXTURE_2D, clouds_1[1]);
             glInterleavedArrays( GL_T2F_N3F_V3F, 0, clouds_1b);                        
             glDrawArrays( GL_TRIANGLES, 0, 6);     
                 glBindTexture(GL_TEXTURE_2D, clouds_1[2]);
                 glInterleavedArrays( GL_T2F_N3F_V3F, 0, clouds_1c);                        
                 glDrawArrays( GL_TRIANGLES, 0, 6);      
                     glBindTexture(GL_TEXTURE_2D, clouds_1[3]);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, clouds_1d);                        
                     glDrawArrays( GL_TRIANGLES, 0, 6);     
               glPopMatrix();      
   
   glPushMatrix();      
      glTranslatef(mainPosition[0], mainPosition[1], mainPosition[2]);      
      glPushMatrix();
             glTranslatef(0.0f, -2.305f, 0.0f); 
             glColor3f(1.0f, 1.0f, 1.0f);
             glBindTexture(GL_TEXTURE_2D, bricksTexture[0]);
             glInterleavedArrays( GL_T2F_N3F_V3F, 0, bricks);                        
             glDrawArrays( GL_TRIANGLES, 0, 12); 
                     glBindTexture(GL_TEXTURE_2D, bricksEdges[0]);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, bricksLeftEdge);                        
                     glDrawArrays( GL_TRIANGLES, 0, 18);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, bricksRightEdge);                        
                     glDrawArrays( GL_TRIANGLES, 0, 18);         
         glPopMatrix(); 
         glPushMatrix();
             glTranslatef(-1.2f, -2.305f + 0.5, 0.0f);                      
             glColor3f(1.0f, 1.0f, 1.0f);
             glBindTexture(GL_TEXTURE_2D, bricksTexture[0]);
             glInterleavedArrays( GL_T2F_N3F_V3F, 0, bricks);                        
             glDrawArrays( GL_TRIANGLES, 0, 12);                      
                     glBindTexture(GL_TEXTURE_2D, bricksEdges[0]);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, bricksLeftEdge);                        
                     glDrawArrays( GL_TRIANGLES, 0, 18);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, bricksRightEdge);                        
                     glDrawArrays( GL_TRIANGLES, 0, 18);
         glPopMatrix();
         glPushMatrix();
             glTranslatef(2.2f, -2.305f + 0.5f, 0.0f);                      
             glColor3f(1.0f, 1.0f, 1.0f);
             glBindTexture(GL_TEXTURE_2D, bricksTexture[0]);
             glInterleavedArrays( GL_T2F_N3F_V3F, 0, bricks);                        
             glDrawArrays( GL_TRIANGLES, 0, 12);                      
                     glBindTexture(GL_TEXTURE_2D, bricksEdges[0]);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, bricksLeftEdge);                        
                     glDrawArrays( GL_TRIANGLES, 0, 18);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, bricksRightEdge);                        
                     glDrawArrays( GL_TRIANGLES, 0, 18);
         glPopMatrix(); 
         glPushMatrix();
             glTranslatef(1.0f, -2.305f + 1.0f, 0.0f);                      
             glColor3f(1.0f, 1.0f, 1.0f);
             glBindTexture(GL_TEXTURE_2D, bricksTexture[0]);
             glInterleavedArrays( GL_T2F_N3F_V3F, 0, bricks);                        
             glDrawArrays( GL_TRIANGLES, 0, 12);                      
                     glBindTexture(GL_TEXTURE_2D, bricksEdges[0]);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, bricksLeftEdge);                        
                     glDrawArrays( GL_TRIANGLES, 0, 18);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, bricksRightEdge);                        
                     glDrawArrays( GL_TRIANGLES, 0, 18);
         glPopMatrix();          
         glPushMatrix();
             glTranslatef(-2.5f, -2.305f + 0.4f, 0.0f);                      
             glColor3f(1.0f, 1.0f, 1.0f);
             glBindTexture(GL_TEXTURE_2D, bricksTexture[0]);
             glInterleavedArrays( GL_T2F_N3F_V3F, 0, bricks);                        
             glDrawArrays( GL_TRIANGLES, 0, 12);                      
                     glBindTexture(GL_TEXTURE_2D, bricksEdges[0]);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, bricksLeftEdge);                        
                     glDrawArrays( GL_TRIANGLES, 0, 18);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, bricksRightEdge);                        
                     glDrawArrays( GL_TRIANGLES, 0, 18);
         glPopMatrix();                               


         glPushMatrix();
             glTranslatef(-4.2f, -2.305f + 1.0f, 0.0f);                      
             glColor3f(1.0f, 1.0f, 1.0f);
             glBindTexture(GL_TEXTURE_2D, bricksTexture[0]);
             glInterleavedArrays( GL_T2F_N3F_V3F, 0, bricks);                        
             glDrawArrays( GL_TRIANGLES, 0, 12);                      
                     glBindTexture(GL_TEXTURE_2D, bricksEdges[0]);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, bricksLeftEdge);                        
                     glDrawArrays( GL_TRIANGLES, 0, 18);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, bricksRightEdge);                        
                     glDrawArrays( GL_TRIANGLES, 0, 18);
         glPopMatrix();              
glPopMatrix();  
//////////////////////////////////////////////////////////___PG_2___//////////////////////////////////////////////////////////////////////////////  
   glPushMatrix();
         glTranslatef(mainGearLowerPosition[0] + mainPosition[0], mainGearLowerPosition[1], mainPosition[2]);  
         glBindTexture(GL_TEXTURE_2D, turnStill[0]);
         glRotatef(mainGearRotation, 0.0f, 0.0f, 1.0f);
         glInterleavedArrays( GL_T2F_N3F_V3F, 0, gearLower);                        
         glDrawArrays( GL_TRIANGLES, 0, 6); 
         mainGearRotation += 1.0;
   glPopMatrix();   
   glPushMatrix();
         glTranslatef(mainGearMiddlePosition[0] + mainPosition[0], mainGearMiddlePosition[1], mainPosition[2]);  
         glBindTexture(GL_TEXTURE_2D, turnStill[0]);
         glRotatef(-mainGearRotation, 0.0f, 0.0f, 1.0f);
         glInterleavedArrays( GL_T2F_N3F_V3F, 0, gearLower);                        
         glDrawArrays( GL_TRIANGLES, 0, 6); 
   glPopMatrix();         
   glPushMatrix();
         glTranslatef(mainGearUpperPosition[0] + mainPosition[0], mainGearUpperPosition[1], mainPosition[2]);  
         glBindTexture(GL_TEXTURE_2D, turnStill[0]);
         glRotatef(mainGearRotation, 0.0f, 0.0f, 1.0f);
         glInterleavedArrays( GL_T2F_N3F_V3F, 0, gearLower);                        
         glDrawArrays( GL_TRIANGLES, 0, 6); 
   glPopMatrix();
   glPushMatrix();
         glTranslatef(mainGearUpperPosition[0] + mainPosition[0], mainGearUpperPosition[1], mainPosition[2] + armsPosition[2]);  
         glBindTexture(GL_TEXTURE_2D, turnStill[1]);
         glRotatef(mainGearRotation, 0.0f, 0.0f, 1.0f);
         glInterleavedArrays( GL_T2F_N3F_V3F, 0, arms);                        
         glDrawArrays( GL_TRIANGLES, 0, 54); 
   glPopMatrix();
//////////////////////////////////////////////////////////___PG_2___//////////////////////////////////////////////////////////////////////////////  

//////////////////////////////////////////////////////////___PG_3___//////////////////////////////////////////////////////////////////////////////  
 pg3_sineIncrement += 0.02f;
    
    pg3_blockMoveTemp = pg3_boxA_Position[1];
    pg3_boxA_Position[1] = (pg3_boxA_Position[1] + sin(pg3_sineIncrement)) * 0.35f;   
    pg3_blockMoveTemp = pg3_blockMoveTemp - pg3_boxA_Position[1];
    lower_edge[6]        =  pg3_boxA_Position[1] - 0.30f - 1.0f;
    upper_edge[6]        =  pg3_boxA_Position[1] + 0.30f - 1.0f;
    Y3[6]                =  pg3_boxA_Position[1] - 0.30f - 1.0f;
    Y4[6]                =  pg3_boxA_Position[1] + 0.30f - 1.0f;    
    if(collisionObjectIdentifier == 6)
    {
         MarioPositionY -= pg3_blockMoveTemp;                          
    }                                
       
       pg3_blockMoveTemp = pg3_boxB_Position[1];       
       pg3_boxB_Position[1] = (pg3_boxB_Position[1] + sin(pg3_sineIncrement * 1.33f)) * 0.35f;
       pg3_blockMoveTemp = pg3_blockMoveTemp - pg3_boxB_Position[1];       
       lower_edge[7] = pg3_boxB_Position[1] - 0.30f - 1.0f;
       upper_edge[7] = pg3_boxB_Position[1] + 0.30f - 1.0f;
       Y3[7]         = pg3_boxB_Position[1] - 0.30f - 1.0f;
       Y4[7]         = pg3_boxB_Position[1] + 0.30f - 1.0f;        
       if(collisionObjectIdentifier == 7)
       {
           MarioPositionY -= pg3_blockMoveTemp;                          
       }          
          pg3_blockMoveTemp = pg3_boxC_Position[1];          
          pg3_boxC_Position[1] = (pg3_boxC_Position[1] + sin(pg3_sineIncrement * 1.66f)) * 0.35f;   
          pg3_blockMoveTemp = pg3_blockMoveTemp - pg3_boxC_Position[1];          
          lower_edge[8] = pg3_boxC_Position[1] - 0.30f - 1.0f;
          upper_edge[8] = pg3_boxC_Position[1] + 0.30f - 1.0f;
          Y3[8]         = pg3_boxC_Position[1] - 0.30f - 1.0f;
          Y4[8]         = pg3_boxC_Position[1] + 0.30f - 1.0f;             
          if(collisionObjectIdentifier == 8)
          {
              MarioPositionY -= pg3_blockMoveTemp;                          
          }             
             pg3_blockMoveTemp = pg3_boxD_Position[1];             
             pg3_boxD_Position[1] = (pg3_boxD_Position[1] + sin(pg3_sineIncrement * 2.0f)) * 0.35f;    
             pg3_blockMoveTemp = pg3_blockMoveTemp - pg3_boxD_Position[1];              
             lower_edge[9] = pg3_boxD_Position[1] - 0.30f - 1.0f;
             upper_edge[9] = pg3_boxD_Position[1] + 0.30f - 1.0f;
             Y3[9]         = pg3_boxD_Position[1] - 0.30f - 1.0f;
             Y4[9]         = pg3_boxD_Position[1] + 0.30f - 1.0f;  
             if(collisionObjectIdentifier == 9)
             {
                 MarioPositionY -= pg3_blockMoveTemp;                          
             }

   glPushMatrix();
         glTranslatef( mainPosition[0] + pg3_boxA_Position[0] + page_03_Position[0], mainPosition[1]+ pg3_boxA_Position[1] - 1.0f, mainPosition[2]+ pg3_boxA_Position[2]);  
         glBindTexture(GL_TEXTURE_2D, pg3_pistons[0]);
         glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg3_Box);                        
         glDrawArrays( GL_TRIANGLES, 0, 24); 
             glBindTexture(GL_TEXTURE_2D, pg3_pistons[1]);
             glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg3_piston);                        
             glDrawArrays( GL_TRIANGLES, 0, 6); 
   glPopMatrix();    
////////////////////////////////// 
   glPushMatrix();
         glTranslatef( mainPosition[0] + pg3_boxB_Position[0] + page_03_Position[0], mainPosition[1]+ pg3_boxB_Position[1] - 1.0f, mainPosition[2]+ pg3_boxB_Position[2]);  
         glBindTexture(GL_TEXTURE_2D, pg3_pistons[0]);
         glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg3_Box);                        
         glDrawArrays( GL_TRIANGLES, 0, 24); 
             glBindTexture(GL_TEXTURE_2D, pg3_pistons[1]);
             glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg3_piston);                        
             glDrawArrays( GL_TRIANGLES, 0, 6); 
   glPopMatrix();   
//////////////////////////////////  
   glPushMatrix();
         glTranslatef( mainPosition[0] + pg3_boxC_Position[0] + page_03_Position[0], mainPosition[1]+ pg3_boxC_Position[1] - 1.0f, mainPosition[2]+ pg3_boxC_Position[2]);  
         glBindTexture(GL_TEXTURE_2D, pg3_pistons[0]);
         glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg3_Box);                        
         glDrawArrays( GL_TRIANGLES, 0, 24); 
             glBindTexture(GL_TEXTURE_2D, pg3_pistons[1]);
             glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg3_piston);                        
             glDrawArrays( GL_TRIANGLES, 0, 6); 
   glPopMatrix();   
//////////////////////////////////   
   glPushMatrix();
         glTranslatef( mainPosition[0] + pg3_boxD_Position[0] + page_03_Position[0], mainPosition[1]+ pg3_boxD_Position[1] - 1.0f, mainPosition[2]+ pg3_boxD_Position[2]);  
         glBindTexture(GL_TEXTURE_2D, pg3_pistons[0]);
         glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg3_Box);                        
         glDrawArrays( GL_TRIANGLES, 0, 24); 
             glBindTexture(GL_TEXTURE_2D, pg3_pistons[1]);
             glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg3_piston);                        
             glDrawArrays( GL_TRIANGLES, 0, 6); 
   glPopMatrix();
   
////////////////////////////////
////////////////////////////////
////////////////////////////////   
/*   if(swingForward)
   {
      swingArmRotation += 1.0;
      if(swingArmRotation > 42)   
           swingForward = false; 
   }
   if(!swingForward)
   {
      swingArmRotation -= 1.0;
      if(swingArmRotation < -42)   
           swingForward = true; 
   }
*/   
swingArmRotation  += sin(pg3b_sineIncrement); 
pg3b_sineIncrement += 0.02f;   
   glPushMatrix();
         glTranslatef( mainPosition[0] + pg3_sawA_Position[0] + page_03_Position[0], mainPosition[1]+ pg3_sawA_Position[1], mainPosition[2]+ pg3_sawA_Position[2]);  
         glBindTexture(GL_TEXTURE_2D, pg3_pistons[2]);
         glTranslatef(0.0f, 2.0f, 0.0f);
         glRotatef(swingArmRotation, 0.0f, 0.0f, 1.0f);
         glTranslatef(0.0f, -2.0f, 0.0f);         
         glRotatef(sawBladeRotation, 0.0f, 0.0f, 1.0f);         
         glInterleavedArrays( GL_T2F_N3F_V3F, 0, sawBlade);                        
         glDrawArrays( GL_TRIANGLES, 0, 6); 
         sawBladeRotation += 3.0;
   glPopMatrix();   
   glPushMatrix();
         glTranslatef( mainPosition[0] + pg3_sawA_Position[0] + page_03_Position[0], mainPosition[1]+ pg3_sawA_Position[1], mainPosition[2]+ pg3_sawA_Position[2]);  
         glTranslatef(0.0f, 2.0f, 0.0f);
         glRotatef(swingArmRotation, 0.0f, 0.0f, 1.0f);
         glTranslatef(0.0f, -2.0f, 0.0f);         
         glBindTexture(GL_TEXTURE_2D, pg3_pistons[3]);
         glInterleavedArrays( GL_T2F_N3F_V3F, 0, sawBladeArm);                        
         glDrawArrays( GL_TRIANGLES, 0, 6); 
   glPopMatrix(); 
///////////////////////////////
   glPushMatrix();
         glTranslatef( mainPosition[0] + pg3_sawA_Position[0] + page_03_Position[0] + 2.69, mainPosition[1]+ pg3_sawA_Position[1], mainPosition[2]+ pg3_sawA_Position[2]);  
         glBindTexture(GL_TEXTURE_2D, pg3_pistons[2]);
         glTranslatef(0.0f, 2.0f, 0.0f);
         glRotatef(swingArmRotation, 0.0f, 0.0f, 1.0f);
         glTranslatef(0.0f, -2.0f, 0.0f);
         glRotatef(sawBladeRotation, 0.0f, 0.0f, 1.0f);         
         glInterleavedArrays( GL_T2F_N3F_V3F, 0, sawBlade);                        
         glDrawArrays( GL_TRIANGLES, 0, 6); 
   glPopMatrix();   
   glPushMatrix();
         glTranslatef( mainPosition[0] + pg3_sawA_Position[0] + page_03_Position[0] + 2.69, mainPosition[1]+ pg3_sawA_Position[1], mainPosition[2]+ pg3_sawA_Position[2]);  
         glTranslatef(0.0f, 2.0f, 0.0f);
         glRotatef(swingArmRotation, 0.0f, 0.0f, 1.0f);
         glTranslatef(0.0f, -2.0f, 0.0f);         
         glBindTexture(GL_TEXTURE_2D, pg3_pistons[3]);
         glInterleavedArrays( GL_T2F_N3F_V3F, 0, sawBladeArm);                        
         glDrawArrays( GL_TRIANGLES, 0, 6); 
   glPopMatrix();

//////////////////////////////////////////////////////////___PG_3___//////////////////////////////////////////////////////////////////////////////               

//////////////////////////////////////////////////////////___PG_4___//////////////////////////////////////////////////////////////////////////////
   glPushMatrix();
         glTranslatef(mainPosition[0] + page_04_Position[0], mainPosition[1] - 1.5, mainPosition[2]);         
         glLightfv (GL_LIGHT0,GL_POSITION,lightPosition);
         glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
         glMatrixMode(GL_TEXTURE);
         glPushMatrix();
             glTranslatef(movepg4Tex, 0.0f, 0.0f);
             glBindTexture(GL_TEXTURE_2D, pg4_textures[0]);
             glInterleavedArrays( GL_T2F_N3F_V3F, 0, conveyorBelt);                        
             glDrawArrays( GL_TRIANGLES, 0, 168); 
         glPopMatrix();
         glMatrixMode( GL_MODELVIEW );
   glPopMatrix();
   movepg4Tex -= 0.001; 
   
         glPushMatrix();
         glTranslatef(mainPosition[0]+ page_04_Position[0]-1.69, mainPosition[1]- 1.5, mainPosition[2]);  //leftCylinder
              glRotatef(wheelsRotation, 0.0f, 0.0f, 1.0f);
                   glDisable(GL_BLEND);              
                   glBindTexture(GL_TEXTURE_2D, pg4_textures[1]);
                   glInterleavedArrays( GL_T2F_N3F_V3F, 0, cylinder);                        
                   glDrawArrays( GL_TRIANGLES, 0, 102);
                      //glEnable(GL_BLEND);
                      //glBindTexture(GL_TEXTURE_2D, pg4_textures[6]);
                      //glInterleavedArrays( GL_T2F_N3F_V3F, 0, wheelsCenter);                        
                      //glDrawArrays( GL_TRIANGLES, 0, 6);                    
        glPopMatrix();
        wheelsRotation -= 0.7;
               glPushMatrix();
                    glTranslatef(mainPosition[0] + page_04_Position[0] + 2.61, mainPosition[1] - 1.5, mainPosition[2]);  //rightCylinder
                    glRotatef(wheelsRotation, 0.0f, 0.0f, 1.0f);
                   glDisable(GL_BLEND);              
                   glBindTexture(GL_TEXTURE_2D, pg4_textures[1]);
                   glInterleavedArrays( GL_T2F_N3F_V3F, 0, cylinder);                        
                   glDrawArrays( GL_TRIANGLES, 0, 102);
                      //glEnable(GL_BLEND);
                      //glBindTexture(GL_TEXTURE_2D, pg4_textures[6]);
                      //glInterleavedArrays( GL_T2F_N3F_V3F, 0, wheelsCenter);                        
                      //glDrawArrays( GL_TRIANGLES, 0, 6);               
               glPopMatrix();      
////////////////////////////////////   
         if(movePistonsForward)
         {
              pg4_movePistons += (0.01f);
              if(pg4_movePistons >= 1.3f)
                   movePistonsForward = false;
         }             
         if(!movePistonsForward)
         {
              pg4_movePistons -= (0.01f);
              if(pg4_movePistons <= 0.0f)
                   movePistonsForward = true;
         }

            
   glPushMatrix();
         glDisable(GL_BLEND);
         glTranslatef(mainPosition[0] + page_04_Position[0] + 0.4f, mainPosition[1] + pg4_movePistons, mainPosition[2]); //__CENTER_SPIKED_PRESS
         glBindTexture(GL_TEXTURE_2D, pg4_textures[2]);
         glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_block);                        
         glDrawArrays( GL_TRIANGLES, 0, 30); 
                glBindTexture(GL_TEXTURE_2D, pg4_textures[3]);
                glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_piston);                        
                glDrawArrays( GL_TRIANGLES, 0, 6); 
                      glEnable(GL_BLEND);
                      glBindTexture(GL_TEXTURE_2D, pg4_textures[4]);
                      glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_spikes5);                        
                      glDrawArrays( GL_TRIANGLES, 0, 6); 
                        glBindTexture(GL_TEXTURE_2D, pg4_textures[5]);
                        glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_spikes4);                        
                        glDrawArrays( GL_TRIANGLES, 0, 6); 
                          glBindTexture(GL_TEXTURE_2D, pg4_textures[4]);
                          glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_spikes3);                        
                          glDrawArrays( GL_TRIANGLES, 0, 6); 
                            glBindTexture(GL_TEXTURE_2D, pg4_textures[5]);
                            glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_spikes2);                        
                            glDrawArrays( GL_TRIANGLES, 0, 6); 
                              glBindTexture(GL_TEXTURE_2D, pg4_textures[4]);
                              glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_spikes1);                        
                              glDrawArrays( GL_TRIANGLES, 0, 6); 
   glPopMatrix();
   glPushMatrix();
         glDisable(GL_BLEND);
         glTranslatef(mainPosition[0] + page_04_Position[0] - 1.31f, mainPosition[1] - pg4_movePistons + 1.27f, mainPosition[2]); //__CENTER_SPIKED_PRESS
         glBindTexture(GL_TEXTURE_2D, pg4_textures[2]);
         glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_block);                        
         glDrawArrays( GL_TRIANGLES, 0, 30); 
                glBindTexture(GL_TEXTURE_2D, pg4_textures[3]);
                glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_piston);                        
                glDrawArrays( GL_TRIANGLES, 0, 6); 
                      glEnable(GL_BLEND);
                      glBindTexture(GL_TEXTURE_2D, pg4_textures[4]);
                      glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_spikes5);                        
                      glDrawArrays( GL_TRIANGLES, 0, 6); 
                        glBindTexture(GL_TEXTURE_2D, pg4_textures[5]);
                        glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_spikes4);                        
                        glDrawArrays( GL_TRIANGLES, 0, 6); 
                          glBindTexture(GL_TEXTURE_2D, pg4_textures[4]);
                          glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_spikes3);                        
                          glDrawArrays( GL_TRIANGLES, 0, 6); 
                            glBindTexture(GL_TEXTURE_2D, pg4_textures[5]);
                            glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_spikes2);                        
                            glDrawArrays( GL_TRIANGLES, 0, 6); 
                              glBindTexture(GL_TEXTURE_2D, pg4_textures[4]);
                              glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_spikes1);                        
                              glDrawArrays( GL_TRIANGLES, 0, 6); 
   glPopMatrix();   
   glPushMatrix();
         glDisable(GL_BLEND);
         glTranslatef(mainPosition[0] + page_04_Position[0]+ 2.1, mainPosition[1] - pg4_movePistons + 1.27f, mainPosition[2]); //__CENTER_SPIKED_PRESS
         glBindTexture(GL_TEXTURE_2D, pg4_textures[2]);
         glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_block);                        
         glDrawArrays( GL_TRIANGLES, 0, 30); 
                glBindTexture(GL_TEXTURE_2D, pg4_textures[3]);
                glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_piston);                        
                glDrawArrays( GL_TRIANGLES, 0, 6); 
                      glEnable(GL_BLEND);
                      glBindTexture(GL_TEXTURE_2D, pg4_textures[4]);
                      glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_spikes5);                        
                      glDrawArrays( GL_TRIANGLES, 0, 6); 
                        glBindTexture(GL_TEXTURE_2D, pg4_textures[5]);
                        glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_spikes4);                        
                        glDrawArrays( GL_TRIANGLES, 0, 6); 
                          glBindTexture(GL_TEXTURE_2D, pg4_textures[4]);
                          glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_spikes3);                        
                          glDrawArrays( GL_TRIANGLES, 0, 6); 
                            glBindTexture(GL_TEXTURE_2D, pg4_textures[5]);
                            glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_spikes2);                        
                            glDrawArrays( GL_TRIANGLES, 0, 6); 
                              glBindTexture(GL_TEXTURE_2D, pg4_textures[4]);
                              glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg4_spikes1);                        
                              glDrawArrays( GL_TRIANGLES, 0, 6); 
   glPopMatrix();   

/////////////////////////////////////////////////////////___PG_4___///////////////////////////////////////////////////////////////////////
// + positionObject[1]
/////////////////////////////////////////////////////////___PG_5___////////////////////////////////////////////////////////////////////////////////
  
if(pg5_pistonsFORWARD)
{
    movePg5_pistons += 0.01f;
    if(movePg5_pistons >= 1.0f)
         pg5_pistonsFORWARD = false;
}
if(!pg5_pistonsFORWARD)
{
    movePg5_pistons -= 0.01f;
    if(movePg5_pistons <= -1.0f)
         pg5_pistonsFORWARD = true;
}  
  
   glPushMatrix();
         glTranslatef( mainPosition[0] + page_05_Position[0] + pg5_blockMiddleUpper[0], mainPosition[1] + pg5_blockMiddleUpper[1] + movePg5_pistons, mainPosition[2]);  
         glBindTexture(GL_TEXTURE_2D, pg5_textures[0]);
         glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg5_box);                        
         glDrawArrays( GL_TRIANGLES, 0, 30); 
   glPopMatrix();glPushMatrix();
                     glTranslatef( mainPosition[0] + page_05_Position[0], mainPosition[1] + 1.81f + movePg5_pistons + 0.3f, mainPosition[2]);  
                     glBindTexture(GL_TEXTURE_2D, pg5_textures[1]);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg5_piston);                        
                     glDrawArrays( GL_TRIANGLES, 0, 6); 
                 glPopMatrix();        
   glPushMatrix();
              glTranslatef( mainPosition[0] + page_05_Position[0] + pg5_blockMiddleLower[0], mainPosition[1] + pg5_blockMiddleLower[1] + movePg5_pistons, mainPosition[2]);  
              glBindTexture(GL_TEXTURE_2D, pg5_textures[0]);
              glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg5_box);                        
              glDrawArrays( GL_TRIANGLES, 0, 30); 
   glPopMatrix();glPushMatrix();
                     glTranslatef( mainPosition[0] + page_05_Position[0], mainPosition[1] - 2.81f + movePg5_pistons - 0.3f, mainPosition[2]);  
                     glBindTexture(GL_TEXTURE_2D, pg5_textures[1]);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg5_piston);                        
                     glDrawArrays( GL_TRIANGLES, 0, 6); 
                 glPopMatrix();
   glPushMatrix();
         glTranslatef( mainPosition[0] + page_05_Position[0] + pg5_blockLeftUpper[0], mainPosition[1] + pg5_blockLeftUpper[1] - movePg5_pistons, mainPosition[2]);  
         glBindTexture(GL_TEXTURE_2D, pg5_textures[0]);
         glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg5_box);                        
         glDrawArrays( GL_TRIANGLES, 0, 30); 
   glPopMatrix();glPushMatrix();
                     glTranslatef( mainPosition[0] + page_05_Position[0] - 1.49f, mainPosition[1] + 2.3f - movePg5_pistons + 0.3f, mainPosition[2]);  
                     glBindTexture(GL_TEXTURE_2D, pg5_textures[1]);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg5_piston);                        
                     glDrawArrays( GL_TRIANGLES, 0, 6); 
                 glPopMatrix();
   glPushMatrix();
              glTranslatef( mainPosition[0] + page_05_Position[0] + pg5_blockLeftLower[0], mainPosition[1] + pg5_blockLeftLower[1] - movePg5_pistons, mainPosition[2]);  
              glBindTexture(GL_TEXTURE_2D, pg5_textures[0]);
              glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg5_box);                        
              glDrawArrays( GL_TRIANGLES, 0, 30); 
   glPopMatrix();glPushMatrix();
                     glTranslatef( mainPosition[0] + page_05_Position[0] - 1.5f, mainPosition[1] - 2.3f - movePg5_pistons - 0.3f, mainPosition[2]);  
                     glBindTexture(GL_TEXTURE_2D, pg5_textures[1]);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg5_piston);                        
                     glDrawArrays( GL_TRIANGLES, 0, 6); 
                 glPopMatrix();
  glPushMatrix();
         glTranslatef( mainPosition[0] + page_05_Position[0] + pg5_blockRightUpper[0], mainPosition[1] + pg5_blockRightUpper[1] - movePg5_pistons, mainPosition[2]);  
         glBindTexture(GL_TEXTURE_2D, pg5_textures[0]);
         glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg5_box);                        
         glDrawArrays( GL_TRIANGLES, 0, 30); 
   glPopMatrix();glPushMatrix();
                     glTranslatef( mainPosition[0] + page_05_Position[0] + 1.5f, mainPosition[1] + 2.3f - movePg5_pistons + 0.3f, mainPosition[2]);  
                     glBindTexture(GL_TEXTURE_2D, pg5_textures[1]);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg5_piston);                        
                     glDrawArrays( GL_TRIANGLES, 0, 6); 
                 glPopMatrix();
   glPushMatrix();
              glTranslatef( mainPosition[0] + page_05_Position[0] + pg5_blockRightLower[0], mainPosition[1] + pg5_blockRightLower[1] - movePg5_pistons, mainPosition[2]);  
              glBindTexture(GL_TEXTURE_2D, pg5_textures[0]);
              glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg5_box);                        
              glDrawArrays( GL_TRIANGLES, 0, 30); 
   glPopMatrix();glPushMatrix();
                     glTranslatef( mainPosition[0] + page_05_Position[0] + 1.5f, mainPosition[1] - 2.3f - movePg5_pistons - 0.3f, mainPosition[2]);  
                     glBindTexture(GL_TEXTURE_2D, pg5_textures[1]);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg5_piston);                        
                     glDrawArrays( GL_TRIANGLES, 0, 6); 
                 glPopMatrix();                

////////////////////////////////////////////////////////___PG_5___/////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////___PG_6___///////////////////////////////////////////////////////////////////////////////
   glPushMatrix();
         glTranslatef(mainPosition[0] + page_06_Position[0], mainPosition[1], mainPosition[2]);         
         glLightfv (GL_LIGHT0,GL_POSITION,lightPosition);
         glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
         glMatrixMode(GL_TEXTURE);
         glPushMatrix();
             glTranslatef(movepg6Tex, 0.0f, 0.0f);
             glBindTexture(GL_TEXTURE_2D, pg6_textures[0]);
             glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg6_conveyorBelt_A);                        
             glDrawArrays( GL_TRIANGLES, 0, 168); 
         glPopMatrix();
         glMatrixMode( GL_MODELVIEW );
   glPopMatrix();glPushMatrix();
                     glTranslatef( mainPosition[0] + page_06_Position[0] - 1.393f, mainPosition[1] + 0.343f, mainPosition[2]);  
                     glRotatef(wheelsRotation, 0.0f, 0.0f, 1.0f);
                     glBindTexture(GL_TEXTURE_2D, pg6_textures[1]);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg6_wheels);                        
                     glDrawArrays( GL_TRIANGLES, 0, 102); 
                 glPopMatrix(); 
                 glPushMatrix();
                     glTranslatef( mainPosition[0] + page_06_Position[0] + 1.12, mainPosition[1] + 0.343f, mainPosition[2]);  
                     glRotatef(wheelsRotation, 0.0f, 0.0f, 1.0f);                     
                     glBindTexture(GL_TEXTURE_2D, pg6_textures[1]);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg6_wheels);                        
                     glDrawArrays( GL_TRIANGLES, 0, 102); 
                 glPopMatrix();
/*                 
                 glPushMatrix();
                     glTranslatef( mainPosition[0] + page_06_Position[0] + positionObject[0], mainPosition[1] + positionObject[1], mainPosition[2]);  
                     glRotatef(wheelsRotation, 0.0f, 0.0f, 1.0f);                     
                     glBindTexture(GL_TEXTURE_2D, pg6_textures[1]);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg6_wheels);                        
                     glDrawArrays( GL_TRIANGLES, 0, 102); 
                 glPopMatrix();
*/

   movepg6Tex -= 0.001; 
/////////////////////////////   
   glPushMatrix();
         glTranslatef(mainPosition[0] + page_06_Position[0], mainPosition[1], mainPosition[2]);         
         glLightfv (GL_LIGHT0,GL_POSITION,lightPosition);
         glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
         glMatrixMode(GL_TEXTURE);
         glPushMatrix();
             glTranslatef(-movepg6Tex, 0.0f, 0.0f);
             glBindTexture(GL_TEXTURE_2D, pg6_textures[0]);
             glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg6_conveyorBelt_B);                        
             glDrawArrays( GL_TRIANGLES, 0, 168); 
         glPopMatrix();
         glMatrixMode( GL_MODELVIEW );
   glPopMatrix();glPushMatrix();
                     glTranslatef( mainPosition[0] + page_06_Position[0] - 1.379f, mainPosition[1] - 2.04f, mainPosition[2]);  
                     glRotatef(wheelsRotation, 0.0f, 0.0f, 1.0f);                     
                     glBindTexture(GL_TEXTURE_2D, pg6_textures[1]);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg6_wheels);                        
                     glDrawArrays( GL_TRIANGLES, 0, 102); 
                 glPopMatrix();
                 glPushMatrix();
                     glTranslatef( mainPosition[0] + page_06_Position[0] + 1.134f, mainPosition[1] - 2.04f, mainPosition[2]);  
                     glRotatef(wheelsRotation, 0.0f, 0.0f, 1.0f);                     
                     glBindTexture(GL_TEXTURE_2D, pg6_textures[1]);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg6_wheels);                        
                     glDrawArrays( GL_TRIANGLES, 0, 102); 
                 glPopMatrix();
/////////////////////////////   
   glPushMatrix();
         glTranslatef(mainPosition[0] + page_06_Position[0], mainPosition[1], mainPosition[2]);         
         glLightfv (GL_LIGHT0,GL_POSITION,lightPosition);
         glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
         glMatrixMode(GL_TEXTURE);
         glPushMatrix();
             glTranslatef(movepg6Tex, 0.0f, 0.0f);
             glBindTexture(GL_TEXTURE_2D, pg6_textures[0]);
             glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg6_conveyorBelt_C);                        
             glDrawArrays( GL_TRIANGLES, 0, 168); 
         glPopMatrix();
         glMatrixMode(GL_MODELVIEW);
   glPopMatrix();glPushMatrix();
                     glTranslatef( mainPosition[0] + page_06_Position[0] - 0.876002f, mainPosition[1] - 0.843002f, mainPosition[2]);  
                     glRotatef(-wheelsRotation, 0.0f, 0.0f, 1.0f);                     
                     glBindTexture(GL_TEXTURE_2D, pg6_textures[1]);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg6_wheels);                        
                     glDrawArrays( GL_TRIANGLES, 0, 102); 
                 glPopMatrix();
                 glPushMatrix();
                     glTranslatef( mainPosition[0] + page_06_Position[0] + 1.64101f, mainPosition[1] - 0.849002f, mainPosition[2]);  
                     glRotatef(-wheelsRotation, 0.0f, 0.0f, 1.0f);                     
                     glBindTexture(GL_TEXTURE_2D, pg6_textures[1]);
                     glInterleavedArrays( GL_T2F_N3F_V3F, 0, pg6_wheels);                        
                     glDrawArrays( GL_TRIANGLES, 0, 102); 
                 glPopMatrix();   
////////////////////////////////////////////////////////___PG_6___////////////////////////////////////////////////////////////////////////



       glEnable(GL_BLEND);   
        X1 = MarioPositionX - 0.19;
        X2 = MarioPositionX + 0.19;
        Y1 = MarioPositionY - 0.30;
        Y2 = MarioPositionY + 0.26;
   
        
        CollisionCheck_DOWN(X1, X2, Y1, Y2);
        
        if(MarioCanMoveDOWN)           
        {      
            MarioPositionY -= gravity;
            gravity += 0.0015;
        }
        CollisionCheck_UP(X1, X2, Y1, Y2);        
       
        if(MarioCanMoveUP)           
        {      
            MarioPositionY += jumpVelocity;
        }
        
        if(jumpVelocity >= 0.0f)
        {
              jumpVelocity -= gravity;
        }
        if(jumpVelocity < 0.0f)
        {
              jumpVelocity = 0.0f;
        }   
   
   
   glPushMatrix();
         glTranslatef(MarioPositionX, MarioPositionY, mainPosition[2]);         
         glLightfv (GL_LIGHT0,GL_POSITION,lightPosition);
         glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
         glBindTexture(GL_TEXTURE_2D, MarioTexture[0]);
         glInterleavedArrays( GL_T2F_N3F_V3F, 0, Mario);                        
         glDrawArrays( GL_TRIANGLES, 0, 6); 
   glPopMatrix();


   if(showCollision)
   {  
      glDisable(GL_TEXTURE_2D);
      glBegin(GL_QUADS);									
	      glColor3f(1.0f, 0.0f, 1.0f);
          glVertex3f( X1,  Y2,  mainPosition[2]);					
          glVertex3f( X2,  Y2,  mainPosition[2]);	    				
          glVertex3f( X2,  Y1,  mainPosition[2]);					
          glVertex3f( X1,  Y1,  mainPosition[2]);
          glColor3f(1.0f, 1.0f, 1.0f);             
      glEnd();
      glEnable(GL_TEXTURE_2D); 
   }
       
        
      //if(crystalHitPing == true)         ///////////_______SOUND
      //{                                  ///////////_______SOUND
           //alSourcePlay(Sources[hit]);   ///////////_______SOUND
      //}                                  ///////////_______SOUND
      //crystalHitPing = false;            ///////////_______SOUND

   glPushMatrix();      
      glTranslatef(mainPosition[0], mainPosition[1], mainPosition[2]);      
          if(showCollision)
          {   
             glDisable(GL_BLEND);
             glDisable(GL_TEXTURE_2D);
             glBegin(GL_QUADS);									
	           glColor3f(1.0f, 1.0f, 1.0f);
          ///////////////////////____PG_1___/////////////////////////                
                glVertex3f(left_edge[0],  upper_edge[0], 0.0f);					
		        glVertex3f(right_edge[0], upper_edge[0], 0.0f);	    				
		        glVertex3f(right_edge[0], lower_edge[0], 0.0f);					
		        glVertex3f(left_edge[0],  lower_edge[0], 0.0f);
		        glColor3f(0.0f, 1.0f, 1.0f);
		        glVertex3f(left_edge[1],  upper_edge[1], 0.0f);					
		        glVertex3f(right_edge[1], upper_edge[1], 0.0f);	    			
		        glVertex3f(right_edge[1], lower_edge[1], 0.0f);					
		        glVertex3f(left_edge[1],  lower_edge[1], 0.0f);
	            glColor3f(0.0f, 0.0f, 1.0f);
		        glVertex3f(left_edge[2],  upper_edge[2], 0.0f);					
		        glVertex3f(right_edge[2], upper_edge[2], 0.0f);	    			
		        glVertex3f(right_edge[2], lower_edge[2], 0.0f);					
		        glVertex3f(left_edge[2],  lower_edge[2], 0.0f);
		        glColor3f(1.0f, 0.0f, 0.0f);  
		        glVertex3f(left_edge[3],  upper_edge[3], 0.0f);					
		        glVertex3f(right_edge[3], upper_edge[3], 0.0f);	    			
		        glVertex3f(right_edge[3], lower_edge[3], 0.0f);					
		        glVertex3f(left_edge[3],  lower_edge[3], 0.0f);
		        glColor3f(0.0f, 1.0f, 0.0f);  
		        glVertex3f(left_edge[4],  upper_edge[4], 0.0f);					
		        glVertex3f(right_edge[4], upper_edge[4], 0.0f);	    			
		        glVertex3f(right_edge[4], lower_edge[4], 0.0f);					
		        glVertex3f(left_edge[4],  lower_edge[4], 0.0f);
		        glColor3f(0.6f, 1.0f, 0.1f); 
		        glVertex3f(left_edge[5],  upper_edge[5], 0.0f);					
		        glVertex3f(right_edge[5], upper_edge[5], 0.0f);	    			
		        glVertex3f(right_edge[5], lower_edge[5], 0.0f);					
		        glVertex3f(left_edge[5],  lower_edge[5], 0.0f);
          ///////////////////////____PG_1___/////////////////////////         
          ///////////////////////____PG_3___/////////////////////////
		        glVertex3f(left_edge[6] ,  upper_edge[6], 0.0f);					
		        glVertex3f(right_edge[6],  upper_edge[6], 0.0f);	    			
		        glVertex3f(right_edge[6],  lower_edge[6], 0.0f);					
		        glVertex3f(left_edge[6],  lower_edge[6], 0.0f); 
				glVertex3f(right_edge[7],  upper_edge[7], 0.0f);	    			
		        glVertex3f(right_edge[7],  lower_edge[7], 0.0f);					
		        glVertex3f(left_edge[7],  lower_edge[7], 0.0f);
		        glVertex3f(left_edge[7],  upper_edge[7], 0.0f);					
		        glVertex3f(right_edge[8],  upper_edge[8], 0.0f);	    			
		        glVertex3f(right_edge[8],  lower_edge[8], 0.0f);					
		        glVertex3f(left_edge[8],  lower_edge[8], 0.0f);
		        glVertex3f(left_edge[8],  upper_edge[8], 0.0f);					
		        glVertex3f(right_edge[9],  upper_edge[9], 0.0f);	    			
		        glVertex3f(right_edge[9],  lower_edge[9], 0.0f);					
		        glVertex3f(left_edge[9],  lower_edge[9], 0.0f);
		        glVertex3f(left_edge[9],  upper_edge[9], 0.0f);					
          ///////////////////////____PG_3___/////////////////////////             
             glEnd();
             glEnable(GL_TEXTURE_2D);
             glEnable(GL_BLEND);
	         glColor3f(1.0f, 1.0f, 1.0f);                     
          }
   glPopMatrix();
/*
frameEnd = GetTickCount();   ///____the final output for framerate.cpp is calculated immediately before the call to ShutDown()
out << "frameNumber = " << frameNumber << endl << "time to render LastFrame = " << (frameEnd - frameStart) << " milliSeconds" <<  endl;//____divided by 1000
out << "total time = " << (GetTickCount() - inTheBeginning)    << " milliSeconds" << endl;//divided by 1000
frameNumber ++;//used for the timer
*/


SwapBuffers( hDC );

glFlush();
glFinish();
}

/////////////_____ProcessKeyboard()________ProcessKeyboard()_________ProcessKeyboard()______ProcessKeyboard()___////////////////
/////////////_____ProcessKeyboard()________ProcessKeyboard()_________ProcessKeyboard()______ProcessKeyboard()___////////////////
/////////////_____ProcessKeyboard()________ProcessKeyboard()_________ProcessKeyboard()______ProcessKeyboard()___////////////////
/////////////_____ProcessKeyboard()________ProcessKeyboard()_________ProcessKeyboard()______ProcessKeyboard()___////////////////

void ProcessKeyboard()								
{
 
 //==========================================================================================================================================================================
 
    if (keys[VK_LEFT])
	{
          CollisionCheck_LEFT(X1, X2, Y1, Y2);
          if(MarioCanMoveLEFT)  
          {   
                mainPosition[0] += 0.03f;////_________________________THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
                for(int i = 0; i < numberOfCollisionObjects; i++)//___THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
                {//___________________________________________________THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
                      X3[i]           += 0.03f;/////////////////////____THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
                      X4[i]           += 0.03f;/////////////////////____THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
                }//___________________________________________________THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
          }       
          MarioIsStoppingLEFT = true;///____________THESE VARIABLES ALLOW CHARACTER TO CONTINUE MOVING FOR A SHORT TIME AFTER KEY IS RELEASED
          MarioStopCountLEFT  = 0.5;///_____________THESE VARIABLES ALLOW CHARACTER TO CONTINUE MOVING FOR A SHORT TIME AFTER KEY IS RELEASED
          MarioStopCountPhaseOutLEFT = 0.01f;///____THESE VARIABLES ALLOW CHARACTER TO CONTINUE MOVING FOR A SHORT TIME AFTER KEY IS RELEASED
    }
    //---------------------------------------------------------------------------------------------------------------------------------------             
                  if (!keys[VK_LEFT] && MarioIsStoppingLEFT)
	              { 
                        MarioStopCountLEFT -= 0.06f;//___COUNTDOWN FOR CHARACTER TO CONTINUE MOVING
                        CollisionCheck_LEFT(X1, X2, Y1, Y2);
                        if(MarioCanMoveLEFT)  
                        {
                                mainPosition[0] += (0.03f-MarioStopCountPhaseOutLEFT);//__PHASE-OUT DIMINISHES HOW FAR CHARACTER MOVES -->>LESS AND LESS EACH CYCLE
                                for(int i = 0; i < numberOfCollisionObjects; i++)
                                { 
                                       X3[i]           += (0.03f-MarioStopCountPhaseOutLEFT);
                                       X4[i]           += (0.03f-MarioStopCountPhaseOutLEFT);
                                }
                        }
                        if(MarioStopCountLEFT <= 0.0f)
                             MarioIsStoppingLEFT = false;                                            
                  }
                  //---------------------------------------------------------------------------------------------------------------------------------------                                  
                                    if (keys[VK_LEFT] && keys['F'])//___________FAST MOVE//___________FAST MOVE//___________FAST MOVE//___________FAST MOVE
                                    {
                                          mainPosition[0] += 0.1f;////_________________________THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
                                          for(int i = 0; i < numberOfCollisionObjects; i++)//___THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
                                          {//___________________________________________________THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC          
                                                   X3[i]           += 0.1f;/////////////////////____THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
                                                   X4[i]           += 0.1f;/////////////////////____THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
                                          }//___________________________________________________THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
                                    } 
    
    //==========================================================================================================================================================================                                                                   
    
    if (keys[VK_RIGHT])
	{
          CollisionCheck_RIGHT(X1, X2, Y1, Y2);
          if(MarioCanMoveRIGHT)  
          {           
                mainPosition[0] -= 0.03f;////_________________________THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
                for(int i = 0; i < numberOfCollisionObjects; i++)//___THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
                {//___________________________________________________THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC          
                    X3[i]           -= 0.03f;/////////////////////____THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
                    X4[i]           -= 0.03f;/////////////////////____THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
                }//___________________________________________________THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
          }
          MarioIsStoppingRIGHT = true;///____________THESE VARIABLES ALLOW CHARACTER TO CONTINUE MOVING FOR A SHORT TIME AFTER KEY IS RELEASED
          MarioStopCountRIGHT  = 0.5;///_____________THESE VARIABLES ALLOW CHARACTER TO CONTINUE MOVING FOR A SHORT TIME AFTER KEY IS RELEASED
          MarioStopCountPhaseOutRIGHT    = 0.01f;//__THESE VARIABLES ALLOW CHARACTER TO CONTINUE MOVING FOR A SHORT TIME AFTER KEY IS RELEASED
    }
    //---------------------------------------------------------------------------------------------------------------------------------------                 
                  if (!keys[VK_RIGHT] && MarioIsStoppingRIGHT)
	              { 
                        MarioStopCountRIGHT -= 0.06f;//___COUNTDOWN FOR CHARACTER TO CONTINUE MOVING
                        CollisionCheck_RIGHT(X1, X2, Y1, Y2);
                        if(MarioCanMoveRIGHT)  
                        {
                                mainPosition[0] -= (0.03f-MarioStopCountPhaseOutRIGHT);//__PHASE-OUT DIMINISHES HOW FAR CHARACTER MOVES -->>LESS AND LESS EACH CYCLE
                                for(int i = 0; i < numberOfCollisionObjects; i++)
                                { 
                                       X3[i]           -= (0.03f-MarioStopCountPhaseOutRIGHT);
                                       X4[i]           -= (0.03f-MarioStopCountPhaseOutRIGHT);
                                }
                        }
                        if(MarioStopCountRIGHT <= 0.0f)
                             MarioIsStoppingRIGHT = false;                                            
                  }
                  //---------------------------------------------------------------------------------------------------------------------------------------                                    
                                    if (keys[VK_RIGHT] && keys['F'])//___________FAST MOVE//___________FAST MOVE//___________FAST MOVE//___________FAST MOVE
                                    {
                                             mainPosition[0] -= 0.1f;////_________________________THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
                                             for(int i = 0; i < numberOfCollisionObjects; i++)//___THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
                                             {//___________________________________________________THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC          
                                                    X3[i]           -= 0.1f;/////////////////////____THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
                                                    X4[i]           -= 0.1f;/////////////////////____THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
                                             }//___________________________________________________THESE FOUR LINES CONNECT SCENE MOVEMENT WITH COLLISION LOGIC
                                    }                     
	
    //==========================================================================================================================================================================
	
    if (keys[VK_UP])
	{
          //mainPosition[1] += 0.03f;
    }
	if (keys[VK_DOWN])
	{
          //mainPosition[1] -= 0.03f;       
    }
 
   
    if (!keys[VK_SPACE]) 			
    {
        spaceBarIsPressed = false;
        jumpVelocity      = 0.0f;
    }
    
    if (keys[VK_SPACE] && !spaceBarIsPressed && MarioJumpReset && !MarioCanMoveDOWN) 			
    {
        if(jumpVelocity < 0.08f)
            gravity = 0.0f;
        jumpVelocity += 0.08f;
        
        if(jumpVelocity >= 0.1f)
        {
             spaceBarIsPressed = true;
             MarioJumpReset = false;
        }     
    }    
    
    if (keys['C'] && resetCollision) 			
	{
        resetCollision = false;
        if(!showCollision)
        {
           showCollision  = true;
           return;
        }
        if(showCollision)
        {   
            showCollision  = false;
            return;
        }       
    }
    if (!keys['C']) 			
	{
        resetCollision = true;
    }
    if (keys['R']) 			
	{
        MarioPositionY = 2.0f;
        gravity = 0.0f;
    }
            
            
    if (keys['L']) 			
	{
        lightPosition[0] += 0.1f;
    }
    if (keys['J']) 			
    {
        lightPosition[0] -= 0.1f;
    }    
    if (keys['I']) 			
	{
        lightPosition[1] += 0.1f;
    }
    if (keys['K']) 				
    {
        lightPosition[1] -= 0.1f;
    }
	if (keys['O']) 			
	{
        lightPosition[2] += 0.1f;
    }
    if (keys['U']) 			
    {
       lightPosition[2] -= 0.1f;
    }


    if (keys[VK_NUMPAD6]) 
	{
          positionObject[0] += 0.003f;//////////!!!!!!____MOVE_ROOM_PIECES____!!!!!!! 
    }
    if (keys[VK_NUMPAD4]) 		
	{
          positionObject[0] -= 0.003f;//////////!!!!!!____MOVE_ROOM_PIECES____!!!!!!!             
    }
	if (keys[VK_NUMPAD8])
    {
          positionObject[1] += 0.003f;//////////!!!!!!____MOVE_ROOM_PIECES____!!!!!!! 
    }		
	if (keys[VK_NUMPAD2]) 
    {
          positionObject[1] -= 0.003f;//////////!!!!!!____MOVE_ROOM_PIECES____!!!!!!! 
    }

	if (keys[VK_NUMPAD9])
    {
          adjustCollision[1] += 0.01f;
    }		
	if (keys[VK_NUMPAD3]) 
    {
          adjustCollision[1] -= 0.01f;
    }
    
    if (keys['W']) quadraticAttenuation += 0.0001f;			
    if (keys['S']) quadraticAttenuation -= 0.0001f;
          
    if (keys['Q']) 			
	{
        ofstream out("lightPosition.cpp");
        
        out << "collisionObjectIdentifier: "  << collisionObjectIdentifier  << "\n";
                
        out << "lightPosition\n" << lightPosition[0] << "\n" << lightPosition[1] << "\n" << lightPosition[2] << "\n";
        out << "quadraticAttenuation: " << quadraticAttenuation <<  "\n\n";
        
        out << "mainPosition: " << mainPosition[0] <<  " "<< mainPosition[1] <<  " " << mainPosition[2] <<  "\n\n";
        
        out << "positionObject[0]: " << positionObject[0] <<  " "<< positionObject[1] <<  " " << positionObject[2] <<  "\n\n";
        out << "adjustCollision: "   << adjustCollision[0] <<  " "<< adjustCollision[1] <<  " " << adjustCollision[2] <<  "\n\n";        
    }
}

//=============================================================================================================================================================
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//=============================================================================================================================================================

void CollisionCheck_LEFT(float X1, float X2, float Y1, float Y2)           //////*****************************************
{
     MarioCanMoveLEFT = true;

     for( int i = 0; i < numberOfCollisionObjects; i++)
     {
         planeX3_inner[i] = X3[i] + 0.05f;   ////left edge
         planeX3_outer[i] = X3[i] - 0.05f;   ////left edge
         planeX4_inner[i] = X4[i] - 0.05f;   ////right edge
         planeX4_outer[i] = X4[i] + 0.05f;   ////right edge
         planeY3_inner[i] = Y3[i] + 0.07f;   ////bottom edge
         planeY3_outer[i] = Y3[i] - 0.05f;   ////bottom edge
         planeY4_inner[i] = Y4[i] - 0.07f;   ////top edge
         planeY4_outer[i] = Y4[i] + 0.05f;   ////top edge

         if((X2 >= X3[i]) && (X4[i] >= X1) && (Y2 >= Y3[i]) && (Y4[i] >= Y1))   
                MarioCanMoveLEFT = false;
         if((Y2 >= planeY3_outer[i]) && (Y2 <= planeY3_inner[i]) && (X2 >= planeX3_outer[i]) && (X1 <= planeX4_outer[i]) && (MarioCanMoveLEFT == false))/////___CLEARS STICKY EDGES
                MarioCanMoveLEFT = true;                                                       /////top edge of moving primary object
         if((Y1 <= planeY4_outer[i]) && (Y1 >= planeY4_inner[i]) && (X2 >= planeX3_outer[i]) && (X1 <= planeX4_outer[i]) && (MarioCanMoveLEFT == false))/////___CLEARS STICKY EDGES
                MarioCanMoveLEFT = true;                                                       /////bottom edge of moving primary object
         if((X2 >= planeX3_outer[i]) && (X2 <= planeX4_inner[i]) && (Y2 >= planeY3_outer[i]) && (Y1 <= planeY4_outer[i]) && (MarioCanMoveLEFT == false))/////___CLEARS STICKY EDGES
                MarioCanMoveLEFT = true;
         if(MarioCanMoveLEFT == false)
         {
                   collisionObjectIdentifier = i;
                   break;
         }
                   
      }        
}

void CollisionCheck_RIGHT(float X1, float X2, float Y1, float Y2)          //////*****************************************
{
     MarioCanMoveRIGHT = true;
  
     for( int i = 0; i < numberOfCollisionObjects; i++)
     {
          planeX3_inner[i] = X3[i] + 0.05f;   ////left edge
          planeX3_outer[i] = X3[i] - 0.05f;   ////left edge
          planeX4_inner[i] = X4[i] - 0.05f;   ////right edge
          planeX4_outer[i] = X4[i] + 0.05f;   ////right edge
          planeY3_inner[i] = Y3[i] + 0.15f;   ////bottom edge
          planeY3_outer[i] = Y3[i] - 0.05f;   ////bottom edge
          planeY4_inner[i] = Y4[i] - 0.07f;   ////top edge
          planeY4_outer[i] = Y4[i] + 0.05f;   ////top edge
     
          if((X2 >= X3[i]) && (X4[i] >= X1) && (Y2 >= Y3[i]) && (Y4[i] >= Y1))
                 MarioCanMoveRIGHT = false;
          if((Y2 >= planeY3_outer[i]) && (Y2 <= planeY3_inner[i]) && (X2 >= planeX3_outer[i]) && (X1 <= planeX4_outer[i]) && (MarioCanMoveRIGHT == false))/////___CLEARS STICKY EDGES
                 MarioCanMoveRIGHT = true;                                                       /////top edge of moving primary object
          if((Y1 >= planeY4_inner[i]) && (Y1 <= planeY4_outer[i]) && (X2 >= planeX3_outer[i]) && (X1 <= planeX4_outer[i]) && (MarioCanMoveRIGHT == false))/////___CLEARS STICKY EDGES
                 MarioCanMoveRIGHT = true;                                                       /////bottom edge of moving primary object
          if((X1 >= planeX4_inner[i]) && (X1 <= planeX4_outer[i]) && (Y1 <= planeY4_outer[i]) && (Y2 >= planeY3_outer[i]) && (MarioCanMoveRIGHT == false))/////___CLEARS STICKY EDGES
                 MarioCanMoveRIGHT = true;
          if(MarioCanMoveRIGHT == false)
          {
                collisionObjectIdentifier = i; 
                break;
          } 
      }  
}

void CollisionCheck_UP(float X1, float X2, float Y1, float Y2)             //////*****************************************
{
     MarioCanMoveUP = true;
    
     for( int i = 0; i < numberOfCollisionObjects; i++)
     {
        planeX3_inner[i] = X3[i] + 0.05f;   ////left edge
        planeX3_outer[i] = X3[i] - 0.05f;   ////left edge
        planeX4_inner[i] = X4[i] - 0.05f;   ////right edge
        planeX4_outer[i] = X4[i] + 0.05f;   ////right edge
        planeY3_inner[i] = Y3[i] + 0.05f;   ////bottom edge
        planeY3_outer[i] = Y3[i] - 0.05f;   ////bottom edge
        planeY4_inner[i] = Y4[i] - 0.15f;   ////top edge
        planeY4_outer[i] = Y4[i] + 0.05f;   ////top edge
     
        if((X2 >= X3[i]) && (X4[i] >= X1) && (Y2 >= Y3[i]) && (Y4[i] >= Y1))        
               MarioCanMoveUP = false;
        if((X2 >= planeX3_outer[i]) && (X2 <= planeX3_inner[i]) && (Y1 <= planeY4_outer[i]) && (Y2 >= planeY3_outer[i]) && (MarioCanMoveUP == false))/////___CLEARS STICKY EDGES
               MarioCanMoveUP = true;
        if((X1 >= planeX4_inner[i]) && (X1 <= planeX4_outer[i]) && (Y1 <= planeY4_outer[i]) && (Y2 >= planeY3_outer[i]) && (MarioCanMoveUP == false))/////___CLEARS STICKY EDGES
               MarioCanMoveUP = true;
        if((Y1 >= planeY4_inner[i]) && (Y1 <= planeY4_outer[i]) && (X1 <= planeX4_outer[i]) && (X2 >= planeX3_outer[i]) && (MarioCanMoveUP == false))/////___CLEARS STICKY EDGES
               MarioCanMoveUP = true;
         if(MarioCanMoveUP == false)
         {
              collisionObjectIdentifier = i;
              break;
         }     
     }   
}

void CollisionCheck_DOWN(float X1, float X2, float Y1, float Y2)           //////*****************************************
{   
     MarioCanMoveDOWN = true;
    
     for( int i = 0; i < numberOfCollisionObjects; i++)
     {
          planeX3_inner[i] = X3[i] + 0.05f;   ////left edge
          planeX3_outer[i] = X3[i] - 0.0f;   ////left edge
          planeX4_inner[i] = X4[i] - 0.05f;   ////right edge
          planeX4_outer[i] = X4[i] + 0.0f;   ////right edge
          planeY3_inner[i] = Y3[i] + 0.15f;   ////bottom edge 
          planeY3_outer[i] = Y3[i] - 0.05f;   ////bottom edge
          planeY4_inner[i] = Y4[i] - 0.00f;   ////top edge
          planeY4_outer[i] = Y4[i] + 0.05f;   ////top edge
       
          if((X2 >= X3[i]) && (X4[i] >= X1) && (Y2 >= Y3[i]) && (Y4[i] >= Y1))
                 MarioCanMoveDOWN = false;
          if((X2 >= planeX3_outer[i]) && (X2 <= planeX3_inner[i]) && (Y1 <= planeY4_outer[i]) && (Y2 >= planeY3_outer[i]) && (MarioCanMoveDOWN == false))/////___CLEARS STICKY EDGES
                 MarioCanMoveDOWN = true;
          if((X1 >= planeX4_inner[i]) && (X1 <= planeX4_outer[i]) && (Y1 <= planeY4_outer[i]) && (Y2 >= planeY3_outer[i]) && (MarioCanMoveDOWN == false))/////___CLEARS STICKY EDGES
                 MarioCanMoveDOWN = true;
          if((Y2 >= planeY3_outer[i]) && (Y2 <= planeY3_inner[i]) && (X2 >= planeX3_outer[i]) && (X1 <= planeX4_outer[i]) && (MarioCanMoveDOWN == false))/////___CLEARS STICKY EDGES
                 MarioCanMoveDOWN = true;
          if(MarioCanMoveDOWN == false)
          {
                gravity = 0.0f;
                MarioJumpReset = true;
                collisionObjectIdentifier = i;
                break;
          }      
             
      }        
}

//=============================================================================================================================================================
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//=============================================================================================================================================================


void SetupCollision(void)
{
    //////////////////___PG_1___////////////////////        
        left_edge [0] = -0.5f;
        right_edge[0] =  0.7f;
        lower_edge[0] = -2.555f;
        upper_edge[0] = -2.055f;

        left_edge [1] = -0.5f   - 1.2f;
        right_edge[1] =  0.5f   - 1.2f;
        lower_edge[1] = -2.555f + 0.5f;
        upper_edge[1] = -2.055f + 0.5f;

        left_edge [2] = -0.5f   + 2.2f;
        right_edge[2] =  0.5f   + 2.2f;
        lower_edge[2] = -2.555f + 0.5f;
        upper_edge[2] = -2.055f + 0.5f;

        left_edge [3] = -0.5f   + 1.0f;
        right_edge[3] =  0.5f   + 1.0f;
        lower_edge[3] = -2.555f + 1.0f;
        upper_edge[3] = -2.055f + 1.0f;

        left_edge [4] = -0.5f   - 2.5f;
        right_edge[4] =  0.5f   - 2.5f;
        lower_edge[4] = -2.555f + 0.4f;
        upper_edge[4] = -2.055f + 0.4f;

        left_edge [5] = -0.5f   - 4.2f;
        right_edge[5] =  0.5f   - 4.2f;
        lower_edge[5] = -2.555f + 1.0f;
        upper_edge[5] = -2.055f + 1.0f;
    //////////////////___PG_1___////////////////////        
    //////////////////___PG_3___////////////////////        
        left_edge [6] = (-2.3f  - 0.5f) + page_03_Position[0];
        right_edge[6] = (-2.3f  + 0.5f) + page_03_Position[0];/////PG_3___BLOCK_1
        lower_edge[6] =  -1.3f   - 0.30f;
        upper_edge[6] =  -1.3f   + 0.30f;
       
        left_edge [7] = (-0.75f - 0.5f) + page_03_Position[0];
        right_edge[7] = (-0.75f + 0.5f) + page_03_Position[0];/////PG_3___BLOCK_2
        lower_edge[7] =  -0.5f  - 0.3f;
        upper_edge[7] =  -0.5f  + 0.3f;

        left_edge [8] = (0.75f  - 0.5f) + page_03_Position[0];
        right_edge[8] = (0.75f  + 0.5f) + page_03_Position[0];/////PG_3___BLOCK_3
        lower_edge[8] = -1.3f   - 0.3f ;
        upper_edge[8] = -1.3f   + 0.3f;

        left_edge [9] = (2.3f   - 0.5f) + page_03_Position[0];
        right_edge[9] = (2.3f   + 0.5f) + page_03_Position[0];/////PG_3___BLOCK_4
        lower_edge[9] = -0.5f   - 0.3f;
        upper_edge[9] = -0.5f   + 0.3f;
    //////////////////___PG_3___///////////////////// 
        for(int i = 0; i < numberOfCollisionObjects; i++)
        {
            X3[i] = left_edge[i];
            X4[i] = right_edge[i];     
            Y3[i] = lower_edge[i];      
            Y4[i] = upper_edge[i]; 
        }
}

//=============================================================================================================================================================
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//=============================================================================================================================================================

void Init( void )
{
     
 
    GLuint PixelFormat;
	
    PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

    pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion   = 1;
    pfd.dwFlags    = PFD_DRAW_TO_WINDOW |PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
	
	hDC = GetDC( hWnd );
	PixelFormat = ChoosePixelFormat( hDC, &pfd );
	SetPixelFormat( hDC, PixelFormat, &pfd);
	hRC = wglCreateContext( hDC );
	wglMakeCurrent( hDC, hRC );

	glEnable( GL_TEXTURE_2D );
	glEnable( GL_DEPTH_TEST );
    glDepthFunc(GL_LEQUAL);	
	
    glClearColor( 1.0f * 140 /255, 1.0f * 254 /255, 1.0f * 255 /255, 0.5f );//___SKY_BLUE
    //glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	
    glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45.0f, 640.0f / 480.0f, 0.1f, 100.0f);

    GLfloat spot_direction[] = {0.0, 0.0, 0.0 };//////////////////_______LIGHT0
     glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION, (float)0.007);////_______LIGHT0
      glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, (float)0.01);//////_______LIGHT0
       glLightf (GL_LIGHT0, GL_CONSTANT_ATTENUATION,(float).003);/////_______LIGHT0
        glEnable(GL_LIGHT0);


SetupCollision();

//mainPosition[0] = - 28.5f;


swingArmRotation = -50.0f;

//LoadGLTextureBMP("bitmaps_02/tree_3A.bmp",                            "bitmaps_02/tree_3A_NM2.bmp",                             textureMap[14], normalMap[14]); 
//LoadGLTextureBMP("bitmaps_02/leavesRound.bmp",                        "bitmaps_02/leavesRound_NM1.bmp",                         textureMap[16], normalMap[16]);

LoadGLTextureTGA("models/clouds/clouds_01/clouds_01a.tga", clouds_1[0]);
LoadGLTextureTGA("models/clouds/clouds_01/clouds_01b.tga", clouds_1[1]);
LoadGLTextureTGA("models/clouds/clouds_01/clouds_01c.tga", clouds_1[2]);
LoadGLTextureTGA("models/clouds/clouds_01/clouds_01d.tga", clouds_1[3]);

LoadGLTextureTGA("models/bricks/bricks.tga",     bricksTexture[0]);
LoadGLTextureTGA("models/bricks/brickEdges.tga", bricksEdges[0]);

LoadGLTextureTGA("models/Mario/Mario.tga",  MarioTexture[0]);

LoadGLTextureTGA("models/turnStill/gear_A.tga",       turnStill[0]);
LoadGLTextureTGA("models/turnStill/armsTexture.tga",  turnStill[1]);

LoadGLTextureTGA("models/pg3/pg3_Box.tga",     pg3_pistons[0]); 
LoadGLTextureTGA("models/pg3/pistonShaft.tga", pg3_pistons[1]);
LoadGLTextureTGA("models/pg3/sawBlade.tga",    pg3_pistons[2]);
LoadGLTextureTGA("models/pg3/sawBladeArm.tga", pg3_pistons[3]);

LoadGLTextureTGA("models/pg4/conveyorBelt.tga",   pg4_textures[0]);
LoadGLTextureTGA("models/pg4/cylinder_0.tga",     pg4_textures[1]);
LoadGLTextureTGA("models/pg4/pg4_block.tga",      pg4_textures[2]);
LoadGLTextureTGA("models/pg4/pistonShaft.tga",    pg4_textures[3]);
LoadGLTextureTGA("models/pg4/spikesWide.tga",     pg4_textures[4]);
LoadGLTextureTGA("models/pg4/spikesNarrow.tga",   pg4_textures[5]);
//LoadGLTextureTGA("models/pg4/wheelsCenter.tga",   pg4_textures[6]);

LoadGLTextureTGA("models/pg5/pg5BoxTex.tga",         pg5_textures[0]);
LoadGLTextureTGA("models/pg5/pg5_pistonSilver.tga",  pg5_textures[1]);

LoadGLTextureTGA("models/pg6/conveyorBelt.tga",  pg6_textures[0]);
LoadGLTextureTGA("models/pg6/cylinder_0.tga",    pg6_textures[1]);
 

//alSourcePlay(Sources[dung]);//for main background music start
   

}
