#pragma once
#ifndef ENGINE_AND_WRAPPER_ENGINE_H
#define ENGINE_AND_WRAPPER_ENGINE_H
#include "Wrapper.h"

class Engine {
private:
    std::map<std::string, Wrapper*> commands;

public:
    Engine() = default;
    Engine(Engine const&) = delete;
    Engine& operator =(Engine const&) = delete;
    Engine(Engine&&) = default;
    Engine& operator =(Engine&&) = default;
    ~Engine() = default;

    void registerCommand(Wrapper* wrapper, std::string const& command) {
        if (!wrapper || command =="")
            throw std::exception();
        else if (commands.find(command) != commands.end()) 
            throw std::exception(); //Command already exist
        else 
            commands.insert({ command, wrapper });
    }

    int execute(const std::string& command, std::map<std::string, int>  const& args) {
        auto iter = commands.find(command);
        if (iter == commands.end())
            throw std::exception(); //Command is not exist
       
        return iter->second->execute(args);
    }
};

#endif //ENGINE_AND_WRAPPER_ENGINE_H