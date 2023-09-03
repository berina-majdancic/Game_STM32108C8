#include "mydriver.h"
#include "stm32f10x.h"   
void pinMode(uint16_t pinNumber, uint16_t PinMode)
{
	if((pinNumber<=A7)) //A CRL 
	{
		
		RCC->APB2ENR|=(1<<2);
		if(PinMode==OUTPUT)
		{
		GPIOA->CRL|=(1<<pinNumber*4);
		GPIOA->CRL|=(1<<(pinNumber*4)+1);
		GPIOA->CRL&=~(1<<(pinNumber*4)+2);
		GPIOA->CRL&=~(1<<(pinNumber*4)+3);
		}
		else if(PinMode==INPUT)
		{
		GPIOA->CRL&=~(1<<pinNumber*4);
		GPIOA->CRL&=~(1<<(pinNumber*4)+1);
		GPIOA->CRL|=(1<<(pinNumber*4)+2);
		GPIOA->CRL&=~(1<<(pinNumber*4)+3);
		}
	}
	if((pinNumber<=A15)&&(pinNumber>A7))//A CRH
	{
		RCC->APB2ENR|=(1<<2);
		if(PinMode==OUTPUT)
		{
		GPIOA->CRH|=(1<<((pinNumber%8)*4));
		GPIOA->CRH|=(1<<((pinNumber%8)*4+1));
		GPIOA->CRH&=~(1<<((pinNumber%8)*4+2));
		GPIOA->CRH&=~(1<<((pinNumber%8)*4+3));
		}
		else if(PinMode==INPUT)
		{
		GPIOA->CRH&=~(1<<((pinNumber%8)*4));
		GPIOA->CRH&=~(1<<((pinNumber%8)*4+1));
		GPIOA->CRH|=(1<<((pinNumber%8)*4+2));
		GPIOA->CRH&=~(1<<((pinNumber%8)*4+3));
		}
	}
	if((pinNumber>A15)&&(pinNumber<=B7))//B CRL
	{
		RCC->APB2ENR|=(1<<3);
		if(PinMode==OUTPUT)
		{
		GPIOB->CRL|=(1<<(pinNumber%16)*4);
		GPIOB->CRL|=(1<<(pinNumber%16)*4+1);
		GPIOB->CRL&=~(1<<(pinNumber%16)*4+2);
		GPIOB->CRL&=~(1<<(pinNumber%16)*4+3);
		}
		else if(PinMode==INPUT)
		{
		GPIOB->CRL&=~(1<<(pinNumber%16)*4);
		GPIOB->CRL&=~(1<<(pinNumber%16)*4+1);
		GPIOB->CRL|=(1<<(pinNumber%16)*4+2);
		GPIOB->CRL&=~(1<<(pinNumber%16)*4+3);
		}
		
	}
	if((pinNumber>B7)&&(pinNumber<=B15))//B CRH
	{
		RCC->APB2ENR|=(1<<3);
		if(PinMode==OUTPUT)
		{
		GPIOB->CRH|=(1<<(pinNumber%24)*4);
		GPIOB->CRH|=(1<<(pinNumber%24)*4+1);
		GPIOB->CRH&=~(1<<(pinNumber%24)*4+2);
		GPIOB->CRH&=~(1<<(pinNumber%24)*4+3);
		}
		else if(PinMode==INPUT)
		{
		GPIOB->CRH&=~(1<<(pinNumber%24)*4);
		GPIOB->CRH&=~(1<<(pinNumber%24)*4+1);
		GPIOB->CRH|=(1<<(pinNumber%24)*4+2);
		GPIOB->CRH&=~(1<<(pinNumber%24)*4+3);
		}
	}
	if((pinNumber>=0x20)&&(pinNumber<=0x22))//C CRH
	{
		RCC->APB2ENR|=(1<<4);
		if(PinMode==OUTPUT)
		{
		GPIOC->CRH|=(1<<(pinNumber%31)*20);
		GPIOC->CRH|=(1<<(pinNumber%31)*20+1);
		GPIOC->CRH&=~(1<<(pinNumber%31)*20+2);
		GPIOC->CRH&=~(1<<(pinNumber%31)*20+3);
		}
		else if(PinMode==INPUT)
		{
			GPIOC->CRH&=~(1<<pinNumber%31)*20;
			GPIOC->CRH&=~(1<<(pinNumber%31)*20+1);
			GPIOC->CRH|=(1<<(pinNumber%31)*20+2);
			GPIOC->CRH&=~(1<<(pinNumber%31)*20+3);
		}
	}
	if(pinNumber==0x23&&PinMode==OUTPUT) //ENTIRE PORT A
	{	
		RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
		GPIOA->CRL|=GPIO_CRL_MODE;
		GPIOA->CRL &=~GPIO_CRL_CNF;
		GPIOA->CRH|=GPIO_CRL_MODE;
		GPIOA->CRH &=~GPIO_CRL_CNF;
		
	}
	if(pinNumber==0x24&&PinMode==OUTPUT) //ENTIRE PORT B
	{	
		RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
		GPIOB->CRL|=GPIO_CRL_MODE;
		GPIOB->CRL &=~GPIO_CRL_CNF;
		GPIOB->CRH|=GPIO_CRL_MODE;
		GPIOB->CRH &=~GPIO_CRL_CNF;
		
	}
	if(pinNumber==0x25&&PinMode==OUTPUT) //ENTIRE PORT C
	{	
		RCC->APB2ENR|=RCC_APB2ENR_IOPCEN;
		GPIOC->CRH|=GPIO_CRL_MODE;
		GPIOC->CRH &=~GPIO_CRL_CNF;
		
	}
	
}

void DigitalWrite(uint16_t PinNumber, bool Value)
{
	if(PinNumber<=A15) //PORT A
	{
		if(Value==true)
		{
			GPIOA->ODR|=(1<<PinNumber);
		}
		else if(Value==false)
		{
			GPIOA->ODR&=~(1<<PinNumber);
		}
	}
	if(PinNumber>=B0&&PinNumber<=B15) //PORT B
	{
		if(Value==true)
		{
			GPIOB->ODR|=(1<<PinNumber%16);
		}
		else if(Value==false)
		{
			GPIOB->ODR&=~(1<<PinNumber%16);
		}
	}
	if(PinNumber>=C13&&PinNumber<=C15) //PORT C
	{
		if(Value==true)
		{
			GPIOC->ODR|=(1<<(PinNumber%31)*13);
		}
		else if(Value==false)
		{
			GPIOC->ODR&=~(1<<(PinNumber%31)*13);
		}
	} 
	if(PinNumber==A_ALL)
	{
		if(Value==true)
		{
			for (int i=A0;i<B0;i++) GPIOA->ODR|=(1<<i);
		}
		else if(Value==false)
		{
			for (int i=A0;i<B0;i++) GPIOA->ODR&=~(1<<i);
		}
	}
	if(PinNumber==B_ALL)
	{
		if(Value==true)
		{
			for (int i=A0;i<B0;i++) GPIOB->ODR|=(1<<i);
		}
		else if(Value==false)
		{
			for (int i=A0;i<B0;i++) GPIOB->ODR&=~(1<<i);
		}
	}
	if(PinNumber==C_ALL)
	{
		if(Value==true)
		{
			for (int i=A13;i<B0;i++) GPIOC->ODR|=(1<<i);
		}
		else if(Value==false)
		{
			for (int i=A13;i<B0;i++) GPIOC->ODR&=~(1<<i);
		}
	}
}



bool DigitalRead(uint16_t pinNumber)
{
	if(pinNumber<=0x0f)
	{
		return (GPIOA->IDR &(1<<(pinNumber))) ;
	}
	else if(pinNumber<=0x1f)
	{
		return (GPIOB->IDR &(1<<(pinNumber%16))) ;
	}
	else if(pinNumber<=0x22)
	{
		return (GPIOC->IDR &(1<<(pinNumber%31)*13)) ;
	}
	
}
