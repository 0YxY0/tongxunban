/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-17     yxyxi       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "CH395_SPI.h"
#include "drv_spi.h"

struct rt_spi_device* device;

static struct rt_spi_configuration ch395_config[] =
{
        CH395_CONFIG,
};

static char *               bus_name = "spi1";              /*设备需要挂载到的总线名称*/
static char *               name = "spi10";                 /*给flash设备的命名，一般为"spixx"，第一个x对应spi总线，第二个x对应总线上的第几个设备*/
static GPIO_TypeDef *       CS_GPIOX = GPIOA;               /*片选脚的端口*/
static uint16_t             CS_GPIO_PIN = GPIO_PIN_4;       /*片选引脚*/

static rt_err_t             flag;                           /*初始化标识*/

/**
 * \brief           绑定flash设备到总线并配置
 * \param[in]       flash: 要写入的spi_flash结构体指针,也即结构体数组flash的成员
 * \param[in]       cfg: 要写入的rt_spi_configuration结构体指针，也即结构体数组flash_config的成员
 * \return          绑定失败返回1；查找失败返回2；配置失败返回3；全部成功返回0
 */
static rt_err_t init(void) {
    rt_err_t res;

    res = rt_hw_spi_device_attach(bus_name, name, CS_GPIOX, CS_GPIO_PIN);           /*flash设备绑定到总线上*/
    if (res != RT_EOK) {
        return 1;
    }

    device = (struct rt_spi_device *)rt_device_find(name);                         /*查找Flash设备*/

    if (!device) {
        rt_kprintf("spi device run failed! can't find %s device!\n", name);
        return 2;
    }
    else {
        res = rt_spi_configure(device, ch395_config);                               /*配置总线*/
        if (res != RT_EOK) {
            return 3;
        }
    }

    flag = 1;

    return RT_EOK;
}

/*******************************************************************************
* Function Name  : xWriteCH395Cmd
* Description    : 向CH395写命令
* Input          : mCmd---将要写入CH395的命令码
* Output         : None
* Return         : None
*******************************************************************************/
void xWriteCH395Cmd(rt_uint8_t cmd)
{
    if(!flag) {
        init();
    }
    rt_spi_release(device);

    rt_spi_take(device);

    struct rt_spi_message message;
    message.send_buf   = &cmd;
    message.recv_buf   = RT_NULL;
    message.length     = 1;
    message.cs_take    = 0;
    message.cs_release = 0;
    message.next       = RT_NULL;

    rt_spi_transfer_message(device, &message);          /* 发送数据 */

    rt_hw_us_delay(2);
}

/*******************************************************************************
* Function Name  : xWriteCH395Data
* Description    : 向CH395写数据
* Input          : mData---将要写入CH395的数据
* Output         : None
* Return         : None
*******************************************************************************/
void xWriteCH395Data(rt_uint8_t data)
{
    if(!flag) {
        init();
    }

    struct rt_spi_message message;
    message.send_buf   = &data;
    message.recv_buf   = RT_NULL;
    message.length     = 1;
    message.cs_take    = 0;
    message.cs_release = 0;
    message.next       = RT_NULL;

    rt_spi_transfer_message(device, &message);          /* 发送数据 */

}

/*******************************************************************************
* Function Name  : xReadCH395Data
* Description    : 从CH395读数据
* Input          : None
* Output         : None
* Return         : 返回读取的数据
*******************************************************************************/
rt_uint8_t xReadCH395Data(void)
{
    if(!flag) {
        init();
    }
    rt_uint8_t recv;

    struct rt_spi_message message;
    message.send_buf   = RT_NULL;
    message.recv_buf   = &recv;
    message.length     = 1;
    message.cs_take    = 0;
    message.cs_release = 0;
    message.next       = RT_NULL;

    rt_spi_transfer_message(device, &message);          /* 接收数据 */

    return recv;
}

/*******************************************************************************
* Function Name  : xReadCH395Data
* Description    : 从CH395读数据
* Input          : None
* Output         : None
* Return         : 返回读取的数据
*******************************************************************************/
void xEndCH395Cmd(void)
{
    if(!flag) {
        init();
    }

    rt_spi_release(device);
}
