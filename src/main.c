#include "func.h"
#include "octree.h"
#include <time.h>
int main() {
  const float tsize = 400;
  float origin[NUM_DIM] = {tsize / 2, tsize / 2, tsize / 2};

  const size_t num_points = 100;
  size_t i;
  srand(time(NULL));

  octree *root = octree_create(origin, origin);

  float position[NUM_DIM];

  for (i = 0; i < num_points; i++) {
    position[AXIS_X] = rand() % (int)tsize;
    position[AXIS_Y] = rand() % (int)tsize;
    position[AXIS_Z] = rand() % (int)tsize;
    octree_insert(root, position);
  }

  octree_print(root);
  gnuplot_file(root, "src/dat/data.dat", 'c');
  gnuplot_file(root, "src/dat/points.dat", 'p');

  octree_free(root);

  return 0;
}