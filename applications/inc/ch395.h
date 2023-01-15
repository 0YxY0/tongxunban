/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     yxyxi       the first version
 */
#ifndef APPLICATIONS_INC_CH395_H_
#define APPLICATIONS_INC_CH395_H_

/* TCP模式，0为客户端，1为服务器 */
#define TCP_CLIENT_MODE                                      0
#define TCP_SERVER_MODE                                      1

struct _CH395_SYS
{
    rt_uint8_t   IPAddr[4];                                           /* CH395IP地址 32bit*/
    rt_uint8_t   GWIPAddr[4];                                         /* CH395网关地址 32bit*/
    rt_uint8_t   MASKAddr[4];                                         /* CH395子网掩码 32bit*/
    rt_uint8_t   MacAddr[6];                                          /* CH395MAC地址 48bit*/
    rt_uint8_t   PHYStat;                                             /* CH395 PHY状态码 8bit*/
    rt_uint8_t   MackFilt;                                            /* CH395 MAC过滤，默认为接收广播，接收本机MAC 8bit*/
    rt_uint32_t  RetranCount;                                         /* 重试次数 默认为10次*/
    rt_uint32_t  RetranPeriod;                                        /* 重试周期,单位MS,默认200MS */
    rt_uint8_t   IntfMode;                                            /* 接口模式 */
    rt_uint8_t   UnreachIPAddr[4];                                    /* 不可到达IP */
    rt_uint16_t  UnreachPort;                                         /* 不可到达端口 */
};

struct _SOCK_INF
{
    rt_uint8_t  IPAddr[4];                                           /* socket目标IP地址 32bit*/
    rt_uint8_t  MacAddr[6];                                          /* socket目标地址 48bit*/
    rt_uint8_t  ProtoType;                                           /* 协议类型 */
    rt_uint8_t  ScokStatus;                                          /* socket状态，参考scoket状态定义 */
    rt_uint8_t  TcpMode;                                             /* TCP模式 */
    rt_uint32_t IPRAWProtoType;                                      /* IPRAW 协议类型 */
    rt_uint16_t DesPort;                                             /* 目的端口 */
    rt_uint16_t SourPort;                                            /* 目的端口 */
    rt_uint16_t SendLen;                                             /* 发送数据长度 */
    rt_uint16_t RemLen;                                              /* 剩余长度 */
    rt_uint8_t  *pSend;                                              /* 发送指针 */
};

/* CH395相关定义 */
extern const rt_uint8_t CH395MACAddr[6];
extern const rt_uint8_t CH395IPAddr[4];                              /* CH395IP地址 */
extern const rt_uint8_t CH395GWIPAddr[4];                            /* CH395网关 */
extern const rt_uint8_t CH395IPMask[4];                              /* CH395子网掩码 */
extern const rt_uint8_t DestIPAddr[4];                               /* 目的IP */


void CH395GlobalInterrupt(void);

void CH395SocketInitOpen( );

void mDelaymS(rt_uint8_t ms);

#endif /* APPLICATIONS_INC_CH395_H_ */
