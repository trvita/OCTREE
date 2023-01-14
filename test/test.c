#include "octree.h"
#include <ctest.h>
#include <stdio.h>

CTEST(index_suite, right) {
  // Given
  const float tsize = 100;
  float origin[NUM_DIM] = {tsize / 2, tsize / 2, tsize / 2};
  octree *root = octree_create(origin, origin);
  float pos[NUM_DIM] = {10.0, 10.0, 10.0};
  unsigned num = 0;
  // When
  const int8_t result = child_index(root, pos, &num);
  // Then
  const int8_t expected = 0;
  ASSERT_EQUAL(expected, result);
}

CTEST(index_suite, wrong) {
  // Given
  const float tsize = 100;
  float origin[NUM_DIM] = {tsize / 2, tsize / 2, tsize / 2};
  octree *root = octree_create(origin, origin);
  float *pos = NULL;
  unsigned num = 0;
  // When
  const int8_t result = child_index(root, pos, &num);
  // Then
  const int8_t expected = 1;
  ASSERT_EQUAL(expected, result);
}

CTEST(index_suite, num_0) {
  // Given
  const float tsize = 100;
  float origin[NUM_DIM] = {tsize / 2, tsize / 2, tsize / 2};
  octree *root = octree_create(origin, origin);
  float pos[NUM_DIM] = {10.0, 10.0, 10.0};
  unsigned num = 0;
  child_index(root, pos, &num);
  // When
  const int8_t result = num;
  // Then
  const int8_t expected = 0;
  ASSERT_EQUAL(expected, result);
}
CTEST(index_suite, num_1) {
  // Given
  const float tsize = 100;
  float origin[NUM_DIM] = {tsize / 2, tsize / 2, tsize / 2};
  octree *root = octree_create(origin, origin);
  float pos[NUM_DIM] = {60.0, 10.0, 10.0};
  unsigned num = 0;
  child_index(root, pos, &num);
  // When
  const int8_t result = num;
  // Then
  const int8_t expected = 1;
  ASSERT_EQUAL(expected, result);
}
CTEST(index_suite, num_2) {
  // Given
  const float tsize = 100;
  float origin[NUM_DIM] = {tsize / 2, tsize / 2, tsize / 2};
  octree *root = octree_create(origin, origin);
  float pos[NUM_DIM] = {10.0, 60.0, 10.0};
  unsigned num = 0;
  child_index(root, pos, &num);
  // When
  const int8_t result = num;
  // Then
  const int8_t expected = 2;
  ASSERT_EQUAL(expected, result);
}
CTEST(index_suite, num_3) {
  // Given
  const float tsize = 100;
  float origin[NUM_DIM] = {tsize / 2, tsize / 2, tsize / 2};
  octree *root = octree_create(origin, origin);
  float pos[NUM_DIM] = {60.0, 60.0, 10.0};
  unsigned num = 0;
  child_index(root, pos, &num);
  // When
  const int8_t result = num;
  // Then
  const int8_t expected = 3;
  ASSERT_EQUAL(expected, result);
}
CTEST(index_suite, num_4) {
  // Given
  const float tsize = 100;
  float origin[NUM_DIM] = {tsize / 2, tsize / 2, tsize / 2};
  octree *root = octree_create(origin, origin);
  float pos[NUM_DIM] = {10.0, 10.0, 60.0};
  unsigned num = 0;
  child_index(root, pos, &num);
  // When
  const int8_t result = num;
  // Then
  const int8_t expected = 4;
  ASSERT_EQUAL(expected, result);
}
CTEST(index_suite, num_5) {
  // Given
  const float tsize = 100;
  float origin[NUM_DIM] = {tsize / 2, tsize / 2, tsize / 2};
  octree *root = octree_create(origin, origin);
  float pos[NUM_DIM] = {60.0, 10.0, 60.0};
  unsigned num = 0;
  child_index(root, pos, &num);
  // When
  const int8_t result = num;
  // Then
  const int8_t expected = 5;
  ASSERT_EQUAL(expected, result);
}
CTEST(index_suite, num_6) {
  // Given
  const float tsize = 100;
  float origin[NUM_DIM] = {tsize / 2, tsize / 2, tsize / 2};
  octree *root = octree_create(origin, origin);
  float pos[NUM_DIM] = {10.0, 60.0, 60.0};
  unsigned num = 0;
  child_index(root, pos, &num);
  // When
  const int8_t result = num;
  // Then
  const int8_t expected = 6;
  ASSERT_EQUAL(expected, result);
}
CTEST(index_suite, num_7) {
  // Given
  const float tsize = 100;
  float origin[NUM_DIM] = {tsize / 2, tsize / 2, tsize / 2};
  octree *root = octree_create(origin, origin);
  float pos[NUM_DIM] = {60.0, 60.0, 60.0};
  unsigned num = 0;
  child_index(root, pos, &num);
  // When
  const int8_t result = num;
  // Then
  const int8_t expected = 7;
  ASSERT_EQUAL(expected, result);
}