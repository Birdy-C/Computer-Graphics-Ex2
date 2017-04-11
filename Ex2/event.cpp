// event.cpp : 处理事件
//@author Birdy&C 2017.4.7
#include "table.h"

void timer(int p)
{
	time++;
	if (time >= 30)  
		time = 0;
	if (loopr)
	{
		glutTimerFunc(200, timer, 0);//循环
	}
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseisdown = true; 
			loopr = false;
			tx = x;
			ty = y;
		}
		else
		{
			mouseisdown = false;
		}
	}

	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN)
		{
			loopr = true;
			glutTimerFunc(200, timer, 0);
		}
}

void motion(int x, int y)
{
	if (mouseisdown == true)		//如果是鼠标左键按下拖动
	{
	rz += x - tx;					//偏移量记录
	rx += y - ty;				
	tx = x;							//更新坐标
	ty = y;
	glutPostRedisplay();
	}
}

void special(int key, int x, int y)
{
	//上下左右键盘控制xz坐标方向上的平移
	switch (key)
	{
	case GLUT_KEY_LEFT:
		mx += 0.2;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		mx -= 0.2;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		mz += 0.2;
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		mz -= 0.2;
		glutPostRedisplay();
		break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	//123改变自动移动方式
	//接收事件的时候改变坐标位置（使得满足作业要求）
	switch (key)
	{
	case '1':
		rx = ry = rz = 0;
		mx = mz = 0;
		mx = 5;
		state = 1;
		break;
	case '2':
		rx = ry = rz = 0;
		mx = mz = 0;
		state = 2;
		break;
	case '3':
		rx = ry = rz = 0;
		mx = mz = 0;
		mx = -5;
		state = 3;
		break;
	}
}

void setProjection(int width, int height)
{
	glViewport(0, 0, width, height);						// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);							// Select The Projection Matrix
	glLoadIdentity();										// Reset The Projection Matrix
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);								// Select The Modelview Matrix
	glLoadIdentity();										// Reset The Modelview Matrix
}

void reshape(int w1, int h1) {

	if (h1 == 0)
		h1 = 1;

	// we're keeping these values cause we'll need them latter
	w = w1;
	h = h1;

	// set subwindow 1 as the active window
	glutSetWindow(subWindow1);
	// resize and reposition the sub window
	glutPositionWindow(border, border);
	glutReshapeWindow(w - 2 * border, h / 2 - border * 3 / 2);
	setProjection(w - 2 * border, h / 2 - border * 3 / 2);

	// set subwindow 2 as the active window
	glutSetWindow(subWindow2);
	// resize and reposition the sub window
	glutPositionWindow(border, (h + border) / 2);
	glutReshapeWindow(w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);
	setProjection(w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);

	// set subwindow 3 as the active window
	glutSetWindow(subWindow3);
	// resize and reposition the sub window
	glutPositionWindow((w + border) / 2, (h + border) / 2);
	glutReshapeWindow(w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);
	setProjection(w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);
}
