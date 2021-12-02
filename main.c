#include <stdio.h>
#include "bdot.h"

int main() {
    double time = 0.1, tau;
    double b[9] = {0, 0, 1, 0, 0, 1, 0, 0, 1};
    double w[6] = {0, 1, 0, 0, 1, 0};
    double m[3];
    calculate_magnetic_moment(b, 9, w, 6, time, m, 3, &tau);
    int i;
    printf("\nMagnetic moment: ");
    for (i = 0; i < 3; i++)
    {
        printf("%f ", m[i]);
    }
    printf("\ntau: %f", tau);
    return 0;
}
