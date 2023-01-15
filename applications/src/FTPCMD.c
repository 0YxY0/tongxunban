/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-15     pengxiping       the first version
 */

#include <rtthread.h>
#include "FTPINC.h"
#include "CH395CMD.h"
#include <stdio.h>
#include <string.h>

/********************************** (C) COPYRIGHT *********************************
* File Name          : ch395FTPCMD.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395芯片FTP客户端应用-FTP命令代码
**********************************************************************************/
struct FTP ftp;
char   send_buff[536];                                                                    /* 发送数据缓存区*/
rt_uint16_t ListNum = 0;
/********************************************************************************
* Function Name  : CH395_FTPLoginUser
* Description    : 认证用户名
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void CH395_FTPLoginUser( )
{
  memset( send_buff, '\0', sizeof(send_buff) );
  sprintf( send_buff, "USER %s\r\n", pUserName);
#if DEBUG
  printf("USER :%s\n", send_buff);
#endif
  CH395_SocketSendData( send_buff, strlen(send_buff),ftp.SocketCtl );
}

/*********************************************************************************
* Function Name  : CH395_FTPLoginPass
* Description    : 认证口令
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void CH395_FTPLoginPass( )
{
  memset( send_buff, '\0', sizeof(send_buff) );
  sprintf( send_buff, "PASS %s\r\n", pPassword);
#if DEBUG
  printf("PASS :%s\n", send_buff);
#endif
  CH395_SocketSendData( send_buff, strlen(send_buff),ftp.SocketCtl );
}

/*********************************************************************************
* Function Name  : CH395_FTPSyst
* Description    : 查询服务器系统类型
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void CH395_FTPSyst( )
{
  memset( send_buff, '\0', sizeof(send_buff) );
  sprintf( send_buff, "SYST\r\n");
#if DEBUG
  printf("SYST :%s\n", send_buff);
#endif
  CH395_SocketSendData( send_buff, strlen(send_buff),ftp.SocketCtl );
}

/*********************************************************************************
* Function Name  : CH395_FTPList
* Description    : 获取文件列表，文件名及时间
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void CH395_FTPList( )
{
  memset( send_buff, '\0', sizeof(send_buff) );
  sprintf( send_buff, "LIST\r\n");
#if DEBUG
  printf("LIST :%s\n", send_buff);
#endif
  CH395_SocketSendData( send_buff, strlen(send_buff),ftp.SocketCtl );
}

/*********************************************************************************
* Function Name  : CH395_FTPNlst
* Description    : 获取文件列表
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void CH395_FTPNlst( )
{
  memset( send_buff, '\0', sizeof(send_buff) );
  sprintf( send_buff, "NLST\r\n");
#if DEBUG
  printf("NLST :%s\n", send_buff);
#endif
  CH395_SocketSendData( send_buff, strlen(send_buff),ftp.SocketCtl );
}

/*********************************************************************************
* Function Name  : CH395_FTPType
* Description    : 设置文件传输类型
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void CH395_FTPType( )
{
  memset( send_buff, '\0', sizeof(send_buff) );
  sprintf( send_buff, "TYPE A\r\n");
#if DEBUG
  printf("TYPE :%s\n", send_buff);
#endif
  CH395_SocketSendData( send_buff, strlen(send_buff),ftp.SocketCtl );
}

/*********************************************************************************
* Function Name  : CH395_FTPSize
* Description    : 获取文件信息
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void CH395_FTPSize( )
{
  memset( send_buff, '\0', sizeof(send_buff) );
  sprintf( send_buff, "SIZE %s\r\n",FileName);
#if DEBUG
  printf("SIZE :%s\n", send_buff);
#endif
  CH395_SocketSendData( send_buff, strlen(send_buff),ftp.SocketCtl );
}

/*********************************************************************************
* Function Name  : CH395_FTPRetr
* Description    : 下载文件
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void CH395_FTPRetr( )
{
  memset( send_buff, '\0', sizeof(send_buff) );
  sprintf( send_buff, "RETR %s\r\n",FileName);
#if DEBUG
  printf("RETR :%s\n", send_buff);
#endif
  CH395_SocketSendData( send_buff, strlen(send_buff),ftp.SocketCtl );
}

/*********************************************************************************
* Function Name  : CH395_FTPCdup
* Description    : 返回上一级目录
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void CH395_FTPCdup( )
{
  memset( send_buff, '\0', sizeof(send_buff) );
  sprintf( send_buff, "CDUP\r\n");
#if DEBUG
  printf("CDUP :%s\n", send_buff);
#endif
  CH395_SocketSendData( send_buff, strlen(send_buff),ftp.SocketCtl );
}

/********************************************************************************
* Function Name  : CH395_FTPMkd
* Description    : 创建目录
* Input          : ReName
* Output         : None
* Return         : None
*********************************************************************************/
void CH395_FTPMkd(rt_uint8_t ReName )
{
  memset( send_buff, '\0', sizeof(send_buff) );
  if(ReName){
    ListNum++;
    sprintf( send_buff, "MKD %s%d\r\n",ListName,ListNum);
  }
  else sprintf( send_buff, "MKD %s\r\n",ListName);
  sprintf( ListMdk,&send_buff[4] );                                                       /*保存目录名*/
#if DEBUG
  printf("MKD :%s\n", send_buff);
#endif
  CH395_SocketSendData( send_buff, strlen(send_buff),ftp.SocketCtl );
}

/*********************************************************************************
* Function Name  : CH395_FTPRmd
* Description    : 删除目录
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void CH395_FTPRmd( )
{
  memset( send_buff, '\0', sizeof(send_buff) );
  sprintf( send_buff, "RMD %s\r\n",ListName);
#if DEBUG
  printf("RMD :%s\n", send_buff);
#endif
  CH395_SocketSendData( send_buff, strlen(send_buff),ftp.SocketCtl );
}

/*********************************************************************************
* Function Name  : CH395_FTPAppe
* Description    : 上传文件
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void CH395_FTPAppe( )
{
  memset( send_buff, '\0', sizeof(send_buff) );
  sprintf( send_buff, "APPE %s\r\n",FileName);
#if DEBUG
  printf("STOR :%s\n", send_buff);
#endif
  CH395_SocketSendData( send_buff, strlen(send_buff),ftp.SocketCtl );
}

/********************************************************************************
* Function Name  : CH395_FTPAllo
* Description    : 下载文件
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void CH395_FTPAllo( )
{
  memset( send_buff, '\0', sizeof(send_buff) );
  sprintf( send_buff, "ALLO 500000\r\n");
#if DEBUG
  printf("ALLO :%s\n", send_buff);
#endif
  CH395_SocketSendData( send_buff, strlen(send_buff),ftp.SocketCtl );
}

/********************************************************************************
* Function Name  : CH395_FTPNoop
* Description    : 发送空指令
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void CH395_FTPNoop( )
{
  memset( send_buff, '\0', sizeof(send_buff) );
  sprintf( send_buff, "NOOP\r\n");
#if DEBUG
  printf("NOOP :%s\n", send_buff);
#endif
  CH395_SocketSendData( send_buff, strlen(send_buff),ftp.SocketCtl );
}

/*********************************************************************************
* Function Name  : CH395_FTPPort
* Description    : 设定连接端口号
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void CH395_FTPPort( rt_uint16_t port )
{
  memset( send_buff, '\0', sizeof(send_buff));
  sprintf( send_buff, "PORT %s%02d,%02d\r\n",SourIP,port/256,port%256);
#if DEBUG
  printf("PORT :%s\n", send_buff);
#endif
  CH395_SocketSendData( send_buff, strlen(send_buff),ftp.SocketCtl );
}

/*********************************************************************************
* Function Name  : CH395_FTPCwd
* Description    : 打开目录
* Input          : index
* Output         : None
* Return         : None
*********************************************************************************/
void CH395_FTPCwd( rt_uint8_t index )
{
  memset( send_buff, '\0', sizeof(send_buff) );
  if(index==1) sprintf( send_buff, "CWD /%s\r\n",ListMdk);
  else sprintf( send_buff, "CWD /%s\r\n",ListName);
  CH395_SocketSendData( send_buff, strlen(send_buff),ftp.SocketCtl );
}

/*********************************************************************************
* Function Name  : CH395_FTPQuit
* Description    : 退出登录
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void CH395_FTPQuit( )
{
  memset( send_buff, '\0', sizeof(send_buff) );
  sprintf( send_buff, "QUIT\r\n");
#if DEBUG
  printf("QUIT :%s\n", send_buff);
#endif
  CH395_SocketSendData( send_buff, strlen(send_buff),ftp.SocketCtl );
}

/********************************************************************************
* Function Name  : CH395_FTPCheckLogin
* Description    : 验证登陆握手信号
* Input          : recv_buff- 握手信息
                   check_type-检测的类型
* Output         : None
* Return         : None
*********************************************************************************/
rt_uint8_t CH395_FTPCheckLogin( char *recv_buff )
{
  if( strncmp("220", recv_buff, 3) == 0 ){                                                /* 连接成功*/
    CH395_FTPLoginUser( );
  }
  else if( strncmp("331", recv_buff, 3) == 0 ){                                            /* 用户名正确*/
    CH395_FTPLoginPass( );
  }
  else if( strncmp("230", recv_buff, 3) == 0 ){                                            /* 登录成功  */
    ftp.CmdStatus = FTP_MACH_LOGINSUC;
  }
  else if( strncmp("530", recv_buff, 3) == 0 ){                                           /* 登陆失败*/
    CH395CloseSocket( ftp.SocketCtl );
  }
  else if( strncmp("221", recv_buff, 3) == 0 ){                                           /* 退出登陆*/
    CH395CloseSocket( ftp.SocketCtl );                                                    /* 关闭连接*/
  }
  return FTP_ERR_LOGIN;
}

/********************************************************************************
* Function Name  : CH395_FTPCheckSearch
* Description    : 验证搜查文件握手信号
* Input          : recv_buff- 握手信息
                   check_type-检测的类型
* Output         : None
* Return         : None
*********************************************************************************/
rt_uint8_t CH395_FTPCheckSearch( char *recv_buff )
{
    printf("#####");

  if( strncmp("200 Type", recv_buff, 8) == 0 ){                                           /* 格式类型*/
    CH395_FTPDatServer( 1,&ftp.SouPort );
    CH395_FTPPort( ftp.SouPort );
  }
  else if( strncmp("200 PORT", recv_buff, 8 ) == 0){
    CH395_FTPList( );
  }
  else if( strncmp("150", recv_buff, 3) == 0 ){                                           /* 获取列表成功*/
    ftp.CmdDataS = FTP_MACH_RECEDATA;
  }
  else if( strncmp("226", recv_buff, 3) == 0 ){                                           /* 列表信息结束*/
    if(ftp.InterCmdS == FTP_MACH_FINDFILE) ftp.CmdStatus = FTP_MACH_SEARCHSUC;
     if(ftp.FindList == 1){
         ftp.FindList = 0;
         CH395_FTPCwd( 0 );
     }
    ftp.InterCmdS = 0;
  }
  else if( strncmp("425", recv_buff, 3) == 0 ){                                           /* 无法建立数据连接*/
    CH395_FTPQuit( );
  }
  else if( strncmp("250", recv_buff, 3) == 0 ){                                           /* 打开目录*/
    printf("250^^^^^^^^^^^^^^^^^^^^^^^^^^");
   ftp.InterCmdS = FTP_MACH_FINDFILE;
    CH395_FTPType( );
  }
  else if( strncmp("221", recv_buff, 3) == 0 ){                                           /* 退出登陆  */
    CH395CloseSocket( ftp.SocketCtl );                                                    /* 关闭连接  */
  }
  else return FTP_ERR_SEARCH;
  return FTP_CHECK_SUCCESS;
}

/*********************************************************************************
* Function Name  : CH395_FTPCheckGetfile
* Description    : 验证下载文件握手信号
* Input          : recv_buff- 握手信息
                   check_type-检测的类型
* Output         : None
* Return         : None
*********************************************************************************/
rt_uint8_t CH395_FTPCheckGetfile( char *recv_buff )
{
  if( strncmp("200 Type", recv_buff, 8) == 0 ){                                           /* 格式类型 */
    CH395_FTPSize( );
  }
  else if( strncmp("213", recv_buff, 3) == 0 ){                                           /* 文件信息 */
    CH395_FTPDatServer( 1,&ftp.SouPort );
    CH395_FTPPort( ftp.SouPort );
  }
  else if( strncmp("200 PORT", recv_buff, 8) == 0 ){
    CH395_FTPRetr( );
  }
  else if( strncmp("150", recv_buff, 3) == 0 ){
    ftp.CmdDataS = FTP_MACH_RECEDATA;
    memset( send_buff, '\0', sizeof(send_buff) );
  }
  else if(strncmp("550", recv_buff, 3) == 0 ){                                            /* 没有找到文件*/
    CH395_FTPQuit( );
  }
  else if(strncmp("226", recv_buff,3) == 0 ){                                             /* 传输完成  */
    ftp.CmdStatus = FTP_MACH_GETSUC;
  }
  else if( strncmp("221", recv_buff, 3) == 0 ){                                           /* 退出登陆   */
    CH395CloseSocket( ftp.SocketCtl );                                                    /* 关闭连接      */
  }
  else return FTP_ERR_GETFILE;
  return (FTP_CHECK_SUCCESS);
}

/*********************************************************************************
* Function Name  : CH395_FTPCheckPutfile
* Description    : 验证上传文件握手信号
* Input          : recv_buff- 握手信息
                   check_type-检测的类型
* Output         : None
* Return         : None
*********************************************************************************/
rt_uint8_t CH395_FTPCheckPutfile( char *recv_buff )
{
  if( strncmp("250", recv_buff, 3) == 0 ){                                                /* 返回上一级目录 */
    if(ftp.InterCmdS == FTP_MACH_MKDLIST){
      CH395_FTPMkd( 0 );
    }
    else if(ftp.InterCmdS == FTP_MACH_PUTFILE){
      CH395_FTPType( );
    }
  }
  else if( strncmp("257", recv_buff, 3) == 0 ){                                           /* 创建成功     */
    ftp.InterCmdS = FTP_MACH_PUTFILE;                                                     /* 上传文件     */
    CH395_FTPCwd( 1 );                                                                    /* 打开目录      */
  }
  else if( strncmp("550", recv_buff, 3) == 0 ){                                           /* 创建的目录名存在*/
#if  1
    CH395_FTPMkd( 1 );                                                                    /* 该目录名存在则创建另外一个目录名（在原先目录名后累加数字如：TXET1）*/
#else
    CH395_FTPCwd( 0 );                                                                    /* 该目录名存在则直接打开 */
#endif
  }
  if( strncmp("200 Type", recv_buff, 8) == 0 ){                                           /* 格式类型   */
    CH395_FTPDatServer( 1,&ftp.SouPort );
    CH395_FTPPort( ftp.SouPort );
  }
  else if( strncmp("200 PORT", recv_buff, 8 ) == 0){
    CH395_FTPAppe( );
  }
  else if( strncmp("150", recv_buff, 3) == 0 ){                                           /* 请求上传文件命令成功*/
    ftp.CmdDataS = FTP_MACH_SENDDATA;                                                     /* 需要发送数据  */
  }
  else if( strncmp("226", recv_buff, 3) == 0 ){                                           /* 上传结束    */
    ftp.CmdStatus = FTP_MACH_PUTSUC;
  }
  else if( strncmp("221", recv_buff, 3) == 0 ){                                           /* 退出登陆   */
    CH395CloseSocket( ftp.SocketCtl );                                                    /* 关闭连接    */
  }
  else return FTP_ERR_PUTFILE;
  return (FTP_CHECK_SUCCESS);
}

/********************************************************************************
* Function Name  : CH395_FTPCmdRespond
* Description    : 验证登陆握手信号
* Input          : recv_buff- 握手信息
                   check_type-检测的类型
* Output         : None
* Return         : None
*********************************************************************************/
rt_uint8_t CH395_FTPCmdRespond( char *recv_buff,rt_uint8_t check_type )
{
  rt_uint8_t s;

  if( strncmp("421", recv_buff, 3) == 0 ){                                                /* 服务器意外断开 */
    return (FTP_CHECK_SUCCESS);
  }
  switch( check_type ){
    case FTP_CMD_LOGIN:                                                                   /* 核对登陆命令过程中的返回信息*/
      s = CH395_FTPCheckLogin( recv_buff );
      return s;
    case FTP_CMD_SEARCH:                                                                  /* 核对搜查文件过程中的返回信息  */
      s = CH395_FTPCheckSearch( recv_buff );
      return s;
    case FTP_CMD_GETFILE:                                                                 /* 核对下载文件过程中的返回信息  */
      s = CH395_FTPCheckGetfile( recv_buff );
      return s;
    case FTP_CMD_PUTFILE:                                                                 /* 核对上传文件过程中的返回信息  */
      s = CH395_FTPCheckPutfile( recv_buff );
      return s;
    default:
      return FTP_ERR_UNKW;
  }
}

/********************************************************************************
* Function Name  : CH395_FTPFindList
* Description    : 核对目录名字
* Input          : pReceiveData- 获取的列表信息
* Output         : None
* Return         : None
*********************************************************************************/
rt_uint8_t CH395_FTPFindList( char *pReceiveData )
{
  rt_uint32_t len,i,j;

  len = ftp.RecDatLen;
  for(i=0;i<len;i++){
    if(strncmp(ListName,&pReceiveData[i],strlen(ListName))==0){
      j = i;
      while(strncmp("<DIR>",&pReceiveData[j],strlen("<DIR>"))){
        j--;
        if( pReceiveData[j]== 'M' ) return 0;
      }
#if DEBUG
  printf("*********\nfind list\n*********\n");
#endif
      return FTP_CHECK_SUCCESS;                /* 找到了指定的文件名 */
    }
  }
  return FTP_ERR_UNLIST;
}

/********************************************************************************
* Function Name  : CH395_FTPFindFile
* Description    : 核对文件名字
* Input          : pReceiveData-获取的文件列表信息
* Output         : None
* Return         : None
*********************************************************************************/
rt_uint8_t CH395_FTPFindFile( char *pReceiveData )
{
  rt_uint32_t len,i;
  len = ftp.RecDatLen;
  for(i=0;i<len;i++){
  if(strncmp(FileName,&pReceiveData[i],strlen(FileName))==0){
#if DEBUG
  printf("*********\nfind file\n*********\n");
#endif
      return FTP_CHECK_SUCCESS;                /* 找到了指定的文件名*/
    }
  }
  return FTP_ERR_UNFILE;
}

/*********************************************************************************
* Function Name  : ch563ftp_loginstart
* Description    : 登陆
* Input          : None
* Output         : None
* Return         : 函数执行结果
*********************************************************************************/
rt_uint8_t CH395_FTPLogin( )
{
  if(ftp.CmdFirtS == 0){
    ftp.CmdFirtS  = 1;
    ftp.FileCmd = FTP_CMD_LOGIN;                                                          /* 进入搜查文件状态   */
    CH395_FTPCtlClient( 0 );
  }
  if( ftp.CmdStatus == FTP_MACH_LOGINSUC ){                                               /* 登陆成功       */
#if DEBUG
  printf("************\nlogin success\n*********\n");
#endif
    ftp.CmdFirtS = 0;
    ftp.CmdStatus = 0;
    ftp.FileCmd = 0;
    return FTP_COMMAND_SUCCESS;
  }
  return FTP_COMMAND_CONTINUE;
}

/*********************************************************************************
* Function Name  : ch563ftp_searchfile
* Description    : 搜查文件
* Input          : pListName - 需要搜查的文件所在目录名
                   pFileName - 该目录下的文件名
* Output         : None
* Return         : None
*********************************************************************************/
rt_uint8_t CH395_FTPSearch(char *pListName,char *pFileName )
{
  if( ftp.CmdFirtS == 0 ){
    ftp.CmdFirtS = 1;
    ftp.FileCmd = FTP_CMD_SEARCH;                                                         /* 进入搜查文件状态  */
    ftp.InterCmdS = FTP_MACH_FINDLIST;                                                    /* 查找目录       */
    memcpy((void *)ListName, '\0', sizeof(ListName));
    sprintf( ListName,pListName );                                                        /* 输入文件夹名字  */
    memcpy((void *)FileName, '\0', sizeof(FileName));
    sprintf( FileName,pFileName );                                                        /* 输入搜查文件的名字  */
    CH395_FTPType( );
  }
  if(ftp.TcpStatus == FTP_MACH_DISCONT){
    if(ftp.CmdStatus == FTP_MACH_SEARCHSUC){                                              /* 搜查文件完成     */
#if DEBUG
  printf("**********\nsearch success\n*********\n");
#endif
      ftp.CmdFirtS = 0;
      ftp.CmdStatus = 0;
      ftp.FileCmd = 0;
      return FTP_COMMAND_SUCCESS;
    }
  }
  return FTP_COMMAND_CONTINUE;
}

/*********************************************************************************
* Function Name  : ch563ftp_getfile
* Description    : 下载文件
* Input          : pFileName - 下载的文件名
* Output         : None
* Return         : None
*********************************************************************************/
rt_uint8_t CH395_FTPGetFile( char *pFileName )
{
  if(ftp.CmdFirtS == 0){
    ftp.CmdFirtS  = 1;
    ftp.FileCmd = FTP_CMD_GETFILE;                                                        /* 进入下载文件状态   */
    ftp.InterCmdS = FTP_MACH_GETFILE;                                                     /* 下载文件       */
    memcpy((void *)FileName,'\0',sizeof(FileName));
    sprintf( FileName,pFileName );                                                        /* 输入下载文件的名字 */
    CH395_FTPType( );
  }
  if(ftp.TcpStatus == FTP_MACH_DISCONT){
    if(ftp.CmdStatus == FTP_MACH_GETSUC){                                                 /* 下载文件成功     */
#if DEBUG
  printf("*********\ngetfile success\n*********\n");
#endif
    ftp.CmdFirtS = 0;
    ftp.CmdStatus = 0;
    ftp.FileCmd = 0;
    return FTP_COMMAND_SUCCESS;
    }
  }
  return FTP_COMMAND_CONTINUE;
}

/*********************************************************************************
* Function Name  : CH395_FTPPutFile
* Description    : 上传文件
* Input          : pListNAme - 上传文件所需保存的目录名
                   pFileName - 上传文件所需保存的文件名
* Output         : None
* Return         : None
*********************************************************************************/
rt_uint8_t CH395_FTPPutFile(char *pListNAme, char *pFileName)
{
  if(ftp.CmdFirtS ==0){
    ftp.CmdFirtS = 1;
    ftp.FileCmd = FTP_CMD_PUTFILE;                                                        /* 进行上传文件状态*/
    ftp.InterCmdS = FTP_MACH_MKDLIST;                                                     /* 创建目录      */
    memcpy((void *)ListName,'\0',sizeof(ListName));
    sprintf( ListName,pListNAme );                                                        /* 输入上传文件的名字*/
    memcpy((void *)FileName,'\0',sizeof(FileName));
    sprintf( FileName,pFileName );                                                        /* 输入上传文件的名字 */
    CH395_FTPCdup( );
  }
  if(ftp.TcpStatus == FTP_MACH_DISCONT){
    if(ftp.CmdStatus == FTP_MACH_PUTSUC){                                                 /* 上传文件成功   */
#if DEBUG
  printf("*********\nputfile success\n*********\n");
#endif
      ftp.CmdFirtS = 0;
      ftp.CmdStatus = 0;
      ftp.FileCmd = 0;
      return FTP_COMMAND_SUCCESS;
    }
  }
  return FTP_COMMAND_CONTINUE;
}
