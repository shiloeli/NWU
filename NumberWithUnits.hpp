#pragma once
#include <iostream>

namespace ariel{
    class NumberWithUnits{
        private:
            double num;
            std::string unit;
            static void check_valid_operator(const std::string &unit1, const std::string &unit2);
            static void check_unit_integrity(const std::string &unit);
            static void update_unit_map(std::string& unit1, std::string& unit2);

        public:
            NumberWithUnits(const double num,const std::string& unit);
            static void read_units(std::ifstream& input);

            NumberWithUnits operator+(const NumberWithUnits& var1)const;
            NumberWithUnits operator-(const NumberWithUnits& var1)const;
            NumberWithUnits operator+()const;
            NumberWithUnits operator-()const;

            NumberWithUnits& operator+=(const NumberWithUnits& var1);
            NumberWithUnits& operator-=(const NumberWithUnits& var1);

            bool operator>(const NumberWithUnits& var1)const;
            bool operator>=(const NumberWithUnits& var1)const;
            bool operator<(const NumberWithUnits& var1)const;
            bool operator<=(const NumberWithUnits& var1)const;
            bool operator==(const NumberWithUnits& var1)const;
            bool operator!=(const NumberWithUnits& var1)const;
            
            NumberWithUnits& operator++();
            NumberWithUnits operator++(int);
            NumberWithUnits& operator--();
            NumberWithUnits operator--(int);

            friend std::ostream& operator<<(std::ostream& out, const NumberWithUnits& var);
            friend std::istream& operator>>(std::istream& in, NumberWithUnits& var);
            friend NumberWithUnits operator*(const double var1,const NumberWithUnits& var2);
            friend NumberWithUnits operator*(const NumberWithUnits& var1, const double var2);
    };
}