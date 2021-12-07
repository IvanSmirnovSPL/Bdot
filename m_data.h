//
// Created by iesm0 on 03.12.2021.
//

#ifndef BDOT_EXCHANGE_H
#define BDOT_EXCHANGE_H

#endif //BDOT_EXCHANGE_H

#include "bdot.h"
#include "imu_data.h"

/*struct rez
{
    f32 x, y, z;
    u64 tau;
};*/

/* Использую imu_data_get(imu_data_s* imu) из imu_data.h */
/* Возвращаю структуру rez - магнитный момент по 3 осям(x, y, z) и время действия(tau) */
void m_data_get(struct rez* magnMoment);


