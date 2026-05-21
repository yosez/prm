#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::string;
using std::vector;
using std::endl;
using std::for_each;

//e.g. --help -h
//e.g. --host 127.0.0.1            single
//e.g. --on 127.0.0.1:8080          pair
//e.g.



class Prm
{
public:
    int argCnt;
    char** argIn;

    vector<string> arg;

    struct IstrStrc
    {
        string abrv;
        string nm;


    };

    template<typename T>
    T getArgIdx(int idx, T typ);

    string getArgLtr(int idx)
    {
        return string(arg[idx]);
    }

    bool getIstr(const string &istr)
    {

        bool flg=false;

        std::for_each(arg.begin(), arg.end(), [istr, &flg](const string &s) {

            cout<<s<<":"<<istr<<endl;
            if (s.compare(istr)==0)
            {
                cout<<"chk ok"<<endl;
                flg=true;
            }

        });

        return flg;
    }

    string getIstrFrst(string istr)
    {
        int psn=-1;

        std::for_each(arg.begin(), arg.end(), [it=arg.begin(), bgn = arg.begin(), istr, &psn](auto &s) mutable  {

            //cout<<*it<<":"<<istr<<endl;
            if (s.compare(istr)==0)
            {

                psn = it - bgn;

            }

            ++it;
        });

        if (psn==-1)
        {
            return nullptr;
        }

        return arg[psn+1];
    }

    string getIstrScnd(string istr)
    {
        int psn=-1;

        std::for_each(arg.begin(), arg.end(), [it=arg.begin(), bgn = arg.begin(), istr, &psn](auto &s) mutable  {

            //cout<<*it<<":"<<istr<<endl;
            if (s.compare(istr)==0)
            {

                psn = it - bgn;

            }

            ++it;
        });

        if (psn==-1)
        {
            return nullptr;
        }

        return arg[psn+2];
    }

    Prm(int argCnt, char* argIn[]): argCnt(argCnt), argIn(argIn)
    {
        arg = vector<string>(argCnt);

        int i=0;

        for (i=0;i<argCnt;i++)
        {
            arg[i] = argIn[i];

            cout<<"prm "<<arg[i]<<endl;
        }


    };
};