/*
 * Singleton.h
 *
 *  Created on: Jun 20, 2018
 *      Author: jpollard
 */

#ifndef SRC_UTILS_SINGLETON_H_
#define SRC_UTILS_SINGLETON_H_

template <typename T>
class Singleton
{
public:
    Singleton() {}
    virtual ~Singleton() { delete _instance; }

    static T& instance() { if(_instance == nullptr) _instance = new T(); return *_instance; }

private:
    static T* _instance;
};

#endif /* SRC_UTILS_SINGLETON_H_ */
