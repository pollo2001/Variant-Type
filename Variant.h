#pragma once
#include <iostream>
#include <optional>
#include <string>


#ifndef Variant_H
#define Variant_H

using namespace std;
namespace ECE141 {
    enum class VariantType{ intType, floatType, stringType };
    struct Variant {

        //default to int of 0
        Variant();
        Variant(const Variant &aCopy);
        Variant &operator=(const Variant &aCopy) ;
        ~Variant() ;

        //prevent implicit conversion
        explicit Variant(int aVal);
       explicit Variant(float aVal) ;
       explicit Variant(string aVal);

        //setters
        Variant &operator=(int aValue);
        Variant &operator=(float aValue);
        Variant &operator=(const string& s) ;

        //getters
        optional<int> asInt() const ;
        optional<float> asFloat() const ;
        optional<string> asString() const ;
        VariantType getType() const ;

        //math ops
        Variant operator+(const Variant &aVar) ;
        Variant operator-(const Variant &aVar) ;
        Variant operator*(const Variant &aVar) ;
        Variant operator/(const Variant &aVar) ;
        Variant operator++() ;
        Variant operator++(int);
        Variant operator--() ;
        Variant operator--(int) ;


        //comp ops
        bool operator==(const Variant &aVar) const;
        bool operator<(const Variant &aVar) const;
        bool operator>(const Variant &aVar) const;
        bool operator<=(const Variant &aVar) const ;
        bool operator>=(const Variant &aVar) const ;
        bool operator!=(const Variant &aVar) const;

        //explicit for type cast/template format, otherwise ignore
        //conversion ops, to cast Variant if valid
        explicit operator int() const;
        explicit operator float()const;
        explicit operator string() const;

        //streams
        //friend keyword: Variant class grants permission to any user in accesseing the standalone function
        friend ostream &operator<<(ostream &aStream, const Variant &aVar) ;


    protected:
        // ---TODO: Add member variables---
        VariantType value_type;
        int int_value;
        float float_value;
        string string_value;
        optional<string> val_to_String() const;
    };
}
#endif