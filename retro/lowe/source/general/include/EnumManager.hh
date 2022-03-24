#ifndef ENUMMANAGER_HH
#define ENUMMANAGER_HH

#include <map>
#include <string>
#include <stdarg.h>
#include <string.h>
#include <cstring>

#define STR(var) #var

#define ENUM(_name, ...)                                \
    class _name {                                      \
     public:                                           \
     static _name self;				\
        enum type {__VA_ARGS__, NUM};                   \
	std::map <std::string, type> converter;		\
        _name() {                                       \
	  createEnumMap(converter,#__VA_ARGS__, NUM, __VA_ARGS__); \
        }                                               \
    };


template <class T> void createEnumMap(std::map<std::string, T> &_map, std::string _list, int _num, ...) {
    char* listCopy = new char[255];
    char* tmpKey;
    strcpy(listCopy, _list.c_str());

    va_list args;
    va_start(args, _num);

    if ((tmpKey = strtok(listCopy, ", ")) != NULL) _map[tmpKey] = static_cast<T> (va_arg(args, int));
    for (int i = 1; i < _num; i++) {
        if ((tmpKey = strtok(NULL, ", ")) != NULL) _map[tmpKey] = static_cast<T> (va_arg(args, int));
    }
    va_end(args);
    delete[] listCopy;
}

#endif
