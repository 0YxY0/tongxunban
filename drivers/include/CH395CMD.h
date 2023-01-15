/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-17     yxyxi       the first version
 */
#ifndef DRIVERS_INCLUDE_CH395CMD_H_
#define DRIVERS_INCLUDE_CONFIG_CH395CMD_H_

void CH395CMDReset(void);                                                           /* 复位 */

void CH395CMDSleep(void);                                                           /* 睡眠 */

rt_uint8_t CH395CMDGetVer(void);                                                    /* 获取芯片及固件版本号 */

rt_uint8_t CH395CMDCheckExist(rt_uint8_t testdata);                                 /* 测试命令 */

void CH395CMDSetPHY(rt_uint8_t phystat);                                            /* 设置PHY状态  */

rt_uint8_t CH395CMDGetPHYStatus(void);                                              /* 获取PHY状态 */

rt_uint8_t CH395CMDGetGlobIntStatus(void);                                          /* 获取CH395全局中断状态 */

rt_uint8_t CH395CMDInitCH395(void);                                                 /* 初始化CH395 */

void CH395CMDSetUartBaudRate(rt_uint32_t baudrate);                                 /* 设置波特率 */

rt_uint8_t CH395GetCmdStatus(void);                                                 /* 获取命令执行状态 */

void CH395CMDSetIPAddr(rt_uint8_t *ipaddr);                                         /* 设置CH395的IP地址 */

void CH395CMDSetGWIPAddr(rt_uint8_t *gwipaddr);                                     /* 设置CH395的网关IP地址 */

void CH395CMDSetMASKAddr(rt_uint8_t *maskaddr);                                     /* 设置子网掩码 */

void CH395CMDSetMACAddr(rt_uint8_t *amcaddr);                                       /* 设置CH395的MAC地址 */

void CH395CMDGetMACAddr(rt_uint8_t *amcaddr);                                       /* 获取MAC地址 */

void CH395CMDSetMACFilt(rt_uint8_t filtype,rt_uint32_t table0,rt_uint32_t table1);  /* 设置CH395的MAC过滤 */

void CH395CMDGetUnreachIPPT(rt_uint8_t *list);                                      /* 获取不可达地址以及端口 */

void CH395CMDGetRemoteIPP(rt_uint8_t sockindex,rt_uint8_t *list);                   /* 获取远端IP和端口，一般在TCP Server下使用 */

void CH395SetSocketDesIP(rt_uint8_t sockindex,rt_uint8_t *ipaddr);                  /* 设置scoket n的目的IP地址 */

void CH395SetSocketProtType(rt_uint8_t sockindex,rt_uint8_t prottype);              /* 设置socket n的协议类型 */

void CH395SetSocketDesPort(rt_uint8_t sockindex,rt_uint16_t desprot);               /* 设置socket n的目的端口 */

void CH395SetSocketSourPort(rt_uint8_t sockindex,rt_uint16_t surprot);              /* 设置socket n的源端口 */

void CH395SetSocketIPRAWProto(rt_uint8_t sockindex,rt_uint8_t prototype);           /* 在IPRAW模式下，设置socket n的IP包协议字段 */

void CH395SetRecvThresLen(rt_uint8_t sockindex,rt_uint16_t len);                    /* 设置socket n的接收中断阀值 */

void CH395SendData(rt_uint8_t sockindex,char *databuf,rt_uint16_t len);       /* 向socket n的发送缓冲区写数据 */

rt_uint16_t CH395GetRecvLength(rt_uint8_t sockindex);                               /* 获取socket n的接收长度 */

void CH395ClearRecvBuf(rt_uint8_t sockindex);                                       /* 清除socket n的接收缓冲区 */

void CH395GetRecvData(rt_uint8_t sockindex,rt_uint16_t len,rt_uint8_t *pbuf);       /* 获取接收数据 */

void CH395CMDSetRetryCount(rt_uint8_t count);                                       /* 设置最大重试次数 */

void CH395CMDSetRetryPeriod(rt_uint16_t period);                                    /* 设置最大重试周期 单位 毫秒*/

void CH395CMDGetSocketStatus(rt_uint8_t sockindex,rt_uint8_t *status) ;             /* 获取socket n的状态 */

rt_uint8_t  CH395OpenSocket(rt_uint8_t sockindex);                                  /* 打开socket n*/

rt_uint8_t  CH395CloseSocket(rt_uint8_t sockindex);                                 /* 关闭socket n*/

rt_uint8_t CH395TCPConnect(rt_uint8_t sockindex);                                   /* TCP连接 */

rt_uint8_t CH395TCPListen(rt_uint8_t sockindex);                                    /* TCP监听 */

rt_uint8_t CH395TCPDisconnect(rt_uint8_t sockindex);                                /* TCP断开连接 */

rt_uint8_t CH395GetSocketInt(rt_uint8_t sockindex);                                 /* 获取socket n的中断状态 */

rt_uint8_t CH395CRCRet6Bit(rt_uint8_t *mac_addr);                                   /* 多播地址CRC32，用于HASH过滤 */
                                                                                    /*Function Count = 36 */
void CH395GetIPInf(rt_uint8_t *addr);

rt_uint8_t  CH395DHCPEnable(rt_uint8_t flag);

rt_uint8_t CH395GetDHCPStatus(void);                                                /*CH395GetDHCPStatus*/

void CH395WriteGPIOAddr(rt_uint8_t regadd,rt_uint8_t regval);

rt_uint8_t CH395ReadGPIOAddr(rt_uint8_t regadd);

rt_uint8_t CH395EEPROMErase(void);

rt_uint8_t CH395EEPROMWrite(rt_uint16_t eepaddr,rt_uint8_t *buf,rt_uint8_t len);

void CH395EEPROMRead(rt_uint16_t eepaddr,rt_uint8_t *buf,rt_uint8_t len);

void CH395SetTCPMss(rt_uint16_t tcpmss);

void CH395SetSocketRecvBuf(rt_uint8_t sockindex,rt_uint8_t startblk,rt_uint8_t blknum);

void CH395SetSocketSendBuf(rt_uint8_t sockindex,rt_uint8_t startblk,rt_uint8_t blknum);

void CH395UDPSendTo(rt_uint8_t *buf,rt_uint32_t len,rt_uint8_t *ip,rt_uint16_t port,rt_uint8_t sockindex);

void CH395SetStartPara(rt_uint32_t mdata);

rt_uint16_t CH395CMDGetGlobIntStatus_ALL(void);

#endif /* DRIVERS_INCLUDE_CH395CMD_H_ */
