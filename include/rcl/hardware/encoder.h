namespace rcl
{
    class Encoder
    {
    protected:
	int card_;
    public:
	void init(int card, unsigned short mode);
	int getCount();
	void quit();
    };
};