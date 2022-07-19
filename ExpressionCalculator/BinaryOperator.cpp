
#include "BinaryOperator.h"

float BinaryOperator::operator()(float left, float right)
{
	return _func(left, right);
}

bool operator>(BinaryOperator& left, BinaryOperator& right)
{
	return left._priority > right._priority;
}

bool operator<(BinaryOperator& left, BinaryOperator& right)
{
	return left._priority < right._priority;
}

bool operator>=(BinaryOperator& left, BinaryOperator& right)
{
	return left._priority >= right._priority;
}

bool operator<=(BinaryOperator& left, BinaryOperator& right)
{
	return left._priority <= right._priority;
}

bool operator==(BinaryOperator& left, BinaryOperator& right)
{
	return left._priority == right._priority;
}

bool operator!=(BinaryOperator& left, BinaryOperator& right)
{
	return left._priority != right._priority;
}