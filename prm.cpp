

#include "./prm.hpp"

class Prm;

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

Istr Prm::findIstr(const string &istrIn)
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
        }

        else if (i.abrv.empty()==false && istrIn.compare(i.abrv)==0)
        {
            cout<<"chk ok abrv"<<endl;
            istrFlg=true;
        }


    });

    Istr rsl = *itr;

    return itr;

};


Istr Prm::findIstrAbrv(const string &istrIn)
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
        }


    });

    Istr rsl = *itr;

    return itr;

};

Istr Prm::findIstrFull(const string &istrIn)
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
        }

    });

    Istr rsl = *itr;

    return itr;

};


