/*
 * Configuration.h
 *
 *  Created on: Jun 20, 2018
 *      Author: jpollard
 */

#ifndef SRC_CONFIGURATION_H_
#define SRC_CONFIGURATION_H_

#include "utils/Singleton.h"
#include "thread/Mutex.h"
#include <unordered_map>
#include <string>

const std::string VEHCILE_TYPE = "vehicle_type";

class Configuration : public Singleton<Configuration>
{
public:
    Configuration();
    virtual ~Configuration();

    std::string getValue(const std::string& key);
    void setValue(const std::string& key, const std::string& value);

private:
    Mutex _lock;
    std::unordered_map<std::string, std::string> _config;
};

#endif /* SRC_CONFIGURATION_H_ */
