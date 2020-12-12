#include "Config.h"



Config& Config::GetInstance(void)
{
    static Config config;
    return config;
}

std::string& Config::Get(const std::string& key, const std::string& def)
{
    if(!configs.count(key))
        configs[key]=def;
    return configs[key];
}



void Config::Save(void)
{
    std::ofstream out(CONFIG_FILE);
    if(!out.is_open())
        return;
    for(auto it=configs.begin(); it != configs.end(); it++)
        out << it->first <<":"<<it->second<<"\n";
}

void Config::Load(void)
{
    std::ifstream in(CONFIG_FILE);
    if(!in.is_open())
        return;
    while(!in.eof())
    {
        std::string key,value;
        std::getline(in, key, ':');
        std::getline(in, value, '\n');
        configs[key]=value;
    }
}


Config::Config()
{
    Load();
}


std::string Config::Set(const std::string& config, const std::string& value)
{
    configs[config]=value;
    return value;
}
