#include "hc_sr04.h"

/*******************
* @brief us级延时

* @param usdelay:要延时的us时间

* @return  
*
*******************/
static void HC_SR04_Delayus(uint32_t usdelay)
{
 __IO uint32_t Delay = usdelay * (SystemCoreClock / 8U / 1000U/1000);//SystemCoreClock:系统频率

 do
 {
  __NOP();
 }
  while (Delay --);
}


void HC_SR04_init(void)
{
	GPIO_InitTypeDef GPIO_Init_my;
	RCC_APB2PeriphClockCmd(HC_SR04_Tring_PORT|HC_SR04_Echo_PORT,ENABLE);
	
	GPIO_Init_my.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
	GPIO_Init_my.GPIO_Pin=HC_SR04_Tring_Pin;
	GPIO_Init_my.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(HC_SR04_Tring_GPIO_Port,&GPIO_Init_my);
	
	GPIO_Init_my.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init_my.GPIO_Pin=HC_SR04_Echo_Pin;
	GPIO_Init_my.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(HC_SR04_Echo_GPIO_Port,&GPIO_Init_my);
}

/*******************
* @brief HC_SR04读取超声波距离
然后就可以读距离了、连上蓝牙可以显示数据

注意:两个HC_SR04_Read()函数调用的时间间隔要2ms及以上，测量范围更大 精度更高

* @param 无

* @return 障碍物距离单位:cm (静止表面平整精度更高) 
*注意:两个HC_SR04_Read()函数调用的时间间隔要2ms及以上，测量范围更大 精度更高 
*******************/

float HC_SR04_Read(void)
{
	uint32_t i = 0;
	float Distance = -1;
	GPIO_SetBits(HC_SR04_Tring_GPIO_Port,HC_SR04_Tring_Pin);//输出15us高电平
	HC_SR04_Delayus(15);
	GPIO_ResetBits(HC_SR04_Tring_GPIO_Port,HC_SR04_Tring_Pin);//高电平输出结束，设置为低电平
	while(GPIO_ReadInputDataBit(HC_SR04_Echo_GPIO_Port,HC_SR04_Echo_Pin) == GPIO_PIN_RESET)//等待回响高电平
	{
		i++;
		HC_SR04_Delayus(1);
		if(i>100000) return -1;//超时退出循环、防止程序卡死这里
	}
	i = 0;
	while(GPIO_ReadInputDataBit(HC_SR04_Echo_GPIO_Port,HC_SR04_Echo_Pin) == GPIO_PIN_SET)//下面的循环是2us
	{
		i = i+1;
		HC_SR04_Delayus(1);//1us 延时，但是整个循环大概2us左右
		if(i >100000) return -2;//超时退出循环

	}
	
	if(i != 0)
		Distance = i*0.034;//这里乘2的原因是上面是2微妙 单位cm

	return Distance ;
}

