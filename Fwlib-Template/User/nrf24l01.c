#include "nrf24l01.h"
#include "spi.h"

const u8 RF2G4_ADDR_TX[5] = { 0X6A,0X69,0X78,0X69,0X6E} ;		// 0X6A,0X69,0X78,0X69,0X6E
const u8 RF2G4_ADDR_RX[5] = { 0X6A,0X69,0X78,0X69,0X6E} ;		// ASCII��jixin

// д�Ĵ�������
u8 NRF24L01_write_reg(u8 reg,u8 data)
{
	
				u8 value;
				CSN_LOW;
				value=SPI_NRF24L01_READ_Write(reg);
				SPI_NRF24L01_READ_Write(data );
				CSN_HIGH;
				return value;
				}
//д�Ĵ���
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
//���Ĵ�������
u8 nrf24l01_read_reg(u8 reg)
{
				u8 value;
				CSN_LOW;
				SPI_NRF24L01_READ_Write(reg);
				value=SPI_NRF24L01_READ_Write(0xff);

				CSN_HIGH;
				return value;
}
//���Ĵ�������
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
		return 0;//�����ȷ
}
// ��ʼ��nrf24l01Ϊ����ģʽ
void NRF24L01_RX_Mode(void)
{
	  CE_LOW;
		nrf24l01_write_reg_cont(W_REGISTER+RX_ADDR_P0,(u8 *)RF2G4_ADDR_TX,TX_ADR_WIDTH);//���յ�ַ
		NRF24L01_write_reg(W_REGISTER+EN_AA,0x01);    		// ʹ��ͨ��0���Զ�Ӧ��
		NRF24L01_write_reg(W_REGISTER+EN_RXADDR,0x01);		// ʹ��ͨ��0�Ľ��յ�ַ
	  NRF24L01_write_reg(W_REGISTER+SETUP_AW,5);       //���õ�ַ���
	  NRF24L01_write_reg(W_REGISTER+RF_CH,40);	     	// ����RFͨ��Ƶ��
		NRF24L01_write_reg(W_REGISTER+RX_PW_P0,14);	  	// ����ͨ��0����Ч���ݿ�ȣ�14λ��
	  NRF24L01_write_reg(W_REGISTER+RF_SETUP,0x0F);		// ����:���书��7dBm����Ƶ������250kbps
	  NRF24L01_write_reg(W_REGISTER+CONFIG, 0x0F);		// ���ò���;����ģʽ������ģʽ��CRC=2Byte������CRC��������
	  CE_HIGH;
}
//��ʼ��Ϊ����ģʽ
void NRF24L01_TX_Mode(void)
{
	
	 CE_LOW;
	 nrf24l01_write_reg_cont(W_REGISTER+TX_ADDR,(u8*)RF2G4_ADDR_TX,TX_ADR_WIDTH);//���÷����ַ
	 nrf24l01_write_reg_cont(W_REGISTER+RX_ADDR_P0,(u8*)RF2G4_ADDR_RX,TX_ADR_WIDTH);//�����Զ�Ӧ���ַӦ�뷢���ַ��֪
   NRF24L01_write_reg(W_REGISTER+EN_AA,0x01);//ʹ��ͨ��0�Զ�Ӧ��
	 NRF24L01_write_reg(W_REGISTER+EN_RXADDR,0x01);//����ͨ����ַ����
	 NRF24L01_write_reg(W_REGISTER+SETUP_AW,5);//���õ�ַ���
	 NRF24L01_write_reg(W_REGISTER+RF_CH,40);//����ͨ��Ƶ�ʡ�����ն�һ��
	
	 NRF24L01_write_reg(W_REGISTER+SETUP_RETR,0x1A);//�����Զ��ط�ʱ��
	
	 NRF24L01_write_reg(W_REGISTER+RF_SETUP,0x0F);//���÷��书�ʡ�
	 NRF24L01_write_reg(W_REGISTER+CONFIG,0x0E);  //���ý�����ģʽ
	  CE_HIGH;//10us����������
	
}
// SI24R1����һ֡����
// P_Data	= �����������׵�ַ
// N_Data	= ���������ݵĸ���
// return	= �������״��
u8 NRF24L01_TX_Packet(u8*Pdata,u8 Ndata)
{
	u8 val_reg;
	CE_LOW;
	
	nrf24l01_write_reg_cont(W_TX_PAYLOAD,Pdata ,Ndata );//��Ҫ���͵�����д�뷢�ͻ�����
	 CE_HIGH;//��������
	while(GPIO_ReadOutputDataBit(GPIOB,NRF24L01_GPIO_IRQ)!=RESET);//����0��ʾ�������
	val_reg=nrf24l01_read_reg(STATUS);
	NRF24L01_write_reg(W_REGISTER+STATUS,val_reg);
	if(val_reg & TX_MAX)
	{
		NRF24L01_write_reg(FLUSH_TX,0xFF);
		return TX_FAIL_MAX;
	}
	if(val_reg & TX_OK )
	{
		return TX_SUCCESS;		// ���ط��ͳɹ�
		
	}
	return 0xFF;				// ���ط���ʧ��

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


