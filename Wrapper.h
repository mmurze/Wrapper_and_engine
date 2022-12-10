#pragma once
#ifndef ENGINE_AND_WRAPPER_WRAPPER_H
#define ENGINE_AND_WRAPPER_WRAPPER_H
#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include <string>
#include <functional>


class Wrapper {
private:
	std::map<std::string, int> args;
	std::function<int(std::vector<int>& vecArgs)> function;

public:
	Wrapper(Wrapper const&) = delete;
	Wrapper& operator=(Wrapper const&) = delete;
	Wrapper(Wrapper&&) = default;
	Wrapper& operator=(Wrapper&&) = default;
	~Wrapper() = default;

	template <typename Subject, typename Function, size_t... i>
	int callFunc(Subject* subject, Function func, std::vector<int> const& args, std::index_sequence<i...>) {
		return (subject->*func)(args[i]...);
	}

	template <typename Subject, typename... Args>
	Wrapper(Subject* subject, int(Subject::* func)(Args...), std::vector<std::pair<std::string, int>> const& args) {
		if(!subject || !func)
			throw std::exception();// Function or subject is null

		for (auto& arg : args)
			this->args.insert(arg);

		if (this->args.size() != args.size())
			throw std::exception(); //Args is not unique

		function = [this, subject, func](std::vector<int >& vec_args) {
			return callFunc(subject, func, vec_args, std::make_index_sequence<sizeof...(Args)>{});
		};
	}

	int execute(std::map<std::string, int> const& args) {
		std::vector<int> vec_args;
		for (auto& arg : args) {
			if (this->args.find(arg.first) == this->args.end())
				throw std::exception(); //Command from args doesn't exist
			this->args.find(arg.first)->second = arg.second;

			vec_args.push_back(arg.second);
		}
		return function(vec_args);
	}
};

#endif //ENGINE_AND_WRAPPER_WRAPPER_H