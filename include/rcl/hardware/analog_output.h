#ifndef AO
#define AO

#include <string>

namespace rcl
{
    class AnalogOutput
    {
    protected:
	//opened device ID
	int card_;
	
	//output voltage
	float voltage_;
    public:
	/*
	 * initialize the ao communication interface card
	 * card: interface card device name
	 */
	void init(std::string card);
	
	/*
	 * set the output voltage
	 * voltage: output voltage. -10V~10V
	 * channel: output channel
	 */
	void setVoltage(float voltage, int channel);
	
	//get the output voltage of the channel
	float getVoltage(int channel);
	
	//release resources, do garbage collection. call when exit the program
	void quit();
    };
};

#endif