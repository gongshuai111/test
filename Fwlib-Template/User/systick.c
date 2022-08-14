void SysTick_Delay_Ms( __IO uint32_t ms)
{
    uint32_t i;
    SysTick_Config(SystemCoreClock/1000);	
	for (i=0; i<ms; i++) 
	{
		// 当置 1 时，读取该位会清 0
		while ( !((SysTick->CTRL)&(1<<16)) );
	}
	// 关闭 SysTick 定时器
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
	
}
void SysTick_Delay_Us( __IO uint32_t us)
{
	uint32_t i;
	SysTick_Config(SystemCoreClock/1000000);
	for (i=0; i<us; i++) 
	{// 当计数器的值减小到 0 的时候， CRTL 寄存器的位 16 会置 1
		while ( !((SysTick->CTRL)&(1<<16)) );
	}
	// 关闭 SysTick 定时器
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
	
	
	
}