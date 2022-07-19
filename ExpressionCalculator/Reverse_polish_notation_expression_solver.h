#pragma once

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <string>
#include <vector>
#include <stack>
#include <map>
#include <functional>

namespace expression_solver
{
	typedef std::function<float(float, float)> binary_operation;

	bool is_num(std::string str)
	{
		std::string::iterator iter = str.begin();
		while (iter != str.end())
		{
			if (!(std::isdigit(*iter) || *iter == '.' || *iter == '-'))
			{
				return false;
			}
			iter++;
		}
		return true;
	}

	class RPN_expression_solver
	{
	public:
		RPN_expression_solver();
		float solve(std::vector<std::string>);
	private:
		std::map<std::string, binary_operation> operation_by_symbol;
	};

	RPN_expression_solver::RPN_expression_solver()
	{
		operation_by_symbol.emplace(std::pair<std::string, binary_operation>("+", [](float a, float b) {return a + b; }));
		operation_by_symbol.emplace(std::pair<std::string, binary_operation>("-", [](float a, float b) {return a - b; }));
		operation_by_symbol.emplace(std::pair<std::string, binary_operation>("*", [](float a, float b) {return a * b; }));
		operation_by_symbol.emplace(std::pair<std::string, binary_operation>("/", [](float a, float b) {return a / b; }));
	}

	float RPN_expression_solver::solve(std::vector<std::string> expr)
	{
		std::stack<float> nums;
		for (std::string s : expr)
		{
			if (is_num(s))
			{
				float num = std::stoi(s);
				nums.push(num);
			}
			else
			{
				float b = nums.top();
				nums.pop();

				float a = nums.top();
				nums.pop();

				float result = operation_by_symbol[s](a, b);
				nums.push(result);
			}
		}

		return nums.top();
	}
}