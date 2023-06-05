#pragma once

#define GLFW_INCLUDE_NONE
#include <C:\Users\33651\OneDrive\Bureau\Lescours\Open Gl\Proj\third_party\glfw\include\GLFW\glfw3.h>

// Needed before including GL/glu.h 
// to avoid a compilation error because of CALLBACK pre-processor definition.
// See https://stackoverflow.com/questions/19198244/how-do-i-get-rid-of-these-compiler-errors-in-glu-h#comment28407913_19198244
// It's usually defined in a system header to define the default calling convention for callbacks, 
// but if it is defined incorrectly this sort of thing happens.
// windef.h usually defines it is __stdcall
#if defined(_WIN64) || defined(_WIN32)
    #include <windef.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

// important to add this line to use M_PI
#define _USE_MATH_DEFINES
#include <math.h>

#define NB_SEG_CIRCLE 64

/* Camera parameters and functions */
static const float Z_NEAR = 0.1f;
static const float Z_FAR = 100.f;
extern float theta;      // Angle between x axis and viewpoint
extern float phy  ;      // Angle between z axis and viewpoint
extern float dist_zoom ; // Distance between origin and viewpoint

void setCamera();

/* Draw cannonic objet functions */
void drawSquare();

void drawCircle();

void drawCone();

void drawSphere();

/* Small tools */
float toRad(float deg);
