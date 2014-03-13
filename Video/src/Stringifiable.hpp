#ifndef __STRINGIFIABLE_HPP__
#define __STRINGIFIABLE_HPP__

#include<string>
#include<iostream>
class Stringifiable{
public:
	virtual std::string toString() const=0;
};
extern std::ostream & operator<<(std::ostream & ostr, const Stringifiable& something);
#endif