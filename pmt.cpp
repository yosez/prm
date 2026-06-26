//
// Created by Y. Zang on 2026/5/21.
//

#include "./prm.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <print>

using std::string;
using std::cout;
using std::endl;
using std::print;


int main(int argCnt, char* arg[])
{
    Prm prm(argCnt, arg); 

    //cout<<prm.getArgLtr(1)<<endl;

    //cout<<prm.getIstr("prm")<<endl;

    // cout<<prm.getIstrFrst("prmfrst")<<endl;
    // cout<<prm.getIstrScnd("prmscd")<<endl;
    //
    cout<<prm.setIstr("help")<<endl;

    cout<<"set istr"<<endl;

    cout<<(prm.getIstr("help")?"true":"false")<<endl;
    cout<<prm.getIstrFst("help")<<endl;

    //int vl = prm.getArgFst("help", Prm::ArgType::Float);

    print("as int: {}", prm.getArgFst<int>("help"));

    //cout<<"get istr"<<dynamic_cast<string>(prm.getArgFst<int>("help"))<<endl;

    return 0;
}

