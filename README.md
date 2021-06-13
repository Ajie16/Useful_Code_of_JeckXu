# Useful_Code_of_JeckXu
小徐同学的总结小代码

[TOC]

# Tree

## 1.IIC_Sim

模拟IIC

## 2.OLED

OLED驱动

- IIC
  硬件IIC驱动OLED代码，使用HAL库开发

## 3.PID_Pos

位置式PID代码

## 4.SPI_Sim

模拟SPI

## 5.uC/OS_System

uCos移植-串口、延时、位操作

```shell
git init
git config core.sparsecheckout true 
echo '/uCOS_System_F103/*' >> .git/info/sparse-checkout #改变添加文件夹
git remote add github https://github.com/Ajie16/Useful_Code_of_JeckXu.git #改变仓库链接
git pull github master #作者jeckxu
```

## 6.Filter

滤波函数

## 7.MPU6050

HAL使用硬件IIC移植DMP读取MPU6050角度数据驱动代码

```shell
git init
git config core.sparsecheckout true 
echo '/MPU6050/*' >> .git/info/sparse-checkout #改变添加文件夹
git remote add github https://github.com/Ajie16/Useful_Code_of_JeckXu.git #改变仓库链接
git pull github master #作者jeckxu
```

