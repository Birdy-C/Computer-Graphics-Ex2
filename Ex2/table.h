//@author Birdy&C 2017.4.7
#pragma once
#define GLUT_DISABLE_ATEXIT_HACK
#include <stdio.h>
#include<windows.h>
#include <gL\GLAUX.H>
#include <gl\GLUT.H>  

//函数声明

//===========main.cpp============//

void init();

//===========event.cpp============//
void timer(int p);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void special(int key, int x, int y);
void keyboard(unsigned char key, int x, int y);
void setProjection(int width, int height);
void reshape(int w1, int h1);

//===========render.cpp============//
AUX_RGBImageRec *LoadBMP(CHAR *Filename); 
int LoadGLTextures();
void Draw_Leg();
void Draw_Table();
void drawMain();
void renderScene(); 
void renderScenesw1();
void renderScenesw2(); 
void renderScenesw3();
void renderSceneAll();



//全局变量

extern bool mouseisdown, loopr;
extern int mainWindow, subWindow1, subWindow2, subWindow3, rx, ry, rz, tx, ty, w, h;
extern int time, state;
extern const int border;
extern float  mx, mz;
extern GLuint  texture[1]; 

