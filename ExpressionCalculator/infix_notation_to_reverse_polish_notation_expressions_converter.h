#pragma once

#include <cstdlib>
#include <cstdio>

#include <vector>
#include <string>
#include <stack>
#include <map>

namespace expression_solver
{

	class IN2RPN_converter
	{
	public:
		IN2RPN_converter();
		std::vector<std::string> convert(std::string);
		std::vector<std::string> split_expression(std::string);
	private:
		std::map<std::string, unsigned int> operator_priority;
	};

	IN2RPN_converter::IN2RPN_converter()
	{
		operator_priority.emplace("(", 0u);
		operator_priority.emplace(")", 1u);
		operator_priority.emplace("*", 3u);
		operator_priority.emplace("/", 3u);
		operator_priority.emplace("+", 2u);
		operator_priority.emplace("-", 2u);
	}

	std::vector<std::string> IN2RPN_converter::split_expression(std::string expr)
	{
		std::vector<std::string> expr_split;
		std::string::iterator iter = expr.begin();

		std::vector<char> operators = { '+', '-', '*', '/', '(', ')' };

		while (iter != expr.end())
		{
			if (*iter == '(')
			{
				expr_split.push_back(std::string({ *iter }));
				expr.erase(iter);
				iter = expr.begin();
			}
			else if (std::find(operators.cbegin(), operators.cend(), *iter) != operators.cend())
			{
				std::string operand = expr.substr(0, iter - expr.begin());
				if (operand != "")
				{
					expr_split.push_back(operand);
				}
				expr_split.push_back(std::string({ *iter }));
				expr.erase(expr.begin(), iter + 1);
				iter = expr.begin();
			}
			else
			{
				iter++;
			}
		}
		std::string operand = expr;
		if (operand != "")
		{
			expr_split.push_back(operand);
		}
		return expr_split;
	}

	std::vector<std::string> IN2RPN_converter::convert(std::string expr)
	{
		std::vector<std::string> expr_split = split_expression(expr);

		std::vector<std::string> RPN_expression;
		std::stack<std::string> operators_stack;

		std::vector<std::string> operators = { "+", "-", "*", "/", "(", ")" };

		std::vector<std::string>::iterator iter = expr_split.begin();

		while (iter != expr_split.end())
		{
			std::string s = *iter;

			if (std::find(operators.cbegin(), operators.cend(), s) != operators.cend())
			{
				if (s == ")")
				{
					while (operators_stack.top() != "(")
					{
						RPN_expression.push_back(operators_stack.top());
						operators_stack.pop();
					}
					operators_stack.pop();
				}
				else if (s == "(")
				{
					operators_stack.push(s);
				}
				else if ((operators_stack.empty() || operators_stack.top() == "(") && s == "-")
				{
					RPN_expression.push_back("-" + *(++iter));
				}
				else
				{
					while (!operators_stack.empty() && operator_priority[operators_stack.top()] >= operator_priority[s])
					{
						RPN_expression.push_back(operators_stack.top());
						operators_stack.pop();
					}
					operators_stack.push(s);
				}
			}
			else
			{
				RPN_expression.push_back(s);
			}

			iter++;
		}

		while (!operators_stack.empty())
		{
			RPN_expression.push_back(operators_stack.top());
			operators_stack.pop();
		}

		return RPN_expression;
	}
}