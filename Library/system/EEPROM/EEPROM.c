/**
  ******************************************************************************
  * @file    eeprom.c
  * @author  PineconePi(基于宏晶科技STC15库函数进行修改)
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This file is used to Configure internal EEPROM 
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  *Pinecone Pi NANO: The size of EEPROM is set by STC-ISP
  *
  *  
  * 
  * 
  * 
  * 
  *
  * 
  ******************************************************************************
	**/
	
#include "system.h"
#include "eeprom.h"
#include "intrins.h"

//========================================================================
// Function:void DisableEEPROM(void)|函数: void	DisableEEPROM(void)
// Description:Turn off the IAP function.|描述: 关闭IAP功能。
// Parameter:|参数: 
//       
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2018-12-20|日期: 2018-12-20
// Author:PineconePi|作者: PineconePi
// Note:备注:
//	
//	
//	
//	
//	
//========================================================================
void	DisableEEPROM(void)
{
    IAP_CONTR = 0;                              //关闭IAP功能
    IAP_CMD = 0;                                //清除命令寄存器
    IAP_TRIG = 0;                               //清除触发寄存器
    IAP_ADDRH = 0x80;                           //将地址设置到非IAP区域
    IAP_ADDRL = 0;
}

//========================================================================
// Function:char EEPROM_Read(int Addr)|函数: char EEPROM_Read(int Addr)
// Description:Read a byte of data to address Addr|描述: 向地址Addr中读取一个字节数据。
// Parameter:Addr: Read address|参数: Addr:读取地址
//       
//       
// Return:Data in a byte of Addr address|返回: Addr地址中一个字节的数据
// Version:VER1.0.0|版本: VER1.0.0
// Date:2018-12-20|日期: 2018-12-20
// Author:PineconePi|作者: PineconePi
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================

char EEPROM_Read(int Addr)
{
    char dat;

    IAP_CONTR = WT_24M;                         //使能IAP
    IAP_CMD = 1;                                //设置IAP读命令
    IAP_ADDRL = Addr;                           //设置IAP低地址
    IAP_ADDRH = Addr >> 8;                      //设置IAP高地址
    IAP_TRIG = 0x5a;                            //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                            //写触发命令(0xa5)
    _nop_();
    dat = IAP_DATA;                             //读IAP数据
    DisableEEPROM();                                  //关闭IAP功能

    return dat;
}

//========================================================================
// Function:void EEPROM_Erase(int Addr)|函数:void EEPROM_Erase(int Addr)
// Description:The address Addr is erased.|描述: 对地址Addr进行数据擦出。
// Parameter:Addr: The address of the EEPROM to be erased.|参数: Addr:要擦除的EEPROM的地址.
//       
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2018-12-20|日期: 2018-12-20
// Author:PineconePi|作者: PineconePi
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
void EEPROM_Erase(int Addr)
{
    IAP_CONTR = WT_24M;                         //使能IAP
    IAP_CMD = 3;                                //设置IAP擦除命令
    IAP_ADDRL = Addr;                           //设置IAP低地址
    IAP_ADDRH = Addr >> 8;                      //设置IAP高地址
    IAP_TRIG = 0x5a;                            //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                            //写触发命令(0xa5)
    _nop_();                                    //
    DisableEEPROM();                                   //关闭IAP功能
}

//========================================================================
// Function:void EEPROM_Write(int Addr, char Dat)|函数:void EEPROM_Write(int Addr, char Dat)
// Description:Write a byte data Dat to the address Addr.|描述: 向地址Addr中写入一个字节数据Dat。
// Parameter:Addr: The address of the EEPROM to be written. Dat: The data to be written|参数: Addr:要写入的EEPROM的地址.Dat:写入的数据
//       
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2018-12-20|日期: 2018-12-20
// Author:PineconePi|作者: PineconePi
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
void EEPROM_Write(int Addr, char Dat)
{
    IAP_CONTR = WT_24M;                         //使能IAP
    IAP_CMD = 2;                                //设置IAP写命令
    IAP_ADDRL = Addr;                           //设置IAP低地址
    IAP_ADDRH = Addr >> 8;                      //设置IAP高地址
    IAP_DATA = Dat;                             //写IAP数据
    IAP_TRIG = 0x5a;                            //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                            //写触发命令(0xa5)
    _nop_();
    DisableEEPROM();                                  //关闭IAP功能
}

