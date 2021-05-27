#include "draw.h"
#include "model.h"
#include "callbacks.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>



float sizeOfField = 2000.0f; //MEgadjuk,hogy mekkora maga a mérete a mapnak
extern GLfloat light_ambient[4]; //Sima fényerõ szabályzás

double fieldWidth = 2000; //A pálya mérete
double fieldLength = 2000; //A pálya mérete
double fieldHeight = 500; //A pály mérete

GLfloat material_ambient_default[] = {0.9, 0.9, 0.9, 0.5};

void draw_content(World* world)
{
	Field roomToDraw = world -> field;
	glEnable(GL_TEXTURE_2D);

    glPushMatrix();
		draw_walls(roomToDraw);
		draw_ground(roomToDraw);
	glPopMatrix();



	draw_skulls(-1750, +1500, 0);
	draw_skulls(-1300, +1500, 0);
	draw_skulls(-800, +1500, 0);
	draw_skulls(-300, +1500, 0);
	draw_skulls(200, +1500, 0);
	draw_skulls(700, +1500, 0);
	draw_skulls(1200, +1500, 0);
	draw_skulls(1700, +1500, 0);


	draw_skulls(-1750, -1800, 180);
	draw_skulls(-1300, -1800, 180);
	draw_skulls(-800, -1800, 180);
	draw_skulls(-300, -1800, 180);
	draw_skulls(200, -1800, 180);
	draw_skulls(700, -1800, 180);
	draw_skulls(1200, -1800, 180);
	draw_skulls(1700, -1800, 180);



	glPushMatrix();
		glTranslatef(world->tanks[0].position.x, world->tanks[0].position.y, world->tanks[0].position.z);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world->tanks[0].material_ambient);

		glBindTexture(GL_TEXTURE_2D, world->tanks[0].texture);
		glScalef(80.0f, 80.0f, 80.0f);
		glRotatef(world->tanks[0].rotation, 0, 1, 0);

		draw_model(&world->tanks[0].model);
    glPopMatrix();

	glPushMatrix();
		glTranslatef(world->tanks[1].position.x, world->tanks[1].position.y, world->tanks[1].position.z);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world->tanks[1].material_ambient);

		glBindTexture(GL_TEXTURE_2D, world->tanks[1].texture);
		glScalef(80.0f, 80.0f, 80.0f);
		glRotatef(world->tanks[1].rotation, 0, 1, 0);

		draw_model(&world->tanks[1].model);
    glPopMatrix();


	if (move_tank_id != -1)
	{
		world->tanks[move_tank_id].position.x = camera.position.x;
		world->tanks[move_tank_id].position.z = camera.position.z;
	}
}



void draw_skulls(int moveX, int moveZ,int degree) {
	glPushMatrix();
		glTranslatef(world.skulls.position.x+moveX, world.skulls.position.y, world.skulls.position.z+moveZ);
		glRotatef(degree, 0, 1, 0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world.skulls.material_ambient);

		glBindTexture(GL_TEXTURE_2D, world.skulls.texture);
		glScalef(15.0f, 15.0f, 15.0f);
		glRotatef(180,0,90,90);

		draw_model(&world.skulls.model);
    glPopMatrix();
}



void draw_ground(Field field) {
	glBindTexture(GL_TEXTURE_2D, field.ground);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_QUADS);
	int x, z;
	float uvTile = 1.0f / (2.0f * sizeOfField / 50.0f);
	for (x = -sizeOfField; x < sizeOfField; x += 50.0f) {
		for (z = -sizeOfField; z < sizeOfField; z += 50.0f) {
			float uvX = x / sizeOfField / 2 + 0.5f;
			float uvY = z / sizeOfField / 2 + 0.5f;
			glTexCoord2f(uvX, uvY);
			glNormal3f(0, -1, 0);
			glVertex3f(x, 0, z);
			glTexCoord2f(uvX + uvTile, uvY);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 50, 0, z);
			glTexCoord2f(uvX + uvTile, uvY + uvTile);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 50, 0, z + 50);
			glTexCoord2f(uvX, uvY + uvTile);
			glNormal3f(0, -1, 0);
			glVertex3f(x, 0, z + 50);
		}
	}
	glEnd();
}



void draw_walls(Field field) {
	glBindTexture(GL_TEXTURE_2D, field.left);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-sizeOfField, 0, -sizeOfField);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-sizeOfField, sizeOfField, -sizeOfField);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-sizeOfField, sizeOfField, sizeOfField);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-sizeOfField, 0, sizeOfField);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, field.right);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sizeOfField, 0, sizeOfField);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sizeOfField, sizeOfField, sizeOfField);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sizeOfField, sizeOfField, -sizeOfField);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sizeOfField, 0, -sizeOfField);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, field.front);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-sizeOfField, 0, -sizeOfField);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sizeOfField, 0, -sizeOfField);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sizeOfField, sizeOfField, -sizeOfField);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-sizeOfField, sizeOfField, -sizeOfField);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, field.back);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-sizeOfField, 0, sizeOfField);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-sizeOfField, sizeOfField, sizeOfField);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sizeOfField, sizeOfField, sizeOfField);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sizeOfField, 0, sizeOfField);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, field.top);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sizeOfField, sizeOfField, sizeOfField);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sizeOfField, sizeOfField, -sizeOfField);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-sizeOfField, sizeOfField, -sizeOfField);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-sizeOfField, sizeOfField, sizeOfField);
	glEnd();
}



void draw_help(int texture) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);

	glTexCoord2f(1, 0);
	glVertex3f(WINDOW_WIDTH, 0, 0);

	glTexCoord2f(1, 1);
	glVertex3f(WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	glTexCoord2f(0, 1);
	glVertex3f(0, WINDOW_HEIGHT, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
