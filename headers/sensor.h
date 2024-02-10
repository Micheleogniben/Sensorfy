#include <vector>
#include <string>

class Sensor{
    public:
        Sensor(std::string, std::string, std::string);
        virtual const std::vector<float> generateData(unsigned short minInterval) const =0;
    private:
        std::string name, desc, id;
};