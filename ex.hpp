#pragma once
#ifndef EX_HPP
#define EX_HPP

#include <exception>
#include <string>

using std::exception;
using std::string;

class ArgumentNotDefinedExcept : public exception
{
    string msg{"Argument not defined."};

    const char* what() const noexcept
    {
        return msg.c_str();
    };
};

//class ArgumentNot

class InstructionNotHasSubinstructionExcept: public exception
{
    string msg{"Instruction does not permit subinstructions. "};

    const char* what() const noexcept
    {
        return msg.c_str();
    }
};

class SubinstructionNotDefinedExcept: public exception
{
    string msg{"Subinstruction not defined."};

    const char* what() const noexcept
    {
        return msg.c_str();
    }
};


#endif