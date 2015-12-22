#include <stack>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <stdexcept>



bool opening(char bracket)
{
	if (bracket == '[' || bracket == '(' || bracket == '{') {
		return true;
	}
	if (bracket == ']' || bracket == ')' || bracket == '}') {
		return false;
	}
	throw std::exception();
}

bool closing(char bracket)
{
	return !opening(bracket);
}

int type(char bracket)
{
	switch (bracket) {
		case '[':
		case ']':	return 1;
		case '(':
		case ')':	return 2;
		case '{':
		case '}':	return 3;
	}
	throw std::exception();
}

char invert(char bracket)
{
	switch (bracket) {
		case '[':	return ']';
		case ']':	return '[';
		case '(':	return ')';
		case ')':	return '(';
		case '{':	return '}';
		case '}':	return '{';
	}
	throw std::exception();
}

int main()
{
	std::vector<char> input;
	std::copy(std::istream_iterator<char>(std::cin), std::istream_iterator<char>(), std::back_inserter(input));

	char top;
	std::stack<char> stack;

	for (char cur : input) {
		if (closing(cur) && !stack.empty() && opening(stack.top())) {
			top = stack.top();
			stack.pop();
			if (type(top) != type(cur)) {
				std::cout << "IMPOSSIBLE" << std::endl;
				return 0;
			}
		}
		else {
			stack.push(cur);
		}
	}

	std::vector<char> post;
	while (!stack.empty() && opening(stack.top())) {
		post.push_back(invert(stack.top()));
		stack.pop();
	}

	std::vector<char> prev;
	while (!stack.empty()) {
		prev.push_back(invert(stack.top()));
		stack.pop();
	}

	for (char cur : prev)
		std::cout << cur;
	for (char cur : input)
		std::cout << cur;
	for (char cur : post)
		std::cout << cur;

	std::cout << std::endl;

	return 0;
}