#include "octree.h"

octree *octree_create(float *at, float *size) {
  octree *tree = (octree *)malloc(sizeof(octree));
  if (tree) {
    memset(tree, 0, sizeof(octree));
    memcpy(tree->center, at, NUM_DIM * sizeof(float));
    memcpy(tree->size, size, NUM_DIM * sizeof(float));
    tree->points_num = 0;
    tree->leaf = true;
    return tree;
  } else
    free(tree);
  return NULL;
}

int8_t child_index(octree *tree, float *position, unsigned *out) {
  if ((tree && position && out) &&
      (fabs(position[AXIS_X] - tree->center[AXIS_X]) <= tree->size[AXIS_X]) &&
      (fabs(position[AXIS_Y] - tree->center[AXIS_Y]) <= tree->size[AXIS_Y]) &&
      (fabs(position[AXIS_Z] - tree->center[AXIS_Z]) <= tree->size[AXIS_Z])) {
    bool cx = position[AXIS_X] > tree->center[AXIS_X];
    bool cy = position[AXIS_Y] > tree->center[AXIS_Y];
    bool cz = position[AXIS_Z] > tree->center[AXIS_Z];

    unsigned mask = (cx << AXIS_X) | (cy << AXIS_Y) | (cz << AXIS_Z);
    *out = mask;
    return 0;
  }
  return 1;
}

int8_t octree_lookup(octree *tree, float *position, octree **out) {
  if (tree && position && out) {
    *out = NULL;
    unsigned mask = 0;
    if (!child_index(tree, position, &mask)) {
      if (tree->leaf) {
        *out = tree;
        return 0;
      }
      return octree_lookup(tree->child[mask], position, out);
    }
  }
  return 1;
}

int8_t octree_delete(octree *tree, float *position) {
  octree *t = NULL;
  size_t i;
  if (tree && position && (!octree_lookup(tree, position, &t))) {
    if (t->points_num > 1) {
      for (i = 0; i < t->points_num; i++) {
        if ((t->points_coordinates[i * NUM_DIM + AXIS_X] == position[AXIS_X]) &&
            (t->points_coordinates[i * NUM_DIM + AXIS_Y] == position[AXIS_Y]) &&
            (t->points_coordinates[i * NUM_DIM + AXIS_Z] == position[AXIS_Z])) {
          t->points_coordinates[i * NUM_DIM + AXIS_X] =
              t->points_coordinates[t->points_num - AXIS_Z];
          t->points_coordinates[i * NUM_DIM + AXIS_Y] =
              t->points_coordinates[t->points_num - AXIS_Y];
          t->points_coordinates[i * NUM_DIM + AXIS_Z] =
              t->points_coordinates[t->points_num - AXIS_X];
          t->points_num--;
          return 0;
        }
      }
    } else
      t->points_num--;
    t->leaf = true;
    return 0;
  } else
    return 1;
}

int8_t octree_insert(octree *tree, float *position) {
  if (tree && position) {

    unsigned mask = 0;
    if (!child_index(tree, position, &mask)) {

      if (tree->leaf && (tree->points_num + 1 < NUM_LIMIT)) {
        memcpy(tree->points_coordinates + NUM_DIM * tree->points_num, position,
               NUM_DIM * sizeof(float));
        tree->points_num++;
        return 0;
      }

      if (tree->leaf && (!octree_divide(tree))) {
        tree->leaf = false;
        for (size_t i = 0; i < tree->points_num; i++) {
          octree_insert(tree, tree->points_coordinates + NUM_DIM * i);
        }
        memset(tree->points_coordinates, 0,
               NUM_LIMIT * NUM_DIM * sizeof(float));
        tree->points_num = 0;
      }

      octree *child = tree->child[mask];
      octree_insert(child, position);

      return 0;
    }
  }
  return 1;
}
int8_t octree_divide(octree *tree) {
  const float half = 0.5;
  const float nhalf = -0.5;

  for (size_t i = 0; i < NUM_NODES; i++) {
    float sign_x = (i & (1 << AXIS_X)) ? (half) : (nhalf);
    float sign_y = (i & (1 << AXIS_Y)) ? (half) : (nhalf);
    float sign_z = (i & (1 << AXIS_Z)) ? (half) : (nhalf);

    float x = tree->center[AXIS_X] + (sign_x * tree->size[AXIS_X]);
    float y = tree->center[AXIS_Y] + (sign_y * tree->size[AXIS_Y]);
    float z = tree->center[AXIS_Z] + (sign_z * tree->size[AXIS_Z]);

    float origin[NUM_DIM] = {x, y, z};
    float size[NUM_DIM] = {half * tree->size[AXIS_X], half * tree->size[AXIS_Y],
                           half * tree->size[AXIS_Z]};
    octree *t = octree_create(origin, size);
    if (t) {
      tree->child[i] = t;
    } else
      printf("division went wrond\n");
  }
  return 0;
}
void octree_print(octree *tree) {
  size_t i = 0;
  if ((tree->leaf == true) /*&& (tree->points_num != 0)*/) {
    printf("\033[31m\ncenter - %.2f %.2f %.2f, size - %.2f %.2f %.2f\033[37m\n",
           tree->center[AXIS_X], tree->center[AXIS_Y], tree->center[AXIS_Z],
           tree->size[AXIS_X], tree->size[AXIS_Y], tree->size[AXIS_Z]);
    for (i = 0; i < tree->points_num; i++) {
      printf("p%ld - %.2f %.2f %.2f\n", i,
             tree->points_coordinates[i * NUM_DIM + AXIS_X],
             tree->points_coordinates[i * NUM_DIM + AXIS_Y],
             tree->points_coordinates[i * NUM_DIM + AXIS_Z]);
    }
  } else {
    for (i = 0; i < NUM_NODES - 4; i++)
      octree_print(tree->child[i]);
    for (i = 4; i < NUM_NODES; i++) {
      octree_print(tree->child[i]);
    }
  }
}
void octree_free(octree *tree) {
  size_t i = 0;
  if (tree) {
    for (i = 0; i < NUM_NODES; i++) {
      octree_free(tree->child[i]);
    }
    free(tree);
  }
}