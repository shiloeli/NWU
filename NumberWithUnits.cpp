#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include "NumberWithUnits.hpp"
using namespace std;

namespace ariel{
            
           static unordered_map<string,unordered_map<string,double>> units_map;

            void NumberWithUnits::check_valid_operator(const string &unit1, const string &unit2){
                if(units_map.count(unit1)==0||units_map.count(unit2)==0){
                    throw invalid_argument("At least one of the units is invalid"); 
                }
                if(unit1 == unit2){
                    return;
                }
                if((units_map[unit1].count(unit2))==0){
                    throw invalid_argument("Units do not match - ["+unit1+"] cannot be converted to ["+unit2+"]");
                }
            }

            void NumberWithUnits::check_unit_integrity(const string &unit){
                if(units_map.count(unit)==0){
                    throw invalid_argument("Invalid unit - ["+unit+"]");   
                }
            }

            void NumberWithUnits::update_unit_map(string& unit1, string& unit2){
                for(const auto& dict: units_map[unit1]) {     
                    if(unit2!=dict.first){
                        units_map[unit2][dict.first] = dict.second * units_map[unit2][unit1];
                        units_map[dict.first][unit2] = 1 / (dict.second * units_map[unit2][unit1]);
                    }
                }
                for(const auto& dict: units_map[unit2]) {
                    if(unit1!=dict.first){
                        units_map[unit1][dict.first] = dict.second * units_map[unit1][unit2];
                        units_map[dict.first][unit1] = 1 / (dict.second * units_map[unit1][unit2]);
                    }
                }
            }

            NumberWithUnits::NumberWithUnits(const double num,const string& unit){
                NumberWithUnits::check_unit_integrity(unit);
                this->num = num;
                this->unit = unit;
            }    

            void NumberWithUnits::read_units(ifstream& input){
                string word, unit;
                const char first_unit=2, number_unit=4, second_unit=5;;
                double num=0;
                uint counter=1;

                while(input >> word){
                    switch(counter){
                        case first_unit:
                            unit = word;
                            break;

                        case number_unit:
                            num = stod(word);
                            break;

                        case second_unit:
                            units_map[unit][word]=num;
                            units_map[word][unit]=(1/num);
                            update_unit_map(unit, word);
                            counter=0;
                            break;
                    }
                    counter++;
                }
            }

            NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& var1)const{
                NumberWithUnits::check_valid_operator(this->unit , var1.unit);
                double sum=0;
                if(this->unit == var1.unit){
                    sum = this->num + var1.num; 
                }else{
                    sum = this->num + (var1.num*units_map[var1.unit][this->unit]);
                }
                NumberWithUnits new_var{sum,this->unit};
                return new_var;
            }

            NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& var1)const{
                NumberWithUnits::check_valid_operator(this->unit,var1.unit);
                double sum=0;
                if(this->unit == var1.unit){
                    sum = this->num - var1.num;
                }else{
                    sum = this->num - (var1.num*units_map[var1.unit][this->unit]);
                }
                NumberWithUnits new_var{sum,this->unit};
                return new_var;
            }

            NumberWithUnits NumberWithUnits::operator+()const{
                NumberWithUnits::check_unit_integrity(this->unit);
                NumberWithUnits var{this->num,this->unit};
                return var;
            }

            NumberWithUnits NumberWithUnits::operator-()const{
                NumberWithUnits::check_unit_integrity(this->unit);
                NumberWithUnits new_var{-this->num,this->unit};
                return new_var;
            }

            NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& var1){
                NumberWithUnits::check_valid_operator(this->unit, var1.unit);
                if(this->unit == var1.unit){
                    this->num = this->num+var1.num;
                    return *this;
                }
                this->num = this->num + units_map[var1.unit][this->unit]*var1.num;
                return *this;
            }
           
            NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& var1){
                NumberWithUnits::check_valid_operator(this->unit, var1.unit);
                if(this->unit == var1.unit){
                    this->num = this->num-var1.num;
                    return *this;
                }
                this->num = this->num - units_map[var1.unit][this->unit]*var1.num;
                return *this;
            }

            bool NumberWithUnits::operator>(const NumberWithUnits& var1)const{
                NumberWithUnits::check_valid_operator(this->unit, var1.unit);
                if(this->unit == var1.unit){
                    return (this->num > var1.num);
                }
                return (this->num > units_map[var1.unit][this->unit]*var1.num);
            }

            bool NumberWithUnits::operator>=(const NumberWithUnits& var1)const{
                return(*this > var1 || *this == var1);
            }

            bool NumberWithUnits::operator<(const NumberWithUnits& var1)const{
                NumberWithUnits::check_valid_operator(this->unit, var1.unit);
                if(this->unit == var1.unit){
                    return (this->num < var1.num);
                }
                return (this->num < units_map[var1.unit][this->unit]*var1.num);
            }

            bool NumberWithUnits::operator<=(const NumberWithUnits& var1)const{
                return(*this == var1 || *this < var1);
            }
            
            bool NumberWithUnits::operator==(const NumberWithUnits& var1)const{
                const double eps = 0.000001;
                NumberWithUnits::check_valid_operator(this->unit, var1.unit);
                if(this->unit == var1.unit){
                    return(abs(this->num-var1.num)<eps);
                    }
                return(abs(num- units_map[var1.unit][this->unit]*var1.num)<eps);
            }

            bool NumberWithUnits::operator!=(const NumberWithUnits& var1)const{
                return(!(*this == var1));
            }

            NumberWithUnits& NumberWithUnits::operator++(){
                NumberWithUnits::check_unit_integrity(this->unit);
                this->num++;
                return *this;
            }

            NumberWithUnits NumberWithUnits::operator++(int){
                NumberWithUnits::check_unit_integrity(this->unit);
                NumberWithUnits temp{this->num++, this->unit};
                return temp;
            }

            NumberWithUnits& NumberWithUnits::NumberWithUnits::operator--(){
                NumberWithUnits::check_unit_integrity(this->unit);
                this->num--;
                return *this;
            }

            NumberWithUnits NumberWithUnits::operator--(int){
                NumberWithUnits::check_unit_integrity(this->unit);
                NumberWithUnits temp{this->num--, this->unit};
                return temp;
            }

            ostream& operator<<(ostream& out, const NumberWithUnits& var){
                return out<<var.num<<"["+var.unit+"]";
            }

            istream& operator>>(istream& in, NumberWithUnits& var){
                string word;
                char character=0;
                double var_num = 0.0;

                while(in>>character){
                    if(character=='['){
                        var_num = stod(word);
                        word = "";
                        in>>character;
                    }

                    if(character == ']'){
                        NumberWithUnits::check_unit_integrity(word);
                        var.num = var_num;
                        var.unit = word;
                        return in;
                    }
                    word += character;
                }
                return in;
            }

            NumberWithUnits operator*(const double var1,const NumberWithUnits& var2){
                NumberWithUnits::check_unit_integrity(var2.unit);
                NumberWithUnits var{(var1*var2.num),var2.unit};
                return var;
            }

            NumberWithUnits operator*(const NumberWithUnits& var1, const double var2){
                NumberWithUnits::check_unit_integrity(var1.unit);
                NumberWithUnits var{(var2*var1.num),var1.unit};
                return var;
            }          
}