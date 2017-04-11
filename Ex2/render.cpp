// render.cpp : 绘制函数
//@author Birdy&C 2017.4.7

#include "table.h"


AUX_RGBImageRec *LoadBMP(CHAR *Filename)    // 载入位图图象
{
	FILE *File = NULL;						// 文件句柄
	int check;
	if (!Filename)							// 确保文件名已提供
	{
		return NULL;						// 如果没提供，返回 NULL
	}
	check = fopen_s(&File, Filename, "r");      // 尝试打开文件
	if (check == 0)								// 文件存在
	{
		fclose(File);							// 关闭句柄
		return auxDIBImageLoadA(Filename);		// 载入位图并返回指针
	}
	return NULL;								// 如果载入失败，返回 NULL
}

int LoadGLTextures()         // 载入位图(调用上面的代码)并转换成纹理
{
	int Status = FALSE;								// 状态指示器
	AUX_RGBImageRec *TextureImage[1];				// 创建纹理的存储空间
	memset(TextureImage, 0, sizeof(void *) * 1);	// 将指针设为 NULL
	TextureImage[0] = LoadBMP("wood.bmp");			// 载入位图，检查有无错误，如果位图没找到则退出

	if (NULL != TextureImage[0])
	{
		Status = TRUE;								// 将 Status 设为 TRUE
		printf("LOAD SUCCESS\n");
		glGenTextures(1, &texture[0]);				// 创建纹理

		glBindTexture(GL_TEXTURE_2D, texture[0]);	// 使用来自位图数据生成 的典型纹理

		// 生成纹理
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 线形滤波
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 线形滤波
	}

	if (TextureImage[0])					// 纹理是否存在
	{
		if (TextureImage[0]->data)			// 纹理图像是否存在
		{
			free(TextureImage[0]->data);    // 释放纹理图像占用的内存
		}
		free(TextureImage[0]);				// 释放图像结构
	}
	return Status;							// 返回 Status
}

void Draw_Leg() // This function draws a triangle with RGB colors
{
	//四面
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 1.0f); 	glVertex3f(-0.5f, 0.5f, 0.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); 	glVertex3f(-0.5f, 0.5f, 3.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); 	glVertex3f(0.5f, 0.5f, 3.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); 	glVertex3f(0.5f, 0.5f, 0.0f); // 纹理和四边形的右上
	
	glTexCoord2f(1.0f, 1.0f); 	glVertex3f(-0.5f, -0.5f, 0.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); 	glVertex3f(0.5f, -0.5f, 0.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); 	glVertex3f(0.5f, -0.5f, 3.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); 	glVertex3f(-0.5f, -0.5f, 3.0f); // 纹理和四边形的右下
	
	glTexCoord2f(1.0f, 0.0f); 	glVertex3f(0.5f, -0.5f, 0.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(0.5f, 0.5f, 0.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.5f, 0.5f, 3.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); 	glVertex3f(0.5f, -0.5f, 3.0f); // 纹理和四边形的左下
		
	glTexCoord2f(0.0f, 0.0f); 	glVertex3f(-0.5f, 0.5f, 0.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); 	glVertex3f(-0.5f, -0.5f, 0.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); 	glVertex3f(-0.5f, -0.5f, 3.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-0.5f, 0.5f, 3.0f); // 纹理和四边形的左上
	
	//底边
	glTexCoord2f(0.4f, 0.0f); glVertex3f(-0.5f, -0.5f, 0); // 纹理和四边形的右下
	glTexCoord2f(0.4f, 0.4f); glVertex3f(-0.5f, 0.5f, 0); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 0.4f); glVertex3f(0.5f, 0.5f, 0); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.4f); glVertex3f(0.5f, -0.5f, 0); // 纹理和四边形的左下

	glEnd();
}

void Draw_Table() // This function draws a triangle with RGB colors
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);			//空心
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//实心
	glBindTexture(GL_TEXTURE_2D, texture[0]);      // 选择纹理
	//glColor3f(1.0f, 1.0f, 1.0f);						//选择颜色
	//上下
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-2.5f, 2.0f, 4.0f);// 纹理和四边形的左上
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(2.5f, 2.0f, 4.0f);// 纹理和四边形的右上
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(2.5f, -2.0f, 4.0f); // 纹理和四边形的右下
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-2.5f, -2.0f, 4.0f);// 纹理和四边形的左下
	
	glTexCoord2f(1.0f, 0.0f); 	glVertex3f(-2.5f, -2.0f, 3.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(-2.5f, 2.0f, 3.0f);// 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); 	glVertex3f(2.5f, 2.0f, 3.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(2.5f, -2.0f, 3.0f); // 纹理和四边形的左下		


	//四面
	glTexCoord2f(0.5f, 0.0f);	glVertex3f(2.5f, -2.0f, 4.0f); // 纹理和四边形的左下
	glTexCoord2f(0.5f, 1.0f);	glVertex3f(2.5f, 2.0f, 3.0f); // 纹理和四边形的右下
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(2.5f, -2.0f, 3.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(2.5f, 2.0f, 4.0f); // 纹理和四边形的左上
	
	glTexCoord2f(0.5f, 0.0f);	glVertex3f(-2.5f, 2.0f, 3.0f); // 纹理和四边形的左上
	glTexCoord2f(1.0f, 0.0f); 	glVertex3f(-2.5f, -2.0f, 3.0f);// 纹理和四边形的左下
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(-2.5f, -2.0f, 4.0f); // 纹理和四边形的右下
	glTexCoord2f(0.5f, 1.0f); 	glVertex3f(-2.5f, 2.0f, 4.0f); // 纹理和四边形的右上
	

	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-2.5f, 2.0f, 3.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.5f);	glVertex3f(-2.5f, 2.0f, 4.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.5f);	glVertex3f(2.5f, 2.0f, 4.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(2.5f, 2.0f, 3.0f); // 纹理和四边形的右上


	glTexCoord2f(1.0f, 0.5f);	glVertex3f(-2.5f, -2.0f, 3.0f);// 纹理和四边形的右上
	glTexCoord2f(0.0f, 0.5f);	glVertex3f(2.5f, -2.0f, 3.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(2.5f, -2.0f, 4.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-2.5f, -2.0f, 4.0f); // 纹理和四边形的右下
	
	
	
	glEnd();

	//画桌子腿
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
	glTranslatef(mx, 0.0f, mz);		// 平移

	//旋转
	glRotatef(rx, 1, 0, 0);	
	glRotatef(ry, 0, 1, 0);
	glRotatef(rz, 0, 0, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除屏幕和深度缓存

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
