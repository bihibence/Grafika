#include "model.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "callbacks.h"
#include <obj/load.h>
#include <obj/draw.h>



void init_object(Object* object, int x, int z, int y)
{
	object->position.x = x;
	object->position.y = y;
	object->position.z = z;

	object->material_ambient[0] = 0.75;
	object->material_ambient[1] = 0.75;
	object->material_ambient[2] = 0.75;
	object->material_ambient[3] = 0.5;
}


GLuint load_texture(const char* filename) {
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	GLuint texture_name;
	Pixel* image;
	glGenTextures(1, &texture_name);

	int width;
	int height;

	image = (Pixel*)SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);

	glBindTexture(GL_TEXTURE_2D, texture_name);
	gluBuild2DMipmaps(GL_TEXTURE_2D,3,width,height,GL_RGBA,GL_UNSIGNED_BYTE,(Pixel*)image);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	return texture_name;
}

void init_entities(World* world) {
	move_tank_id = -1;

	//Tanks:
	load_model(&world->tanks[0].model, "data/models/tank.obj");
	world->tanks[0].texture = load_texture("data/textures/tank.jpg");
	init_object(&world->tanks[0], 1500, -100, 0);
	world->tanks[0].rotation = 270.0f; //forgatás

	world->tanks[1].model = world->tanks[0].model;
	world->tanks[1].texture = world->tanks[0].texture;
	init_object(&world->tanks[1], -1500, 80, 0);
	world->tanks[1].rotation = 90.0f;

	// Skulls:
	load_model(&world->skulls.model, "data/models/Skull.obj");
	world->skulls.texture = load_texture("data/textures/skull.jpg"); //Tesz rá egy textúrát
	init_object(&world->skulls, -120, 170, 2);

	// Battlefield:
	world->field.ground = load_texture("data/textures/ground.jpg");
	world->field.top = load_texture("data/textures/top.jpg");
	world->field.back = load_texture("data/textures/wall.jpg");
	world->field.front = world->field.back;
	world->field.left = world->field.back;
	world->field.right = world->field.back;

	// Help:
	world->helpTexture = load_texture("data/textures/help.png");
}
