#include "tcs34725.h"
#include "stdio.h"

void TCS34725_Write(uint8_t addr,uint8_t data)
{
		addr = addr|TCS34725_COMMAND_BIT;
	
		iic_start();
		iic_send_byte(0x52);
		iic_wait_ack();
		iic_send_byte(addr);
		iic_wait_ack();
		iic_send_byte(data);
		iic_wait_ack();
		iic_stop();
}

uint8_t TCS34725_Read(uint8_t addr)
{
		uint8_t data;
		addr = addr|TCS34725_COMMAND_BIT;
		
		iic_start();
		iic_send_byte(0x52);
		iic_wait_ack();
		iic_send_byte(addr);
		iic_wait_ack();
		iic_start();
		iic_send_byte(0x53);
		iic_wait_ack();
		data=iic_read_byte(0);
		iic_stop();
		return data;
}

/*******************************************************************************
 * @brief TCS34725璁剧疆绉垎鏃堕棿
 *
 * @return None
*******************************************************************************/
void TCS34725_SetIntegrationTime(uint8_t time)
{
	TCS34725_Write(TCS34725_ATIME,time);
}

/*******************************************************************************
 * @brief TCS34725璁剧疆澧炵泭
 *
 * @return None
*******************************************************************************/
void TCS34725_SetGain(uint8_t gain)
{
	TCS34725_Write(TCS34725_CONTROL,gain);
}

/*******************************************************************************
 * @brief TCS34725浣胯兘
 *
 * @return None
*******************************************************************************/
void TCS34725_Enable(void)
{
	uint8_t cmd = TCS34725_ENABLE_PON;
	
	TCS34725_Write(TCS34725_ENABLE,cmd);
	cmd = TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN;
	TCS34725_Write(TCS34725_ENABLE,cmd);
}

/*******************************************************************************
 * @brief TCS34725澶辫兘
 *
 * @return None
*******************************************************************************/
void TCS34725_Disable(void)
{
	uint8_t cmd = 0;
	
	cmd = TCS34725_Read(TCS34725_ENABLE);
	cmd = cmd & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
	TCS34725_Write(TCS34725_ENABLE, cmd);
}

/*******************************************************************************
 * @brief TCS34725鍒濆鍖?
 *
 * @return ID - ID瀵勫瓨鍣ㄤ腑鐨勫€?
*******************************************************************************/
uint8_t TCS34725_Init(void)
{
	uint8_t id=0;
	
	iic_init(); 
	id = TCS34725_Read(TCS34725_ID);  //TCS34725 鐨?ID 鏄?0x44 鍙互鏍规嵁杩欎釜鏉ュ垽鏂槸鍚︽垚鍔熻繛鎺?0x4D鏄疶CS34727;
	if(id==0x4D | id==0x44)
	{
		TCS34725_SetIntegrationTime(TCS34725_INTEGRATIONTIME_24MS);
		TCS34725_SetGain(TCS34725_GAIN_1X);
		TCS34725_Enable();
		return 1;
	}
	return 0;
}

/*******************************************************************************
 * @brief TCS34725鑾峰彇鍗曚釜閫氶亾鏁版嵁
 *
 * @return data - 璇ラ€氶亾鐨勮浆鎹㈠€?
*******************************************************************************/
uint16_t TCS34725_GetChannelData(uint8_t reg)
{
	uint8_t tmp[2] = {0,0};
	uint16_t data;
	
	tmp[0] = TCS34725_Read(reg);
	tmp[1] = TCS34725_Read(reg+1);
	data = (tmp[1] << 8) | tmp[0];
	
	return data;
}

/*******************************************************************************
 * @brief TCS34725鑾峰彇鍚勪釜閫氶亾鏁版嵁
 *
 * @return 1 - 杞崲瀹屾垚锛屾暟鎹彲鐢?
 *   	   0 - 杞崲鏈畬鎴愶紝鏁版嵁涓嶅彲鐢?
*******************************************************************************/
uint8_t TCS34725_GetRawData(COLOR_RGBC *rgbc)
{
	uint8_t status = TCS34725_STATUS_AVALID;
	
	status = TCS34725_Read(TCS34725_STATUS);
	
	if(status & TCS34725_STATUS_AVALID)
	{
		rgbc->c = TCS34725_GetChannelData(TCS34725_CDATAL);	
		rgbc->r = TCS34725_GetChannelData(TCS34725_RDATAL);	
		rgbc->g = TCS34725_GetChannelData(TCS34725_GDATAL);	
		rgbc->b = TCS34725_GetChannelData(TCS34725_BDATAL);
		return 1;
	}
	return 0;
}

//RGB杞琀SL
void RGBtoHSL(COLOR_RGBC *Rgb, COLOR_HSL *Hsl)
{
	u8 maxVal,minVal,difVal;
	u8 r = Rgb->r*100/Rgb->c;   //[0-100]
	u8 g = Rgb->g*100/Rgb->c;
	u8 b = Rgb->b*100/Rgb->c;
	
	maxVal = max3v(r,g,b);
	minVal = min3v(r,g,b);
	difVal = maxVal-minVal;
	
	//璁＄畻浜害
	Hsl->l = (maxVal+minVal)/2;   //[0-100]
	
	if(maxVal == minVal)//鑻=g=b,鐏板害
	{
		Hsl->h = 0; 
		Hsl->s = 0;
	}
	else
	{
		//璁＄畻鑹茶皟
		if(maxVal==r)
		{
			if(g>=b)
				Hsl->h = 60*(g-b)/difVal;
			else
				Hsl->h = 60*(g-b)/difVal+360;
		}
		else
			{
				if(maxVal==g)Hsl->h = 60*(b-r)/difVal+120;
				else
					if(maxVal==b)Hsl->h = 60*(r-g)/difVal+240;
			}
		
		//璁＄畻楗卞拰搴?
		if(Hsl->l<=50)Hsl->s=difVal*100/(maxVal+minVal);  //[0-100]
		else
			Hsl->s=difVal*100/(200-(maxVal+minVal));
	}
}
