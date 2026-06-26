#ifndef PRM_HPP
#define PRM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <print>
#include <concepts>
#include <tuple>
#include "./ex.hpp"

using std::cout;
using std::string;
using std::vector;
using std::endl;
using std::for_each;
using std::stol;
using std::stoi;
using std::stod;
using std::stof;

class ArgumentNotDefinedExcept;


//e.g. --help -h
//e.g. --host 127.0.0.1            single
//e.g. --on 127.0.0.1:8080          pair
//e.g.

class Prm;

//class ExceptCommandNo


/*
 * arg = Argument
 * prm = Parameter
 * istr = Instruction
 * abrv = Abbreviation
 * subistr = Subinstruction
 * fst = Firs.
 * lst = Las.
 *
 */

class Prm
{
public:
    int argCnt;
    //const char** argIn;
    char** argIn;

    vector<string> arg;

    //Prm()

    //prm pair "--output a.txt" or "-o a.txt"

    struct Subistr;

    struct Istr
    {
        string nm{};
        string abrv{};

        int cnt{0};

        string desc{};

        bool hasSubistr{false};

        vector<Subistr> sub{};
    };

    struct Subistr
    {
        string nm{};

    };

    vector<Istr> istr{};

    //lst prm
    bool lstArg{false};
    bool pultArg{false};
    string lst{};

    //fst prm
    bool fstArg{false};
    bool scdArg{false};
    string fst{};


    bool helpFlg{false};
    string helpAbrv{};
    string helpFull{};

    bool drctRd{true};

    int setIstr(const string &nm);

    int setIstr(const string &nm, const string &abrv);

    int setIstr(const string &nm, const string &abrv, const int &cnt);

    int setIstr(const std::pair<string, string> & pair);


    int addDesc(Istr istr, const string &desc);

    int addDesc(const string &name, const string &desc);

    void setHelp(bool barH =false, bool doubleBarHelp=true);

    string getHelp();

    void setSubistr(Istr &istr, const string &sub);

    template<typename T>
    T getSubistr(const Istr &istr, const string &sub);

    template<typename T>
    T getSubistr(const string &nm, const string &sub);

    void setFst();
    string getFst();

    void setScd();

    string getScd();

    string getLstLtr();

    string getFstLtr();


    void setLst();

    void setPult();

    string getLst();

    string getPult();

    enum class ArgType {
        Float,
        Double,
        String,
        IP,
        Date,
        Int, //
        Int8,
        Int16,
        Int32,
        Int64,
        Int128,
        UInt32,
        Long,
        LongLong
    };

    ///TODO ex
    template<typename T >
    requires (std::is_same<T, ArgType>::value==false)
    T getArgFst(string arg);

    template<typename T>
    requires (std::is_same<T, ArgType>::value)
    T getArgFst(string arg, T typ);



    string getArgLtr(int idx);




    ///PROCESSING
    bool getIstr(const string &istrIn);

    string getIstrFst(string istrIn);

    ///TODO bdr chk
    string getIstrScd(string istrIn);

    // Prm(int argCnt, char* argIn[]): argCnt(argCnt)
    // {
    //     arg = vector<string>(argCnt);
    //
    //     int i=0;
    //
    //     argIn = (char**)malloc (argCnt*sizeof(void*));
    //
    //     for (i=0;i<argCnt;i++)
    //     {
    //         this->argIn[i] = const_cast<const char*>(argIn[i]);
    //
    //         arg[i] = argIn[i];
    //
    //         cout<<"prm ltr: "<<arg[i]<<endl;
    //     }
    //
    //
    // };

    Prm(int argCnt, char* argIn[]): argCnt(argCnt), argIn(argIn)
    {
        arg = vector<string>(argCnt);

        int i=0;

        for (i=0;i<argCnt;i++)
        {
            //(this->argIn)[i]=new char[]{(char*)argIn[i]};

            arg[i] = argIn[i];

            cout<<"prm ltr: "<<arg[i]<<endl;
        }


    };

    template<typename T>
    requires(std::is_same<T, ArgType>::value==false)
    T getSubistr(const Istr &istr, const string &sub);

    template<typename T=ArgType>
    requires(std::is_same_v<T, ArgType>)
    T getSubistr(const Istr &istr, const string &sub);


private:
    Istr findIstr(const string &nm);
    Istr findIstrAbrv(const string &nm);
    Istr findIstrFull(const string &nm);



};

//using Istr = Prm::Istr;
using ArgType = Prm::ArgType;

template<typename T>
requires (std::is_same<T, ArgType>::value)
T Prm::getArgFst(string arg, T typ)
{
    //string s(arg);
    string s{getIstrFst(arg)};

    T rs;


    switch (typ)
    {
        case ArgType::Double:
        {
            rs = dynamic_cast<T>(std::stod(s));
            break;
        }
        case ArgType::Float:
        {
            rs = dynamic_cast<T>(std::stof(s));
            break;
        }
        case ArgType::Int:
        {
            rs = dynamic_cast<T>(std::stoi(s));
            break;
        }
        case ArgType::Long:
        {
            rs = dynamic_cast<T>(std::stol(s));
            break;
        }
        case ArgType::String:
        {
            rs = dynamic_cast<T>(s);
            break;
        }
        default:
        {
            throw ArgumentNotDefinedExcept();
        }
    }

    return rs;
}

template<typename T >
requires (std::is_same<T, ArgType>::value==false)
T Prm::getArgFst(string arg)
{
    //string s(arg);
    string s{getIstrFst(arg)};

    T rs;

    if constexpr (typeid(T)==typeid(double))
    {
        rs = reinterpret_cast<T>(std::stod(s));
    }
    else if constexpr (typeid(T)==typeid(float))
    {
        rs = reinterpret_cast<T>(std::stof(s));
    }
    else if constexpr (typeid(T)==typeid(int))
    {
        rs = reinterpret_cast<T>(std::stoi(s));
    }
    else if constexpr (typeid(T)==typeid(long))
    {
        rs = reinterpret_cast<T>(std::stol(s));
    }
    else if constexpr (typeid(T) == typeid(string))
    {
        rs = reinterpret_cast<T>(s);
    }

    return rs;
}


#endif