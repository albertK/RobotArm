#ifndef ENCODER
#define ENCODER

namespace rcl
{
    class Encoder
    {
    protected:
	//interface card ID number
	int card_0_;
	int card_1_;
	
	//encoder mode
	int mode_;
    public:
	//initialize the encoder interface card
	bool init();
	
	/*
	 * get the encoder count
	 * channel: range from 0 ~ DoF-1
	 */
	long getCount(int channel);
	
	//release resources, do garbage collection. call when exit the program
	void quit();
    };
};

#endif