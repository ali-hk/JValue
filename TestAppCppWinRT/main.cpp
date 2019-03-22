// main.cpp : Defines the entry point for the console application.
//

#include "pch.h"

using namespace winrt;
using namespace Windows::Foundation;

int main()
{
    init_apartment();

    JValue test = JValue::Parse(LR"|({ "test": { "value1": true, "value2": "yes" } })|");
    bool result = test[L"test"][L"value1"];
    auto testStr = test.ToString();

    bool testOpt = test[L"test"][L"value1"].value_or(false);
    JValue test2 =
    {
        { L"root",
            {
                { L"Key",
                  {
                    { L"SubKey", 1 }
                  }
                },
                { L"Key2", false }
            }
        }
    };
    auto test2Str = test2.ToString();

    int x = test2[L"root"][L"Key"][L"SubKey"];
    std::wstring nonExistent = test2[L"root"][L"fake"].value_or(L"NONEXISTENT");
}
