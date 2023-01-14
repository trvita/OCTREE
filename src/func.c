#include "func.h"
void gnuplot_cubes(octree *tree, FILE *out) {
  if (tree && !tree->leaf) {
    size_t i;
    fprintf(out, "%.2f %.2f %.2f %.2f %.2f %.2f\n",
            tree->center[AXIS_X] - tree->size[AXIS_X],
            tree->center[AXIS_X] + tree->size[AXIS_X],
            tree->center[AXIS_Y] - tree->size[AXIS_Y],
            tree->center[AXIS_Y] + tree->size[AXIS_Y],
            tree->center[AXIS_Z] - tree->size[AXIS_Z],
            tree->center[AXIS_Z] + tree->size[AXIS_Z]);
    for (i = 0; i < NUM_NODES; i++) {
      gnuplot_cubes(tree->child[i], out);
    }
  }
}
void gnuplot_points(octree *tree, FILE *out) {
  size_t i;
  if (tree) {
    for (i = 0; i < tree->points_num; i++) {
      fprintf(out, "%.2f %.2f %.2f\n",
              tree->points_coordinates[i * NUM_DIM + AXIS_X],
              tree->points_coordinates[i * NUM_DIM + AXIS_Y],
              tree->points_coordinates[i * NUM_DIM + AXIS_Z]);
    }
    for (i = 0; i < NUM_NODES; i++) {
      gnuplot_points(tree->child[i], out);
    }
  }
}
void gnuplot_file(octree *tree, const char *filename, char cubeorpoint) {

  FILE *out;
  if ((out = fopen(filename, "w")) == NULL) {
    printf("Error: %s file opening went wrong\n", filename);
    return;
  }
  if (cubeorpoint == 'c') {
    gnuplot_cubes(tree, out);
  } else if (cubeorpoint == 'p')
    gnuplot_points(tree, out);
  else
    printf("Wrong option entered. Nothing changed.\n");
  fclose(out);
}