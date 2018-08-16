/*
 * Singleton.h
 *
 *  Created on: Jun 20, 2018
 *      Author: jpollard
 */

#ifndef SRC_UTILS_SINGLETON_H_
#define SRC_UTILS_SINGLETON_H_

#include <memory>

template <typename T>
class Singleton
{
public:
    Singleton() {}
    virtual ~Singleton() {}

    static T& instance() { if(_instance == nullptr) _instance.reset(new T()); return *_instance; }

private:
    static std::unique_ptr<T> _instance;
};

#endif /* SRC_UTILS_SINGLETON_H_ */
