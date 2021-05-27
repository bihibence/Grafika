#ifndef INCLUDE_DRAW_H_
#define INCLUDE_DRAW_H_

#include "model.h"

#ifndef GL_EXT_texture_edge_clamp
#define GL_CLAMP_TO_EDGE                 0x812F
#endif


// Draw the content.
void draw_content(World* world);

// Draws the ground.
void draw_ground(Field field);

// Draws the room.
void draw_walls(Field field);

// Draws the help menu
void draw_help(int texture);

// Draw the Skulls
void draw_skulls(int moveX, int moveZ,int degree);

// Draws the Tanks
void draw_tanks(int moveX, int moveZ,int degree);

#endif /* INCLUDE_DRAW_H_ */
