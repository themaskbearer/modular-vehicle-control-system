/*
 * HardwareIOFile.cpp
 *
 *  Created on: Sep 26, 2018
 *      Author: jpollard
 */

#include "HardwareIOFile.h"
#include "utils/ErrorLogger.h"
#include "utils/Exceptions.h"

#include <cstdlib>

HardwareIOFile::HardwareIOFile(std::string fileName) :
    _fileName(fileName)
{
    _file.open(_fileName.c_str());
    if(!_file.is_open()) {
        ERROR_LOGGER.recordError("failed to open hardware IO file " + _fileName);
        throw FileOpenFailure(_fileName);
    }
}


HardwareIOFile::~HardwareIOFile()
{
    _file.close();
}


void HardwareIOFile::write(std::string value)
{
    std::string str = "echo " + value + " > ";
    str += _fileName;
    system(str.c_str());
}


void HardwareIOFile::write(int value)
{
    std::string str = "echo ";
    str += value + " > ";
    str += _fileName;
    system(str.c_str());
}


int HardwareIOFile::read()
{
    // Not implemented
    return 0;
}

