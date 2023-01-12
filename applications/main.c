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

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#define CH395_INT_WIRE              rt_pin_read(45)

/* 常用变量定义 */
rt_uint8_t  MyBuffer[4096];                                             /* 数据缓冲区 */
struct _SOCK_INF  SockInf;                                         /* 保存Socket信息 */
struct _CH395_SYS  CH395Inf;                                       /* 保存CH395信息 */

/* CH395相关定义 */
//const rt_uint8_t CH395MACAddr[6] = {0x02,0x03,0x04,0x05,0x06,0x07};   /* CH395MAC地址 */
const rt_uint8_t CH395IPAddr[4] = {192,168,1,10};                       /* CH395IP地址 */
const rt_uint8_t CH395GWIPAddr[4] = {192,168,1,1};                      /* CH395网关 */
const rt_uint8_t CH395IPMask[4] = {255,255,255,0};                      /* CH395子网掩码 */

/* socket 相关定义*/
//const rt_uint8_t  Socket0DesIP[4] = {192,168,1,100};                    /* Socket 0目的IP地址 */
const rt_uint16_t Socket0SourPort = 5000;                               /* Socket 0源端口 */

/**********************************************************************************
* Function Name  : mStopIfError
* Description    : 调试使用，显示错误代码，并停机
* Input          : iError
* Output         : None
* Return         : None
**********************************************************************************/
void mStopIfError(rt_uint8_t iError)
{
    if (iError == CMD_ERR_SUCCESS) return;                           /* 操作成功 */
    printf("Error: %02X\n", (rt_uint16_t)iError);                         /* 显示错误 */
    while ( 1 )
    {
        rt_thread_mdelay(200);
        rt_thread_mdelay(200);
    }
}

/**********************************************************************************
* Function Name  : InitCH395InfParam
* Description    : 初始化CH395Inf参数
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
void InitCH395InfParam(void)
{
    memset(&CH395Inf,0,sizeof(CH395Inf));                            /* 将CH395Inf全部清零*/
    memcpy(CH395Inf.IPAddr,CH395IPAddr,sizeof(CH395IPAddr));         /* 将IP地址写入CH395Inf中 */
    memcpy(CH395Inf.GWIPAddr,CH395GWIPAddr,sizeof(CH395GWIPAddr));   /* 将网关IP地址写入CH395Inf中 */
    memcpy(CH395Inf.MASKAddr,CH395IPMask,sizeof(CH395IPMask));       /* 将子网掩码写入CH395Inf中 */
//  memcpy(CH395Inf.MacAddr,CH395MACAddr,sizeof(CH395MACAddr));
}

/**********************************************************************************
* Function Name  : InitSocketParam
* Description    : 初始化socket
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
void InitSocketParam(void)
{
    memset(&SockInf,0,sizeof(SockInf));                              /* 将SockInf[0]全部清零*/
//    memcpy(SockInf.IPAddr,Socket0DesIP,sizeof(Socket0DesIP));        /* 将目的IP地址写入 */
    SockInf.SourPort = Socket0SourPort;                              /* 源端口 */
    SockInf.ProtoType = PROTO_TYPE_TCP;                              /* TCP模式 */
    SockInf.TcpMode = TCP_SERVER_MODE;
}

/**********************************************************************************
* Function Name  : CH395SocketInitOpen
* Description    : 配置CH395 socket 参数，初始化并打开socket
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
void CH395SocketInitOpen(void)
{
    rt_uint8_t i;

    /* socket 0为TCP 服务器模式 */
//    CH395SetSocketDesIP(0,SockInf.IPAddr);                           /* 设置socket 0目标IP地址 */
    CH395SetSocketProtType(0,SockInf.ProtoType);                     /* 设置socket 0协议类型 */
//    CH395SetSocketDesPort(0,SockInf.DesPort);                        /* 设置socket 0目的端口 */
    CH395SetSocketSourPort(0,SockInf.SourPort);                      /* 设置socket 0源端口 */
    i = CH395OpenSocket(0);                                          /* 打开socket 0 */
    mStopIfError(i);                                                 /* 检查是否成功 */
    i = CH395TCPListen(0);                                           /* TCP连接 */
    mStopIfError(i);                                                 /* 检查是否成功 */
}

/**********************************************************************************
* Function Name  : CH395SocketInterrupt
* Description    : CH395 socket 中断,在全局中断中被调用
* Input          : sockindex
* Output         : None
* Return         : None
**********************************************************************************/
void CH395SocketInterrupt(rt_uint8_t sockindex)
{
   rt_uint8_t  sock_int_socket;
   rt_uint16_t len;
   rt_uint16_t tmp;
   rt_uint8_t  buf[10];

   sock_int_socket = CH395GetSocketInt(sockindex);                   /* 获取socket 的中断状态 */
   if(sock_int_socket & SINT_STAT_SENBUF_FREE)                       /* 发送缓冲区空闲，可以继续写入要发送的数据 */
   {
       if(SockInf.SendLen >= SockInf.RemLen)SockInf.RemLen = 0;      /* 数据已经发送完毕 */
       else
       {
            SockInf.pSend += SockInf.SendLen;                        /* 对发送指针进行偏移 */
            SockInf.RemLen -= SockInf.SendLen;                       /* 计算剩余长度 */
            if(SockInf.RemLen > 2048)SockInf.SendLen = 2048;         /* 计算本次可以发送的数据长度 */
            else SockInf.SendLen = SockInf.RemLen;
            CH395SendData(sockindex,SockInf.pSend,SockInf.SendLen);  /* 发送数据 */
       }
   }
   if(sock_int_socket & SINT_STAT_SEND_OK)                           /* 发送完成中断 */
   {
   }
   if(sock_int_socket & SINT_STAT_RECV)                              /* 接收中断 */
   {
       len = CH395GetRecvLength(sockindex);                          /* 获取当前缓冲区内数据长度 */
       printf("receive len = %d\n",len);
       if(len == 0)return;
       if(SockInf.RemLen != 0)return;                                /* 如果数据未发送完毕，则不再接收 */
       CH395GetRecvData(sockindex,len,MyBuffer);                     /* 读取数据 */
       SockInf.RemLen = len;                                         /* 保存长度 */
       if(len > 2048)len = 2048;                                     /* 发送缓冲区最大为2048 */
       CH395SendData(sockindex,MyBuffer,len);
       SockInf.SendLen = len;                                        /* 保存发送的长度 */
       SockInf.pSend = MyBuffer;                                     /* 发送换取区指针 */
   }
   if(sock_int_socket & SINT_STAT_CONNECT)                          /* 连接中断，仅在TCP模式下有效*/
   {
       printf("SINT_STAT_CONNECT\n");
       if(SockInf.TcpMode == TCP_SERVER_MODE)                       /* 如果socket 为服务器模式，用户可以获取远端的IP和端口*/
       {
         CH395CMDGetRemoteIPP(sockindex,buf);
         printf("IP address = %d.%d.%d.%d\n",(rt_uint16_t)buf[0],(rt_uint16_t)buf[1],(rt_uint16_t)buf[2],(rt_uint16_t)buf[3]);
         tmp = (rt_uint16_t)(buf[5]<<8) + buf[4];
         printf("Port = %d\n",tmp);
       }
   }
   if(sock_int_socket & SINT_STAT_DISCONNECT)                        /* 断开中断，仅在TCP模式下有效 */
   {
      printf("SINT_STAT_DISCONNECT \n");
   }
   if(sock_int_socket & SINT_STAT_TIM_OUT)                           /* 超时中断，仅在TCP模式下有效 */
   {
       printf("SINT_STAT_TIM_OUT\n");
   }
}

/**********************************************************************************
* Function Name  : CH395GlobalInterrupt
* Description    : CH395全局中断函数
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
void CH395GlobalInterrupt(void)
{
   rt_uint16_t  init_status;
   rt_uint8_t  buf[10];

    init_status = CH395CMDGetGlobIntStatus_ALL();
    if(init_status & GINT_STAT_UNREACH)                              /* 不可达中断，读取不可达信息 */
    {
        CH395CMDGetUnreachIPPT(buf);
    }
    if(init_status & GINT_STAT_IP_CONFLI)                            /* 产生IP冲突中断，建议重新修改CH395的 IP，并初始化CH395*/
    {
    }
    if(init_status & GINT_STAT_PHY_CHANGE)                           /* 产生PHY改变中断*/
    {

        printf("Init status : GINT_STAT_PHY_CHANGE\n");

      }
    if(init_status & GINT_STAT_SOCK0)
    {
        CH395SocketInterrupt(0);                                     /* 处理socket 0中断*/
    }
    if(init_status & GINT_STAT_SOCK1)
    {
        CH395SocketInterrupt(1);                                     /* 处理socket 1中断*/
    }
    if(init_status & GINT_STAT_SOCK2)
    {
        CH395SocketInterrupt(2);                                     /* 处理socket 2中断*/
    }
    if(init_status & GINT_STAT_SOCK3)
    {
        CH395SocketInterrupt(3);                                     /* 处理socket 3中断*/
    }
    if(init_status & GINT_STAT_SOCK4)
    {
        CH395SocketInterrupt(4);                                     /* 处理socket 4中断*/
    }
    if(init_status & GINT_STAT_SOCK5)
    {
        CH395SocketInterrupt(5);                                     /* 处理socket 5中断*/
    }
    if(init_status & GINT_STAT_SOCK6)
    {
        CH395SocketInterrupt(6);                                     /* 处理socket 6中断*/
    }
    if(init_status & GINT_STAT_SOCK7)
    {
        CH395SocketInterrupt(7);                                     /* 处理socket 7中断*/
    }
}

/**********************************************************************************
* Function Name  : CH395Init
* Description    : 配置CH395的IP,GWIP,MAC等参数，并初始化
* Input          : None
* Output         : None
* Return         : 函数执行结果
**********************************************************************************/
rt_uint8_t  CH395Init(void)
{
    rt_uint8_t i;

    i = CH395CMDCheckExist(0x65);
    if(i != 0x9a)return CH395_ERR_UNKNOW;                            /* 测试命令，如果无法通过返回0XFA */
                                                                     /* 返回0XFA一般为硬件错误或者读写时序不对 */
#if (CH395_OP_INTERFACE_MODE == 5)
#ifdef UART_WORK_BAUDRATE
    CH395CMDSetUartBaudRate(UART_WORK_BAUDRATE);                     /* 设置波特率 */
    rt_thread_mdelay(10);
    Set_MCU_BaudRate();
    i = xReadCH395Data();                                            /* 如果设置成功，CH395返回CMD_ERR_SUCCESS */
    if(i == CMD_ERR_SUCCESS)printf("Set Success\n");
#endif
#endif
    CH395CMDSetIPAddr(CH395Inf.IPAddr);                              /* 设置CH395的IP地址 */
//  CH395CMDSetMACAddr(CH395Inf.MacAddr);                            /* 设置CH395的MAC地址 */
    CH395CMDSetGWIPAddr(CH395Inf.GWIPAddr);                          /* 设置网关地址 */
    CH395CMDSetMASKAddr(CH395Inf.MASKAddr);                          /* 设置子网掩码，默认为255.255.255.0*/
    i = CH395CMDInitCH395();                                         /* 初始化CH395芯片 */
    return i;
}

/**********************************************************************************
* Function Name  : TCP-Server
* Description    : TCP服务端测试函数
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
int tcp_server (void)
{
    rt_uint8_t i;
    CH395CMDReset();                                                /* 不加这句，就会失败 */
    rt_thread_mdelay(200);
    printf("CH395EVT Test Demo\n");
    i = CH395CMDGetVer();
    printf("CH395VER : %2x\n",(rt_uint16_t)i);
    InitCH395InfParam();                                             /* 初始化CH395相关变量 */
    i = CH395Init();                                                 /* 初始化CH395芯片 */
    mStopIfError(i);
    while(1)
    {                                                                /* 等待以太网连接成功*/
       if(CH395CMDGetPHYStatus() == PHY_DISCONN)                     /* 查询CH395是否连接 */
       {
           rt_thread_mdelay(200);                                            /* 未连接则等待200MS后再次查询 */
       }
       else
       {
           printf("CH395 Connect Ethernet\n");                       /* CH395芯片连接到以太网，此时会产生中断 */
           break;
       }
    }
    InitSocketParam();                                               /* 初始化socket相关变量 */
    CH395SocketInitOpen();
    while(1)
    {
      if(!CH395_INT_WIRE)CH395GlobalInterrupt();
    }
}
MSH_CMD_EXPORT(tcp_server, tcp server test);

int main(void)
{
    rt_pin_mode(24, PIN_MODE_OUTPUT);
    rt_pin_mode(45, PIN_MODE_INPUT);

    rt_pin_write(24, 0);

    int i = 0;

    while(i < 5) {
        rt_pin_write(24, 1);
        rt_thread_mdelay(500);

        rt_pin_write(24, 0);
        rt_thread_mdelay(500);

        i++;
    }

    return RT_EOK;
}
