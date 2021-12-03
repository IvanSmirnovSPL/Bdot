#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "globdefs.h"
#include "bdot.h"



f32 rand_0_1(void)
{
    return rand() / ((double) RAND_MAX);
}

f32 random_range(f32 min, f32 max)
{
    return min + rand_0_1() * (max - min);
}

int main() {
    struct min_max
    {
        f32 min, max;
    };
    struct min_max b_[3], w_[3];
    b_[0].min = -0.45; b_[0].max = -0.55; b_[1].min = 1.1; b_[1].max = 1.2; b_[2].min = 0.6; b_[2].max = 0.7;
    w_[0].min = 100; w_[0].max = 120; w_[1].min = 50; w_[1].max = 80; w_[2].min = -10; w_[2].max = -5;
    u64 t = 300, tau;
    f32 b[99];
    f32 w[99];
    s16 i, j;
    srand(time(0));
    for (i = 0; i < 99 / 3; i++)
    {
        for(j = 0; j < 3; j++){b[i * 3 + j] = random_range(b_[j].min, b_[j].max);}
        for(j = 0; j < 3; j++){w[i * 3 + j] = random_range(w_[j].min, w_[j].max);}
    }
    f32 m[3];
    calculate_magnetic_moment(b, 99, w, 99, t, m, 3, &tau);
    printf("\nMagnetic moment: ");
    for (i = 0; i < 3; i++)
    {
        printf("%f ", m[i]);
    }
    printf("\ntau: %llu", tau);
    return 0;
}
