/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-17     yxyxi       the first version
 */
#ifndef DRIVERS_INCLUDE_CH395_SPI_H_
#define DRIVERS_INCLUDE_CH395_SPI_H_

#define CH395_INT_WIRE              rt_pin_read(45)                            /* CH395的INT#引脚 */

#ifndef CH395_CONFIG
#define CH395_CONFIG                                                \
    {                                                               \
        .data_width = 8,                                            \
        .mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB,         \
        .max_hz = 30 * 1000 *1000                                   \
    }
#endif /* CH395_CONFIG */

void xWriteCH395Cmd(rt_uint8_t);
void xWriteCH395Data(rt_uint8_t);
rt_uint8_t xReadCH395Data(void);
void xEndCH395Cmd(void);

#endif /* DRIVERS_INCLUDE_CH395_SPI_H_ */
