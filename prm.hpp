#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <print>

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

    struct Istr
    {
        string nm{};
        string abrv{};


        int cnt{0};
    };

    vector<Istr> istr{};



    int setIstr(const string &nm)
    {
        istr.push_back(Istr{nm});

        return 0;
    }

    int setIstr(const string &nm, const string &abrv)
    {
        istr.push_back(Istr{nm, abrv});

        return 0;
    }

    int setIstr(const string &nm, const string &abrv, const int &cnt)
    {
        istr.push_back(Istr{nm, abrv, cnt});

        return 0;
    }

    template<typename T>
    T getArgIdx(int idx, T typ);

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

    string getLst()
    {
        return arg.back();
    }

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