#include "piodio.h"

#include "rcl/hardware/analog_output.h"
#include "rcl/common/parameters.h"

bool rcl::AnalogOutput::init()
{
    card_ = PIODA_Open(rcl::Parameters::CommunicationInterface::ao_dev.c_str());
    if(card_ < 0)
	return false;
    
    if(PIODA_DriverInit(card_))
	return false;
    
    voltage_.resize(rcl::Parameters::CommunicationInterface::channel);
    
    for(unsigned int i = 0; i < rcl::Parameters::CommunicationInterface::channel; ++i)
    {
	voltage_.at(i) = 0.0;
	PIODA_AnalogOutputCalVoltage(card_, i, voltage_.at(i));
    }
    
    return true;
}

void rcl::AnalogOutput::quit()
{
    PIODA_Close(card_);
}

void rcl::AnalogOutput::setVoltage(float voltage, int channel)
{
    if(voltage > 10)
	voltage_.at(channel) = 10;
    else if(voltage < -10)
	voltage_.at(channel) = -10;
    else
	voltage_.at(channel) = voltage;
    
    PIODA_AnalogOutputCalVoltage(card_, channel, voltage_.at(channel));
}

float rcl::AnalogOutput::getVoltage(int channel)
{
    return voltage_.at(channel);
}
