
// INCLUDES
#include "stm32f411xe.h"
#include "l3gd20.h"
#include "ddSpi.h"


///////////////////////////////////////////////////////////////////
/// MEDIUM LAYER
///////////////////////////////////////////////////////////////////
uint8_t L3GD20_Read_Single_Register(uint8_t address)
{
  uint8_t read_val = 0;
  
  L3GD20_CS_LOW();
  SPI_TX_RX_Byte_Polling(address | READWRITE_CMD);
  read_val = SPI_TX_RX_Byte_Polling(DUMMY_BYTE);
  L3GD20_CS_HIGH(); 
  
  return read_val;
}

void L3GD20_Write_Single_Register(uint8_t address, uint8_t data)
{
  L3GD20_CS_LOW();
  SPI_TX_RX_Byte_Polling(address);
  SPI_TX_RX_Byte_Polling(data);
  L3GD20_CS_HIGH(); 
}


///////////////////////////////////////////////////////////////////
/// HIGH LAYER
///////////////////////////////////////////////////////////////////


// brief  : L3GD20_Init
// Arg1   : 
// return : 
void L3GD20_Init(void)
{  
  // CS SETUP 
  L3GD20_CS_CLOCK_ON();
  GPIOE->MODER   |= (0x01 << (3*2));    //PE.3 OUT --> SPI1_CS
  GPIOE->OSPEEDR |= (0x02 << (3*2));    //PE.3 Fast Speed
  L3GD20_CS_HIGH();                     //        
  // SPI
  SPI1_Setup();
}



/**
  * @brief L3GD20 De-initialization
  * @param  None
  * @retval None
  */
void L3GD20_DeInit(void)
{
}

/**
  * @brief  Read ID address of L3GD20
  * @param  None
  * @retval ID name
  */
uint8_t L3GD20_ReadID(void)
{
  uint8_t tmp = 0;
  
  /* Read WHO I AM register */
  //GYRO_IO_Read(&tmp, L3GD20_WHO_AM_I_ADDR, 1);
  
  tmp = L3GD20_Read_Single_Register(L3GD20_WHO_AM_I_ADDR);
  
  if(tmp == I_AM_L3GD20)
    return 1;
  else
    return 0;
}

/**
  * @brief  Reboot memory content of L3GD20
  * @param  None
  * @retval None
  */
void L3GD20_RebootCmd(void)
{
//  uint8_t tmpreg;
//  
//  /* Read CTRL_REG5 register */
//  GYRO_IO_Read(&tmpreg, L3GD20_CTRL_REG5_ADDR, 1);
//  
//  /* Enable or Disable the reboot memory */
//  tmpreg |= L3GD20_BOOT_REBOOTMEMORY;
//  
//  /* Write value to MEMS CTRL_REG5 register */
//  GYRO_IO_Write(&tmpreg, L3GD20_CTRL_REG5_ADDR, 1);
}

/**
  * @brief Set L3GD20 in low-power mode
  * @param 
  * @retval  None
  */
void L3GD20_LowPower(uint16_t InitStruct)
{  
//  uint8_t ctrl = 0x00;
//
//  /* Write value to MEMS CTRL_REG1 register */
//  ctrl = (uint8_t) InitStruct;
//  GYRO_IO_Write(&ctrl, L3GD20_CTRL_REG1_ADDR, 1);
}

/**
  * @brief  Set L3GD20 Interrupt INT1 configuration
  * @param  Int1Config: the configuration setting for the L3GD20 Interrupt.
  * @retval None
  */
void L3GD20_INT1InterruptConfig(uint16_t Int1Config)
{
//  uint8_t ctrl_cfr = 0x00, ctrl3 = 0x00;
//  
//  /* Read INT1_CFG register */
//  GYRO_IO_Read(&ctrl_cfr, L3GD20_INT1_CFG_ADDR, 1);
//  
//  /* Read CTRL_REG3 register */
//  GYRO_IO_Read(&ctrl3, L3GD20_CTRL_REG3_ADDR, 1);
//  
//  ctrl_cfr &= 0x80;
//  ctrl_cfr |= ((uint8_t) Int1Config >> 8);
//  
//  ctrl3 &= 0xDF;
//  ctrl3 |= ((uint8_t) Int1Config);   
//  
//  /* Write value to MEMS INT1_CFG register */
//  GYRO_IO_Write(&ctrl_cfr, L3GD20_INT1_CFG_ADDR, 1);
//  
//  /* Write value to MEMS CTRL_REG3 register */
//  GYRO_IO_Write(&ctrl3, L3GD20_CTRL_REG3_ADDR, 1);
}

/**
  * @brief  Enable INT1 or INT2 interrupt
  * @param  IntSel: choice of INT1 or INT2 
  *      This parameter can be: 
  *        @arg L3GD20_INT1
  *        @arg L3GD20_INT2   
  * @retval None
  */
void L3GD20_EnableIT(uint8_t IntSel)
{  
//  uint8_t tmpreg;
//  
//  /* Read CTRL_REG3 register */
//  GYRO_IO_Read(&tmpreg, L3GD20_CTRL_REG3_ADDR, 1);
//  
//  if(IntSel == L3GD20_INT1)
//  {
//    tmpreg &= 0x7F;	
//    tmpreg |= L3GD20_INT1INTERRUPT_ENABLE;
//  }
//  else if(IntSel == L3GD20_INT2)
//  {
//    tmpreg &= 0xF7;
//    tmpreg |= L3GD20_INT2INTERRUPT_ENABLE;
//  }
//  
//  /* Write value to MEMS CTRL_REG3 register */
//  GYRO_IO_Write(&tmpreg, L3GD20_CTRL_REG3_ADDR, 1);
}

/**
  * @brief  Disable  INT1 or INT2 interrupt
  * @param  IntSel: choice of INT1 or INT2 
  *      This parameter can be: 
  *        @arg L3GD20_INT1
  *        @arg L3GD20_INT2   
  * @retval None
  */
void L3GD20_DisableIT(uint8_t IntSel)
{  
//  uint8_t tmpreg;
//  
//  /* Read CTRL_REG3 register */
//  GYRO_IO_Read(&tmpreg, L3GD20_CTRL_REG3_ADDR, 1);
//  
//  if(IntSel == L3GD20_INT1)
//  {
//    tmpreg &= 0x7F;	
//    tmpreg |= L3GD20_INT1INTERRUPT_DISABLE;
//  }
//  else if(IntSel == L3GD20_INT2)
//  {
//    tmpreg &= 0xF7;
//    tmpreg |= L3GD20_INT2INTERRUPT_DISABLE;
//  }
//  
//  /* Write value to MEMS CTRL_REG3 register */
//  GYRO_IO_Write(&tmpreg, L3GD20_CTRL_REG3_ADDR, 1);
}

/**
  * @brief  Set High Pass Filter Modality
  * @param  FilterStruct: contains the configuration setting for the L3GD20.        
  * @retval None
  */
void L3GD20_FilterConfig(uint8_t FilterStruct) 
{
//  uint8_t tmpreg;
//  
//  /* Read CTRL_REG2 register */
//  GYRO_IO_Read(&tmpreg, L3GD20_CTRL_REG2_ADDR, 1);
//  
//  tmpreg &= 0xC0;
//  
//  /* Configure MEMS: mode and cutoff frequency */
//  tmpreg |= FilterStruct;
//  
//  /* Write value to MEMS CTRL_REG2 register */
//  GYRO_IO_Write(&tmpreg, L3GD20_CTRL_REG2_ADDR, 1);
}

/**
  * @brief  Enable or Disable High Pass Filter
  * @param  HighPassFilterState: new state of the High Pass Filter feature.
  *      This parameter can be: 
  *         @arg: L3GD20_HIGHPASSFILTER_DISABLE 
  *         @arg: L3GD20_HIGHPASSFILTER_ENABLE          
  * @retval None
  */
void L3GD20_FilterCmd(uint8_t HighPassFilterState)
{
//  uint8_t tmpreg;
//  
//  /* Read CTRL_REG5 register */
//  GYRO_IO_Read(&tmpreg, L3GD20_CTRL_REG5_ADDR, 1);
//  
//  tmpreg &= 0xEF;
//  
//  tmpreg |= HighPassFilterState;
//  
//  /* Write value to MEMS CTRL_REG5 register */
//  GYRO_IO_Write(&tmpreg, L3GD20_CTRL_REG5_ADDR, 1);
}

/**
  * @brief  Get status for L3GD20 data
  * @param  None         
  * @retval Data status in a L3GD20 Data
  */
uint8_t L3GD20_GetDataStatus(void)
{
//  uint8_t tmpreg;
//  
//  /* Read STATUS_REG register */
//  GYRO_IO_Read(&tmpreg, L3GD20_STATUS_REG_ADDR, 1);
//  
//  return tmpreg;
}

/**
* @brief  Calculate the L3GD20 angular data.
* @param  pfData: Data out pointer
* @retval None
*/
void L3GD20_ReadXYZAngRate(float *pfData)
{
//  uint8_t tmpbuffer[6] ={0};
//  int16_t RawData[3] = {0};
//  uint8_t tmpreg = 0;
//  float sensitivity = 0;
//  int i =0;
//  
//  GYRO_IO_Read(&tmpreg,L3GD20_CTRL_REG4_ADDR,1);
//  
//  GYRO_IO_Read(tmpbuffer,L3GD20_OUT_X_L_ADDR,6);
//  
//  /* check in the control register 4 the data alignment (Big Endian or Little Endian)*/
//  if(!(tmpreg & L3GD20_BLE_MSB))
//  {
//    for(i=0; i<3; i++)
//    {
//      RawData[i]=(int16_t)(((uint16_t)tmpbuffer[2*i+1] << 8) + tmpbuffer[2*i]);
//    }
//  }
//  else
//  {
//    for(i=0; i<3; i++)
//    {
//      RawData[i]=(int16_t)(((uint16_t)tmpbuffer[2*i] << 8) + tmpbuffer[2*i+1]);
//    }
//  }
//  
//  /* Switch the sensitivity value set in the CRTL4 */
//  switch(tmpreg & L3GD20_FULLSCALE_SELECTION)
//  {
//  case L3GD20_FULLSCALE_250:
//    sensitivity=L3GD20_SENSITIVITY_250DPS;
//    break;
//    
//  case L3GD20_FULLSCALE_500:
//    sensitivity=L3GD20_SENSITIVITY_500DPS;
//    break;
//    
//  case L3GD20_FULLSCALE_2000:
//    sensitivity=L3GD20_SENSITIVITY_2000DPS;
//    break;
//  }
//  /* Divide by sensitivity */
//  for(i=0; i<3; i++)
//  {
//    pfData[i]=(float)(RawData[i] * sensitivity);
//  }
}




/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/     
