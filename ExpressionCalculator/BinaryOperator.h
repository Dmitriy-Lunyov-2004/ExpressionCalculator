#pragma once

#include <functional>
#include <string>

typedef std::function<float(float, float)> binary_operator_function;

class BinaryOperator
{
	friend bool operator>(BinaryOperator&, BinaryOperator&);
	friend bool operator<(BinaryOperator&, BinaryOperator&);
	friend bool operator>=(BinaryOperator&, BinaryOperator&);
	friend bool operator<=(BinaryOperator&, BinaryOperator&);
	friend bool operator==(BinaryOperator&, BinaryOperator&);
	friend bool operator!=(BinaryOperator&, BinaryOperator&);
public:
	float operator()(float, float);
	unsigned int get_priority() { return _priority; }
	std::string get_symbol() { return _symbol; }
private:
	std::string _symbol;
	unsigned int _priority;
	binary_operator_function _func;
};