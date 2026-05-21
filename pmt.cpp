//
// Created by Y. Zang on 2026/5/21.
//

#include "./prm.hpp"
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;


int main(int argCnt, char* arg[])
{
    Prm prm(argCnt, arg);

    //cout<<prm.getArgLtr(1)<<endl;

    //cout<<prm.getIstr("prm")<<endl;

    cout<<prm.getIstrFrst("prmfrst")<<endl;
    cout<<prm.getIstrScnd("prmscd")<<endl;

    std::cout << "pmt prm" << std::endl;
    return 0;
}

