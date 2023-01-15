/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-11     RT-Thread    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <stdio.h>
#include <string.h>
#include "drv_spi.h"
#include "CH395CMD.h"
#include "ch395.h"
#include "CH395INC.h"
#include "FTPINC.H"

#define CH395_INT_WIRE                                              rt_pin_read(45)

extern struct FTP ftp;
/**********************************************************************************/
/* CH395相关定义 */
const  rt_uint8_t CH395IPAddr[4]   = {192,168,1,10};                   /* CH395IP地址 */
const  rt_uint8_t CH395GWIPAddr[4] = {192,168,1,1};                  /* CH395网关 */
const  rt_uint8_t CH395IPMask[4]   = {255,255,255,0};                    /* CH395子网掩码 */
const  rt_uint8_t DestIPAddr[4]    = {192,168,1,100};                   /* 目的IP */
/* FTP相关定义 */
const  rt_uint8_t *pUserName = "anonymous";                              /* 匿名登陆 */
const  rt_uint8_t *pPassword = "123@";
char   ListName[24];                                                /* 用于保存目录名 */
char   ListMdk[24];                                                 /*用于保存新创建的目录名 */
char   FileName[24];                                                /*用于保存搜查文件的文件名  */
char   SourIP[17];                                                  /*用于保存转换成字符的IP地址 */

/***********************************************************************************
* Function Name  : main
* Description    : 主函数
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
void main( void )
{
  CH395_FTPConnect( );                                              /*进行TCP FTP控制连接*/
    while(1)
    {
        if(!CH395_INT_WIRE) CH395GlobalInterrupt();
    CH395_FTPClientCmd( );                                          /*查询状态执行相应命令*/
    }
}
