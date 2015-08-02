#ifndef _PIXELX_PARTICLE_H
#define _PIXELX_PARTICLE_H

#include "PxVertex.h"

struct PxParticle
{
  float t;       /* Life time */
  float v;       /* Speed */
  float d;       /* Particle direction */
  float x, y, z; /* Particle Coordinates */
  float xd, zd;  /* X and Z increase values */
  char type;     /* type (moving or fading) */
  float a;       /* Fade alpha */
  struct PxParticle *next, *prev;
};

typedef PxVertex PxPoint;

#define PI 3.14159f
#define GRAVITY_ACCL 9.8

#endif