#ifndef __PID_H
#define __PID_H
#include "stm32f10x.h"
typedef struct PID //PID算法的数据结构 
{
	//参数
  float P;         
  float I;
  float D;
  
  float Error;     //比例项
  float Integral;  //积分项
  float Differ;    //微分项
  float PreError;  //前一个误差值
  float PrePreError;//微分量
  //积分限幅
  float Ilimit; 
  float Irang;
  
  //P&I&D的输出
  float Pout;
  float Iout;
  float Dout;
  //总输出
  float OutPut;   
  //积分分离标志	
  uint8_t Ilimit_flag;    
}PID_TYPE;

//函数定义区
void PidPrg_init(void);
void PID_Pos(PID_TYPE*PID,float target,float measure);

#endif

