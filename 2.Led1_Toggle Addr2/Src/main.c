///LED pin toggle

///PORT  :A
// PIN   :12
#include<stdint.h>

#define PERIPH_BASE               (0x40000000UL) // base address of map we use whenever we need it


//0x4000 0000 +0x0002 0000 = 0x4002 0000 , 0x4002 0000 is the starting Address of AHBI  and Port A register

#define AHB1_PHERIPH_OFFSET       (0x00020000UL)
#define AHB1_PHERIPH_BASE         (PERIPH_BASE + AHB1_PHERIPH_OFFSET) // base value of AHBI bus = 0x4002 0000

#define GPIOD_OFFSET              (0x0C00UL)
#define GPIOD_BASE                (AHB1_PHERIPH_BASE + GPIOD_OFFSET) //base value of GPIO bus = 0x40020C00

#define RCC_OFFSET                (0x3800UL)
#define RCC_BASE                  (AHB1_PHERIPH_BASE + RCC_OFFSET) //base value of RCC bus = 0x4002 3800

/// register Section go to reference manual

/*#define AHB1EN_R_OFFSET           (0x30UL)
#define RCC_AHB1ENR              (*(volatile uint32_t* ) (RCC_BASE + AHB1EN_R_OFFSET)) //ClkCntrlReg = 0x4002 3800 + 0x30UL = 0x40023830

#define GPIOD_MODER_OFFSET        (0x00UL)
#define GPIOD_MODER_R             (*(volatile uint32_t*)(GPIOD_BASE + GPIOD_MODER_OFFSET)) //GPIOD PORT REG = 0x400 20C00 + 0x00UL = 0x40020C00

#define GPIOD_ODR_OFFSET          (0x14UL)
#define GPIOD_ODR_R               (*(volatile uint32_t*)(GPIOD_BASE  + GPIOD_ODR_OFFSET)) //GPIOD OUTPU DATA REG = 0x40020C00 + 0x14UL = 0x40020C14
*/
#define GPIOD_EN                  (1U << 3) // 0000 0000 0000 0000 0000 0000 0000 1000
#define GPIOC_EN                  (1U << 2) // 0000 0000 0000 0000 0000 0000 0000 0100
#define GPIOB_EN                  (1U << 2) // 0000 0000 0000 0000 0000 0000 0000 0010

#define PIN12                     (1U << 12)
#define LEDPIN_1                    (PIN12)

#define PIN13                     (1U << 13)
#define LEDPIN_2                    (PIN13)

#define PIN14                     (1U << 14)
#define LEDPIN_3                    (PIN14)

#define PIN15                     (1U << 15)
#define LEDPIN_4                   (PIN15)
#define __IO volatile




 typedef struct{

	 __IO uint32_t MODER;
	 __IO uint32_t DUMMY[4];
	 __IO uint32_t ODR;


 }GPIO_R_;


 typedef struct
 {
	 __IO uint32_t DUMMY_[12] ;
	 __IO uint32_t AHB1ENR_ ;
 }RCC_EN_R;

#define RCC        ((RCC_EN_R*)RCC_BASE )
#define GPIO_D_    ((GPIO_R_*)GPIOD_BASE  )


int main(void)

{
	GPIO_R_ volatile *const pmodereg = (GPIO_R_*)GPIOD_BASE;

	// enable clock access
	// set PD12  High

	/*RCC_AHB1ENR  |=  GPIOD_EN;

	GPIOD_MODER_R |= (1 << 24);
	GPIOD_MODER_R &= ~(1 << 25);

	GPIOD_MODER_R |= (1 << 26);
	GPIOD_MODER_R &= ~(1 << 27);

	GPIOD_MODER_R |= (1 << 28);
	GPIOD_MODER_R &= ~(1 << 29);

	GPIOD_MODER_R |= (1 << 30);
	GPIOD_MODER_R &= ~(1 << 31);*/


	RCC->AHB1ENR_ |=  GPIOD_EN;

	//GPIO_D_->MODER |= (1 << 24);
	//GPIO_D_->MODER  &= ~(1 << 25);
	pmodereg->MODER |= (1 << 24);
	pmodereg->MODER &= ~(1 << 25);




	while(1)
	{
		//GPIOD_ODR_R ^= LEDPIN_1 ;

		GPIO_D_->ODR ^= LEDPIN_1 ;

		for(uint32_t i =0 ; i < 100000 ; i++);
	}





}













