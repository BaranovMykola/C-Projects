#pragma once
#include <fstream>

using std::ostream;

class Literal
{
private:
	bool atom;
	bool negative;
public:
	void denide() { negative = !negative; }
	friend ostream& operator<<(ostream& stream, const Literal& output) { return stream << output.atom; }
};
