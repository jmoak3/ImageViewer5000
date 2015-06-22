#ifndef MESHLOAD_H
#define MESHLOAD_H

#include "3DMath.h"

int LoadMesh(char * fileName, int ** pindices, Vector3 ** ppoints, int *numInds, int *numPts);

#endif