void SysTick_Delay_Ms( __IO uint32_t ms)
{
    uint32_t i;
    SysTick_Config(SystemCoreClock/1000);	
	for (i=0; i<ms; i++) 
	{
		// ���� 1 ʱ����ȡ��λ���� 0
		while ( !((SysTick->CTRL)&(1<<16)) );
	}
	// �ر� SysTick ��ʱ��
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
	
}
void SysTick_Delay_Us( __IO uint32_t us)
{
	uint32_t i;
	SysTick_Config(SystemCoreClock/1000000);
	for (i=0; i<us; i++) 
	{// ����������ֵ��С�� 0 ��ʱ�� CRTL �Ĵ�����λ 16 ���� 1
		while ( !((SysTick->CTRL)&(1<<16)) );
	}
	// �ر� SysTick ��ʱ��
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
	
	
	
}