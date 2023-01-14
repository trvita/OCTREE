#pragma once
#include "octree.h"
#include <stdio.h>

void gnuplot_cubes(octree *tree, FILE *file);
void gnuplot_points(octree *tree, FILE *file);
void gnuplot_file(octree *tree, const char *filename, char cubeorpoint);