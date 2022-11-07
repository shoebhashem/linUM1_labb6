#define _GNU_SOURCE
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>

#include "resistance.h"

#define MAX_NBR_COMP 3


int cmpfloat(const void *_a, const void *_b)
{
  const float *a = _a;
  const float *b = _b;
  if (*a > *b) return -1;
  if (*a < *b) return 1;
  return 0;
}

void sort_components_low_to_high(float *r)
{
  // Simpler to always work with a sorted list of components

  qsort(r, MAX_NBR_COMP, sizeof(r[0]), cmpfloat);
}


int count_nbr_components(const float *r)
{
  // Count number of resistors in r, fewer resistors is better

  int nbr_components = 0;
  for (int i = 0; i < MAX_NBR_COMP; i++) {
    if (r[i] <= 0) {
      break;
    }
    nbr_components++;
  }
  return nbr_components;
}


int count_nbr_values(const float *r)
{
  // Count number of different values used, fewer different values is better

  int nbr_values = 1;
  for (int i = 1; i < MAX_NBR_COMP; i++) {
    if (r[i] <= 0) {
      break;
    }
    if (r[i-1] != r[i]) {
      nbr_values++;
    }
  }
  return nbr_values;
}


int e_resistance(float orig_resistance, float *res_array)
{
  float E12[] = {8.2, 6.8, 5.6, 4.7, 3.9, 3.3, 2.7, 2.2, 1.8, 1.5, 1.2, 1.0};
  int nbr_e12 = sizeof(E12) / sizeof(E12[0]);
  int nbr_test = nbr_e12 * 4;

  float exp = floor(logf(orig_resistance) / logf(10));
  float base = orig_resistance / exp10f(exp);

  assert(base >= 1.0);
  assert(base < 10.0);

  int idx_max_value = -1;
  for (int i = 0; i < nbr_e12; i++) {
    if (E12[i] <= base) {
      idx_max_value = i;
      break;
    }
  }

  float best[MAX_NBR_COMP] = {-1, -1, -1};
  float best_diff = MAXFLOAT;
  int best_nbr_values = INT_MAX;
  int best_nbr_components = INT_MAX;

  float i_scale = 1.0;
  for (int i = 0, i_idx = idx_max_value; i < nbr_test; i++, i_idx++) {
    if (i_idx == nbr_e12) {
      i_idx = 0;
      i_scale = i_scale / 10.0;
    }
    if (i == nbr_test-1) {
      i_scale = 0;
    }
    float k_scale = 1.0;
    for (int k = 0, k_idx = idx_max_value; k < nbr_test; k++, k_idx++) {
      if (k_idx == nbr_e12) {
	k_idx = 0;
	k_scale = k_scale / 10.0;
      }
      if (k == nbr_test-1) {
	k_scale = 0;
      }
      float m_scale = 1.0;
      for (int m = 0, m_idx = idx_max_value; m < nbr_test; m++, m_idx++) {
	if (m_idx == nbr_e12) {
	  m_idx = 0;
	  m_scale = m_scale / 10.0;
	}
	if (m == nbr_test-1) {
	  m_scale = 0;
	}
	float r[MAX_NBR_COMP] = {E12[i_idx] * i_scale, E12[k_idx] * k_scale, E12[m_idx] * m_scale};
	float test = calc_resistance(MAX_NBR_COMP, 'S', r);
	float diff = fabs(base - test);

	sort_components_low_to_high(r);

	int nbr_components = count_nbr_components(r);

	int nbr_values = count_nbr_values(r);

	if (diff < best_diff ||
	    (diff == best_diff && nbr_components < best_nbr_components) ||
	    (diff == best_diff && nbr_components == best_nbr_components && nbr_values < best_nbr_values)) {
	  for (int i = 0; i < MAX_NBR_COMP; i++) {
	    best[i] = r[i];
	  }
	  best_diff = diff;
	  best_nbr_values = nbr_values;
	  best_nbr_components = nbr_components;
	}
      }
    }
  }

  int count = 0;
  for (int i = 0; i < MAX_NBR_COMP; i++) {
    if (best[i] <= 0.0) {
      break;
    }

    *res_array = best[i] * exp10f(exp);
    res_array++;
    count++;
  }
  
  return count;
}
