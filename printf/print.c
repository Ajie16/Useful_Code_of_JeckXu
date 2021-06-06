//printf重定向代码,修改其底层fputc
#if 1
#include <stdio.h>

/* 告知连接器不从C库链接使用半主机的函数 */
#pragma import(__use_no_semihosting)

/* 定义 _sys_exit() 以避免使用半主机模式 */
void _sys_exit(int x)
{
    x = x;
}

/* 标准库需要的支持类型 */
struct __FILE
{
    int handle;
};

FILE __stdout;

/*  */
int fputc(int ch, FILE *stream)
{
    /* 堵塞判断串口是否发送完成 */
	/* 不同芯片的串口标志位不一定相同！ */
    while((USART1->SR & 0X40) == 0);

    /* 串口发送完成，将该字符发送 */
    USART1->DR = (uint8_t) ch;

    return ch;
}

#endif