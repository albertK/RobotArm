#ifndef AO
#define AO

#include <string>
#include <vector>

namespace rcl
{
    class AnalogOutput
    {
    protected:
	//check if the class has been initialized. avoid multiple initialization
	bool init_;
	
	//opened device ID
	int card_;
	
	//output voltage
	std::vector<float> voltage_;
    public:
	AnalogOutput():init_(false){};
	
	/*
	 * initialize the ao communication interface card
	 * card: interface card device name
	 */
	bool init();
	
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
    
    static AnalogOutput ao;
};

#endif