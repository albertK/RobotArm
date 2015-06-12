#include "piodio.h"

#include "rcl/hardware/analog_output.h"
#include "rcl/common/parameters.h"

void rcl::AnalogOutput::init()
{
    card_ = PIODA_Open(rcl::Parameters::CommunicationInterface::ao_dev.c_str());
    PIODA_DriverInit(card_);
    
    voltage_.resize(rcl::Parameters::CommunicationInterface::channel);
    
    for(unsigned int i = 0; i < rcl::Parameters::CommunicationInterface::channel; ++i)
    {
	voltage_.at(i) = 0.0;
	PIODA_AnalogOutputCalVoltage(card_, i, voltage_.at(i));
    }
}

void rcl::AnalogOutput::quit()
{
    PIODA_Close(card_);
}

void rcl::AnalogOutput::setVoltage(float voltage, int channel)
{
    voltage_.at(channel) = voltage;
    PIODA_AnalogOutputCalVoltage(card_, channel, voltage_.at(channel));
}

float rcl::AnalogOutput::getVoltage(int channel)
{
    return voltage_.at(channel);
}
