#include"Stringifiable.hpp"

std::ostream & operator<<(std::ostream & ostr, const Stringifiable& something)
{
	return ostr << something.toString();
}