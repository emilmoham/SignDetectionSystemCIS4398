#include "ConfigParser.h"
#include <iostream>

int main(int argc, char **argv)
{
    ConfigParser cfg;
    if (!cfg.load("config.ini"))
    {
        std::cout << "Could not open config file" << std::endl;
        return 0;
    }

    // Fetch config values
    std::string strVal = cfg.getValue<std::string>("StrKey");
    int intVal         = cfg.getValue<int>("IntKey");
    bool boolVal       = cfg.getValue<bool>("BoolKey");
    float floatVal     = cfg.getValue<float>("FloatKey");

    // Compare to expected values
    std::string expectedStr = "str_value";
    int expectedInt = 1012;
    bool expectedBool = false;
    float expectedFloat = 1.14159f;

    bool pass = true;
    if (strVal.compare(expectedStr) != 0)
    {
        std::cout << "[Fail]: String values do not match. Expected \"" << expectedStr << "\", got \"" << strVal << "\"" << std::endl;
        pass = false;
    }
    if (intVal != expectedInt)
    {
        std::cout << "[Fail]: Integer values do not match. Expected " << expectedInt << ", got " << intVal << std::endl;
        pass = false;
    }
    if (boolVal != expectedBool)
    {
        std::cout << "[Fail]: Boolean values do not match. Expected " << expectedBool << ", got " << boolVal << std::endl;
        pass = false;
    }
    if (floatVal != expectedFloat)
    {
        std::cout << "[Fail]: Floating-point values do not match. Expected " << expectedFloat << ", got " << floatVal << std::endl;
        pass = false;
    }

    if (pass)
    {
        std::cout << "[ConfigParser]: All tests passed" << std::endl;
    }
}

