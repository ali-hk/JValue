#include "pch.h"
#include "TestClass.h"

using namespace ABI::TestWrlComponent;
using namespace Microsoft::WRL;

_Use_decl_annotations_
IFACEMETHODIMP TestClass::TestMethod()
{
    try
    {
        JValue test = JValue::Parse(LR"|({ "test": { "value1": true, "value2": "yes" } })|");
        bool result = test[L"test"][L"value1"];
        OutputDebugString(std::to_wstring(result).data());
        OutputDebugString(test.ToString().data());

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
                    { L"Key2", false },
                    { L"strValue", L"value" },
                    { L"arr", 
                        JArray {
                            1, 2, 3, 4
                        }
                    }
                }
            }
        };
        OutputDebugString(test2.ToString().data());

        int x = test2[L"root"][L"Key"][L"SubKey"];
        std::wstring str = test2[L"root"][L"strValue"];
        std::vector<int> arr = test2[L"root"][L"arr"];
        std::wstring nonExistent = test2[L"root"][L"fake"].value_or(L"NONEXISTENT");
    }
    catch (const std::runtime_error& err)
    {
        OutputDebugStringA(err.what());
        RETURN_HR(E_FAIL);
    }
    catch (...)
    {
        OutputDebugString(L"Unknown exception");
        RETURN_HR(E_FAIL);
    }

    RETURN_HR(S_OK);
}

TestClass::TestClass()
{
}

TestClass::~TestClass()
{
}
