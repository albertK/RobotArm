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
    public:
	/*
	 * initialize the encoder interface card
	 * card: interface card ID number
	 * mode: working mode
	 * 	 q=Quadrant-counting mode
	 * 	 c=CW/CCW counting mode
	 * 	 d=Pulse/Direction counting mode
	 */
	bool init(int card, char mode);
	
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