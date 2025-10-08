//
// Created by gennydawg on 1/17/24.
//Had trouble utilizing provided main tester

#include <iostream>
#include <optional>
#include <string>
#include "Variant.h"

using namespace std;
namespace ECE141{

    //default to int of 0
   Variant::Variant() : value_type{VariantType::intType}, int_value{0} {}

  Variant::Variant(const Variant &aCopy) { *this = aCopy; }

   Variant & Variant:: operator=(const Variant &aCopy) {
        if (aCopy.value_type == VariantType::floatType) {
            value_type = VariantType::floatType;
            float_value = aCopy.float_value;
            return *this;
        }
        else if (aCopy.value_type == VariantType::intType) {
            value_type = VariantType::intType;
            int_value = aCopy.int_value;
            return *this;
        }
        else if (aCopy.value_type == VariantType::stringType) {
            value_type=VariantType::stringType;
            string_value = aCopy.string_value;
            return *this;
        }

        else throw "No type found for LHS";
    }

    Variant::~Variant() = default;

    //removed explicit keyword, compiler did not recognize argument when constructing Variant during compile time
    Variant::Variant(int aVal) : value_type{VariantType::intType}, int_value{aVal} {}

    Variant::Variant(float aVal) : value_type{VariantType::floatType}, float_value{aVal} {}

    Variant::Variant(string aVal) : value_type{VariantType::stringType}, string_value(aVal) {}


    //setters
    Variant & Variant:: operator=(int aValue) {
        value_type = VariantType::intType;
        int_value = aValue;
        return *this;
    }

    Variant & Variant::operator=(float aValue) {
        value_type = VariantType::floatType;
        float_value = aValue;
        return *this;
    }


    Variant &Variant::operator=(const string& aValue) {
        // Check for self-assignment
        if (string_value== aValue) {
            return *this;
        }

        // Set the value type
        value_type = VariantType::stringType;

        // Assign the new value using std::string
        string_value = aValue;

        return *this;
    }

    //getters
    optional<int> Variant::asInt() const { // Retrieve value as int
        if (value_type == VariantType::intType) {
            return int_value;
        }
        else if (value_type == VariantType::floatType) {
            return static_cast<int> (float_value);
        }
        return std::stoi(string_value);
    }

    optional<float> Variant::asFloat() const {  // Retrieve value as float
        if (value_type == VariantType::floatType) return float_value;
        else if (value_type == VariantType::intType) return static_cast<float> (int_value);
        return stof(string_value); //return float value of string
    }

    optional<string> Variant::asString() const { // Retrieve value as string, char*
        if (value_type == VariantType::stringType) return string_value;
        else return val_to_String(); //call to helper, cycle stealing?
    }

    VariantType Variant::getType() const { // Get current type of variant
        return value_type;
    }

    //math ops
    Variant Variant::operator+(const Variant &aVar) { //val_or() built into optional
        Variant I;
        I.value_type = this->value_type;
        if (value_type == VariantType::intType) {
            I.int_value = this->int_value + aVar.asInt().value_or(0);
            return I;
        }
        else if (value_type == VariantType::floatType) {
            I.float_value = this->float_value + aVar.asFloat().value_or(0);
            return I;
        }
        else
            I.string_value = this->string_value + aVar.asString().value_or(string());
        return I; //return some empty string
    }

    Variant Variant::operator-(const Variant &aVar) { //val_or() built into optional
        Variant I;
        I.value_type = this->value_type;
        if (value_type == VariantType::intType) {
            I.int_value = this->int_value - aVar.asInt().value_or(0);
            return I;
        }
        else if (value_type == VariantType::floatType) {
            I.float_value = this->float_value - aVar.asFloat().value_or(0);
            return I;
        }
        else throw invalid_argument("Tried to subtract strings?");
    }

    Variant Variant::operator*(const Variant &aVar) { //val_or() built into optional
        Variant I;
        I.value_type = this->value_type; //must have some type
        if (value_type == VariantType::intType) {
            I.int_value = this->int_value * aVar.asInt().value_or(0);
            return I;
        }
        else if (value_type == VariantType::floatType) {
            I.float_value = this->float_value * aVar.asFloat().value_or(0);
            return I;
        }
        else throw invalid_argument("Tried to multiply strings?");
    }

    Variant Variant::operator/(const Variant &aVar) { //val_or() built into optional
        //check div by 0
        if (aVar.float_value == 0 || aVar.int_value == 0 || aVar.string_value == "0") {
            throw invalid_argument("Can't divide by 0");
        }
        Variant I;
        I.value_type = this->value_type;
        if (value_type == VariantType::intType) {
            I.int_value = this->int_value / aVar.asInt().value_or(0);
            return I;
        }
        else if (value_type == VariantType::floatType) {
            I.float_value = this->float_value / aVar.asFloat().value_or(0);
            return I;
        }
        else throw invalid_argument("Tried to divide strings?");
    }

    Variant Variant::operator++() {
        if (value_type != VariantType::intType) {
            throw invalid_argument("Can't increment/decrement string/float type");
        }
        //because value type already defined, so association will only be towards ctor def
        this->int_value++;
        return *this;
    }

    Variant Variant::operator++(int) {
        Variant I(*this);
        if (value_type != VariantType::intType) {
            throw invalid_argument("Can't increment/decrement string/float type");
        }
        //because value type already defined, so association will only be towards ctor def
        this->int_value++;
        return I;
    }

    Variant Variant::operator--() {
        if (value_type != VariantType::intType) {
            throw invalid_argument("Can't increment/decrement string/float type");
        }
        //because value type already defined, so association will only be towards ctor def
        this->int_value--;
        return *this;
    }

    Variant Variant::operator--(int) {
        Variant I(*this);
        if (value_type != VariantType::intType) {
            throw invalid_argument("Can't increment/decrement string/float type");
        }
        //because value type already defined, so association will only be towards ctor def
        this->int_value--;
        return I;
    }

    //added const
    //fixed case where values were converted to int and lost value resulting in numerically false comparisons
    //just need to directly compare floats to account for decimals, more precise comparison
    //same for string
    //comp ops
    bool Variant::operator==(const Variant &aVar) const{
        if ((this->asFloat().value_or(0)) == aVar.asFloat().value_or(0)) return true;
        else if((this->asString().value_or(string()) == aVar.asString().value_or(string()) ))return true;
        return false;
    }

    bool Variant:: operator<(const Variant &aVar) const {
        if ((this->asFloat().value_or(0)) < aVar.asFloat().value_or(0)) return true;
        else if ((this->asString().value_or(string()) < aVar.asString().value_or(string())))return true;
        return false;
    }

    bool Variant::operator>(const Variant &aVar) const {
        if ((this->asFloat().value_or(0)) > aVar.asFloat().value_or(0)) return true;
        else if((this->asString().value_or(string()) > aVar.asString().value_or(string()) ))return true;
        return false;
    }

    bool Variant::operator<=(const Variant &aVar) const {
        if ((this->asFloat().value_or(0)) <= aVar.asFloat().value_or(0)) return true;
        else if((this->asString().value_or(string()) <= aVar.asString().value_or(string()) ))return true;
        return false;
    }

    bool Variant::operator>=(const Variant &aVar) const {
        if ((this->asFloat().value_or(0)) >= aVar.asFloat().value_or(0)) return true;
        else if((this->asString().value_or(string()) >= aVar.asString().value_or(string()) ))return true;
        return false;
    }

    bool Variant::operator!=(const Variant &aVar) const {
        if ((this->asFloat().value_or(0)) != aVar.asFloat().value_or(0)) return true;
        else if((this->asString().value_or(string()) != aVar.asString().value_or(string()) ))return true;
        return false;
    }

    //explicit for type cast/template format, otherwise ignore
    //conversion ops, to cast Variant if valid
     Variant::operator int() const{ return this->asInt().value_or(0); }

   Variant::operator float()const{return this->asFloat().value_or(0);}

      Variant::operator string() const{return this->asString().value_or(string());}


    //streams
    //friend keyword: Variant class grants permission to any user in accesseing the standalone function
     ostream& operator<<(ostream &aStream, const Variant &aVar) {
        if(aVar.getType() == VariantType::intType) aStream<<aVar.asInt().value_or(0);
        else if(aVar.getType() == VariantType::floatType) aStream<<aVar.asFloat().value_or(0);
        else aStream<<aVar.asString().value_or(string());

        return aStream;
    }

    optional<string> Variant::val_to_String() const {
        if (value_type == VariantType::intType)
            return to_string(int_value);
        else if (value_type == VariantType::floatType)
            return to_string(float_value);
        else
        return nullopt;
    }

}
