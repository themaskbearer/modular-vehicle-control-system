/*
 * Configuration.h
 *
 *  Created on: Jun 20, 2018
 *      Author: jpollard
 */

#ifndef SRC_CONFIGURATION_H_
#define SRC_CONFIGURATION_H_

#include "utils/Singleton.h"
#include <mutex>
#include <unordered_map>
#include <string>

const std::string VEHICLE_TYPE = "vehicle_type";
const std::string DATA_LOG_PATH = "data_log_path";
const std::string ERROR_LOG_PATH = "error_log_path";
const std::string MEMORY_FILE_PATH = "memory_log_path";
const std::string ENABLE_CONSOLE = "enable_console";

class Configuration : public Singleton<Configuration>
{
public:
    typedef std::unique_ptr<Configuration> Ptr;

    Configuration();
    virtual ~Configuration();

    bool isValueSet(const std::string& key);
    std::string getValue(const std::string& key);
    void setValue(const std::string& key, const std::string& value);

private:
    std::mutex _lock;
    std::unordered_map<std::string, std::string> _config;
};

#define CONFIG  Configuration::instance()

#endif /* SRC_CONFIGURATION_H_ */
