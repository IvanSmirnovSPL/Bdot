//
// Created by iesm0 on 01.12.2021.
//
#include <stdio.h>
#include <math.h>
#include "bdot.h"

struct config_values
{
    f32 m_max[3], tolerance, angle, speed;
    u64 work_time , work_time_b_dot;
};

/* show named vector*/
void show_item(char* name, f32* array, s16 n_a)
{
    printf("\n%s: ", name);
    s64 i;
    for (i = 0; i < n_a; i++)
    {
        printf("%f ", array[i]);
    }
}

/*calculate weight average of vector*/
void weighted_moving_average(const f32* array, s16 n_a, f32* rez, s16 n_r)
{
    s16 tmp = n_a / n_r;
    f32 total_weight = 1. * tmp * (tmp + 1) / 2;
    s64 i, j;
    for (j = 0; j < n_r; j++){rez[j] = 0.;}
    for (i = 0; i < tmp; i++)
    {
        for (j = 0; j < n_r; j++){rez[j] += (i + 1) * array[j + n_r * i];}
    }
    for (i = 0; i < n_r; i++){rez[i] /= total_weight;}
}

/*calculate average value of vector*/
void average(const f32* array, s16 n_a, f32* rez, s16 n_r)
{
    s64 i, j;
    for (j = 0; j < n_r; j++){rez[j] = 0.;}
    s16 tmp = n_a / n_r;
    for (i = 0; i < tmp; i++)
    {
        for (j = 0; j < n_r; j++){rez[j] += array[j + n_r * i];}
    }
    for (i = 0; i < n_r; i++){rez[i] /= tmp;}
}

/*calculate standard deviation from mean value*/
void determine_deviation(const f32 *array, s16 n_a, const f32 *mean, f32 *rez, s16 n_r)
{
    s64 i, j;
    for (j = 0; j < n_r; j++){rez[j] = 0.;}
    s16 tmp = n_a / n_r;
    for (i = 0; i < tmp; i++)
    {
        for (j = 0; j < n_r; j++){rez[j] += (array[j + n_r * i] - mean[j]) * (array[j + n_r * i] - mean[j]);}
    }
    for (i = 0; i < n_r; i++){rez[i] = sqrt(rez[i]);}
}

/*calculate  cross product a x b*/
void cross_product(const f32* a, s16 n_a, const f32* b, s16 n_b,  f32* rez, s16 n_r)
{
    if (n_a == 3 && n_b == 3 && n_r == 3)
    {
        rez[0] = a[1] * b[2] - a[2] * b[1];
        rez[1] = a[2] * b[0] - a[0] * b[2];
        rez[2] = a[0] * b[1] - a[1] * b[0];
    }
    else
    {
        printf("\nCheck dimensions of vectors in cross_product: n_a = %zu, n_b = %zu, n_r = %zu, they must be 3\n", n_a, n_b, n_r);
    }
}

/*calculate derivative of vector from two values in step distance*/
void derivative (const f32* a, s16 n_a, const f32* b, s16 n_b, const u64 step, f32* rez, s16 n_r)
{
    if (n_a == 3 && n_b == 3 && n_r == 3)
    {
        if (step != 0)
        {
            s64 j;
            for (j = 0; j < n_r; j++){rez[j] = (a[j] - b[j]) / step;}
        }
        else
        {
            printf("\nCheck step in derivative: step = %llu, it must be non-zero\n", step);
        }
    }
    else
    {
        printf("\nCheck dimensions of vectors in derivative: n_a = %zu, n_b = %zu, n_r = %zu, they must be 3\n", n_a, n_b, n_r);
    }
}

/* convert angle value from degree to radian */
void deg_to_rad(f32* w, s16 n_w)
{
    f32 M_PI = 3.14159265358979323846;
    s64 i;
    for (i = 0; i < n_w; i++){w[i] = w[i] * (M_PI / 180.0);}
}


/* scaling magnetic moment */
void scaling(f32 *m, s16 n_m, f32 *m_max)
{
    s64 i;
    f32 k[3] = {0, 0, 0}, K, tmp;
    for (i = 0; i < n_m; i++)
    {
        if (m[i] != 0)
        {
            k[i] = (m_max[i] / m[i]) > 0 ? (m_max[i] / m[i]) : - (m_max[i] / m[i]);
        }
    }
    if (k[0] > k[1]) { tmp = k[0]; k[0] = k[1]; k[1] = tmp; }
    if (k[0] > k[2]) { tmp = k[0]; k[0] = k[2]; k[2] = tmp; }
    if (k[1] > k[2]) { tmp = k[1]; k[1] = k[2]; k[2] = tmp; }

    K = k[0] > 0 ? k[0] : (k[1] > 0 ? k[1] : k[2]);
    for (i = 0; i < n_m; i++){m[i] *= K;}
}

/*if angular velocity sensor doesn't work*/
void b_dot_from_field_only(f32* b, s16 n_b, u64 step, struct config_values conf, f32* rez, s16 n_r, u64* tau)
{
    s16 tmp = (n_b / 3) / 2;
    s16 center = tmp * 3;
    f32 vec1[3], vec2[3];
    weighted_moving_average(b, center, vec1, 3);
    weighted_moving_average(b + center, n_b - center, vec2, 3);
    derivative (vec2, 3, vec1, 3, step * 500, rez, n_r);
    scaling(rez, 3, conf.m_max);
    *tau = conf.work_time_b_dot;
}

void m_from_b_and_w (f32* b, s16 n_b, f32* w, s16 n_w, struct config_values conf, f32* rez, s16 n_r, u64* tau)
{
    s16 i;
    f32 b_avg[3], w_avg[3], tmp = 0;
    weighted_moving_average(b, n_b, b_avg, n_r);
    weighted_moving_average(w, n_w, w_avg, n_r); for (i = 0; i < n_r; i++){tmp += w_avg[i] * w_avg[i];}
    //show_item("b_avg", b_avg, 3);
    cross_product(w_avg, n_r, b_avg, n_r,  rez, n_r);
    scaling(rez, n_r, conf.m_max);
    *tau = sqrt(tmp) < conf.speed ? conf.work_time : conf.angle * 1000 / sqrt(tmp);
}

void sum(f32* a, s16 n_a, f32* rez)
{
    s16 i;
    *rez = 0;
    for (i = 0; i < n_a; i++){*rez += a[i];}
}

void calculate_magnetic_moment(f32* b, s16 n_b, f32* w, s16 n_w, u64 time, f32* m, s16 n_m, u64* tau)
{
    struct config_values conf;
    conf.m_max[0] = 0.5; conf.m_max[1] = 0.5; conf.m_max[2] = 0.2;
    conf.angle = 3.14159265358979323846 / 6;
    conf.tolerance = 5;
    conf.speed = 5;
    conf.work_time = 900; conf.work_time_b_dot = 300;

    f32  w_avg[3], sigma[3], sigma_total;

    deg_to_rad(w, n_w);
    average(w, n_w, w_avg, n_m);
    determine_deviation(w, n_w, w_avg, sigma, n_m);  sum(sigma, n_m, &sigma_total);
    if (sigma_total < conf.tolerance)
    {
        m_from_b_and_w (b, n_b, w, n_w, conf, m, n_m, tau);
    }
    else
    {
        b_dot_from_field_only(b, n_b, time, conf, m, n_m, tau);
    }
}