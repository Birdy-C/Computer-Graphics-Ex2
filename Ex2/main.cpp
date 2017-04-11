// main.cpp : �������̨Ӧ�ó������ڵ㡣
//@author Birdy&C 2017.4.7

#include "table.h"

//�Ӵ���
int mainWindow, subWindow1, subWindow2, subWindow3;
//��ת��¼
int rx = 0;
int ry = 0;
int rz = 0;
//ƽ�Ƽ�¼
float mx = 0;
float mz = 0;
//���λ��
int tx, ty;
//�߽���
const int border = 6;
//�����ڴ�С
int w, h;
//�Զ��¼�����
bool mouseisdown = false;
bool loopr = false;
int state = 1;
int time = 0;
//�洢����
GLuint  texture[1]; 



//��ʼ��
void init()
{
	//������Ʋ���

	//glCullFace(GL_BACK);				//����ü�(���治�ɼ�)
	//glEnable(GL_CULL_FACE);			//���òü�
	glEnable(GL_DEPTH_TEST);			//��Ȳ���
	glEnable(GL_TEXTURE_2D);
	LoadGLTextures();					//����������ͼ


	//�¼�������
	glutIgnoreKeyRepeat(0);				//ȷ���Ƿ�����Զ�����������
	glutMouseFunc(mouse);				//������¼�
	glutMotionFunc(motion);				//����϶��¼�
	glutKeyboardFunc(keyboard);			//�����¼�
	glutSpecialFunc(special);			//������� û��ASCIIֵ ����������


	//���տ��Ʋ���
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
	LoadGLTextures();            //����������ͼ

	glutDisplayFunc(renderSceneAll);
	glutReshapeFunc(reshape);
	init();


	//�Ӵ��ڽ���
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


