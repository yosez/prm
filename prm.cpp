

#include "./prm.hpp"

class Prm;

//enum class Prm::ArgType;
//using ArgType = Prm::ArgType;

int Prm::setIstr(const string &nm)
{
    istr.push_back(Istr{nm});

    return 0;
}

int Prm::setIstr(const string &nm, const string &abrv)
{
    istr.push_back(Istr{nm, abrv});

    return 0;
}

int Prm::setIstr(const string &nm, const string &abrv, const int &cnt)
{
    istr.push_back(Istr{nm, abrv, cnt});

    return 0;
}

int Prm::setIstr(const std::pair<string, string> & pair)
{
    istr.push_back(Istr{pair.first, pair.second});
}

int Prm::addDesc(Istr istr, const string &desc)
{
    istr.desc=desc;

    return 0;
}

int Prm::addDesc(const string &name, const string &desc)
{
    auto istr = std::move(findIstr(name));

    istr.desc = desc;

    return 0;
}

Prm::Istr Prm::findIstr(const string &istrIn)
{
    bool istrFlg=false;


    cout<<istr.size()<<":"<<istr[0].nm<<":"<<istrIn<<endl;

    //find in instr
    auto itr = find_if(istr.begin(), istr.end(), [vct = istr, istrIn, &istrFlg](const Istr &i) {


        cout<<vct[0].nm<<":"<<istrIn<<endl;
        cout<<i.nm<<":"<<istrIn<<endl;

        if (i.nm.empty() ==false && istrIn.compare(i.nm)==0)
        {
            cout<<"chk ok nm"<<endl;
            istrFlg=true;

            return true;
        }

        else if (i.abrv.empty()==false && istrIn.compare(i.abrv)==0)
        {
            cout<<"chk ok abrv"<<endl;
            istrFlg=true;

            return true;
        }

        return false;
    });

    Istr rsl = *itr;

    return rsl;

};


Prm::Istr Prm::findIstrAbrv(const string &istrIn)
{
    bool istrFlg=false;


    cout<<istr.size()<<":"<<istr[0].nm<<":"<<istrIn<<endl;

    //find in instr
    auto itr = find_if(istr.begin(), istr.end(), [vct = istr, istrIn, &istrFlg](const Istr &i) {


        cout<<vct[0].nm<<":"<<istrIn<<endl;
        cout<<i.nm<<":"<<istrIn<<endl;


        if (i.abrv.empty()==false && istrIn.compare(i.abrv)==0)
        {
            cout<<"chk ok abrv"<<endl;
            istrFlg=true;

            return true;
        }

        return false;
    });

    Istr rsl = *itr;

    return rsl;

};

// template<typename T>
// requires (std::is_same<T, ArgType>::value)
// T Prm::getArgFst(string arg, T typ)
// {
//     //string s(arg);
//     string s{getIstrFst(arg)};
//
//     T rs;
//
//
//     switch (typ)
//     {
//         case ArgType::Double:
//         {
//             rs = dynamic_cast<T>(std::stod(s));
//             break;
//         }
//         case ArgType::Float:
//         {
//             rs = dynamic_cast<T>(std::stof(s));
//             break;
//         }
//         case ArgType::Int:
//         {
//             rs = dynamic_cast<T>(std::stoi(s));
//             break;
//         }
//         case ArgType::Long:
//         {
//             rs = dynamic_cast<T>(std::stol(s));
//             break;
//         }
//         case ArgType::String:
//         {
//             rs = dynamic_cast<T>(s);
//             break;
//         }
//         default:
//         {
//             throw ArgumentNotDefinedExcept();
//         }
//     }
//
//     return rs;
// }


string Prm::getArgLtr(int idx)
{
    return string(arg[idx]);
}

///TODO
//--host<ip, port> 127.0.0.1 6637
// void Prm::setSubistr(Istr &istr, const string &sub)
// {
//     if (istr.hasSubistr==false)
//     {
//         throw InstructionNotHasSubinstructionExcept();
//     }
//
//     istr.sub.emplace_back(sub);
//
//
// }

/// TODO
// template<typename T>
// void Prm::getSubistr(const Istr &istr, const string &sub)
// {
//     if (istr.hasSubistr==false)
//     {
//         throw InstructionNotHasSubinstructionExcept();
//     }
//
//     bool subFlg=false;
//
//     for_each(istr.sub.begin(), istr.sub.end(), [&sub, &subFlg](const Subistr &si) {
//         if (si.nm == sub)
//         {
//             subFlg=true;
//
//         }
//     });
//
//     if (!subFlg)
//     {
//         throw InstructionNotHasSubinstructionExcept();
//     }
// }

string Prm::getLst()
{
    if (lstArg ==false || arg.back().starts_with("-") == false)
    {
        return string{};
    }

    return arg.back();
}

string Prm::getPult()
    {
        if (pultArg == false || arg.at(arg.size()-2).starts_with("-")==false)
        {
            return string{};
        }

        return arg.at(arg.size()-2);
    }

bool Prm::getIstr(const string &istrIn)
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


void Prm::setFst()
{
    fstArg=true;
}

string Prm::getFst()
{
    if (fstArg ==false || arg.front().starts_with("-"))
    {
        return string{};
    }

    return arg.front();
}

void Prm::setScd()
{
    scdArg=true;
}

string Prm::getScd()
{
    if (pultArg==false)
    {
        throw ArgumentNotDefinedExcept{};
    }



    if (pultArg == false || arg.at(1).starts_with("-")==false)
    {
        return string{};
    }

    return string{arg.at(2)};
}

string Prm::getLstLtr()
{
    return arg.back();
}

string Prm::getFstLtr()
{
    return arg.front();
}

void Prm::setLst()
{
    lstArg=true;

}

void Prm::setPult()
{
    pultArg=true;
}





Prm::Istr Prm::findIstrFull(const string &istrIn)
{
    bool istrFlg=false;


    cout<<istr.size()<<":"<<istr[0].nm<<":"<<istrIn<<endl;

    //find in instr
    auto itr = find_if(istr.begin(), istr.end(), [vct = istr, istrIn, &istrFlg](const Istr &i) {


        cout<<vct[0].nm<<":"<<istrIn<<endl;
        cout<<i.nm<<":"<<istrIn<<endl;

        if (i.nm.empty() ==false && istrIn.compare(i.nm)==0)
        {
            cout<<"chk ok nm"<<endl;
            istrFlg=true;

            return true;
        }

        return false;

    });

    Istr rsl = *itr;

    return rsl;

};



string Prm::getIstrFst(string istrIn)
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
string Prm::getIstrScd(string istrIn)
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

