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


#endif