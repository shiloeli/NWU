#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;
#include "NumberWithUnits.hpp"
using namespace ariel;

void get_two_units(NumberWithUnits& a, NumberWithUnits& b){
        cout<<"Write the arguments as follows: number [ unit ]"<<endl;
        cout<<"Write the first argument"<<endl;
        cin>>a;
        cout<<"Write the second argument"<<endl;
        cin>>b;
    }

void get_one_units(NumberWithUnits& a){
        cout<<"Write the arguments as follows: number [ unit ]"<<endl;
        cout<<"Write the argument"<<endl;
        cin>>a;
    }

int main() {
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  string oper;
  bool flag=true;

  while(flag){
  cout<<"Write the binary action you want to perform :"<<endl;
  cout<<"+,-,+=,-=,==,!=,<,>,<=,>="<<endl;
  cout<<"++[unit],--[unit],[unit]++,[unit]--"<<endl;
  cout<<"+[unit],-[unit],*[unit],[unit]*"<<endl;
  cin>>oper;
    
    if(oper=="+"){
        NumberWithUnits var1{0,"sec"};
        NumberWithUnits var2{0,"sec"};
        get_two_units(var1, var2);
        cout<<"Answer: ";
        cout<<(var1+var2)<<endl;
    }
    if(oper=="-"){
        NumberWithUnits var1{0,"sec"};
        NumberWithUnits var2{0,"sec"};
        get_two_units(var1, var2);
        cout<<"Answer: ";
        cout<<var1-var2<<endl;
    }
    if(oper=="+="){
        NumberWithUnits var1{0,"sec"};
        NumberWithUnits var2{0,"sec"};
        get_two_units(var1, var2);
        cout<<"Answer: ";
        var1+=var2;
        cout<<var1<<endl;
    }
    if(oper=="-="){
        NumberWithUnits var1{0,"sec"};
        NumberWithUnits var2{0,"sec"};
        get_two_units(var1, var2);
        cout<<"Answer: ";
        var1-=var2;
        cout<<var1<<endl;
    }
    if(oper==">"){
        NumberWithUnits var1{0,"sec"};
        NumberWithUnits var2{0,"sec"};
        get_two_units(var1, var2);
        cout<<"Answer: ";
        cout<<(var1==var2)<<endl;
    }
    if(oper==">="){
        NumberWithUnits var1{0,"sec"};
        NumberWithUnits var2{0,"sec"};
        get_two_units(var1, var2);
        cout<<"Answer: ";
        cout<<(var1>=var2)<<endl;
    }
    if(oper=="<"){
        NumberWithUnits var1{0,"sec"};
        NumberWithUnits var2{0,"sec"};
        get_two_units(var1, var2);
        cout<<"Answer: ";
        cout<<(var1<var2)<<endl;
    }
    if(oper=="<="){
        NumberWithUnits var1{0,"sec"};
        NumberWithUnits var2{0,"sec"};
        get_two_units(var1, var2);
        cout<<"Answer: ";
        cout<<(var1<=var2)<<endl;
    }
    if(oper=="=="){
        NumberWithUnits var1{0,"sec"};
        NumberWithUnits var2{0,"sec"};
        get_two_units(var1, var2);
        cout<<"Answer: ";
        cout<<(var1==var2)<<endl;
    }
    if(oper=="!="){
        NumberWithUnits var1{0,"sec"};
        NumberWithUnits var2{0,"sec"};
        get_two_units(var1, var2);
        cout<<"Answer: ";
        cout<<(var1!=var2)<<endl;
      }
    if(oper=="++[unit]"){
        NumberWithUnits var1{0,"sec"};
        get_one_units(var1);
        cout<<"Answer: ";
        cout<<++var1<<endl;
    }
    if(oper=="--[unit]"){
        NumberWithUnits var1{0,"sec"};
        get_one_units(var1);
        cout<<"Answer: ";
        cout<<--var1<<endl;
    }
    if(oper=="[unit]++"){
        NumberWithUnits var1{0,"sec"};
        get_one_units(var1);
        cout<<"Answer: ";
        cout<<var1++<<endl;
    }
    if(oper=="[unit]--"){
        NumberWithUnits var1{0,"sec"};
        get_one_units(var1);
        cout<<"Answer: ";
        cout<<var1--<<endl;
    }
    if(oper=="+[unit]"){
        NumberWithUnits var1{0,"sec"};
        get_one_units(var1);
        cout<<"Answer: ";
        cout<<+var1<<endl;
    }
    if(oper=="-[unit]"){
        NumberWithUnits var1{0,"sec"};
        get_one_units(var1);
        cout<<"Answer: ";
        cout<<-var1<<endl;
    }
    if(oper=="*[unit]"){
        NumberWithUnits var1{0,"sec"};
        get_one_units(var1);
        double num;
        cout<<"Now,write a variable of double types"<<endl;
        cin>>num;
        cout<<"Answer: ";
        cout<<num*var1<<endl;
    }
    if(oper=="[unit]*"){
        NumberWithUnits var1{0,"sec"};
        get_one_units(var1);
        double num;
        cout<<"Now,write a variable of double types"<<endl;
        cin>>num;
        cout<<"Answer: ";
        cout<<var1*num<<endl;
    }

    string ans;
    cout<<"Would you like to perform an additional action ? write yes/no "<<endl;
    cin>>ans;
    if(ans=="no"){
      flag=false;
    }
  }
  return 0;
}
