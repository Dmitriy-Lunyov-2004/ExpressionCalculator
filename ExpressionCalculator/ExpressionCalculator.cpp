
#include <iostream>

#include <cstdio>
#include <cstdlib>

#include "Reverse_polish_notation_expression_solver.h"
#include "infix_notation_to_reverse_polish_notation_expressions_converter.h"

int main()
{
	std::string expression;

	std::cout << "Input the expression: " << std::endl;
	std::getline(std::cin, expression);

	expression.erase(std::remove(expression.begin(), expression.end(), ' '), expression.end());
	expression.erase(std::remove(expression.begin(), expression.end(), '\n'), expression.end());
	expression.erase(std::remove(expression.begin(), expression.end(), '\t'), expression.end());

	std::cout << "Trim:" << std::endl;
	std::cout << expression << std::endl;

	expression_solver::IN2RPN_converter conv;
	
	std::cout << "Delimiter: " << std::endl;
	std::vector<std::string> expr_split = conv.split_expression(expression);
	for (std::string s : expr_split)
	{
		std::cout << s << " ";
	}
	std::cout << std::endl;

	std::vector<std::string> rpn_expr = conv.convert(expression);

	std::cout << "Reverse Polish Notation: " << std::endl;
	for (std::string s : rpn_expr)
	{
		std::cout << s << " ";
	}
	std::cout << std::endl;

	expression_solver::RPN_expression_solver solver;
	std::cout << "answer: " << solver.solve(rpn_expr) << std::endl;

	return 0;
}