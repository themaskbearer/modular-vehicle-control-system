/*
 * HardwareIOFile.h
 *
 *  Created on: Sep 26, 2018
 *      Author: jpollard
 */

#ifndef SRC_HARDWAREIOFILE_H_
#define SRC_HARDWAREIOFILE_H_

#include <string>
#include <fstream>

class HardwareIOFile {
public:
	explicit HardwareIOFile(std::string fileName);
	virtual ~HardwareIOFile();

	void write(std::string value);
	void write(int value);
	int read();

private:
	std::string _fileName;
	std::ofstream _file;
};

#endif /* SRC_HARDWAREIOFILE_H_ */
