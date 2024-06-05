#include "timer.h"

void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //鏃堕挓浣胯兘
	
	//瀹氭椂鍣═IM3鍒濆鍖?
	TIM_TimeBaseStructure.TIM_Period = arr; //璁剧疆鍦ㄤ笅涓€涓洿鏂颁簨浠惰鍏ユ椿鍔ㄧ殑鑷姩閲嶈杞藉瘎瀛樺櫒鍛ㄦ湡鐨勫€?
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //璁剧疆鐢ㄦ潵浣滀负TIMx鏃堕挓棰戠巼闄ゆ暟鐨勯鍒嗛鍊?
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //璁剧疆鏃堕挓鍒嗗壊:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM鍚戜笂璁℃暟妯″紡
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //鏍规嵁鎸囧畾鐨勫弬鏁板垵濮嬪寲TIMx鐨勬椂闂村熀鏁板崟浣?
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //浣胯兘鎸囧畾鐨凾IM3涓柇,鍏佽鏇存柊涓柇

	//涓柇浼樺厛绾VIC璁剧疆
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3涓柇
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //鍏堝崰浼樺厛绾?绾?
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //浠庝紭鍏堢骇3绾?
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ閫氶亾琚娇鑳?
	NVIC_Init(&NVIC_InitStructure);  //鍒濆鍖朜VIC瀵勫瓨鍣?


	TIM_Cmd(TIM3, ENABLE);  //浣胯兘TIMx					 
}
