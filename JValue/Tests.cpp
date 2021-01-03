#include "pch.h"

#include "Tests.h"

#include "CppUnitTest.h"

#if defined(__cplusplus_winrt) || defined(CPPWINRT_VERSION)
#define JSON_VALUE_TYPE(type) WDJ::JsonValueType::type
#else
#define JSON_VALUE_TYPE(type) WDJ::JsonValueType::JsonValueType_ ## type
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
    TEST_CLASS(JValueUnitTests)
    {
    public:

        //
        // Test: NewCStringJsonValue_Success
        //
        //      Calls NewCStringJsonValue with a c-string, and validates that an IJsonValue is returned
        //      with the expected string.
        //
        TEST_METHOD(NewCStringJsonValue_Success)
        {
            JValue jvalue = L"StrValue";

            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(String)));
            std::wstring strValue = jvalue;
            Assert::IsTrue(0 == wcscmp(L"StrValue", strValue.data()));
        }

        //
        // Test: NewCStringJsonValue_Fail_Args
        //
        //      Calls NewCStringJsonValue with a null c-string, and validates that an exception was thrown.
        //
        TEST_METHOD(NewCStringJsonValue_Fail_Args)
        {
            bool threwException = false;

            try
            {
                const wchar_t* nullStr = nullptr;
                JValue jvalue = nullStr;
            }
            catch (const std::invalid_argument&)
            {
                threwException = true;
            }
            Assert::IsTrue(threwException);
        }

        //
        // Test: NewStringJsonValue_Success
        //
        //      Calls NewStringJsonValue with a string, and validates that an IJsonValue is returned
        //      with the expected string.
        //
        TEST_METHOD(NewStringJsonValue_Success)
        {
            std::wstring strValueInput(L"StrValue");
            JValue jvalue = strValueInput;

            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(String)));
            std::wstring strValue = jvalue;
            Assert::IsTrue(0 == wcscmp(L"StrValue", strValue.data()));
        }

        //
        // Test: NewStringViewJsonValue_Success
        //
        //      Calls NewStringViewJsonValue with a string_view, and validates that an IJsonValue is returned
        //      with the expected string.
        //
        TEST_METHOD(NewStringViewJsonValue_Success)
        {
            std::wstring strValueInput(L"StrValue");
            std::wstring_view strValueView = strValueInput;
            JValue jvalue = strValueView;

            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(String)));
            std::wstring strValue = jvalue;
            Assert::IsTrue(0 == wcscmp(L"StrValue", strValue.data()));
        }

        //
        // Test: NewStringViewJsonValue_Fail
        //
        //      Calls NewStringViewJsonValue_Fail with a string_view and converts back to string_view,
        //      and validates that an exception was thrown.
        //
        TEST_METHOD(NewStringViewJsonValue_Fail)
        {
            std::wstring strValueInput(L"StrValue");
            std::wstring_view strValueView = strValueInput;
            JValue jvalue = strValueView;

            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(String)));

            bool threwException = false;

            try
            {
                std::wstring_view strValue = jvalue;
            }
            catch (const std::logic_error&)
            {
                threwException = true;
            }
            Assert::IsTrue(threwException);
        }

        //
        // Test: NewWinrtStringJsonValue_Success
        //
        //      Calls NewWinrtStringJsonValue with a WInRT string, and validates that an IJsonValue is returned
        //      with the expected string.
        //
        TEST_METHOD(NewWinRtStringJsonValue_Success)
        {
#if defined(__cplusplus_winrt)
            auto strValueInput = ref new Platform::String(L"StrValue");
#elif defined(CPPWINRT_VERSION)
            auto strValueInput = winrt::hstring(L"StrValue");
#endif
            JValue jvalue = strValueInput;

            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(String)));
#if defined(__cplusplus_winrt)
            Platform::String^ strValue = jvalue;
            Assert::IsTrue(0 == wcscmp(L"StrValue", strValue->Data()));
#elif defined(CPPWINRT_VERSION)
            winrt::hstring strValue = jvalue;
            Assert::IsTrue(0 == wcscmp(L"StrValue", strValue.data()));
#endif
        }

        //
        // Test: NewWinrtStringRefJsonValue_Success
        //
        //      Calls NewWinrtStringReJsonValue with a WInRT string reference, and validates that an IJsonValue is returned
        //      with the expected string.
        //
        TEST_METHOD(NewWinRtStringRefJsonValue_Success)
        {
#if defined(__cplusplus_winrt)
            auto strValueInput = L"StrValue";
            auto strValueRef = Platform::StringReference(strValueInput);
#elif defined(CPPWINRT_VERSION)
            auto strValueInput = winrt::hstring(L"StrValue");
            const winrt::hstring& strValueRef = strValueInput;
#endif
            JValue jvalue = strValueInput;

            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(String)));

#if defined(__cplusplus_winrt)
            Platform::String^ strValue = jvalue;
            Assert::IsTrue(0 == wcscmp(L"StrValue", strValue->Data()));
#elif defined(CPPWINRT_VERSION)
            winrt::hstring strValue = jvalue;
            Assert::IsTrue(0 == wcscmp(L"StrValue", strValue.data()));
#endif
        }

#if defined(__cplusplus_winrt)
        //
        // Test: NewWinrtStringRefJsonValue_Fail
        //
        //      Calls NewWinrtStringReJsonValue with a WInRT string reference, and converts back to a string reference,
        //      and validates that an exception was thrown.
        //
        TEST_METHOD(NewWinRtStringRefJsonValue_Fail)
        {
            auto strValueInput = L"StrValue";
            auto strValueRef = Platform::StringReference(strValueInput);
            JValue jvalue = strValueInput;

            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(String)));

            bool threwException = false;

            try
            {
                Platform::StringReference strValue = jvalue;
            }
            catch (const std::logic_error&)
            {
                threwException = true;
            }
            Assert::IsTrue(threwException);
        }
#endif

#if defined(ENABLE_STD_OPTIONAL)
        TEST_METHOD(AddOptionalWithValueToJsonObject_Success)
        {
            int intValueExpected = 5;
            auto intOpt = std::make_optional<int>(intValueExpected);
            JValue jvalue = intOpt;

            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(Number)));
            int intValueActual = jvalue;
            Assert::IsTrue(intValueActual == intValueExpected);
        }

        TEST_METHOD(AddOptionalWithEmptyValueToJsonObject_Success)
        {
            std::optional<int> value;
            value = std::nullopt;
            JValue jvalue = value;

            Assert::IsTrue(jvalue.IsNull());
        }
#endif

#if defined(__cplusplus_winrt)
        TEST_METHOD(AddBoxWithValueToJsonObject_Success)
        {
            int intValueExpected = 5;
            Platform::Box<int>^ intOpt = ref new Platform::Box<int>(intValueExpected);
            JValue jvalue = intOpt;

            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(Number)));
            int intValueActual = jvalue;
            Assert::IsTrue(intValueActual == intValueExpected);
        }

        TEST_METHOD(AddBoxWithoutValueToJsonObject_Success)
        {
            Platform::Box<int>^ value = nullptr;
            JValue jvalue = value;

            Assert::IsTrue(jvalue.IsNull());
        }

        TEST_METHOD(AddIBoxWithValueToJsonObject_Success)
        {
            int intValueExpected = 5;
            Platform::IBox<int>^ intOpt = ref new Platform::Box<int>(intValueExpected);
            JValue jvalue = intOpt;

            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(Number)));
            int intValueActual = jvalue;
            Assert::IsTrue(intValueActual == intValueExpected);
        }

        TEST_METHOD(AddIBoxWithoutValueToJsonObject_Success)
        {
            Platform::IBox<int>^ value = nullptr;
            JValue jvalue = value;

            Assert::IsTrue(jvalue.IsNull());
        }
#endif

        //
        // Test: NewBooleanJsonValue_Success
        //
        //      Calls NewBooleanJsonValue, and make sure the created IJsonValue has the right properties.
        //
        TEST_METHOD(NewBooleanJsonValue_Success)
        {
            JValue jvalue = true;

            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(Boolean)));
            bool value = jvalue;
            Assert::IsTrue(value == true);

            jvalue = false;
            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(Boolean)));
            value = jvalue;
            Assert::IsTrue(value == false);
        }

        //
        // Test: NewNumberJsonValue_Success
        //
        //      Calls NewNumberJsonValue, and make sure the created IJsonValue has the right properties.
        //
        TEST_METHOD(NewNumberJsonValue_Success)
        {
            int intValueExpected = 5;
            JValue jvalue = intValueExpected;

            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(Number)));
            int intValueActual = jvalue;
            Assert::IsTrue(intValueActual == intValueExpected);

            long longValueExpected = 5l;
            jvalue = longValueExpected;

            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(Number)));
            long longValueActual = jvalue;
            Assert::IsTrue(longValueActual == longValueExpected);

            double doubleValueExpected = 5.0;
            jvalue = doubleValueExpected;

            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(Number)));
            double doubleValueActual = jvalue;
            Assert::IsTrue(doubleValueActual == doubleValueExpected);
        }

        //
        // Test: NewNullJsonValue_Success
        //
        //      Calls NewNullJsonValue, and make sure the created IJsonValue has the right properties.
        //
        TEST_METHOD(NewNullJsonValue_Success)
        {
            JValue jvalue = nullptr;

            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(Null)));
            Assert::IsTrue(jvalue.IsNull());
        }

        //
        // Test: NewJsonObject_Success
        //
        TEST_METHOD(NewJsonObject_Success)
        {
            JValue jvalue =
            {
            };

            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(Object)));
            Assert::IsTrue(!jvalue.IsNull());
        }

        //
        // Test: NewJsonArray_Success
        //
        TEST_METHOD(NewJsonArray_Success)
        {
            JValue jvalue = JArray();

            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(Array)));
            Assert::IsTrue(!jvalue.IsNull());
        }

        //
        // Test: AddValueToJsonObject_Success
        //
        //      Adds a IJsonValue to a IJsonObject, and make sure we can read it back.
        //
        TEST_METHOD(AddValueToJsonObject_Success)
        {
            JValue jvalue =
            {
                { L"SubKey", 5 }
            };

            JValue target =
            {
            };

            target.Insert(L"ValueKey", jvalue);

            JValue valueKeyValue = target[L"ValueKey"];
            Assert::IsTrue(valueKeyValue.IsValueType(JSON_VALUE_TYPE(Object)));
            JValue subKeyValue = valueKeyValue[L"SubKey"];
            Assert::IsTrue(subKeyValue.IsValueType(JSON_VALUE_TYPE(Number)));
            int value = subKeyValue;
            Assert::IsTrue(5 == value);

            JValue subKeyValueDirect = target[L"ValueKey"][L"SubKey"];
            Assert::IsTrue(subKeyValueDirect.IsValueType(JSON_VALUE_TYPE(Number)));
            value = subKeyValueDirect;
            Assert::IsTrue(5 == value);
        }

        //
        // Test: AddValueToJsonObject_Fail_Args
        //
        //      Calls AddValueToJsonObject with invalid arguments.
        //
        TEST_METHOD(AddValueToJsonObject_Fail_Args)
        {
            bool threwException = false;
            JValue jvalue =
            {
                { L"SubKey", 5 }
            };

            JValue target =
            {
            };

            try
            {
                target.Insert(nullptr, jvalue);
            }
            catch (...)
            {
                threwException = true;
            }

            Assert::IsTrue(threwException);
        }

        //
        // Test: AddStringToJsonObject_Success
        //
        //      Adds a string to a IJsonObject, and make sure we can read it back.
        //
        TEST_METHOD(AddStringToJsonObject_Success)
        {
            JValue target =
            {
            };

            target.Insert(L"StrValue", L"value");
            JValue strValueValue = target[L"StrValue"];
            Assert::IsTrue(strValueValue.IsValueType(JSON_VALUE_TYPE(String)));
            std::wstring valueStrValue = strValueValue;
            Assert::IsTrue(L"value" == valueStrValue);
        }

        //
        // Test: AddStringToJsonObject_Fail_Args
        //
        //      Calls AddStringToJsonObject with invalid arguments.
        //
        TEST_METHOD(AddStringToJsonObject_Fail_Args)
        {
            bool threwException = false;

            JValue target =
            {
            };

            try
            {
                target.Insert(nullptr, L"value");
            }
            catch (...)
            {
                threwException = true;
            }
            Assert::IsTrue(threwException);

            threwException = false;
            try
            {
                const wchar_t* value = nullptr;
                target.Insert(L"StrValue", value);
            }
            catch (...)
            {
                threwException = true;
            }
            Assert::IsTrue(threwException);
        }

        //
        // Test: AddBooleanToJsonObject_Success
        //
        //      Adds a boolean to a IJsonObject, and make sure we can read it back.
        //
        TEST_METHOD(AddBooleanToJsonObject_Success)
        {
            JValue target =
            {
            };

            target.Insert(L"TrueValue", true);
            JValue trueValueValue = target[L"TrueValue"];
            Assert::IsTrue(trueValueValue.IsValueType(JSON_VALUE_TYPE(Boolean)));
            bool valueTrueValue = trueValueValue;
            Assert::IsTrue(true == valueTrueValue);

            target.Insert(L"FalseValue", false);
            JValue falseValueValue = target[L"FalseValue"];
            Assert::IsTrue(falseValueValue.IsValueType(JSON_VALUE_TYPE(Boolean)));
            bool valueFalseValue = falseValueValue;
            Assert::IsTrue(false == valueFalseValue);
        }

        //
        // Test: AddNumberToJsonObject_Success
        //
        //      Adds a number to a IJsonObject, and make sure we can read it back.
        //
        TEST_METHOD(AddNumberToJsonObject_Success)
        {
            JValue target =
            {
            };

            int intValueExpected = 5;
            target.Insert(L"IntValue", intValueExpected);
            JValue jvalue = target[L"IntValue"];
            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(Number)));
            int intValueActual = jvalue;
            Assert::IsTrue(intValueActual == intValueExpected);

            long longValueExpected = 5l;
            target.Insert(L"LongValue", longValueExpected);
            jvalue = target[L"LongValue"];
            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(Number)));
            long longValueActual = jvalue;
            Assert::IsTrue(longValueActual == longValueExpected);

            double doubleValueExpected = 5.0;
            target.Insert(L"DoubleValue", doubleValueExpected);
            jvalue = target[L"DoubleValue"];
            Assert::IsTrue(jvalue.IsValueType(JSON_VALUE_TYPE(Number)));
            double doubleValueActual = jvalue;
            Assert::IsTrue(doubleValueActual == doubleValueExpected);
        }

        //
        // Test: AddArrayToJsonObject_Success
        //
        //      Adds a IJsonArray to a IJsonObject, and make sure we can read it back.
        //
        TEST_METHOD(AddArrayToJsonObject_Success)
        {
            JValue target =
            {
            };

            JArray emptyArray;
            target.Insert(L"EmptyJArray", emptyArray);
            JValue emptyArrayValue = target[L"EmptyJArray"];
            Assert::IsTrue(emptyArrayValue.IsValueType(JSON_VALUE_TYPE(Array)));
            JArray valueEmptyArray = emptyArrayValue;
            Assert::IsTrue(valueEmptyArray.empty());

            JArray arrayWithItems{ 1, 2, 3, 4 };
            target.Insert(L"JArrayWithItems", arrayWithItems);
            JValue jArrayWithItemsValue = target[L"JArrayWithItems"];
            Assert::IsTrue(jArrayWithItemsValue.IsValueType(JSON_VALUE_TYPE(Array)));
            JArray valueJArrayWithItems = jArrayWithItemsValue;
            Assert::IsTrue(!valueJArrayWithItems.empty());
            int firstItem = valueJArrayWithItems[0];
            Assert::IsTrue(firstItem == 1);

            std::vector<std::wstring> emptyStrArray;
            target.Insert(L"EmptyStrArray", emptyStrArray);
            JValue emptyStrArrayValue = target[L"EmptyStrArray"];
            Assert::IsTrue(emptyStrArrayValue.IsValueType(JSON_VALUE_TYPE(Array)));
            std::vector<std::wstring> valueEmptyStrArray = emptyStrArrayValue;
            Assert::IsTrue(valueEmptyStrArray.empty());

            JArray arrayWithStrItems{ L"One", L"Two", L"Three" };
            target.Insert(L"ArrayWithStrItems", arrayWithStrItems);
            JValue arrayWithStrItemsValue = target[L"ArrayWithStrItems"];
            Assert::IsTrue(arrayWithStrItemsValue.IsValueType(JSON_VALUE_TYPE(Array)));
            std::vector<std::wstring> valueArrayWithStrItems = arrayWithStrItemsValue;
            Assert::IsTrue(!valueArrayWithStrItems.empty());
            Assert::IsTrue(0 == wcscmp(valueArrayWithStrItems[0].data(), L"One"));
        }

#if defined(ENABLE_STD_OPTIONAL)
        TEST_METHOD(AddOptionalToJsonObject_Success)
        {
        }
#endif

        //
        // Test: AppendValueToJsonArray_Success
        //
        //      Appends a value to an IJsonArray, and make sure we can read it back.
        //
        TEST_METHOD(AppendValueToJsonArray_Success)
        {
            JValue jvalue =
            {
                { L"SubKey", 5 }
            };

            JValue target = JArray();

            target.Append(jvalue);

            Assert::IsTrue(target.IsValueType(JSON_VALUE_TYPE(Array)));
            JArray array = target;
            Assert::IsTrue(array.size() == 1);
            JValue firstValue = array[0];
            Assert::IsTrue(firstValue.IsValueType(JSON_VALUE_TYPE(Object)));
            JValue subKeyValue = firstValue[L"SubKey"];
            Assert::IsTrue(subKeyValue.IsValueType(JSON_VALUE_TYPE(Number)));
            int value = subKeyValue;
            Assert::IsTrue(5 == value);

            JValue subKeyValueDirect = target[0][L"SubKey"];
            Assert::IsTrue(subKeyValueDirect.IsValueType(JSON_VALUE_TYPE(Number)));
            value = subKeyValueDirect;
            Assert::IsTrue(5 == value);
        }

        //
        // Test: AppendStringToJsonArray_Success
        //
        //      Appends a string to an IJsonArray, and make sure we can read it back.
        //
        TEST_METHOD(AppendStringToJsonArray_Success)
        {
            JValue target = JArray();

            target.Append(L"value");

            Assert::IsTrue(target.IsValueType(JSON_VALUE_TYPE(Array)));
            JArray array = target;
            Assert::IsTrue(array.size() == 1);
            JValue firstValue = array[0];
            Assert::IsTrue(firstValue.IsValueType(JSON_VALUE_TYPE(String)));
            std::wstring value = firstValue;
            Assert::IsTrue(0 == wcscmp(L"value", value.data()));
        }

        //
        // Test: AppendStringToJsonArray_Fail_Args
        //
        //      Calls AppendStringToJsonArray with invalid arguments.
        //
        TEST_METHOD(AppendStringToJsonArray_Fail_Args)
        {
            JValue target = JArray();
            bool threwException = false;

            try
            {
                const wchar_t* value = nullptr;
                target.Append(value);
            }
            catch (...)
            {
                threwException = true;
            }
            Assert::IsTrue(threwException);
        }

        //
        // Test: AppendBooleanToJsonArray_Success
        //
        //      Appends a boolean to an IJsonArray, and make sure we can read it back.
        //
        TEST_METHOD(AppendBooleanToJsonArray_Success)
        {
            JValue target = JArray();

            target.Append(true);
            Assert::IsTrue(target.IsValueType(JSON_VALUE_TYPE(Array)));
            JArray array = target;
            Assert::IsTrue(array.size() == 1);
            JValue firstValue = array[0];
            Assert::IsTrue(firstValue.IsValueType(JSON_VALUE_TYPE(Boolean)));
            bool value = firstValue;
            Assert::IsTrue(value == true);

            target.Append(false);
            JArray arrayWithTwo = target;
            Assert::IsTrue(arrayWithTwo.size() == 2);
            JValue secondValue = arrayWithTwo[1];
            Assert::IsTrue(secondValue.IsValueType(JSON_VALUE_TYPE(Boolean)));
            value = secondValue;
            Assert::IsTrue(value == false);
        }

        //
        // Test: AppendNumberToJsonArray_Success
        //
        //      Appends a number to an IJsonArray, and make sure we can read it back.
        //
        TEST_METHOD(AppendNumberToJsonArray_Success)
        {
            JValue target = JArray();

            int intValueExpected = 5;
            target.Append(intValueExpected);
            Assert::IsTrue(target.IsValueType(JSON_VALUE_TYPE(Array)));
            JArray array = target;
            Assert::IsTrue(array.size() == 1);
            JValue firstValue = array[0];
            Assert::IsTrue(firstValue.IsValueType(JSON_VALUE_TYPE(Number)));
            int intValueActual = firstValue;
            Assert::IsTrue(intValueActual == intValueExpected);

            long longValueExpected = 5l;
            target.Append(longValueExpected);
            JArray arrayWithTwo = target;
            Assert::IsTrue(arrayWithTwo.size() == 2);
            JValue secondValue = arrayWithTwo[1];
            Assert::IsTrue(secondValue.IsValueType(JSON_VALUE_TYPE(Number)));
            long longValueActual = secondValue;
            Assert::IsTrue(longValueActual == longValueExpected);

            double doubleValueExpected = 5.0;
            target.Append(doubleValueExpected);
            JArray arrayWithThree = target;
            Assert::IsTrue(arrayWithThree.size() == 3);
            JValue thirdValue = arrayWithThree[2];
            Assert::IsTrue(thirdValue.IsValueType(JSON_VALUE_TYPE(Number)));
            double doubleValueActual = thirdValue;
            Assert::IsTrue(doubleValueActual == doubleValueExpected);
        }

        //
        // Test: AppendArrayToJsonArray_Success
        //
        //      Appends an array to an IJsonArray, and make sure we can read it back.
        //
        TEST_METHOD(AppendArrayToJsonArray_Success)
        {
            JValue target = JArray();

            JArray emptyArray;
            target.Append(emptyArray);
            JValue emptyArrayValue = target[0];
            Assert::IsTrue(emptyArrayValue.IsValueType(JSON_VALUE_TYPE(Array)));
            JArray valueEmptyArray = emptyArrayValue;
            Assert::IsTrue(valueEmptyArray.empty());

            JArray arrayWithItems{ 1, 2, 3, 4 };
            target.Append(arrayWithItems);
            JValue jArrayWithItemsValue = target[1];
            Assert::IsTrue(jArrayWithItemsValue.IsValueType(JSON_VALUE_TYPE(Array)));
            JArray valueJArrayWithItems = jArrayWithItemsValue;
            Assert::IsTrue(!valueJArrayWithItems.empty());
            int firstItem = valueJArrayWithItems[0];
            Assert::IsTrue(firstItem == 1);

            std::vector<std::wstring> emptyStrArray;
            target.Append(emptyStrArray);
            JValue emptyStrArrayValue = target[2];
            Assert::IsTrue(emptyStrArrayValue.IsValueType(JSON_VALUE_TYPE(Array)));
            std::vector<std::wstring> valueEmptyStrArray = emptyStrArrayValue;
            Assert::IsTrue(valueEmptyStrArray.empty());

            JArray arrayWithStrItems{ L"One", L"Two", L"Three" };
            target.Append(arrayWithStrItems);
            JValue arrayWithStrItemsValue = target[3];
            Assert::IsTrue(arrayWithStrItemsValue.IsValueType(JSON_VALUE_TYPE(Array)));
            std::vector<std::wstring> valueArrayWithStrItems = arrayWithStrItemsValue;
            Assert::IsTrue(!valueArrayWithStrItems.empty());
            Assert::IsTrue(0 == wcscmp(valueArrayWithStrItems[0].data(), L"One"));
        }

#if defined(ENABLE_STD_OPTIONAL)
        TEST_METHOD(AppendOptionalToJsonArray_Success)
        {
        }
#endif

        //
        // Test: StringToJsonValue_Success
        //
        //      Parses a JSON document into an IJsonValue.  Verifies that the value is what
        //      we expect.
        //
        TEST_METHOD(StringToJsonValue_Success)
        {
            JValue value = JValue::Parse(LR"|({ "test": { "BoolValue": true, "StrValue": "yes", "NumValue": 1, "NullValue": null } })|");
            Assert::IsTrue(!value.IsNull());
            Assert::IsTrue(value.IsValueType(JSON_VALUE_TYPE(Object)));

            JValue boolJValue = value[L"test"][L"BoolValue"];
            Assert::IsTrue(boolJValue.IsValueType(JSON_VALUE_TYPE(Boolean)));
            bool boolValue = boolJValue;
            Assert::IsTrue(boolValue == true);

            JValue strJValue = value[L"test"][L"StrValue"];
            Assert::IsTrue(strJValue.IsValueType(JSON_VALUE_TYPE(String)));
            std::wstring strValue = strJValue;
            Assert::IsTrue(0 == wcscmp(L"yes", strValue.data()));

            JValue numJValue = value[L"test"][L"NumValue"];
            Assert::IsTrue(numJValue.IsValueType(JSON_VALUE_TYPE(Number)));
            int numValue = numJValue;
            Assert::IsTrue(numValue == 1);

            JValue nullJValue = value[L"test"][L"NullValue"];
            Assert::IsTrue(nullJValue.IsValueType(JSON_VALUE_TYPE(Null)));
            Assert::IsTrue(nullJValue.IsNull());
        }

        //
        // Test: StringToJsonValue_Fail_Args
        //
        //      Calls StringToJsonValue with invalid arguments.
        //
        TEST_METHOD(StringToJsonValue_Fail_Args)
        {
            bool threwException = false;

            try
            {
                std::wstring document;
                JValue value = JValue::Parse(document);
            }
            catch (...)
            {
                threwException = true;
            }
            Assert::IsTrue(threwException);
        }

        //
        // Test: StringToJsonValue_Fail_Bad_Json
        //
        //      Calls StringToJsonValue with malformed JSON.
        //
        TEST_METHOD(StringToJsonValue_Fail_Bad_Json)
        {
            bool threwException = false;

            try
            {
                JValue value = JValue::Parse(L"{ bad json; {");
            }
            catch (...)
            {
                threwException = true;
            }
            Assert::IsTrue(threwException);
        }

        //
        // Test: TryGetNamedValue_Success_Found
        //
        //      Calls TryGetNamedValue on a known value, and validate that it is returned properly.
        //
        TEST_METHOD(TryGetNamedValue_Success_Found)
        {
            JValue target =
            {
                { L"ValueKey", 5 }
            };

            int value = target[L"ValueKey"].value_or(0);
            Assert::IsTrue(5 == value);
        }

        //
        // Test: TryGetNamedValue_Success_NotFound
        //
        //      Calls TryGetNamedValue on a value that doesn't exist.  Verify that it returns false.
        //
        TEST_METHOD(TryGetNamedValue_Success_NotFound)
        {
            JValue target =
            {
                { L"ValueKey", 5 },
                { L"NullValueKey", nullptr}
            };

            JValue invalidKeyValue = target[L"InvalidKey"];
            Assert::IsTrue(invalidKeyValue.IsValueType(JSON_VALUE_TYPE(Null)));
            int value = invalidKeyValue.value_or(0);
            Assert::IsTrue(0 == value);

            JValue valueKeyValue = target[L"ValueKey"];
            Assert::IsTrue(valueKeyValue.IsValueType(JSON_VALUE_TYPE(Number)));
            std::wstring strValue = valueKeyValue.value_or(L"FallbackValue");
            Assert::IsTrue(0 == wcscmp(L"FallbackValue", strValue.data()));

            JValue nullValueKeyValue = target[L"NullValueKey"];
            Assert::IsTrue(nullValueKeyValue.IsValueType(JSON_VALUE_TYPE(Null)));
            strValue = nullValueKeyValue.value_or(L"FallbackValue");
            Assert::IsTrue(0 == wcscmp(L"FallbackValue", strValue.data()));
        }

        //
        // Test: TryGetNamedValue_Fail_Args
        //
        //      Calls TryGetNamedValue with invalid arguments.
        //
        TEST_METHOD(TryGetNamedValue_Fail_Args)
        {
            JValue target =
            {
                { L"ValueKey", 5 }
            };

            bool threwException = false;

            try
            {
                const wchar_t* nullKey = nullptr;
                JValue nullKeyValue = target[nullKey];
            }
            catch (...)
            {
                threwException = true;
            }
            Assert::IsTrue(threwException);
        }

        //
        // Test: TryGetNamedString_Success_Found
        //
        //      Calls TryGetNamedString on a known value, and validate that it is returned properly.
        //
        TEST_METHOD(TryGetNamedString_Success_Found)
        {
            JValue target =
            {
                { L"ValueKey", L"StrValue" }
            };

            std::wstring value = target[L"ValueKey"].value_or(L"FallbackValue");
            Assert::IsTrue(0 == wcscmp(L"StrValue", value.data()));
        }

        //
        // Test: TryGetNamedString_Success_NotFound
        //
        //      Calls TryGetNamedString on a non-existant value.  Verify that it returns false.
        //
        TEST_METHOD(TryGetNamedString_Success_NotFound)
        {
            JValue target =
            {
                { L"ValueKey", 1 }
            };

            std::wstring value = target[L"InvalidKey"].value_or(L"FallbackValue");
            Assert::IsTrue(0 == wcscmp(L"FallbackValue", value.data()));

            value = target[L"ValueKey"].value_or(L"FallbackValue");
            Assert::IsTrue(0 == wcscmp(L"FallbackValue", value.data()));
        }

        //
        // Test: TryGetNamedBoolean_Success_Found
        //
        //      Calls TryGetNamedBoolean on a known value, and validate that it is returned properly.
        //
        TEST_METHOD(TryGetNamedBoolean_Success_Found)
        {
            JValue target =
            {
                { L"ValueKey", true }
            };

            bool value = target[L"ValueKey"].value_or(false);
            Assert::IsTrue(value == true);
        }

        //
        // Test: TryGetNamedBoolean_Success_NotFound
        //
        //      Calls TryGetNamedBoolean on a non-existant value.  Verify that it returns false.
        //
        TEST_METHOD(TryGetNamedBoolean_Success_NotFound)
        {
            JValue target =
            {
                { L"ValueKey", 1 }
            };

            bool value = target[L"InvalidKey"].value_or(false);
            Assert::IsTrue(value == false);

            value = target[L"ValueKey"].value_or(false);
            Assert::IsTrue(value == false);
        }

        //
        // Test: TryGetNamedNumber_Success_Found
        //
        //      Calls TryGetNamedNumber on a known value, and validate that it is returned properly.
        //
        TEST_METHOD(TryGetNamedNumber_Success_Found)
        {
            JValue target =
            {
                { L"ValueKey", 1 }
            };

            int intValue = target[L"ValueKey"].value_or(0);
            Assert::IsTrue(intValue == 1);

            target =
            {
                { L"ValueKey", 2l }
            };

            long longValue = target[L"ValueKey"].value_or(0);
            Assert::IsTrue(longValue == 2l);

            target =
            {
                { L"ValueKey", 3.0 }
            };

            double doubleValue = target[L"ValueKey"].value_or(0);
            Assert::IsTrue(doubleValue == 3.0);
        }

        //
        // Test: TryGetNamedNumber_Success_NotFound
        //
        //      Calls TryGetNamedNumber on a non-existant value.  Verify that it returns false.
        //
        TEST_METHOD(TryGetNamedNumber_Success_NotFound)
        {
            JValue target =
            {
                { L"ValueKey", false }
            };

            int intValue = target[L"InvalidKey"].value_or(0);
            Assert::IsTrue(intValue == 0);

            intValue = target[L"ValueKey"].value_or(0);
            Assert::IsTrue(intValue == 0);

            long longValue = target[L"InvalidKey"].value_or(0);
            Assert::IsTrue(longValue == 0);

            longValue = target[L"ValueKey"].value_or(0);
            Assert::IsTrue(longValue == 0);

            double doubleValue = target[L"InvalidKey"].value_or(0);
            Assert::IsTrue(doubleValue == 0);

            doubleValue = target[L"ValueKey"].value_or(0);
            Assert::IsTrue(doubleValue == 0);
        }

        //
        // Test: TryGetNamedObject_Success_Found
        //
        //      Calls TryGetNamedObject on a known value, and validate that it is returned properly.
        //
        TEST_METHOD(TryGetNamedObject_Success_Found)
        {
            JValue target =
            {
                { L"ValueKey",
                    {
                        { L"SubKey", 5 }
                    }
                }
            };

            JValue value = target[L"ValueKey"].value_or(JValue(nullptr));
            Assert::IsTrue(value.IsValueType(JSON_VALUE_TYPE(Object)));
            int subKeyValue = value[L"SubKey"];
            Assert::IsTrue(subKeyValue == 5);
        }

        //
        // Test: TryGetNamedObject_Success_NotFound
        //
        //      Calls TryGetNamedObject on a non-existant value.  Verify that it returns false.
        //
        TEST_METHOD(TryGetNamedObject_Success_NotFound)
        {
            JValue target =
            {
                { L"ValueKey",
                    {
                        { L"SubKey", 5 }
                    }
                }
            };

            JValue value = target[L"InvalidKey"].value_or(JValue(nullptr));
            Assert::IsTrue(value.IsNull());

            target =
            {
                { L"NullValueKey", nullptr }
            };
            JValue nullValue = target[L"NullValueKey"].value_or(JValue(5));
            Assert::IsTrue(nullValue.IsValueType(JSON_VALUE_TYPE(Number)));
        }

        //
        // Test: TryGetNamedArray_Success_Found
        //
        //      Calls TryGetNamedArray on a known value, and validate that it is returned properly.
        //
        TEST_METHOD(TryGetNamedArray_Success_Found)
        {
            JValue target =
            {
                { L"ValueKey",
                    JArray {
                        L"One",
                        L"Two",
                        L"Three"
                    }
                }
            };

            JArray array = target[L"ValueKey"].values_or();
            Assert::IsTrue(array.size() == 3);

            std::vector<std::wstring> strArray = target[L"ValueKey"].values_or<std::wstring>();
            Assert::IsTrue(strArray.size() == 3);
        }

        //
        // Test: TryGetNamedArray_Success_NotFound
        //
        //      Calls TryGetNamedArray on a non-existant value.  Verify that it returns false.
        //
        TEST_METHOD(TryGetNamedArray_Success_NotFound)
        {
            JValue target =
            {
                { L"ValueKey",
                    JArray {
                        L"One",
                        L"Two",
                        L"Three"
                    }
                }
            };

            JArray array = target[L"InvalidKey"].values_or();
            Assert::IsTrue(array.size() == 0);

            std::vector<std::wstring> strArray = target[L"InvalidKey"].values_or<std::wstring>();
            Assert::IsTrue(strArray.size() == 0);

            std::vector<int> nonIntArray = target[L"ValueKey"].values_or<int>();
            Assert::IsTrue(nonIntArray.size() == 0);

            std::vector<int> nonIntArrayWithFallback = target[L"ValueKey"].values_or<int>(0);
            Assert::IsTrue(nonIntArrayWithFallback.size() == 3);
            Assert::IsTrue(nonIntArrayWithFallback[0] == 0);
            Assert::IsTrue(nonIntArrayWithFallback[1] == 0);
            Assert::IsTrue(nonIntArrayWithFallback[2] == 0);

            target =
            {
                { L"ValueKey", 5 }
            };

            JArray nonArray = target[L"ValueKey"].values_or();
            Assert::IsTrue(nonArray.size() == 0);

            std::vector<std::wstring> nonStrArray = target[L"ValueKey"].values_or<std::wstring>();
            Assert::IsTrue(nonStrArray.size() == 0);

            target =
            {
                { L"ValueKey",
                    JArray {
                        L"One",
                        2,
                        false
                    }
                }
            };

            JArray mixedArray = target[L"ValueKey"].values_or();
            Assert::IsTrue(mixedArray.size() == 3);

            std::vector<std::wstring> mixedStrArray = target[L"ValueKey"].values_or<std::wstring>();
            Assert::IsTrue(mixedStrArray.size() == 1);

            std::vector<std::wstring> mixedStrArrayWithFallback = target[L"ValueKey"].values_or<std::wstring>(L"");
            Assert::IsTrue(mixedStrArrayWithFallback.size() == 3);
            Assert::IsTrue(0 == wcscmp(mixedStrArrayWithFallback[0].data(), L"One"));
            Assert::IsTrue(mixedStrArrayWithFallback[1].empty());
            Assert::IsTrue(mixedStrArrayWithFallback[2].empty());
        }

        //
        // Test: PopulateStringVectorFromJsonArray_Success
        //
        //      Creates an IJsonArray of strings, and validates that a std::vector< std::wstring >
        //      is properly populated from those values.
        //
        TEST_METHOD(PopulateStringVectorFromJsonArray_Success)
        {
            JValue target =
            {
                { L"ValueKey",
                    JArray {
                        L"One",
                        L"Two",
                        L"Three"
                    }
                }
            };

            JArray array = target[L"ValueKey"];
            Assert::IsTrue(array.size() == 3);

            std::vector<std::wstring> strArray = target[L"ValueKey"];
            Assert::IsTrue(strArray.size() == 3);

            target =
            {
                { L"ValueKey",
                    JArray {
                        L"One",
                        2,
                        false
                    }
                }
            };

            JArray mixedArray = target[L"ValueKey"];
            Assert::IsTrue(mixedArray.size() == 3);
        }

        //
        // Test: PopulateStringVectorFromJsonArray_Fail_Args
        //
        //      Calls PopulateStringVectorFromJsonArray with invalid arguments.
        //
        TEST_METHOD(PopulateStringVectorFromJsonArray_Fail_Args)
        {
            bool threwException = false;

            JValue target =
            {
                { L"ValueKey",
                    JArray {
                        L"One",
                        L"Two",
                        L"Three"
                    }
                }
            };

            try
            {
                JArray array = target[L"InvalidKey"];
            }
            catch (...)
            {
                threwException = true;
            }
            Assert::IsTrue(threwException);

            threwException = false;
            try
            {
                std::vector<std::wstring> strArray = target[L"InvalidKey"];
            }
            catch (...)
            {
                threwException = true;
            }
            Assert::IsTrue(threwException);

            target =
            {
                { L"ValueKey", 5 }
            };

            threwException = false;
            try
            {
                JArray nonArray = target[L"ValueKey"];
            }
            catch (...)
            {
                threwException = true;
            }
            Assert::IsTrue(threwException);

            threwException = false;
            try
            {
                std::vector<std::wstring> nonStrArray = target[L"ValueKey"];
            }
            catch (...)
            {
                threwException = true;
            }
            Assert::IsTrue(threwException);
        }

        //
        // Test: PopulateStringVectorFromJsonArray_Fail_WrongElementType
        //
        //      Calls PopulateStringVectorFromJsonArray with an array that contains non-strings.
        //      Validates that a DocumentException is thrown.
        //
        TEST_METHOD(PopulateStringVectorFromJsonArray_Fail_WrongElementType)
        {
            JValue target =
            {
                { L"ValueKey",
                    JArray {
                        L"One",
                        L"Two",
                        L"Three"
                    }
                }
            };

            bool threwException = false;
            try
            {
                std::vector<int> nonIntArray = target[L"ValueKey"];
            }
            catch (...)
            {
                threwException = true;
            }
            Assert::IsTrue(threwException);

            target =
            {
                { L"ValueKey",
                    JArray {
                        L"One",
                        2,
                        false
                    }
                }
            };

            threwException = false;
            try
            {
                std::vector<std::wstring> mixedStrArray = target[L"ValueKey"];
            }
            catch (...)
            {
                threwException = true;
            }
            Assert::IsTrue(threwException);
        }

        //
        // Test: JsonValueToString_Success
        //
        //      Creates a JSON value from a string and they calls JsonValueToString.  Compares that they
        //      are the same.
        //
        TEST_METHOD(JsonValueToString_Success)
        {
            std::wstring rawJsonString = LR"|({"test":{"BoolValue":true,"StrValue":"yes","NumValue":1,"NullValue":null}})|";
            JValue value = JValue::Parse(rawJsonString);
            std::wstring toStringActual = value.ToString();
            Assert::IsTrue(0 == wcscmp(rawJsonString.data(), toStringActual.data()));
        }

        TEST_METHOD(SerializeComplexObject_Success)
        {
            std::wstring stringValueActual = L"String";
            bool boolValueActual = true;
            int numValueActual = 6;
            TestComplexSubObject subObjectActual = { 5, 10.0 };
            std::vector<int> arrayValueActual = { 1, 2, 3, 4 };
#if defined(ENABLE_STD_OPTIONAL)
            std::optional<int> optIntSetActual = 12;
            std::optional<std::wstring> optStrSetActual = L"OptString";
            std::optional<int> optIntUnsetActual = std::nullopt;
            std::optional<std::wstring> optStrUnsetActual = std::nullopt;
#endif
            TestComplexObject actualComplexObj(
                stringValueActual,
                boolValueActual,
                numValueActual,
                subObjectActual,
                arrayValueActual
#if defined(ENABLE_STD_OPTIONAL)
                , optIntSetActual,
                optStrSetActual
#endif
            );

            JValue jvalue = {
                { L"ComplexObject", actualComplexObj }
            };

#if defined(ENABLE_STD_OPTIONAL)
            std::wstring serializedExpected = LR"|({"ComplexObject":{"StrValue":"String","BoolValue":true,"NumValue":6,"ObjectValue":{"x":5,"y":10},"ArrayValue":[1,2,3,4],"OptInt":12,"OptStr":"OptString"}})|";
#else
            std::wstring serializedExpected = LR"|({"ComplexObject":{"StrValue":"String","BoolValue":true,"NumValue":6,"ObjectValue":{"x":5,"y":10},"ArrayValue":[1,2,3,4]}})|";
#endif
            std::wstring serializedActual = jvalue.ToString();

            Assert::IsTrue(0 == wcscmp(serializedActual.data(), serializedExpected.data()));

            auto actualComplexObjPtr = std::make_shared<TestComplexObject>(
                stringValueActual,
                boolValueActual,
                numValueActual,
                subObjectActual,
                arrayValueActual
#if defined(ENABLE_STD_OPTIONAL)
                , optIntSetActual,
                optStrSetActual
#endif
                );

            jvalue = {
                { L"ComplexObject", actualComplexObjPtr }
            };

#if defined(ENABLE_STD_OPTIONAL)
            serializedExpected = LR"|({"ComplexObject":{"StrValue":"String","BoolValue":true,"NumValue":6,"ObjectValue":{"x":5,"y":10},"ArrayValue":[1,2,3,4],"OptInt":12,"OptStr":"OptString"}})|";
#else
            serializedExpected = LR"|({"ComplexObject":{"StrValue":"String","BoolValue":true,"NumValue":6,"ObjectValue":{"x":5,"y":10},"ArrayValue":[1,2,3,4]}})|";
#endif
            serializedActual = jvalue.ToString();

            Assert::IsTrue(0 == wcscmp(serializedActual.data(), serializedExpected.data()));
#if defined(ENABLE_STD_OPTIONAL)
            TestComplexObject actualComplexObjWithUnsetOptionals(
                stringValueActual,
                boolValueActual,
                numValueActual,
                subObjectActual,
                arrayValueActual,
                optIntUnsetActual,
                optStrUnsetActual
            );

            jvalue = {
                { L"ComplexObject", actualComplexObjWithUnsetOptionals }
            };

            serializedExpected = LR"|({"ComplexObject":{"StrValue":"String","BoolValue":true,"NumValue":6,"ObjectValue":{"x":5,"y":10},"ArrayValue":[1,2,3,4]}})|";
            serializedActual = jvalue.ToString();
            Assert::IsTrue(0 == wcscmp(serializedActual.data(), serializedExpected.data()));
#endif
        }

        TEST_METHOD(DeserializeComplexObject_Success)
        {
#if defined(ENABLE_STD_OPTIONAL)
            std::wstring rawJsonString = LR"|({"ComplexObject":{"StrValue":"String","BoolValue":true,"NumValue":6,"ObjectValue":{"x":5,"y":10},"ArrayValue":[1,2,3,4],"OptInt":12,"OptStr":"OptString"}})|";
#else
            std::wstring rawJsonString = LR"|({"ComplexObject":{"StrValue":"String","BoolValue":true,"NumValue":6,"ObjectValue":{"x":5,"y":10},"ArrayValue":[1,2,3,4]}})|";
#endif

            JValue parsedJvalue = JValue::Parse(rawJsonString);
            TestComplexObject actualComplexObj = parsedJvalue[L"ComplexObject"];
            Assert::IsTrue(actualComplexObj.StrValue == L"String");
            Assert::IsTrue(actualComplexObj.BoolValue == true);
            Assert::IsTrue(actualComplexObj.NumValue == 6);
            Assert::IsTrue(actualComplexObj.ObjectValue.x == 5 && actualComplexObj.ObjectValue.y == 10);
            Assert::IsTrue(actualComplexObj.ArrayValue.size() == 4);
#if defined(ENABLE_STD_OPTIONAL)
            Assert::IsTrue(actualComplexObj.OptInt.has_value() && actualComplexObj.OptInt.value() == 12);
            Assert::IsTrue(actualComplexObj.OptStr.has_value() && 0 == wcscmp(actualComplexObj.OptStr.value().data(), L"OptString"));
#endif

            std::shared_ptr<TestComplexObject> actualComplexObjPtr = parsedJvalue[L"ComplexObject"];
            Assert::IsTrue(actualComplexObjPtr->StrValue == L"String");
            Assert::IsTrue(actualComplexObjPtr->BoolValue == true);
            Assert::IsTrue(actualComplexObjPtr->NumValue == 6);
            Assert::IsTrue(actualComplexObjPtr->ObjectValue.x == 5 && actualComplexObjPtr->ObjectValue.y == 10);
            Assert::IsTrue(actualComplexObjPtr->ArrayValue.size() == 4);
#if defined(ENABLE_STD_OPTIONAL)
            Assert::IsTrue(actualComplexObjPtr->OptInt.has_value() && actualComplexObjPtr->OptInt.value() == 12);
            Assert::IsTrue(actualComplexObjPtr->OptStr.has_value() && 0 == wcscmp(actualComplexObjPtr->OptStr.value().data(), L"OptString"));
#endif

#if defined(ENABLE_STD_OPTIONAL)
            std::wstring rawJsonStringUnsetOptional = LR"|({"ComplexObject":{"StrValue":"String","BoolValue":true,"NumValue":6,"ObjectValue":{"x":5,"y":10},"ArrayValue":[1,2,3,4]}})|";
            parsedJvalue = JValue::Parse(rawJsonStringUnsetOptional);
            TestComplexObject actualComplexObjUnsetOptional = parsedJvalue[L"ComplexObject"];
            Assert::IsTrue(actualComplexObjUnsetOptional.StrValue == L"String");
            Assert::IsTrue(actualComplexObjUnsetOptional.BoolValue == true);
            Assert::IsTrue(actualComplexObjUnsetOptional.NumValue == 6);
            Assert::IsTrue(actualComplexObjUnsetOptional.ObjectValue.x == 5 && actualComplexObjUnsetOptional.ObjectValue.y == 10);
            Assert::IsTrue(actualComplexObjUnsetOptional.ArrayValue.size() == 4);
            Assert::IsTrue(!actualComplexObjUnsetOptional.OptInt.has_value());
            Assert::IsTrue(!actualComplexObjUnsetOptional.OptStr.has_value());

            std::wstring rawJsonStringMismatchedValueType = LR"|({"ComplexObject":{"StrValue":"String","BoolValue":true,"NumValue":6,"ObjectValue":{"x":"5","y":"10"},"ArrayValue":[1,2,3,4]}})|";
            parsedJvalue = JValue::Parse(rawJsonStringMismatchedValueType);
            std::optional<TestComplexObject> actualComplexObjMismatchedValueType = parsedJvalue[L"ComplexObject"].value_or_opt<TestComplexObject>();
            Assert::IsTrue(actualComplexObjMismatchedValueType.has_value() == false);
#else
            std::wstring rawJsonStringMismatchedValueType = LR"|({"ComplexObject":{"StrValue":"String","BoolValue":true,"NumValue":6,"ObjectValue":{"x":"5","y":"10"},"ArrayValue":[1,2,3,4]}})|";
            parsedJvalue = JValue::Parse(rawJsonStringMismatchedValueType);
            TestComplexObject actualComplexObjMismatchedValueType = parsedJvalue[L"ComplexObject"].value_or(TestComplexObject());
            Assert::IsTrue(actualComplexObjMismatchedValueType.StrValue.empty());
            Assert::IsTrue(actualComplexObjMismatchedValueType.BoolValue == false);
            Assert::IsTrue(actualComplexObjMismatchedValueType.NumValue == 0);
            Assert::IsTrue(actualComplexObjMismatchedValueType.ObjectValue.x == 0 && actualComplexObjMismatchedValueType.ObjectValue.y == 0);
            Assert::IsTrue(actualComplexObjMismatchedValueType.ArrayValue.empty());
#endif
        }

    };
}

template<>
struct SerializationTrait<Tests::TestComplexObject>
{
    void serialize(JValue& target, const Tests::TestComplexObject& value)
    {
        target = {
            { L"StrValue", value.StrValue },
            { L"BoolValue", value.BoolValue },
            { L"NumValue", value.NumValue },
            { L"ObjectValue", value.ObjectValue },
            { L"ArrayValue", value.ArrayValue }
    #if defined(ENABLE_STD_OPTIONAL)
            , { L"OptInt", value.OptInt },
            { L"OptStr", value.OptStr }
    #endif
        };
    }

    void deserialize(const JValue& json, Tests::TestComplexObject& target)
    {
        target = Tests::TestComplexObject(
            json[L"StrValue"],
            json[L"BoolValue"],
            json[L"NumValue"],
            json[L"ObjectValue"],
            json[L"ArrayValue"]
#if defined(ENABLE_STD_OPTIONAL)
            , json[L"OptInt"].value_or_opt<int>(),
            json[L"OptStr"].value_or_opt<std::wstring>()
#endif
        );
    }
};

template<>
struct SerializationTrait<std::shared_ptr<Tests::TestComplexObject>>
{
    void serialize(JValue& target, const std::shared_ptr<Tests::TestComplexObject>& value)
    {
        target = *value;
    }

    void deserialize(const JValue& json, std::shared_ptr<Tests::TestComplexObject>& target)
    {
        target = std::make_shared<Tests::TestComplexObject>(
            json[L"StrValue"],
            json[L"BoolValue"],
            json[L"NumValue"],
            json[L"ObjectValue"],
            json[L"ArrayValue"]
#if defined(ENABLE_STD_OPTIONAL)
            , json[L"OptInt"].value_or_opt<int>(),
            json[L"OptStr"].value_or_opt<std::wstring>()
#endif
        );
    }
};

template<>
struct SerializationTrait<Tests::TestComplexSubObject>
{
    void serialize(JValue& target, const Tests::TestComplexSubObject& value)
    {
        target = {
            { L"x", value.x },
            { L"y", value.y }
        };
    }

    void deserialize(const JValue& json, Tests::TestComplexSubObject& target)
    {
        target = Tests::TestComplexSubObject{ json[L"x"], json[L"y"] };
    }
};
