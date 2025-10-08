#pragma once
#include <iostream>
#include "Testable.h"
#include "Variant.h"
#include <map> //pull test names with map

using namespace std;
namespace ECE141 {
    class VariantTestable : public Testable {
    public:

        //always update tests num
        VariantTestable() : Testable() {
            theNumberOfTests = testList.size();
        }

        //to find tests by name, pointer to functions
        using Callable = bool (VariantTestable::*)();
        map <string, Callable> testList{
                {"ctorTest", &VariantTestable::test1},
                {"ConvTest", &VariantTestable::test2},
                {"MathTest", &VariantTestable::test3},
                {"CompTest", &VariantTestable::test4},
                {"Stream/Val Test", &VariantTestable::test5}

        };

        // Retrieve the name of a specific test by iterating map
        optional<string> getTestName(size_t anIndex) const override {
            size_t thePos{0};
            for (auto thePair: testList) {
                if (anIndex == thePos++) {
                    return thePair.first;
                }
            }
            return nullopt;
        }

        //dispatching method
        bool operator()(const string &aName) override {
            return testList.count(aName) != 0 && (this->*testList[aName])();
        }

        //ctor and getters and setters
        bool test1() {
            Variant V;
            if (V.asInt() != 0) return false;
            Variant V1(1);
            if (V1.asInt() != 1) return false;
            Variant V2(V1);
            if (!(V1 == V2))return false;

            Variant Vs("hi");
            if (Vs.asString() != "hi") return false;
            Variant Vf(7.19f);
            if (Vf.asFloat() != 7.19f) return false;

            return true;
        }

        //conversions
        bool test2() {
            // Test explicit conversion from int
            Variant V1 = convertExplicitly<int>(5);
            if (V1.asInt() != 5 || V1.getType() != VariantType::intType) return false;

            // Test explicit conversion from float
            Variant V2 = convertExplicitly<float>(3.14f);
            if (V2.asFloat() != 3.14f || V2.getType() != VariantType::floatType) return false;

            // Test explicit conversion from string
            Variant V3 = convertExplicitly<string>("test");
            if (V3.asString() != "test" || V3.getType() != VariantType::stringType) return false;

            return true;
        }

        template<typename T>
        static Variant convertExplicitly(T value) {
            return Variant(value);
        }

        bool test3() {// Test addition
            Variant V1 = Variant(5) + Variant(3);
            if (V1.asInt() != 8 || V1.getType() != VariantType::intType) return false;

            // Test subtraction
            Variant V2 = Variant(7.5f) - Variant(2.5f);
            if (V2.asFloat() != 5.0f || V2.getType() != VariantType::floatType) return false;

            // Test multiplication
            Variant V3 = Variant(4) * Variant(2);
            if (V3.asInt() != 8 || V3.getType() != VariantType::intType) return false;

            // Test division
            Variant V4 = Variant(10) / Variant(2);
            if (V4.asInt() != 5 || V4.getType() != VariantType::intType) return false;

            // Test pre-increment
            Variant V5 = Variant(3);
            Variant V6 = ++V5;
            if (V5.asInt() != 4 || V6.asInt() != 4) return false;

            // Test post-increment
            Variant V7 = Variant(2);
            Variant V8 = V7++;
            if (V7.asInt() != 3 || V8.asInt() != 2) return false;

            // Test pre-decrement
            Variant V9 = Variant(7);
            Variant V10 = --V9;
            if (V9.asInt() != 6 || V10.asInt() != 6) return false;

            // Test post-decrement
            Variant V11 = Variant(4);
            Variant V12 = V11--;
            if (V11.asInt() != 3 || V12.asInt() != 4) return false;

            return true;

        }

        bool test4(){

            ECE141::Variant theV0(100);
            ECE141::Variant theV1(theV0);
            if (!(theV0 == theV1)) return false;

            ECE141::Variant theV2(200);
            if (!(theV1 < theV2)) return false;


            ECE141::Variant theV3(200.0f);
            theV0 = theV3;

            if (!(theV0 == theV3)) return false;



            if (!(theV1 < theV3)) return false;

            ECE141::Variant theV4("200");
            theV0 = theV4;
            if (!(theV0 == theV4)) return false;

            if (!(theV1 < theV4)) return false;

            return true;
        }

        bool test5(){
            {
                // Test constructors
                ECE141::Variant theV1(100);
                ECE141::Variant theV2(6.28f);
                ECE141::Variant theV3("testing");


                std::stringstream theOut;
                theOut << theV1 << " " << std::fixed
                       << theV2 << " " << theV3 << "\n";


                std::stringstream theIn1(theOut.str()); //in1 now holds in order V1,V2,V3
                int theInt;
                std::string theString1, theString2;
                theIn1 >> theInt >> theString1 >> theString2;
                theString1.erase(theString1.find_last_not_of('0') + 1, std::string::npos);

                if (theInt != 100 || theString1 != "6.28" || theString2 != "testing") {
                    cout<<"\n \n";
                    cout<<"theInt is "<<theInt<<endl;
                    cout<<"theString1 is "<<theString1<<endl;
                    cout<<"theString2 is "<<theString2<<endl;

                    return false;
                }


                // Test assignment operators
                theOut.str(std::string());
                ECE141::Variant theVar(theV1); // Invoke the copy-constructor
                theVar = 200;
                theOut << theVar << " ";
                theVar = 3.14f;
                theOut << std::fixed << theVar << " ";
                theVar = "again";
                theOut << std::fixed << theVar << "\n";
                std::stringstream theIn2(theOut.str());
                theIn2 >> theInt >> theString1 >> theString2;
                theString1.erase(theString1.find_last_not_of('0') + 1, std::string::npos);
                if (theInt != 200 || theString1 != "3.14" || theString2 != "again")
                    return false;

                // Test asInt()
                theVar = 3.14f;
                if (theVar.asInt() != 3)
                    cout<<false;

                // Test asFloat() and asString()
                auto theFloatVal = theVar.asFloat();
                theOut.str(std::string());
                theOut << std::fixed << theFloatVal.value();
                theString1 = theOut.str();
                if (theVar.asString() != theString1)
                    return false;

                return true;
            }
        }
    };
}