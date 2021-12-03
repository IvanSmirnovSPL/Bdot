//
// Created by iesm0 on 03.12.2021.
//

#include "m_data.h"
#include "bdot.h"


void m_data_get(struct rez* magnMoment)
{
    imu_data_s imu;
    imu_data_get(&imu);
    u16 t = ABS(imu.time[1] - imu.time[0]);
    u64 n_b = SIZE_OF_IMU_VECTOR * 3;
    f32 b[n_b], w[n_b];
    s16 i;
    for (i = 0; i < SIZE_OF_IMU_VECTOR; i++)
    {
        b[i] = imu.magn[i].x; b[i + 1] = imu.magn[i].y; b[i + 2] = imu.magn[i].z;
        w[i] = imu.gyro[i].x; w[i + 1] = imu.gyro[i].y; w[i + 2] = imu.gyro[i].z;
    }
    calculate_magnetic_moment(b, n_b, w, n_b, t, magnMoment);
}
