#pragma once
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum {
  NUM_NODES = 8,
  NUM_DIM = 3,
  NUM_LIMIT = 4,
  AXIS_X = 0,
  AXIS_Y = 1,
  AXIS_Z = 2
};

typedef struct octree {
  struct octree *child[NUM_NODES];
  bool leaf;
  float center[NUM_DIM];
  float size[NUM_DIM];
  float points_coordinates[NUM_LIMIT * NUM_DIM];
  size_t points_num;
} octree;

octree *octree_create(float *at, float *size);
int8_t child_index(octree *tree, float *position, unsigned *out);
int8_t octree_divide(octree *tree);
int8_t octree_insert(octree *tree, float *position);
int8_t octree_lookup(octree *tree, float *position, octree **out);
int8_t octree_delete(octree *tree, float *position);
void octree_print(octree *tree);
void octree_free(octree *tree);
