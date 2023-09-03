#include "stm32f10x.h" 
#include "fonts.h"
#include "ssd1306.h"
#include "ssd1306_i2c.h"

//A0 i A6 input 1000 
long map(long x, long in_min, long in_max, long out_min, long out_max);
void delay(int x)
{
	for(int i=0;i<x*10000;i++){;}
}
int main(void){
	int raw,playerx,score=48,rx,ry,oldscore=48, lives=51,level=49,t=60,x,y,rx1,ry1,select=1,ys;
	bool firsttime=true,menu=true;
	RCC->APB2ENR|=RCC_APB2ENR_IOPAEN | RCC_APB2ENR_ADC1EN;
	RCC->AHBENR|=RCC_AHBENR_DMA1EN;
	RCC->APB2ENR |=(1<<0)|(1<<2)|(1<<9);
	SSD1306_Init();
	RCC->CFGR|=RCC_CFGR_ADCPRE_DIV6;
	RCC->APB2ENR|= RCC_APB2ENR_IOPBEN;

		 GPIOB->CRL|=(1<<0)|(1<<1);
		 GPIOB->CRL&=~(1<<2);
	SSD1306_Init();
	
	RCC->APB2ENR |=(1<<0)|(1<<2)|(1<<9);
	RCC->CFGR|=(2<<14);
	ADC1->SQR3|=(0<<0);
	ADC1->CR2|=(3<<0);
	ADC1->CR2|=(1<<3);
	while(ADC1->CR2 & ADC_CR2_RSTCAL){;}
	ADC1->CR2|=(1<<2);
	while(ADC1->CR2 & ADC_CR2_CAL){;}
	ADC1->CR2|=(1<<0);
	//------------------------- VARIABLES-------------------------//
uint16_t adcReadings[2]={0,0}; //raw readings from two chanells

	/*
	select sampling time for coversion on specified chanell -> our case chanell 0
	*/
	ADC1->SMPR2 |= ADC_SMPR2_SMP6; //0x00000007 = 0111
	ADC1->SMPR2 |= ADC_SMPR2_SMP0; //0x00000007 = 0111
	//ADC1->SMPR2 |= ADC_SMPR2_SMP1;

	//select sequence  -> we now have two chanel so we  "point" to first sequence on SQR3 register for channel 0 
	//and to second sequence for channel 6
	ADC1->SQR1 |=(1<<20);  //two chanel conversion
	ADC1 ->SQR3 |=(0<<0);	//first sequence for channel 0
	ADC1 ->SQR3 |=(6<<5);	//second sequence for channel 6
	//	ADC1 ->SQR3 |=(1<<10);
//enable SCAN and DMA mode
		ADC1->CR1|=ADC_CR1_SCAN;
		ADC1->CR2|=ADC_CR2_DMA;


//------------------------- DMA -------------------------//
		//DMA must explain with datasheet
		DMA1_Channel1->CPAR=(uint32_t)(&(ADC1->DR));
		DMA1_Channel1->CMAR =(uint32_t)adcReadings;
		DMA1_Channel1->CNDTR=2;
		
		DMA1_Channel1->CCR |=DMA_CCR1_CIRC|DMA_CCR1_MINC|DMA_CCR1_MSIZE_0|DMA_CCR1_PSIZE_0;
		
		//turn on after all other settings are finished
		DMA1_Channel1->CCR|=DMA_CCR1_EN;
		
//------------------------- END DMA ----------------------//
rx=rand()%120+1;
		ry=rand()%50+20;
		

	while(1)
	{
		SSD1306_Fill(SSD1306_COLOR_BLACK);

		while(menu)
		{
			
			switch(select)
			{
				case 1:SSD1306_GotoXY(20,10);SSD1306_Puts("Level 1",&Font_7x10,SSD1306_COLOR_WHITE); SSD1306_GotoXY(10,25);
			SSD1306_Puts("Level 2",&Font_7x10,SSD1306_COLOR_WHITE);
			SSD1306_GotoXY(10,40);
			SSD1306_Puts("Level 3",&Font_7x10,SSD1306_COLOR_WHITE);
				 break;
				case 2:	SSD1306_GotoXY(10,10) ;SSD1306_Puts("Level 1",&Font_7x10,SSD1306_COLOR_WHITE);
			SSD1306_GotoXY(20,25);SSD1306_Puts("Level 2",&Font_7x10,SSD1306_COLOR_WHITE);SSD1306_GotoXY(10,40);
			SSD1306_Puts("Level 3",&Font_7x10,SSD1306_COLOR_WHITE); break;
				case 3:        SSD1306_GotoXY(10,10);              SSD1306_Puts("Level 1",&Font_7x10,SSD1306_COLOR_WHITE);SSD1306_GotoXY(10,25);
			SSD1306_Puts("Level 2",&Font_7x10,SSD1306_COLOR_WHITE);
			SSD1306_GotoXY(20,40);SSD1306_Puts("Level 3",&Font_7x10,SSD1306_COLOR_WHITE); break;
			}
			x= map(adcReadings[0],0,4096,0,107);
				 y=  map(adcReadings[1],0,4096,100,0);
		
			if(y>70){  select++; if(select>3)select=3;SSD1306_Fill(SSD1306_COLOR_BLACK);while(y>70){ y=  map(adcReadings[1],0,4096,100,0);}}

			if(y<20){select--;SSD1306_Fill(SSD1306_COLOR_BLACK);while(y<20){ y=  map(adcReadings[1],0,4096,100,0);}}
			
			if(x>90){ menu=false;level=select+48;}

			SSD1306_UpdateScreen();
			//SSD1306_Putc(score,&Font_7x10,SSD1306_COLOR_WHITE);
		}
		if(lives>0)
		{
			if(t<1&&level==50){t=60; lives--;} //timer lvl 2
			if(t<1&&level==51){t=40; lives--;} //timer lvl 3
			if(lives==48) {level=49;lives=51;score=48;}
			SSD1306_Fill(SSD1306_COLOR_BLACK);
			SSD1306_GotoXY(1,1);
			SSD1306_Puts("S:",&Font_7x10,SSD1306_COLOR_WHITE);
			SSD1306_Putc(score,&Font_7x10,SSD1306_COLOR_WHITE);
			SSD1306_GotoXY(45,1);
			SSD1306_Puts("L:",&Font_7x10,SSD1306_COLOR_WHITE);
			SSD1306_Putc(lives,&Font_7x10,SSD1306_COLOR_WHITE);	
			SSD1306_GotoXY(90,1);
			SSD1306_Puts("LVL:",&Font_7x10,SSD1306_COLOR_WHITE);
			SSD1306_Putc(level,&Font_7x10,SSD1306_COLOR_WHITE);	
			switch(level)
			{
				case 49:
				 x= map(adcReadings[0],0,4096,0,107);
				 y=  map(adcReadings[1],0,4096,100,0);if(y<20)y=20;
				break;
				case 50:
				 x= map(adcReadings[0],0,4096,0,119);
				 y=  map(adcReadings[1],0,4096,100,0);if(y<20)y=10;
				break;
				case 51:
				 x= map(adcReadings[0],0,4096,0,119);
				 y=  map(adcReadings[1],0,4096,100,0);if(y<20)y=10;
			}
			
			if(y>50)y=50;
			
			if(oldscore<score||t<1)
			{
					rx=rand()%120+1;
					ry=rand()%30+20;
				rx1=rx;ry1=ry;
			}
			oldscore=score;
			
			
			if(level==49) //LVL 1
			{
			SSD1306_GotoXY(x,y);
			SSD1306_Puts("'_'",&Font_7x10,SSD1306_COLOR_WHITE);
			SSD1306_GotoXY(rx,ry);
			SSD1306_Puts("*",&Font_7x10,SSD1306_COLOR_WHITE);
			if((rx+20>x&&rx<x+20)&&(ry>y-10&&ry<y+10)) //hitbox
			{score++;delay(1);} //add score
			if(score>57) 
			{
				score=48;
				level++;
			}
			}
			else if(level==50) //LVL 2
			{
				SSD1306_GotoXY(x,y);
				SSD1306_Puts("_",&Font_7x10,SSD1306_COLOR_WHITE);
				SSD1306_GotoXY(rx,ry);
				SSD1306_Puts("*",&Font_7x10,SSD1306_COLOR_WHITE);
				if((rx+12>x&&rx<x+12)&&(ry>y&&ry<y+10)) //hitbox
				{score++;t+=12;delay(1);}		//add score and some time to our timer
				if(score>57) 
				{
					score=48;
					level++;
				}
				t--; //timer--
			}
			else if(level==51) //LVL 3
			{
				SSD1306_GotoXY(x,y);
			SSD1306_Putc('_',&Font_7x10,SSD1306_COLOR_WHITE);
				
		
				rx=rand()%(rx1)+(rx1);
				ry=rand()%(ry1)+(ry1);
				if(ry<20)ry=20;
				if(rx<1)rx=1;
				if(ry>40)ry=40;
				if(rx>120)rx=120;
			
		
			
			SSD1306_GotoXY(rx,ry);
			SSD1306_Puts("*",&Font_7x10,SSD1306_COLOR_WHITE);
			if((rx+12>x&&rx<x+12)&&(ry>y&&ry<y+10)) //hitbox
			{score++;t+=5;delay(1);}		//add score and some time to our timer
			if(score>57) 
			{
				score=48;
				level=52;
			}
			t--; //timer--
			}
			SSD1306_UpdateScreen();
	}
	}
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}