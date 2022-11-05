/*
 * Lexx Damm
 */

#include "libresistance.h"

float calc_resistance(int count, char conn, float* array)
{
    float res = 0;
    int i = 0;

    if (array == NULL || count < 1)
        return -1;

    switch (conn) {
        case 'P':
            for (i; i < count; i++) {
                res = res + 1 / array[i];
            }
            res = 1 / res;
            break;
        case 'S':
            for (i; i < count; i++) {
                res = res + array[i];
            }
            break;
        default:
            return -1;
    }

    return res;
}
