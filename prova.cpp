
#include "./catch_amalgamated.hpp"
#define CATCH_CONFIG_MAIN
#include <print>
#include <vector>

#include <typeinfo>
#include <any>
#include <typeindex>
#include "prm.hpp"

class Prm;
using std::print;
using std::string;
using std::type_index;
using std::type_info;

vector<char *>gnrArg(int num, ...)
{

}

TEST_CASE(" First Arg.")
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

TEST_CASE("istr. second argument")
{
    vector<const char*> args{"0.1", "--host", "127.0.0.1", "6379"};
    vector<char *> args2{};

    for (auto str: args)
    {
        args2.push_back((char*)str);
    }

    Prm prm(args2.size(), args2.data());

    CHECK(prm.getIstrScd("host").compare(string{"6379"})==0);
}

TEST_CASE("subistr prova")
{
    Prm::Subistr sub{{"hel","guangming"}, {"123","12345"}};

    print("sub.ltr: {}", sub.ltr[1]);
    CHECK(std::any_cast<int>(sub.getIdx(1, type_index(typeid(int))))==12345);

}

TEST_CASE("subistr prova n. 2 ")
{
    Prm::Subistr sub{{"hel","guangming"}, {"123","12345"}};

    print("sub.ltr: {}", sub.ltr[0]);
    CHECK(std::any_cast<int>(sub.getIdx(0))==123);

}