#ifndef ENCODER
#define ENCODER

namespace rcl
{
    class Encoder
    {
    protected:
	//interface card ID number
	int card_;
    public:
	/*
	 * initialize the encoder interface card
	 * card: interface card ID number
	 * mode: working mode
	 * 	 q=Quadrant-counting mode
	 * 	 c=CW/CCW counting mode
	 * 	 d=Pulse/Direction counting mode
	 */
	void init(int card, char mode);
	
	//get the encoder count
	int getCount();
	
	//release resources, do garbage collection. call when exit the program
	void quit();
    };
};

#endif