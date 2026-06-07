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

class Prm
{
public:
    int argCnt;
    char** argIn;

    vector<string> arg;

    //prm pair "--output a.txt" or "-o a.txt"
    struct Istr
    {
        string nm{};
        string abrv{};

        int cnt{0};

        string desc{};
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

    int setIstr(const string &nm);

    int setIstr(const string &nm, const string &abrv);

    int setIstr(const string &nm, const string &abrv, const int &cnt);

    int setIstr(const std::pair<string, string> & pair);


    int addDesc(Istr istr, const string &desc);

    int addDesc(const string &name, const string &desc);

    void setHelp(bool barH =false, bool doubleBarHelp=true)
    {

    }

    string getHelp()
    {

    }

    int setFst()
    {
        fstArg=true;
        return 0;
    }

    string getFst()
    {
        if (fstArg ==false || arg.front().starts_with("-"))
        {
            return string{};
        }

        return arg.front();
    }

    string getScd()
    {
        if (pultArg == false || arg.at(1).starts_with("-")==false)
        {
            return string{};
        }

        return arg.at(2);
    }

    string getLstLtr()
    {
        return arg.back();
    }

    string getFstLtr()
    {
        return arg.front();
    }

    int setLst()
    {
        lstArg=true;
        return 0;
    }

    int setPult()
    {
        pultArg=true;
        return 0;
    }

    string getLst()
    {
        if (lstArg ==false || arg.back().starts_with("-") == false)
        {
            return string{};
        }

        return arg.back();
    }

    string getPult()
    {
        if (pultArg == false || arg.at(arg.size()-2).starts_with("-")==false)
        {
            return string{};
        }

        return arg.at(arg.size()-2);
    }

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
    T getArgFst(string arg)
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

    template<typename T = ArgType>
    requires (std::is_same<T, ArgType>::value)
    T getArgFst(string arg, T typ)
    {
        //string s(arg);
        string s{getIstrFst(arg)};

        T rs;

        // if (typ == ArgType::Double)
        // {
        //     rs = dynamic_cast<T>(std::stod(s));
        // }
        // else if (typ==ArgType::Float)
        // {
        //     rs = dynamic_cast<T>(std::stof(s));
        // }
        // else if (typ==ArgType::Int)
        // {
        //     rs = dynamic_cast<T>(std::stoi(s));
        // }
        // else if (typ==ArgType::Long)
        // {
        //     rs = dynamic_cast<T>(std::stol(s));
        // }
        // else if (typ == ArgType::String)
        // {
        //     rs = dynamic_cast<T>(s);
        // }

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

    string getArgLtr(int idx)
    {
        return string(arg[idx]);
    }

    // bool getIstr(const string &istr)
    // {
    //
    //     bool flg=false;
    //
    //     std::for_each(arg.begin(), arg.end(), [istr, &flg](const string &s) {
    //
    //         cout<<s<<":"<<istr<<endl;
    //         if (s.compare(istr)==0)
    //         {
    //             cout<<"chk ok"<<endl;
    //             flg=true;
    //         }
    //
    //     });
    //
    //     return flg;
    // }


    ///PROCESSING
    bool getIstr(const string &istrIn)
    {

        bool istrFlg=false;


        cout<<istr.size()<<":"<<istr[0].nm<<":"<<istrIn<<endl;

        //find in instr
        for_each(istr.begin(), istr.end(), [vct = istr, istrIn, &istrFlg](const Istr &i) {


            cout<<vct[0].nm<<":"<<istrIn<<endl;
            cout<<i.nm<<":"<<istrIn<<endl;

            if (i.nm.empty() ==false && istrIn.compare(i.nm)==0)
            {
                cout<<"chk ok nm"<<endl;
                istrFlg=true;
            }

            else if (i.abrv.empty()==false && istrIn.compare(i.abrv)==0)
            {
                cout<<"chk ok abrv"<<endl;
                istrFlg=true;
            }


        });

        bool argFlg=false;
        //find in arguments
        for_each(arg.begin(), arg.end(), [&istrIn, &argFlg](const string &s) {
            if (s.starts_with("--"))
            {
                if (s.substr(2).compare(istrIn)==0)
                {
                    argFlg=true;
                }
            }
            else if (s.starts_with("-"))
            {
                if (s.substr(1).compare(istrIn)==0)
                {
                    argFlg=true;
                }
            }
        });

        if (istrFlg==false || argFlg==false)
        {
            throw ArgumentNotDefinedExcept();
        }

        return istrFlg&&argFlg;
    }

    string getIstrFst(string istrIn)
    {
        int psn=-1;

        vector<string>::iterator itr= arg.begin();

        bool istrFlg=false;

        //find in instruction
        for_each(istr.begin(), istr.end(), [&istrIn,  &istrFlg](const Istr &s) {
            if (s.nm.empty()==false && s.nm.compare(istrIn)==0)
            {
                cout<<"istr flg ok"<<endl;
                istrFlg=true;
            }
            else if (s.abrv.empty()==false && s.abrv.compare(istrIn)==0)
            {
                cout<<"istr flg ok"<<endl;
                istrFlg=true;
            }


        });

        bool argFlg =false;

        //find in
        //arg is input arguments
        for_each(arg.begin(), arg.end(), [&istrIn, &argFlg, &itr, &psn, bgn= arg.begin()](const string &s) {
            if (istrIn.starts_with("--"))
            {
                //arg inst cmp istrIn
                if (s.substr(2).compare(istrIn)==0)
                {
                    cout<<"arg flg ok"<<endl;
                    argFlg=true;

                    psn = itr - bgn;
                }
            }
            else if (s.starts_with("-"))
            {
                if (s.substr(2).compare(istrIn)==0)
                {
                    cout<<"arg flg ok"<<endl;
                    argFlg=true;

                    psn = itr - bgn;
                }
            }

            ++itr;
        });

        //psn = argFlg && istrFlg ? itr - arg.begin() : -1;

        cout<<"psn: "<<psn<<":"<<arg[psn]<<endl;

        if (psn ==-1)
        {
            return string{};
        }

        return arg[psn+1];

    }


    ///TODO bdr chk
    string getIstrScd(string istrIn)
    {
        int psn=-1;

        vector<string>::iterator itr= arg.begin();

        bool istrFlg=false;

        //find in instruction
        for_each(istr.begin(), istr.end(), [&istrIn,  &istrFlg](const Istr &s) {
            if (s.nm.empty()==false && s.nm.compare(istrIn))
            {
                istrFlg=true;
            }
            else if (s.abrv.empty()==false && istrIn.compare(s.abrv))
            {
                istrFlg=true;
            }


        });

        bool argFlg =false;

        //find in
        //arg is input arguments
        for_each(arg.begin(), arg.end(), [&istrIn, &argFlg, &itr, &psn, bgn = arg.begin()](const string &s) {
            if (istrIn.starts_with("--"))
            {
                //arg inst cmp istrIn
                if (s.substr(2).compare(istrIn)==0)
                {
                    argFlg=true;

                    psn = itr - bgn;
                }
            }
            else if (s.starts_with("-"))
            {
                if (s.substr(2).compare(istrIn)==0)
                {
                    argFlg=true;

                    psn = itr - bgn;
                }
            }

            ++itr;
        });

        cout<<"psn: "<<psn<<":"<<arg[psn]<<endl;

        if (psn ==-1)
        {
            return string{};
        }

        ///TODO ex
        return arg[psn+2];

    }


private:
    Istr findIstr(const string &nm);
    Istr findIstrAbrv(const string &nm);
    Istr findIstrFull(const string &nm);

    // string getIstrFrst(string istr)
    // {
    //     int psn=-1;
    //
    //     for_each(arg.begin(), arg.end(), [it=arg.begin(), bgn = arg.begin(), istr, &psn](auto &s) mutable  {
    //
    //         //cout<<*it<<":"<<istr<<endl;
    //         if (s.compare(istr)==0)
    //         {
    //
    //             psn = it - bgn;
    //
    //         }
    //
    //         ++it;
    //     });
    //
    //     if (psn==-1)
    //     {
    //         return nullptr;
    //     }
    //
    //     return arg[psn+1];
    // }
    //
    // string getIstrScnd(string istr)
    // {
    //     int psn=-1;
    //
    //     std::for_each(arg.begin(), arg.end(), [it=arg.begin(), bgn = arg.begin(), istr, &psn](auto &s) mutable  {
    //
    //         //cout<<*it<<":"<<istr<<endl;
    //         if (s.compare(istr)==0)
    //         {
    //
    //             psn = it - bgn;
    //
    //         }
    //
    //         ++it;
    //     });
    //
    //     if (psn==-1)
    //     {
    //         return nullptr;
    //     }
    //
    //     return arg[psn+2];
    // }



    //
    // string getFst()
    // {
    //     return arg.front();
    // }

    Prm(int argCnt, char* argIn[]): argCnt(argCnt), argIn(argIn)
    {
        arg = vector<string>(argCnt);

        int i=0;

        for (i=0;i<argCnt;i++)
        {
            arg[i] = argIn[i];

            cout<<"prm ltr: "<<arg[i]<<endl;
        }


    };
};
#endif