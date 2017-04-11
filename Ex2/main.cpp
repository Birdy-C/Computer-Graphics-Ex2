// main.cpp : 定义控制台应用程序的入口点。
//@author Birdy&C 2017.4.7

#include "table.h"

//子窗口
int mainWindow, subWindow1, subWindow2, subWindow3;
//旋转记录
int rx = 0;
int ry = 0;
int rz = 0;
//平移记录
float mx = 0;
float mz = 0;
//鼠标位置
int tx, ty;
//边界宽度
const int border = 6;
//主窗口大小
int w, h;
//自动事件控制
bool mouseisdown = false;
bool loopr = false;
int state = 1;
int time = 0;
//存储纹理
GLuint  texture[1]; 



//初始化
void init()
{
	//纹理控制部分

	//glCullFace(GL_BACK);				//背面裁剪(背面不可见)
	//glEnable(GL_CULL_FACE);			//启用裁剪
	glEnable(GL_DEPTH_TEST);			//深度测试
	glEnable(GL_TEXTURE_2D);
	LoadGLTextures();					//载入纹理贴图


	//事件处理部分
	glutIgnoreKeyRepeat(0);				//确认是否忽略自动的连续击键
	glutMouseFunc(mouse);				//鼠标点击事件
	glutMotionFunc(motion);				//鼠标拖动事件
	glutKeyboardFunc(keyboard);			//键盘事件
	glutSpecialFunc(special);			//特殊键盘 没有ASCII值 如上下左右


	//光照控制部分
	GLfloat DiffuseLightn[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light_position1[] = { 10.0, 20.0, 30.0, 0.0 };
	GLfloat light_position2[] = { 10.0, 10.0, -30.0, 0.0 };

	glLightfv(GL_LIGHT0,  GL_DIFFUSE, DiffuseLightn);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLightn);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glDepthFunc(GL_LESS);

}


int main (int argc,  char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640,480);
	mainWindow = glutCreateWindow("Birdy");
	LoadGLTextures();            //载入纹理贴图

	glutDisplayFunc(renderSceneAll);
	glutReshapeFunc(reshape);
	init();


	//子窗口建立
	subWindow1 = glutCreateSubWindow(mainWindow, border, border, w - 2 * border, h / 2 - border * 3 / 2);
	glutDisplayFunc(renderScenesw1);
	init();

	subWindow2 = glutCreateSubWindow(mainWindow, border, (h + border) / 2, w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);
	glutDisplayFunc(renderScenesw2);
	init();

	subWindow3 = glutCreateSubWindow(mainWindow, (w + border) / 2, (h + border) / 2, w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);
	glutDisplayFunc(renderScenesw3);
	init();

	
	glutMainLoop();
	
	return 0;
}


