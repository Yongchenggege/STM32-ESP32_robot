#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "a4950.h"
#include "OLED.h"
#include "tcs34725.h"
#include "Colorlight.h"
#include "hc_sr04.h"
#include "usart.h"
#include "string.h"

#include "MPU_6050.h"



static void sendCmd_toESP32(uint8_t cmd);
static void Color_display(void);
static void color_recognition(COLOR_RGBC *rgbc);
static void Speed_display(void);
static void Mpu_display(void);
static void sendCmd_toComputer(uint8_t cmd);

static pid_ctrl pid_speed_ctrl;
static pid_ctrl pid_speed_ctrl2;
extern uint8_t r_flag;
static int motor1speed = 0;
static int motor2speed = 0;
static uint8_t dir = 0;

#define NOWAIT					0
SemaphoreHandle_t Usart_MuxSem_Handle = NULL;
static uint8_t r_flag;
static uint8_t c_flag;
static uint8_t m_flag;
SemaphoreHandle_t Stop_MuxSem_Handle = NULL;
static uint8_t stop_flag;
static uint8_t sr04_flag = 1;
static float obj_dist = 10;

// tcs3472
COLOR_RGBC rgb;

void Color_Task(void * pvParameters);

void Car_Task(void * pvParameters);

void Motor_Task(void * pvParameters);

void Auto_Task(void * pvParameters);

void usart_task(void * pvParameters);

void sr04_task(void * pvParameters);

typedef struct {
	float k1;
	float k2;
	float k3;
	float r_g_m;
	float r_b_m;
	float g_b_m;
	float r_g_w;
	float r_b_w;
	float g_b_w;
	float r_g_y;
	float r_b_y;
	float g_b_y;
}re_t;

re_t re[1] = {			{0.875,0.716,1.456, 		// k1,k2,k3
						 2.088, 2.491, 1.186, 	// r_g,r_b,g_b middle_light
						 1.268,0.974,0.836, 	// r_g,r_b,g_b white_light
						1.017,1.559,2.125}
};


int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	
//	stdelay_init(72);
	
	pid_ctrl_init(&pid_speed_ctrl,60,3,2,PULSE_MAX);
	
	pid_ctrl_init(&pid_speed_ctrl2,60,3,2,PULSE_MAX);
	
	Colorlight_init();
	
	OLED_Init();
	
	a4950_init();
	
	TCS34725_Init();
	
	HC_SR04_init();
	

	
	mpu_dmp_init();

	
	usart1_init(115200);
	
	usart2_init(115200);
	
	BaseType_t ret;
	
	Usart_MuxSem_Handle = xSemaphoreCreateMutex();
	
	if (NULL != Usart_MuxSem_Handle) 
	{
		printf("Usart_MuxSem_Handle 互斥量创建成功！\n");
	}
	
	Stop_MuxSem_Handle = xSemaphoreCreateMutex();
	
	if (NULL != Stop_MuxSem_Handle) 
	{
		printf("Stop_MuxSem_Handle 互斥量创建成功！\n");
	}
	
	//中断优先级数值越小，优先级就越高，而FreeRTOS的任务优先级是，任务优先级数值越小任务优先级越低。
	// 创建任务，第一个参数是任务的堆栈大小，第二个参数是任务的参数，第三个参数是任务的优先级。
	// 创建任务1
	ret = xTaskCreate(Car_Task, "Task 1", 400, NULL, 1, NULL);
	
	if (ret != pdTRUE) 
	{
			printf("Car_Task error!\n"); 
	}
	
	// 创建任务2
	ret = xTaskCreate(Color_Task, "Task 2", 512, NULL, 2, NULL);
	
	if (ret != pdTRUE) 
	{
			printf("Color_Task error!\n"); 
	}
	
	// 创建任务3
	ret = xTaskCreate(Motor_Task, "Task 3", 400, NULL, 3, NULL);
	
	if (ret != pdTRUE) 
	{
			printf("Motor_Task error!\n"); 
	}
	
	// 创建任务4
	ret = xTaskCreate(Auto_Task, "Task 4", 400, NULL, 4, NULL); // 分配12k的内存
	
	if (ret != pdTRUE) 
	{
			printf("Auto_Task error!\n"); 
	}
	
	// 
	ret = xTaskCreate(usart_task, "usart_task", 128, NULL, 5, NULL);
	
	if (ret != pdTRUE) 
	{
			printf("usart_task error!\n"); 
	}
	
	//
	ret = xTaskCreate(sr04_task, "sr04_task", 128, NULL, 5, NULL);
	
	if (ret != pdTRUE) 
	{
			printf("sr04_task error!\n"); 
	}
	
	// 启动调度器，开始任务调度
  vTaskStartScheduler();
}

void usart_task(void * pvParameters)
{
	BaseType_t ret;
	uint8_t temp_flag = 0;
	
	while(1)
	{
		if(uart_receive_status(2) == USART_OK)
		{
			temp_flag = usart2_unpackage();
			
			if(temp_flag)
			{
				ret = xSemaphoreTake(Usart_MuxSem_Handle, /* 互斥量句柄 */ 
                           NOWAIT); 					 		/* 等待时间 */
			
				if(pdTRUE == ret)
				{
					r_flag = temp_flag;
					ret = xSemaphoreGive( Usart_MuxSem_Handle ); //给出互斥量
				}
			}
		}
		else if(uart_receive_status(1) == USART_OK)
		{
			temp_flag = usart1_unpackage();
			if(temp_flag)
			{
				ret = xSemaphoreTake(Usart_MuxSem_Handle, /* 互斥量句柄 */ 
                           NOWAIT); 					 		/* 等待时间 */
			
				if(pdTRUE == ret)
				{
					m_flag = temp_flag;
					ret = xSemaphoreGive( Usart_MuxSem_Handle ); //给出互斥量
				}				
			}
		
		}
		
		vTaskDelay(20);
	}
}

void Car_Task(void * pvParameters)
{
	BaseType_t ret;
	uint8_t temp_flag = 0;
	
	while(1)
	{	
		ret = xSemaphoreTake(Usart_MuxSem_Handle, /* 互斥量句柄 */ 
                           NOWAIT); 					 		/* 等待时间 */
			
		if(pdTRUE == ret)
		{
			if(r_flag > 8 && r_flag < 14)
			{
				temp_flag = r_flag;
				r_flag = 0;
			}
			ret = xSemaphoreGive( Usart_MuxSem_Handle ); //给出互斥量
		}
		
		switch(temp_flag)
		{
			case 9:  motor1speed = 10,motor2speed = 10,dir  = 1;temp_flag = 0;break;
			case 10: motor1speed = 10,motor2speed = 10,dir  = 0;temp_flag = 0;break;
			case 11: motor1speed = 10,motor2speed = 5,dir  = 1;temp_flag = 0;break;
			case 12: motor1speed = 5,motor2speed = 10,dir  = 1;temp_flag = 0;break;
			case 13: motor1speed = 0,motor2speed = 0,dir  = 1;temp_flag = 0;break;
			default: break;
		}
		
		pidmotor_run(&pid_speed_ctrl,&pid_speed_ctrl2,motor1speed,motor2speed,dir); 
		Speed_display();
		Mpu_display();
		
		vTaskDelay(10);
	}
	
}

void Motor_Task(void * pvParameters)
{
	BaseType_t ret;
	uint8_t temp_flag = 0;
//	
	while(1)
	{
		ret = xSemaphoreTake(Usart_MuxSem_Handle, /* 互斥量句柄 */ 
                           NOWAIT); 					 		/* 等待时间 */
			
		if(pdTRUE == ret)
		{
			if(r_flag < 9)
			{
				temp_flag = r_flag;
				r_flag = 0;
			}
			ret = xSemaphoreGive( Usart_MuxSem_Handle ); //给出互斥量
		}
		
/*机械臂控制部分*/	
		switch(temp_flag)
		{
			case 1:sendCmd_toESP32(0x01);temp_flag = 0;break;
			case 2:sendCmd_toESP32(0x02);temp_flag = 0;break;
			case 3:sendCmd_toESP32(0x03);temp_flag = 0;break;
			case 4:sendCmd_toESP32(0x04);temp_flag = 0;break;
			case 5:sendCmd_toESP32(0x05);temp_flag = 0;break;
			case 6:sendCmd_toESP32(0x06);temp_flag = 0;break;
			case 7:sendCmd_toESP32(0x07);temp_flag = 0;break;
			case 8:sendCmd_toESP32(0x08);temp_flag = 0;break;
			default:break;
		}
		vTaskDelay(20);
	}
}

void Color_Task(void * pvParameters) 
{
	// 任务主体
	for( ;; ) 
	{
		Color_display();
		color_recognition(&rgb);
		vTaskDelay(200);
	}
}

void sr04_task(void * pvParameters)
{
	BaseType_t ret;
	float dist;
	
	while(1)
	{
		if(sr04_flag)
		{
			dist = HC_SR04_Read();
			
			if(dist > 0)
			{
				if(dist < obj_dist)
				{
					ret = xSemaphoreTake(Stop_MuxSem_Handle, /* 互斥量句柄 */ 
														 NOWAIT); 					 		/* 等待时间 */
				
					if(pdTRUE == ret)
					{
						stop_flag = 1;
						sr04_flag = 0;
						ret = xSemaphoreGive( Stop_MuxSem_Handle ); //给出互斥量
					}
				}
			}
		}
		
		vTaskDelay(100);
	}
}

/*
操作员必须将小车放在标定好的起始位置后才可以点击自动运行
当收到自动运行的指令后  开始直线行驶  途中用红外传感器识别前方物体距离
如果距离小于15则停止运动  判断颜色识别结果  如果是红色  则放左边  如果是蓝色则放右边  
如果是绿色  后退  当红外传感距离大于某个值时停止
*/
void Auto_Task(void * pvParameters)
{
	BaseType_t ret;
	uint8_t start = 0;
	uint8_t detection = 0;
	
	while(1)
	{
		ret = xSemaphoreTake(Usart_MuxSem_Handle, /* 互斥量句柄 */ 
                           NOWAIT); 					 		/* 等待时间 */
			
		if(pdTRUE == ret)
		{
			if(r_flag == 14)
			{
				start = 1;
				sr04_flag = 1;
				detection = 1;
				r_flag = 0;
			}
			ret = xSemaphoreGive( Usart_MuxSem_Handle ); //给出互斥量
		}
		
		// 需要机械臂完成后回复才继续
		if(m_flag == 0x01)
		{
			stop_flag = 0;
			sr04_flag = 1;
			detection = 1;		
		}
		
		if(start)
		{
			if(stop_flag)
			{
				pidmotor_run(&pid_speed_ctrl,&pid_speed_ctrl2,0,0,dir);
				
				if(detection)
				{
					switch(c_flag)
					{
						case 1:sendCmd_toESP32(0x09); break;//红
						case 2:sendCmd_toESP32(0x0A); break;//蓝
						case 3:sendCmd_toComputer(0x04);start = 0;break;//绿  到头了
						default:break;
					}
					detection = 0;
				}
			}
			else
				pidmotor_run(&pid_speed_ctrl,&pid_speed_ctrl2,10,10,dir);
			
		}
		
		vTaskDelay(10);
	}
}

static void sendCmd_toESP32(uint8_t cmd)
{
	USART_SendData(USART1,0xAA);
	while(!USART_GetFlagStatus(USART1,USART_FLAG_TC));
	USART_SendData(USART1,cmd);
	while(!USART_GetFlagStatus(USART1,USART_FLAG_TC));
	USART_SendData(USART1,0xBB);
	while(!USART_GetFlagStatus(USART1,USART_FLAG_TC));
}

static void sendCmd_toComputer(uint8_t cmd)
{
	USART_SendData(USART2,0xAA);
	while(!USART_GetFlagStatus(USART2,USART_FLAG_TC));
	USART_SendData(USART2,cmd);
	while(!USART_GetFlagStatus(USART2,USART_FLAG_TC));
	USART_SendData(USART2,0xBB);
	while(!USART_GetFlagStatus(USART2,USART_FLAG_TC));
}

static void Color_display(void)
{
	uint8_t text[20]={0};
	
	TCS34725_GetRawData(&rgb);
//	printf("%d %d %d\r\n",rgb.r,rgb.g,rgb.b);//采样程序
	
	memset(text,'\0',sizeof(text)); 
	sprintf((char *)text,"R:%d  ",rgb.r);
	OLED_ShowString(1,1,(char *)text);
	memset(text,'\0',sizeof(text));
	sprintf((char *)text,"G:%d  ",rgb.g);
	OLED_ShowString(1,6,(char *)text);
	memset(text,'\0',sizeof(text));
	sprintf((char *)text,"B:%d  ",rgb.b);
	OLED_ShowString(1,11,(char *)text);
}

static void Speed_display(void)
{
	uint8_t text[20]={0};
	float v1 = get_motor_speed(1);
	float v2 = get_motor_speed(0);
	
	memset(text,'\0',sizeof(text)); 
	sprintf((char *)text,"v1:%.2f",v1);
	OLED_ShowString(2,1,(char *)text);
	memset(text,'\0',sizeof(text));
	sprintf((char *)text,"v2:%.2f",v2);
	OLED_ShowString(2,9,(char *)text);
	
//	printf("%.2f  %.2f\r\n",v1,v2);
//	printf("speed2 = %.2f\r\n",v2);


}
	
static void Mpu_display(void)
{
	uint8_t text[20]={0};
	float pitch,roll,yall;
	
	if(mpu_dmp_get_data(&pitch,&roll,&yall)==0)
	{
		memset(text,'\0',sizeof(text)); 
		sprintf((char *)text,"p:%.2f",pitch);
		OLED_ShowString(3,1,(char *)text);
		memset(text,'\0',sizeof(text)); 
		sprintf((char *)text,"r:%.2f",roll);
		OLED_ShowString(3,9,(char *)text);
		memset(text,'\0',sizeof(text)); 
		sprintf((char *)text,"y:%.2f",yall);
		OLED_ShowString(4,1,(char *)text);		
	}
	


}

static void color_recognition(COLOR_RGBC *rgbc)
{
	float k1 = re[0].k1; // r:g
	float k2 = re[0].k2; // r:b
	float k3 = re[0].k3; // g:b
	float r_g = rgbc->r/(rgbc->g*1.0); // 
	float r_b = rgbc->r/(rgbc->b*1.0); // 
	float g_b = rgbc->g/(rgbc->b*1.0); // 
	
	if(rgb.r >20 && rgb.g >20 && rgb.b >20)
	{
		if((r_g >= (re[0].r_g_m-k1) && r_g <= (re[0].r_g_m+k1)) && (r_b >= (re[0].r_b_m-k2) && r_b <= (re[0].r_b_m+k2)) && (g_b >= (re[0].g_b_m-k3) && g_b <= (re[0].g_b_m+k3))) 
		{	
			c_flag = 1;
			sendCmd_toComputer(0x01);//红色
			RGB_SetColor(0x04);
		} 
		else if((r_g >= (re[0].r_g_w-k1) && r_g <= (re[0].r_g_w+k1)) && (r_b >= (re[0].r_b_w-k2) && r_b <= (re[0].r_b_w+k2)) && (g_b >= (re[0].g_b_w-k3) && g_b <= (re[0].g_b_w+k3))) 
		{ 
			c_flag = 2;
			sendCmd_toComputer(0x02);//蓝色
			RGB_SetColor(0x01);
		}		
		else if((r_g >= (re[0].r_g_y-k1) && r_g <= (re[0].r_g_y+k1)) && (r_b >= (re[0].r_b_y-k2) && r_b <= (re[0].r_b_y+k2)) && (g_b >= (re[0].g_b_y-k3) && g_b <= (re[0].g_b_y+k3))) 
		{ 
			c_flag = 3;
			sendCmd_toComputer(0x03);//绿色		
			RGB_SetColor(0x02);
		}		
	
	}

	else{
		c_flag = 0;
		sendCmd_toComputer(0x04);//无色	
		RGB_SetColor(0x00);
	}
}
