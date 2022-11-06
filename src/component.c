#define _GNU_SOURCE
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "resistance.h"

#include <stdio.h>


int cmpfloat(const void *_a, const void *_b)
{
  const float *a = _a;
  const float *b = _b;
  if (*a > *b) return -1;
  if (*a < *b) return 1;
  return 0;
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

  int i_idx, k_idx, m_idx;
  float best[3] = {-1, -1, -1};
  float best_diff = MAXFLOAT;

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
	float r[3] = {E12[i_idx] * i_scale, E12[k_idx] * k_scale, E12[m_idx] * m_scale};
	float test = calc_resistance(3, 'S', r);
	float diff = fabs(base - test);
	/* if (i_idx==11&&k_idx==11&&m_idx==11){ */
	/*   printf("{%f %f %f} ", r[0], r[1], r[2]); */
	/*   printf("[%g %g %g] ", i_scale, k_scale, m_scale); */
	/*   printf("> %f %f %f\n", test, diff, best_diff); */
	/* } */
	//	printf("test: %f, diff %f\n", test, diff);

	// Count number of resistors in r and best, fewer resisters is better
	int cnt_best = ((best[0] > 0)?1:0) + ((best[1] > 0)?1:0) + ((best[2] > 0)?1:0);
	int cnt_r = ((r[0] > 0)?1:0) + ((r[1] > 0)?1:0) + ((r[2] > 0)?1:0);

	// Count number of different values used, fewer different values is better

	qsort(r, 3, sizeof(r[0]), cmpfloat);
	if (cnt_r == 1) {
	  nbr_values_r = 1;
	} else if (cnt_r == 2) {
	  nbr_values_r = (r[0] == r[1]) ? 1 : 2;
	} else {
	  if (r[0] == r[1] && r[1] == r[2]) {
	    nbr_values_r = 3;
	  } else if (r[0] == r[1] || r[1] == r[2]) {
	    nbr_values_r = 2;
	  }
	}
	for (int i = 0; i < 3; i++) {
	  if (r[0] <= 0) break;
	  
	}
	if (diff < best_diff ||
	    (diff == best_diff && cnt_r < cnt_best) ||
	    (diff == best_diff && cnt_r == cnt_best && nbr_values_r < nbr_values_best)) {
	  best[0] = r[0];
	  best[1] = r[1];
	  best[2] = r[2];
	  best_diff = diff;
	}
      }
    }
  }
  printf("-- %f %f %f %f\n", best[0], best[1], best[2], best_diff);
  int count = 0;
  for (int i = 0; i < 3; i++) {
    if (best[i] > 0.0) {
      *res_array = best[i] * exp10f(exp);
      res_array++;
      count++;
    }
  }
  
  return count;
}
