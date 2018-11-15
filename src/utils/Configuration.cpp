/*
 * Configuration.cpp
 *
 *  Created on: Jun 20, 2018
 *      Author: jpollard
 */

#include "Configuration.h"


template<> Configuration::Ptr Singleton<Configuration>::_instance = nullptr;

Configuration::Configuration()
{

}

Configuration::~Configuration()
{

}


bool Configuration::isValueSet(const std::string& key)
{
    auto data_pair = _config.find(key);
    if(data_pair != _config.end())
        return true;
    else
        return false;
}


std::string Configuration::getValue(const std::string& key)
{
    std::lock_guard<std::mutex> guard(_lock);
    std::string value;

    auto data_pair = _config.find(key);
    if(data_pair != _config.end())
        value = data_pair->second;

    return value;
}


void Configuration::setValue(const std::string& key, const std::string& value)
{
    std::lock_guard<std::mutex> guard(_lock);
    auto insertResult = _config.insert(std::pair<std::string, std::string>(key, value));
    if(!insertResult.second)
    {
        insertResult.first->second = value;
    }
}
