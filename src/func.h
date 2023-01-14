#pragma once
#include "octree.h"
#include <stdio.h>

void swap(float *p1, float *p2);
void gnuplot_cubes(octree *tree, FILE *file);
void gnuplot_points(octree *tree, FILE *file);
void gnuplot_file(octree *tree, const char *filename, char cubeorpoint);