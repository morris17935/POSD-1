#include "global.h"
#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "number.h"
#include "list.h"
#include "scanner.h"
#include "parser.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
    string cinstring="";
    string allcin="";
    cout<<"?- ";
    while((getline(cin,cinstring,'\n')) && cinstring != "halt."){
        if(cinstring == ""){
            allcin="";
            cout<<"?- ";
        }
        else if(int(cinstring.find("."))<0){
            allcin = allcin + cinstring;
            cout<<"|    ";
        }
        else{
            allcin = allcin + cinstring;
            Scanner s(allcin);
            Parser p(s);
            try{
              p.buildExpression();
              cout<<result<<endl<<"?- ";
            } catch (std::string & msg) {
              cout << msg;
            }
            allcin="";
        }
    }
}