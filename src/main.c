
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int count = 0;

void delay(uint32_t time)
{
	while(time--);
}

void GPIO_Config()
{
	RCC ->CR |= 0x00030000; 		// HSEON and HSEONRDY enable
	while(!(RCC ->CR & 0x00020000));// HSEON Ready Flag wait
	RCC ->CR |= 0x00080000;  		// CSS Enable
	RCC ->PLLCFGR |= 0x00400000; 	// PLL e HSE sectik
	RCC ->PLLCFGR |= 0x00000004; 	// PLL M = 4
	RCC ->PLLCFGR |= 0x00005A00;	// PLL N = 168
	RCC ->PLLCFGR |= 0x00000000; 	// PLL P = 2
	RCC ->CFGR |= 0x00000000;		// AHB Prescaler = 1
	RCC ->CFGR |= 0x00080000;		// APB2 Prescaler = 2
	RCC ->CFGR |= 0x00001400;		// APB1 Prescaler = 4
	RCC ->CIR |= 0x00080000;		// HSERDY Flah Clear
	RCC ->CIR |= 0x00800000;		// CSS Flag Clear

	RCC ->AHB1ENR = 0x00000009; 	//GPIOA ve GPIOD Aktif

	GPIOD ->MODER = 0x55000000; 	// 12 13, 14 ,15 yani ledlerin bulundugu pinler dijital outputs
	GPIOD ->OTYPER = 0x00000000; 	// 12 , 13 , 14 , 15 pins Push Pull
	GPIOD ->OSPEEDR = 0xFF000000; 	// 12 , 13 , 14 , 15 pins 100MHz
	GPIOD ->PUPDR = 0x00000000; 	// 12 , 13 , 14 , 15 pins NO PULL

}

int main(void)
{
	GPIO_Config();

  while (1)
  {
	  if(GPIOA ->IDR & 0x00000001) 	// A Portunun 1 inci pinindeki degeri oku
	  {
		  while(GPIOA ->IDR & 0x00000001); 	// butona basma devam bitene kadar bekle
		  delay(1680000);

		  count++;
	  }

	  if(count %2 == 0)	// count degerinin 2 ile tam bolunuyorsa
	  {
		  GPIOD ->ODR = 0x00000000;
	  }
	  else
	  {
		  GPIOD ->ODR = 0x000F000;	// 12 , 13, 14 ,14 Pinle aktif edildi
	  }
  }
}

/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
