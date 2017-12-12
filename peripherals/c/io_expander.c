#include "io_expander.h"

//*****************************************************************************
// Checks if io expander is busy writing the last transaction
//*****************************************************************************
static i2c_status_t io_expander_wait_for_write(int32_t I2C_base)
{
  
  i2c_status_t status;
  
  if( !i2cVerifyBaseAddr(I2C_base) )
  {
    return  I2C_INVALID_BASE;
  }

  // set I2C address to slave and in Write Mode
  status = i2cSetSlaveAddr(I2C_base, MCP23017_DEV_ID, I2C_WRITE);

  // Ppoll while the device is busy.  The  MCP24LC32AT will not ACK
  // writing an address while the write has not finished.
  do 
  {
    // The data we send does not matter.  This has been set to 0x00, but could
    // be set to anything
    status = i2cSendByte( I2C_base, 0xFF, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);
    
    // Wait for address to finish transmitting
    while ( I2CMasterBusy(I2C_base)) {};
    
    // If the address was not ACKed, try again.
  } while (I2CMasterAdrAck(I2C_base) == false);

  return  status;
} 

//*****************************************************************************
// Sets the address to read/write from in the MCP23017  
//
// Paramters
//    I2C_base:   a valid base address of an I2C peripheral
//
//    address:    8-bit address
//
// Returns
// I2C_OK if the byte was written to the MCP23017.
//*****************************************************************************
static i2c_status_t io_expander_byte_write(uint32_t  I2C_base, uint8_t  address, uint8_t data)
{
  i2c_status_t status;
    
  // Before doing anything, make sure the I2C device is idle
  while ( I2CMasterBusy(I2C_base)) {};
  
  // Set the I2C address to be the MCP23017
	status = i2cSetSlaveAddr(I2C_base, MCP23017_DEV_ID, I2C_WRITE);
		
	// If the EEPROM is still writing the last byte written, wait
  io_expander_wait_for_write(I2C_base);
  
  // Send the address
	status = i2cSendByte(I2C_base, address, I2C_MCS_START | I2C_MCS_RUN);
		
  // Send the data		
	status = i2cSendByte(I2C_base, data, I2C_MCS_RUN | I2C_MCS_STOP);
	
  return status;
}

//*****************************************************************************
// Reads one byte of data from the current address of the MCP23017  
//
// Paramters
//    I2C_base:   a valid base address of an I2C peripheral
//
//    data:       data to read.
//
// Returns
// I2C_OK if the byte was written to the MCP23017.
//*****************************************************************************
static i2c_status_t io_expander_byte_read(uint32_t  I2C_base, uint8_t	address, uint8_t *data)
{
  i2c_status_t status;
  
  // Before doing anything, make sure the I2C device is idle
  while ( I2CMasterBusy(I2C_base)) {};

  // If the EEPROM is still writing the last byte written, wait
  io_expander_wait_for_write(I2C_base);		
		
  // Set the I2C slave address to be the MCP23017 and in write mode
  status = i2cSetSlaveAddr(I2C_base, MCP23017_DEV_ID, I2C_WRITE);
  
  // Send the address
	status = i2cSendByte(I2C_base, address, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);		

  // Set the I2C slave address to be the MCP23017 and in Read Mode
	status = i2cSetSlaveAddr(I2C_base, MCP23017_DEV_ID, I2C_READ);
		
  // Read the data returned by the MCP23017
  status = i2cGetByte( I2C_base, data , I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);

  return I2C_OK;
}


//*****************************************************************************
// Set the value of the 8 red LEDs
//*****************************************************************************
void io_expander_write_LEDs(uint8_t LEDs)
{
	io_expander_byte_write(IO_EXPANDER_I2C_BASE, MCP23017_GPIOA_R, LEDs);
}

//*****************************************************************************
// Read the value of the up/down and left/right buttons
//*****************************************************************************
uint8_t io_expander_read_buttons()
{
	uint8_t buttons;
	
	io_expander_byte_read(IO_EXPANDER_I2C_BASE, MCP23017_GPIOB_R, &buttons);
	
	return buttons & 0x0f;
}

//*****************************************************************************
// Initialize the GPIO Expander
//*****************************************************************************
bool io_expander_init(void)
{ 
  // Configure I2C GPIO Pins on TI Board  
  if(gpio_enable_port(IO_EXPANDER_GPIO_BASE) == false)
  {
    return false;
  }
  
  // Configure SCL 
  if(gpio_config_digital_enable(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SCL_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_alternate_function(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SCL_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_port_control(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SCL_PCTL_M, IO_EXPANDER_I2C_SCL_PIN_PCTL)== false)
  {
    return false;
  }
    

  
  // Configure SDA 
  if(gpio_config_digital_enable(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_open_drain(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_alternate_function(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_port_control(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PCTL_M, IO_EXPANDER_I2C_SDA_PIN_PCTL)== false)
  {
    return false;
  }
  
  
  //  Initialize I2C peripheral
  if( initializeI2CMaster(IO_EXPANDER_I2C_BASE)!= I2C_OK)
  {
    return false;
  }
	
	// Initialize GPIO pins on MCP23017
	
	// set GPIOA on expander to be output
	io_expander_byte_write(IO_EXPANDER_I2C_BASE, MCP23017_IODIRA_R, 0x00);
	
	// set GPIOB on expander to be input, enable PUR, and enable polarity
	io_expander_byte_write(IO_EXPANDER_I2C_BASE, MCP23017_IODIRB_R, 0xFF);
	io_expander_byte_write(IO_EXPANDER_I2C_BASE, MCP23017_GPPUB_R, 0xFF);
	io_expander_byte_write(IO_EXPANDER_I2C_BASE, MCP23017_IPOLB_R, 0xFF);
	
  return true;
  
}