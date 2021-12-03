//
// Created by iesm0 on 01.12.2021.
//

#ifndef BDOT_BDOT_H
#define BDOT_BDOT_H

#endif //BDOT_BDOT_H

#include "globdefs.h"

/* "b" is magnetic field (format - 1D array type [b1_x, b1_y, b1_z, b2_x, b2_y, b2_z, ...])*/
/* "n_b" is size of "b" array*/
/* "w" is angular velocity (format - 1D array type [w1_x, w1_y, w1_z, w2_x, w2_y, w2_z, ...])*/
/* "n_w" is size of "w" array*/
/* "time" is time of measuring values(mainly magnetic field "b"), [time] = m_sec*/
/* "m" is magnetic moment (format - 1D array type [m_x, m_y, m_z]) <- return parameter*/
/* "n_m" is size of "m" array (it is 3)*/
/* "tau" is duration of action magnetic torque, [tau] = m_sec <- return parameter*/
void calculate_magnetic_moment(f32* b, s16 n_b, f32* w, s16 n_w, u64 time, f32* m, s16 n_m, u64* tau);