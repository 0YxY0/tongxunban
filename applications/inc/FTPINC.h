/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-15     pengxiping       the first version
 */
#ifndef APPLICATIONS_INC_FTPINC_H_
#define APPLICATIONS_INC_FTPINC_H_

/********************************** (C) COPYRIGHT *********************************
* File Name          : CH395FTPINC
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395FTPINC头文件声明
**********************************************************************************/
#ifndef __FTPINC_H__
#define __FTPINC_H__
#define DEBUG            1                                   /* 调试  （晶振22.1184Mhz。波特率115200）*/
typedef struct FTP
{
  rt_uint8_t TcpStatus;                                           /* TCP连接状态*/
    rt_uint8_t CmdStatus;                                         /* 接口命令执行状态*/
  rt_uint8_t InterCmdS;                                           /* 接口命令执行标志位*/
  rt_uint8_t CmdFirtS;                                            /* 命令第一次执行标志位*/
  rt_uint8_t FindList;                                            /* 找到指定的文件夹*/
  rt_uint8_t FindFile;                                            /* 找到指定的文件名*/
  rt_uint8_t CmdDataS;                                            /* 传输数据状态*/
  rt_uint8_t SocketCtl;                                           /* ftp控制连接socket索引*/
  rt_uint8_t DatMonitor;                                          /* ftp数据连接侦听socket索引*/
  rt_uint8_t DatTransfer;                                         /* ftp数据连接传输socket索引*/
  rt_uint8_t FileCmd;                                             /* 接口命令类型  */
  rt_uint16_t SouPort;                                            /* 端口号*/
  rt_uint16_t RecDatLen;                                          /* 接收到的数据长度*/
}_FTP;
extern   char  ListName[24];                                 /* 用于保存目录名 */
extern   char  ListMdk[24];                                  /* 用于保存新创建的目录名*/
extern   char  FileName[24];                                 /* 用于保存文件名*/
extern   char  SourIP[17];                                   /* 用于保存转换成字符的IP地址*/
extern  const rt_uint8_t *pUserName;                              /* 匿名登陆*/
extern  const rt_uint8_t *pPassword;                              /* e-mail 名字作为登陆口令*/
/* TCP连接状态 */
#define FTP_MACH_DISCONT               0x00                  /* TCP断开连接*/
#define FTP_MACH_CONNECT               0x01                  /* TCP连接*/
/* 错误状态 */
#define FTP_MACH_QUIT                  0x01                  /* 登陆前错误*/
#define FTP_MACH_CLOSE                 0x02                  /* 登陆后错误*/
/* 数据传输状态 */
#define FTP_MACH_SENDDATA              0x01                  /* 需要发送数据*/
#define FTP_MACH_RECEDATA              0x02                  /* 需要接收数据*/
#define FTP_MACH_DATAOVER              0x04                  /* 数据传输完成*/
/* 接口名执行状态 */
#define FTP_MACH_LOGINSUC              0x01                  /* 登录成功*/
#define FTP_MACH_SEARCHSUC             0x02                  /* 寻找文件完成*/
#define FTP_MACH_GETSUC                0x04                  /* 下载文件成功*/
#define FTP_MACH_PUTSUC                0x08                  /* 上传文件成功*/
/*  命令执行过程标志位 */
#define FTP_MACH_FINDLIST              0x01                  /* 寻找目录标志位*/
#define FTP_MACH_FINDFILE              0x02                  /* 寻找文件标志位*/
#define FTP_MACH_GETFILE               0x04                  /* 下载文件标志位*/
#define FTP_MACH_MKDLIST               0x08                  /* 创建目录标志位*/
#define FTP_MACH_PUTFILE               0x10                  /* 上传文件标志位*/
/* 返回状态信息 */
#define FTP_CHECK_NULL                 0x00                  /* 没握手信号返回则不进行返回信息核对*/
#define FTP_CHECK_SUCCESS              0x00                  /* 检测握手信息正确  */
#define FTP_COMMAND_SUCCESS            0x00                  /* 接口命令执行成功*/
#define FTP_COMMAND_CONTINUE           0x01                  /* 接口命令还在执行过程中*/
/* 主程序接口命令类型 */
#define FTP_CMD_LOGIN                  0x01                  /* 登录*/
#define FTP_CMD_SEARCH                 0x02                  /* 寻找文件*/
#define FTP_CMD_GETFILE                0x03                  /* 下载文件*/
#define FTP_CMD_PUTFILE                0x04                  /* 上传文件*/
/* *********************************************************************************************************************
* 握手信号核对错误代码
************************************************************************************************************************/
#define FTP_ERR_LOGIN               0x20                     /* 登录*/
#define FTP_ERR_SEARCH              0x21                     /* 寻找文件*/
#define FTP_ERR_GETFILE             0x22                     /* 下载文件*/
#define FTP_ERR_PUTFILE             0x23                     /* 上传文件*/
#define FTP_ERR_UNLIST        0x2a                           /* 未找到目录*/
#define FTP_ERR_UNFILE        0x2b                           /* 未找到文件*/
#define FTP_ERR_UNKW        0x2f                             /* 未知错误*/

void  CH395_FTPClientCmd( void );                            /* 查询状态，执行子命令*/

void  CH395_FTPInterCmd( void );                             /* 执行对应的命令，可自行调整执行顺序*/

void  CH395_SocketSendData( char *PSend, rt_uint32_t Len,rt_uint8_t index  ); /* 发送数据*/

void  CH395_FTPConnect( void );                               /* 563初始化*/

void  CH395_FTPInitVari( void );                              /* 变量初始化*/

void CH395_FTPProcessReceDat( char *recv_buff,rt_uint8_t check_type,rt_uint8_t socketid );/* 检查应答信息*/

rt_uint8_t CH395_FTPCmdRespond( char *recv_buff,rt_uint8_t check_type );  /* 检查应答信息*/

void  CH395_FTPCtlClient( rt_uint8_t socketid);                      /* 创建FTP控制连接*/

void CH395_FTPDatServer( rt_uint8_t socketid,rt_uint16_t *port );         /* 创建FTP数据连接*/

void  CH395_FTPCommand( rt_uint8_t choiceorder);                     /* 根据命令类型执行对应的命令*/

rt_uint8_t CH395_FTPLogin( void );                                   /* 登陆 */

rt_uint8_t CH395_FTPSearch(char *pListNAme,char *pFileName );        /* 查找文件*/

rt_uint8_t CH395_FTPGetFile( char *pFileName );                      /* 下载文件*/

rt_uint8_t CH395_FTPPutFile(char *pListNAme, char *pFileName);       /* 上传文件*/

rt_uint8_t CH395_FTPFindFile( char *pReceiveData );                  /* 核对文件名字*/

rt_uint8_t CH395_FTPFindList( char *pReceiveData );                  /* 核对文件夹名*/

void  CH395_FTPGetSockeID( rt_uint8_t socketid );                    /* 获取数据连接socket索引*/

rt_uint8_t CH395_FTPMkdirCheck( char *rece_buf);                     /* 创建目录命令执行状态*/

rt_uint8_t CH395_FTPGetFileData( char *recv_buff );                  /* 读取下载的数据*/

void  CH395_FTPQuit( void );                                    /* 退出*/

rt_uint8_t CH395_FTPWriteData ( char *recv_buff ,rt_uint16_t len);

#endif


#endif /* APPLICATIONS_INC_FTPINC_H_ */
