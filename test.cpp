
#include "./catch_amalgamated.hpp"
#define CATCH_CONFIG_MAIN
#include <print>
#include <vector>
#include "prm.hpp"

class Prm;
using std::print;
using std::string;

TEST_CASE("Test First Argument")
{
    // const char *arr[6]={"0.1","123","--host","127.0.0.1","123","ltr"};
    //
    // char* arrTsf[6];

    vector<const char*> args{"0.1", "--host", "127.0.0.1"};
    vector<char *> args2{};

     for (auto str: args)
     {
         args2.push_back((char*)str);
     }
    //
    Prm prm(3, args2.data());
    print("{}", prm.getArgLtr(1));
    prm.setIstr("host");
    prm.getIstrFst(std::string("host")).compare(string("127.0.0.1"));
    print("istr fst {}\n", prm.getIstrFst("host"));
    CHECK(prm.getIstrFst("host").compare(string("127.0.0.1"))==0);
    //CHECK(1==1);
}