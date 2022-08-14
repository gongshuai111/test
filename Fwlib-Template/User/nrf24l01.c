#include "nrf24l01.h"
#include "spi.h"

const u8 RF2G4_ADDR_TX[5] = { 0X6A,0X69,0X78,0X69,0X6E} ;		// 0X6A,0X69,0X78,0X69,0X6E
const u8 RF2G4_ADDR_RX[5] = { 0X6A,0X69,0X78,0X69,0X6E} ;		// ASCII：jixin

// 写寄存器函数
u8 NRF24L01_write_reg(u8 reg,u8 data)
{
	
				u8 value;
				CSN_LOW;
				value=SPI_NRF24L01_READ_Write(reg);
				SPI_NRF24L01_READ_Write(data );
				CSN_HIGH;
				return value;
				}
//写寄存器
u8 nrf24l01_write_reg_cont(u8 reg,u8 *Pdata,u8 number)
{
				u8 nnumber;
				u8 value;
				CSN_LOW;
				value=SPI_NRF24L01_READ_Write( reg);
				for(;nnumber <number;nnumber++)
				{
				SPI_NRF24L01_READ_Write(*Pdata++);	
				}
				CSN_HIGH;
				return value;
	
}
//读寄存器函数
u8 nrf24l01_read_reg(u8 reg)
{
				u8 value;
				CSN_LOW;
				SPI_NRF24L01_READ_Write(reg);
				value=SPI_NRF24L01_READ_Write(0xff);

				CSN_HIGH;
				return value;
}
//读寄存器函数
u8 nrf24l01_read_const(u8 reg,u8 *Pdata,u8 number)
{
				u8 nnumber;
				u8 value;
				CSN_LOW ;
				value=SPI_NRF24L01_READ_Write(reg);
				for(;nnumber <number ;nnumber ++)
				{

				Pdata[nnumber]=SPI_NRF24L01_READ_Write(0xff);
				}

				CSN_HIGH;
				return value;
}

u8 nrf24l01_check(void)
{
	
	u8 Array_test[5]={0x50,0x50,0x50,0x50,0x50};
	u8 c_test=0;
	nrf24l01_write_reg_cont(W_REGISTER+TX_ADDR,Array_test,TX_ADR_WIDTH);
	c_test=nrf24l01_write_reg_cont(TX_ADDR,Array_test,TX_ADR_WIDTH);
	for(;c_test<5;c_test++)
	{
		
		if(Array_test[c_test]!=0x50)
		break;
		
	}
	if(c_test!=5)
		return 1;
	else
		return 0;//检测正确
}
// 初始化nrf24l01为接收模式
void NRF24L01_RX_Mode(void)
{
	  CE_LOW;
		nrf24l01_write_reg_cont(W_REGISTER+RX_ADDR_P0,(u8 *)RF2G4_ADDR_TX,TX_ADR_WIDTH);//接收地址
		NRF24L01_write_reg(W_REGISTER+EN_AA,0x01);    		// 使能通道0的自动应答
		NRF24L01_write_reg(W_REGISTER+EN_RXADDR,0x01);		// 使能通道0的接收地址
	  NRF24L01_write_reg(W_REGISTER+SETUP_AW,5);       //设置地址宽度
	  NRF24L01_write_reg(W_REGISTER+RF_CH,40);	     	// 设置RF通信频率
		NRF24L01_write_reg(W_REGISTER+RX_PW_P0,14);	  	// 设置通道0的有效数据宽度（14位）
	  NRF24L01_write_reg(W_REGISTER+RF_SETUP,0x0F);		// 设置:发射功率7dBm、射频数据率250kbps
	  NRF24L01_write_reg(W_REGISTER+CONFIG, 0x0F);		// 配置参数;接收模式、开机模式、CRC=2Byte、开启CRC、。。。
	  CE_HIGH;
}
//初始化为发送模式
void NRF24L01_TX_Mode(void)
{
	
	 CE_LOW;
	 nrf24l01_write_reg_cont(W_REGISTER+TX_ADDR,(u8*)RF2G4_ADDR_TX,TX_ADR_WIDTH);//设置发射地址
	 nrf24l01_write_reg_cont(W_REGISTER+RX_ADDR_P0,(u8*)RF2G4_ADDR_RX,TX_ADR_WIDTH);//设置自动应答地址应与发射地址已知
   NRF24L01_write_reg(W_REGISTER+EN_AA,0x01);//使能通道0自动应答
	 NRF24L01_write_reg(W_REGISTER+EN_RXADDR,0x01);//接收通道地址允许
	 NRF24L01_write_reg(W_REGISTER+SETUP_AW,5);//设置地址宽度
	 NRF24L01_write_reg(W_REGISTER+RF_CH,40);//设置通信频率。与接收端一致
	
	 NRF24L01_write_reg(W_REGISTER+SETUP_RETR,0x1A);//设置自动重发时间
	
	 NRF24L01_write_reg(W_REGISTER+RF_SETUP,0x0F);//设置发射功率、
	 NRF24L01_write_reg(W_REGISTER+CONFIG,0x0E);  //设置接收内模式
	  CE_HIGH;//10us后启动发送
	
}
// SI24R1发送一帧数据
// P_Data	= 待发送数据首地址
// N_Data	= 待发送数据的个数
// return	= 发送完成状况
u8 NRF24L01_TX_Packet(u8*Pdata,u8 Ndata)
{
	u8 val_reg;
	CE_LOW;
	
	nrf24l01_write_reg_cont(W_TX_PAYLOAD,Pdata ,Ndata );//将要发送的数据写入发送缓存器
	 CE_HIGH;//启动发送
	while(GPIO_ReadOutputDataBit(GPIOB,NRF24L01_GPIO_IRQ)!=RESET);//等于0表示发送完成
	val_reg=nrf24l01_read_reg(STATUS);
	NRF24L01_write_reg(W_REGISTER+STATUS,val_reg);
	if(val_reg & TX_MAX)
	{
		NRF24L01_write_reg(FLUSH_TX,0xFF);
		return TX_FAIL_MAX;
	}
	if(val_reg & TX_OK )
	{
		return TX_SUCCESS;		// 返回发送成功
		
	}
	return 0xFF;				// 返回发送失败

}
u8 NRF24L01_RX_Packet(u8*Pdata,u8 nnumber)
{
		u8 val_reg;
		
		val_reg=nrf24l01_read_reg(STATUS);
	  NRF24L01_write_reg(W_REGISTER+STATUS,val_reg);
		if(val_reg & RX_OK)
		{
			nrf24l01_read_const(R_REGISTER,Pdata ,nnumber);
			NRF24L01_write_reg(FLUSH_RX,0xFF);
			return RX_SUCCESS;
		}
   return RX_FAIL;
		
	
	
}


