#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED
#include <string>
#include <map>
#include <fstream>
#include <sstream>

class Config
{
public:

    const char* CONFIG_FILE = "config.cfg";

    static Config& GetInstance(void);
    std::string& Get(const std::string& key, const std::string& def);


    template <class T>
    T Get(const std::string& key, const std::string& def)
    {
        T output;
        std::stringstream ss(Get(key, def));
        ss >> output;
        return output;
    }

    void Save(void);
    void Load(void);
    std::string Set(const std::string& config, const std::string& value);

private:

    Config();
    std::map<std::string,std::string> configs;
};


#endif // CONFIG_H_INCLUDED
