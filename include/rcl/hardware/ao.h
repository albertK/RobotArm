#include <string>

namespace rcl
{
    class AO
    {
    protected:
	int card_;
	float voltage_;
    public:
	void init(std::string card);
	void setVoltage(float voltage, int channel);
	float getVoltage(int channel);
	void quit();
    };
};