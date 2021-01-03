#pragma once

#include "JValue.h"

#if _HAS_CXX17 
#define ENABLE_STD_OPTIONAL
#include <optional>
#endif

namespace Tests
{
    struct TestComplexSubObject
    {
        int x;
        double y;
    };

    class TestComplexObject
    {
    public:
        TestComplexObject(
            const std::wstring& strValue,
            bool boolValue,
            int numValue,
            TestComplexSubObject objectValue,
            const std::vector<int>& arrayValue
#if defined(ENABLE_STD_OPTIONAL)
            , std::optional<int> optInt,
            std::optional<std::wstring> optStr
#endif
        )
            : StrValue(strValue),
            BoolValue(boolValue),
            NumValue(numValue),
            ObjectValue(objectValue),
            ArrayValue(arrayValue)
#if defined(ENABLE_STD_OPTIONAL)
            , OptInt(optInt),
            OptStr(optStr)
#endif
        {}

        TestComplexObject() = default;
        TestComplexObject& operator=(const TestComplexObject& other) = default;

        std::wstring StrValue;
        bool BoolValue;
        int NumValue;
        TestComplexSubObject ObjectValue;
        std::vector<int> ArrayValue;
#if defined(ENABLE_STD_OPTIONAL)
        std::optional<int> OptInt;
        std::optional<std::wstring> OptStr;
#endif
    };
}