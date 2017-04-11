// render.cpp : ���ƺ���
//@author Birdy&C 2017.4.7

#include "table.h"


AUX_RGBImageRec *LoadBMP(CHAR *Filename)    // ����λͼͼ��
{
	FILE *File = NULL;						// �ļ����
	int check;
	if (!Filename)							// ȷ���ļ������ṩ
	{
		return NULL;						// ���û�ṩ������ NULL
	}
	check = fopen_s(&File, Filename, "r");      // ���Դ��ļ�
	if (check == 0)								// �ļ�����
	{
		fclose(File);							// �رվ��
		return auxDIBImageLoadA(Filename);		// ����λͼ������ָ��
	}
	return NULL;								// �������ʧ�ܣ����� NULL
}

int LoadGLTextures()         // ����λͼ(��������Ĵ���)��ת��������
{
	int Status = FALSE;								// ״ָ̬ʾ��
	AUX_RGBImageRec *TextureImage[1];				// ��������Ĵ洢�ռ�
	memset(TextureImage, 0, sizeof(void *) * 1);	// ��ָ����Ϊ NULL
	TextureImage[0] = LoadBMP("wood.bmp");			// ����λͼ��������޴������λͼû�ҵ����˳�

	if (NULL != TextureImage[0])
	{
		Status = TRUE;								// �� Status ��Ϊ TRUE
		printf("LOAD SUCCESS\n");
		glGenTextures(1, &texture[0]);				// ��������

		glBindTexture(GL_TEXTURE_2D, texture[0]);	// ʹ������λͼ�������� �ĵ�������

		// ��������
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // �����˲�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // �����˲�
	}

	if (TextureImage[0])					// �����Ƿ����
	{
		if (TextureImage[0]->data)			// ����ͼ���Ƿ����
		{
			free(TextureImage[0]->data);    // �ͷ�����ͼ��ռ�õ��ڴ�
		}
		free(TextureImage[0]);				// �ͷ�ͼ��ṹ
	}
	return Status;							// ���� Status
}

void Draw_Leg() // This function draws a triangle with RGB colors
{
	//����
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 1.0f); 	glVertex3f(-0.5f, 0.5f, 0.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); 	glVertex3f(-0.5f, 0.5f, 3.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); 	glVertex3f(0.5f, 0.5f, 3.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); 	glVertex3f(0.5f, 0.5f, 0.0f); // ������ı��ε�����
	
	glTexCoord2f(1.0f, 1.0f); 	glVertex3f(-0.5f, -0.5f, 0.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); 	glVertex3f(0.5f, -0.5f, 0.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); 	glVertex3f(0.5f, -0.5f, 3.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); 	glVertex3f(-0.5f, -0.5f, 3.0f); // ������ı��ε�����
	
	glTexCoord2f(1.0f, 0.0f); 	glVertex3f(0.5f, -0.5f, 0.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(0.5f, 0.5f, 0.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.5f, 0.5f, 3.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); 	glVertex3f(0.5f, -0.5f, 3.0f); // ������ı��ε�����
		
	glTexCoord2f(0.0f, 0.0f); 	glVertex3f(-0.5f, 0.5f, 0.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); 	glVertex3f(-0.5f, -0.5f, 0.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); 	glVertex3f(-0.5f, -0.5f, 3.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-0.5f, 0.5f, 3.0f); // ������ı��ε�����
	
	//�ױ�
	glTexCoord2f(0.4f, 0.0f); glVertex3f(-0.5f, -0.5f, 0); // ������ı��ε�����
	glTexCoord2f(0.4f, 0.4f); glVertex3f(-0.5f, 0.5f, 0); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.4f); glVertex3f(0.5f, 0.5f, 0); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.4f); glVertex3f(0.5f, -0.5f, 0); // ������ı��ε�����

	glEnd();
}

void Draw_Table() // This function draws a triangle with RGB colors
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);			//����
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//ʵ��
	glBindTexture(GL_TEXTURE_2D, texture[0]);      // ѡ������
	//glColor3f(1.0f, 1.0f, 1.0f);						//ѡ����ɫ
	//����
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-2.5f, 2.0f, 4.0f);// ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(2.5f, 2.0f, 4.0f);// ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(2.5f, -2.0f, 4.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-2.5f, -2.0f, 4.0f);// ������ı��ε�����
	
	glTexCoord2f(1.0f, 0.0f); 	glVertex3f(-2.5f, -2.0f, 3.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(-2.5f, 2.0f, 3.0f);// ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); 	glVertex3f(2.5f, 2.0f, 3.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(2.5f, -2.0f, 3.0f); // ������ı��ε�����		


	//����
	glTexCoord2f(0.5f, 0.0f);	glVertex3f(2.5f, -2.0f, 4.0f); // ������ı��ε�����
	glTexCoord2f(0.5f, 1.0f);	glVertex3f(2.5f, 2.0f, 3.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(2.5f, -2.0f, 3.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(2.5f, 2.0f, 4.0f); // ������ı��ε�����
	
	glTexCoord2f(0.5f, 0.0f);	glVertex3f(-2.5f, 2.0f, 3.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); 	glVertex3f(-2.5f, -2.0f, 3.0f);// ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(-2.5f, -2.0f, 4.0f); // ������ı��ε�����
	glTexCoord2f(0.5f, 1.0f); 	glVertex3f(-2.5f, 2.0f, 4.0f); // ������ı��ε�����
	

	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-2.5f, 2.0f, 3.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.5f);	glVertex3f(-2.5f, 2.0f, 4.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.5f);	glVertex3f(2.5f, 2.0f, 4.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(2.5f, 2.0f, 3.0f); // ������ı��ε�����


	glTexCoord2f(1.0f, 0.5f);	glVertex3f(-2.5f, -2.0f, 3.0f);// ������ı��ε�����
	glTexCoord2f(0.0f, 0.5f);	glVertex3f(2.5f, -2.0f, 3.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(2.5f, -2.0f, 4.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-2.5f, -2.0f, 4.0f); // ������ı��ε�����
	
	
	
	glEnd();

	//��������
	glPushMatrix();
	glTranslatef(1.5f, 1.0f, 0.0f);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5f, -1.0f, 0.0f);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5f, 1.0f, 0.0f);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5f, -1.0f, 0.0f);
	Draw_Leg();
	glPopMatrix();


	glFlush();


}

void drawMain()
{
	glPushMatrix();

	if (loopr)
	{
		switch (state)
		{
		case 1:
			mz = 0.1 * time;
			state = 1;
			break;
		case 2:
			rx = 12 * time;
			break;
		case 3:
			glScalef(1 + 0.01*time, 1 + 0.01*time, 1 + 0.01*time);
			break;
		}
	}
	glTranslatef(mx, 0.0f, mz);		// ƽ��

	//��ת
	glRotatef(rx, 1, 0, 0);	
	glRotatef(ry, 0, 1, 0);
	glRotatef(rz, 0, 0, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �����Ļ����Ȼ���

	Draw_Table();						// Draw table	

	glPopMatrix();

}

// Display func for main window
void renderScene() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glutSwapBuffers();
	glutSetWindow(mainWindow);
	glClear(GL_COLOR_BUFFER_BIT);
	glutPostRedisplay();
}

// Display func for sub window 1
void renderScenesw1() {

	glutSetWindow(subWindow1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0, 15.0f, 0, 0, 0, 0, 0.0f, 0.0f, 1.0f);
	glPushMatrix();
	drawMain();
	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();

}

// Display func for sub window 2
void renderScenesw2() {

	glutSetWindow(subWindow2);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(15.0f, 0, 0, 0, 0, 0, 0.0f, 0.0f, 1.0f);
	glPushMatrix();
	drawMain();
	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();
}

// Display func for sub window 3
void renderScenesw3() {

	glutSetWindow(subWindow3);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 0, 15.0f, 0, 0, 0, 0, -1, 0);
	glPushMatrix();
	drawMain();
	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();

}

// Global render func
void renderSceneAll()
{
	renderScene();
	renderScenesw1();
	renderScenesw2();
	renderScenesw3();
}
