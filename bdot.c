//
// Created by iesm0 on 01.12.2021.
//
#include <stdio.h>
#include <math.h>
#include "bdot.h"

/* show named vector*/
void show_item(char* name, double* array, size_t n_a)
{
    printf("\n%s: ", name);
    int i;
    for (i = 0; i < n_a; i++)
    {
        printf("%f ", array[i]);
    }
}

/*calculate weight average of vector*/
void weighted_moving_average(const double* array, size_t n_a, double* rez, size_t n_r)
{
    size_t tmp = n_a / n_r;
    double total_weight = 1. * tmp * (tmp + 1) / 2;
    int i, j;
    for (j = 0; j < n_r; j++){rez[j] = 0.;}
    for (i = 0; i < tmp; i++)
    {
        for (j = 0; j < n_r; j++){rez[j] += (i + 1) * array[j + n_r * i];}
    }
    for (i = 0; i < n_r; i++){rez[i] /= total_weight;}
}

/*calculate average value of vector*/
void average(const double* array, size_t n_a, double* rez, size_t n_r)
{
    int i, j;
    for (j = 0; j < n_r; j++){rez[j] = 0.;}
    size_t tmp = n_a / n_r;
    for (i = 0; i < tmp; i++)
    {
        for (j = 0; j < n_r; j++){rez[j] += array[j + n_r * i];}
    }
    for (i = 0; i < n_r; i++){rez[i] /= tmp;}
}

/*calculate standard deviation from mean value*/
void determine_deviation(const double* array, size_t n_a, const double* mean, size_t n_m, double* rez, size_t n_r)
{
    int i, j;
    for (j = 0; j < n_r; j++){rez[j] = 0.;}
    size_t tmp = n_a / n_r;
    for (i = 0; i < tmp; i++)
    {
        for (j = 0; j < n_r; j++){rez[j] += (array[j + n_r * i] - mean[j]) * (array[j + n_r * i] - mean[j]);}
    }
    for (i = 0; i < n_r; i++){rez[i] = sqrt(rez[i]);}
}

/*calculate  cross product a x b*/
void cross_product(const double* a, size_t n_a, const double* b, size_t n_b,  double* rez, size_t n_r)
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
void derivative (const double* a, size_t n_a, const double* b, size_t n_b, const double step, double* rez, size_t n_r)
{
    if (n_a == 3 && n_b == 3 && n_r == 3)
    {
        if (step != 0)
        {
            int j;
            for (j = 0; j < n_r; j++){rez[j] = (a[j] - b[j]) / step;}
        }
        else
        {
            printf("\nCheck step in derivative: step = %f, it must be non-zero\n", step);
        }
    }
    else
    {
        printf("\nCheck dimensions of vectors in derivative: n_a = %zu, n_b = %zu, n_r = %zu, they must be 3\n", n_a, n_b, n_r);
    }
}


void calculate_magnetic_moment(double* b, size_t n_b, double* w, size_t n_w, double time, double* m, size_t n_m, double* tau)
{
    *tau = 0.1;
    double b_avg[3], w_avg[3];
    weighted_moving_average(b, n_b, b_avg, 3);
    show_item("B_avg", b_avg, 3);
    weighted_moving_average(w, n_w, w_avg, 3);
    show_item("w_avg", w_avg, 3);
    cross_product(w_avg, 3, b_avg, 3,  m, n_m);
    show_item("m", m, 3);

}