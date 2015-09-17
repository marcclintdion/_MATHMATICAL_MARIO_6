#include "FontListBasic.cpp"//______Wednesday November 11, 2009

float pushNumber = 0.075f;

float value      = 1.23f;
float InputValue = 0.0f;
float tempInputValue = 0.0f;
float tempInputValueB = 0.0f;
float numberPosition = 0.0f;
int   Input_01   = 0;
int   Input_02   = 0;
int   tempValueA  = 0;
int   tempValueB  = 0;

void printNumbers(float InputValue) 
{
    tempInputValue  = InputValue;
    tempValueA  = (int)InputValue;
    tempInputValueB = tempInputValue;
    
    InputValue      = InputValue - tempValueA;
    tempInputValueB = tempInputValueB - tempValueA;
    tempInputValueB = tempInputValueB *10;

    InputValue = InputValue * 10;

    Input_01 = (int)InputValue;
    
    tempInputValueB = tempInputValueB - Input_01;

    tempInputValue = tempInputValueB * 10;
    Input_02 = (int)tempInputValue;
 
            
             glPushMatrix();        
                  glTranslatef(-0.07, 0.0f, 0.0f);
                  glScalef(3.0f, 3.0f, 3.0f);
                  glInterleavedArrays( GL_V3F, 0, decimalPoint_VERT );                        
                  glDrawArrays( GL_TRIANGLES, 0, 6);
             glPopMatrix();
    
        
        if(Input_01 == 0)
        {    
             glPushMatrix();        
                  glTranslatef(numberPosition, 0.0f, 0.0f);
                  glInterleavedArrays( GL_V3F, 0, zero_VERT );                        
                  glDrawArrays( GL_TRIANGLES, 0, 36);
             glPopMatrix();
        }
        if(Input_02 == 0)
        {    
             glPushMatrix();        
                  glTranslatef(numberPosition + pushNumber, 0.0f, 0.0f);
                  glInterleavedArrays( GL_V3F, 0, zero_VERT );                        
                  glDrawArrays( GL_TRIANGLES, 0, 36);
             glPopMatrix();
        }
////////////////////////////////////////////////////////////////////////////////       
        if(Input_01 == 1)
        {
            glPushMatrix();
                glTranslatef(numberPosition, 0.0f, 0.0f);            
                glInterleavedArrays( GL_V3F, 0, one_VERT );                        
                glDrawArrays( GL_TRIANGLES, 0, 6);
            glPopMatrix();
        }
        if(Input_02 == 1)
        {
            glPushMatrix();
                glTranslatef(numberPosition + pushNumber, 0.0f, 0.0f);            
                glInterleavedArrays( GL_V3F, 0, one_VERT );                        
                glDrawArrays( GL_TRIANGLES, 0, 6);
            glPopMatrix();
        }
////////////////////////////////////////////////////////////////////////////////        
        if(Input_01 == 2)
        {
            glPushMatrix();
                glTranslatef(numberPosition, 0.0f, 0.0f);            
                glInterleavedArrays( GL_V3F, 0, two_VERT );                        
                glDrawArrays( GL_TRIANGLES, 0, 27);
            glPopMatrix();
        }
        if(Input_02 == 2)
        {
            glPushMatrix();
                glTranslatef(numberPosition + pushNumber, 0.0f, 0.0f);            
                glInterleavedArrays( GL_V3F, 0, two_VERT );                        
                glDrawArrays( GL_TRIANGLES, 0, 27);
            glPopMatrix();
        }        
////////////////////////////////////////////////////////////////////////////////        
        if(Input_01 == 3)
        {    
            glPushMatrix();
                glTranslatef(numberPosition, 0.0f, 0.0f);           
                glInterleavedArrays( GL_V3F, 0, three_VERT );                        
                glDrawArrays( GL_TRIANGLES, 0, 51);   
            glPopMatrix();
        }
        if(Input_02 == 3)
        {    
            glPushMatrix();
                glTranslatef(numberPosition + pushNumber, 0.0f, 0.0f);           
                glInterleavedArrays( GL_V3F, 0, three_VERT );                        
                glDrawArrays( GL_TRIANGLES, 0, 51);   
            glPopMatrix();
        }
////////////////////////////////////////////////////////////////////////////////        
        if(Input_01 == 4)
        {    
            glPushMatrix();
                glTranslatef(numberPosition, 0.0f, 0.0f);            
                glInterleavedArrays( GL_V3F, 0, four_VERT );                        
                glDrawArrays( GL_TRIANGLES, 0, 18);
            glPopMatrix();
        }
        if(Input_02 == 4)
        {    
            glPushMatrix();
                glTranslatef(numberPosition + pushNumber, 0.0f, 0.0f);            
                glInterleavedArrays( GL_V3F, 0, four_VERT );                        
                glDrawArrays( GL_TRIANGLES, 0, 18);
            glPopMatrix();
        }
////////////////////////////////////////////////////////////////////////////////        
        if(Input_01 == 5)
        {    
            glPushMatrix();
                glTranslatef(numberPosition, 0.0f, 0.0f);            
                glInterleavedArrays( GL_V3F, 0, five_VERT );                        
                glDrawArrays( GL_TRIANGLES, 0, 39);
            glPopMatrix();
        }
        if(Input_02 == 5)
        {    
            glPushMatrix();
                glTranslatef(numberPosition + pushNumber, 0.0f, 0.0f);            
                glInterleavedArrays( GL_V3F, 0, five_VERT );                        
                glDrawArrays( GL_TRIANGLES, 0, 39);
            glPopMatrix();
        }
////////////////////////////////////////////////////////////////////////////////        
        if(Input_01 == 6)
        {    
            glPushMatrix();
                glTranslatef(numberPosition, 0.0f, 0.0f);    
                glInterleavedArrays( GL_V3F, 0, six_VERT );                        
                glDrawArrays( GL_TRIANGLES, 0, 69);
            glPopMatrix();
        }
        if(Input_02 == 6)
        {    
            glPushMatrix();
                glTranslatef(numberPosition + pushNumber, 0.0f, 0.0f);    
                glInterleavedArrays( GL_V3F, 0, six_VERT );                        
                glDrawArrays( GL_TRIANGLES, 0, 69);
            glPopMatrix();
        }
////////////////////////////////////////////////////////////////////////////////        
        if(Input_01 == 7)
        {    
            glPushMatrix();
                glTranslatef(numberPosition, 0.0f, 0.0f);            
                glInterleavedArrays( GL_V3F, 0, seven_VERT );                        
                glDrawArrays( GL_TRIANGLES, 0, 15);
            glPopMatrix();
        }
        if(Input_02 == 7)
        {    
            glPushMatrix();
                glTranslatef(numberPosition + pushNumber, 0.0f, 0.0f);            
                glInterleavedArrays( GL_V3F, 0, seven_VERT );                        
                glDrawArrays( GL_TRIANGLES, 0, 15);
            glPopMatrix();
        }
////////////////////////////////////////////////////////////////////////////////        
        if(Input_01 == 8)
        {    
            glPushMatrix();
                glTranslatef(numberPosition, 0.0f, 0.0f);            
                glInterleavedArrays( GL_V3F, 0, eight_VERT );                        
                glDrawArrays( GL_TRIANGLES, 0, 84);
            glPopMatrix();
        }
        if(Input_02 == 8)
        {    
            glPushMatrix();
                glTranslatef(numberPosition + pushNumber, 0.0f, 0.0f);            
                glInterleavedArrays( GL_V3F, 0, eight_VERT );                        
                glDrawArrays( GL_TRIANGLES, 0, 84);
            glPopMatrix();
        }
////////////////////////////////////////////////////////////////////////////////        
        if(Input_01 == 9)
        {    
            glPushMatrix();
                glTranslatef(numberPosition, 0.0f, 0.0f);           
                glInterleavedArrays( GL_V3F, 0, nine_VERT );                        
                glDrawArrays( GL_TRIANGLES, 0, 60);
            glPopMatrix();   
        }
        if(Input_02 == 9)
        {    
            glPushMatrix();
                glTranslatef(numberPosition + pushNumber, 0.0f, 0.0f);           
                glInterleavedArrays( GL_V3F, 0, nine_VERT );                        
                glDrawArrays( GL_TRIANGLES, 0, 60);
            glPopMatrix();   
        }
////////////////////////////////////////////////////////////////////////////////
        
}//__close-->>  printNumbers(function)
