#pragma once

#include <algorithm>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#if _HAS_CXX17 
#define ENABLE_STD_OPTIONAL
#include <optional>
#endif

#if defined(_WRL_MODULE_H_) || defined(_WRL_IMPLEMENTS_H_) || defined(_WRL_CLIENT_H_)
#define USE_WRL
#endif

#if defined(__cplusplus_winrt) || defined(CPPWINRT_VERSION) || defined(USE_WRL)

#ifdef __cplusplus_winrt
namespace WDJ = Windows::Data::Json;
#define WINRT_OBJ_REF(type) type^
#define WINRT_OBJ_CONST_REF(type) type^
#define DETAILS_NS details::cx
#define JSON_VALUE_TYPE(type) WDJ::JsonValueType::type
using WDJ_JsonObject = WDJ::JsonObject;
using WDJ_JsonArray = WDJ::JsonArray;
#elif defined(CPPWINRT_VERSION)
#include <winrt/Windows.Data.Json.h>
namespace WDJ = winrt::Windows::Data::Json;
#define WINRT_OBJ_REF(type) type
#define WINRT_OBJ_CONST_REF(type) const type&
#define DETAILS_NS details::cppwinrt
#define JSON_VALUE_TYPE(type) WDJ::JsonValueType::type
using WDJ_JsonObject = WDJ::JsonObject;
using WDJ_JsonArray = WDJ::JsonArray;
#elif defined(USE_WRL)
#include <Windows.Data.Json.h>
#include <Windows.Foundation.Collections.h>
namespace WDJ = ABI::Windows::Data::Json;
#define WINRT_OBJ_REF(type) Microsoft::WRL::ComPtr<type>
#define WINRT_OBJ_CONST_REF(type) const Microsoft::WRL::ComPtr<type>&
#define DETAILS_NS details::wrl
#define JSON_VALUE_TYPE(type) WDJ::JsonValueType::JsonValueType_ ## type
using WDJ_JsonObject = WDJ::IJsonObject;
using WDJ_JsonArray = WDJ::IJsonArray;
#endif

class JValue;
typedef std::vector<JValue> JArray;

template<class _Ty>
using is_bool_integral =
std::bool_constant<std::is_integral_v<_Ty>
    && std::is_same_v<std::remove_cv_t<_Ty>, bool>>;

template<class _Ty>
using is_string =
std::bool_constant<std::is_same_v<std::decay_t<_Ty>, wchar_t*>
    || std::is_same_v<std::decay_t<_Ty>, const wchar_t*>
    || std::is_same_v<std::decay_t<_Ty>, std::wstring>
    || std::is_same_v<std::decay_t<_Ty>, const std::wstring>
>;

template<class _Ty>
using is_wchart =
std::bool_constant<std::is_same_v<std::decay_t<_Ty>, wchar_t*>
    || std::is_same_v<std::decay_t<_Ty>, const wchar_t*>
>;

template<class _Ty>
using is_ijsonvalue =
std::bool_constant<std::is_same_v<std::decay_t<_Ty>, WINRT_OBJ_REF(WDJ::IJsonValue)>
    || std::is_same_v<std::decay_t<_Ty>, WINRT_OBJ_REF(WDJ::JsonValue)>
    || std::is_same_v<std::decay_t<_Ty>, WINRT_OBJ_REF(WDJ_JsonObject)>
>;

#ifdef __cplusplus_winrt
namespace details::cx
{
    inline WINRT_OBJ_REF(WDJ::IJsonValue) Parse(const std::wstring& json)
    {
        return WDJ::JsonValue::Parse(ref new Platform::String(json.data()));
    }

    inline WINRT_OBJ_REF(WDJ::IJsonValue) CreateNumberValue(double value)
    {
        return WDJ::JsonValue::CreateNumberValue(value);
    }

    inline WINRT_OBJ_REF(WDJ::IJsonValue) CreateBooleanValue(bool value)
    {
        return WDJ::JsonValue::CreateBooleanValue(value);
    }

    inline WINRT_OBJ_REF(WDJ::IJsonValue) CreateStringValue(const std::wstring& value)
    {
        return WDJ::JsonValue::CreateStringValue(ref new Platform::String(value.data()));
    }

    inline WINRT_OBJ_REF(WDJ::IJsonValue) CreateNullValue()
    {
        return WDJ::JsonValue::CreateNullValue();
    }

    inline WINRT_OBJ_REF(WDJ_JsonArray) CreateJsonArray()
    {
        return ref new WDJ_JsonArray();
    }

    inline WINRT_OBJ_REF(WDJ_JsonObject) CreateJsonObject()
    {
        return ref new WDJ_JsonObject();
    }

    inline void Append(WINRT_OBJ_CONST_REF(WDJ_JsonArray) target, WINRT_OBJ_CONST_REF(WDJ::IJsonValue) value)
    {
        target->Append(value);
    }

    inline void Insert(WINRT_OBJ_CONST_REF(WDJ_JsonObject) target, const std::wstring& key, WINRT_OBJ_CONST_REF(WDJ::IJsonValue) value)
    {
        target->Insert(ref new Platform::String(key.data()), value);
    }

    inline std::wstring GetString(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
    {
        return target->GetString()->Data();
    }

    inline double GetNumber(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
    {
        return target->GetNumber();
    }

    inline bool GetBoolean(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
    {
        return target->GetBoolean();
    }

    inline WINRT_OBJ_REF(WDJ_JsonArray) GetArray(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
    {
        return target->GetArray();
    }

    inline WINRT_OBJ_REF(WDJ_JsonObject) GetObject(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
    {
        return target->GetObject();
    }

    inline WINRT_OBJ_REF(WDJ::IJsonValue) GetAt(WINRT_OBJ_CONST_REF(WDJ_JsonArray) target, uint32_t index)
    {
        return target->GetAt(index);
    }

    inline bool HasKey(WINRT_OBJ_CONST_REF(WDJ_JsonObject) target, const std::wstring& key)
    {
        return target->HasKey(ref new Platform::String(key.data()));
    }

    inline WINRT_OBJ_REF(WDJ::IJsonValue) GetNamedValue(WINRT_OBJ_CONST_REF(WDJ_JsonObject) target, const std::wstring& key)
    {
        return target->GetNamedValue(ref new Platform::String(key.data()));
    }

    inline uint32_t Size(WINRT_OBJ_CONST_REF(WDJ_JsonArray) target)
    {
        return target->Size;
    }

    inline WDJ::JsonValueType ValueType(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
    {
        return target->ValueType;
    }

    inline std::wstring Stringify(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
    {
        return target->Stringify()->Data();
    }

    inline WINRT_OBJ_REF(WDJ::IJsonValue) CastToJsonValue(WINRT_OBJ_CONST_REF(WDJ_JsonObject) target)
    {
        return target;
    }

    inline WINRT_OBJ_REF(WDJ::IJsonValue) CastToJsonValue(WINRT_OBJ_CONST_REF(WDJ_JsonArray) target)
    {
        return target;
    }
}
#elif defined(CPPWINRT_VERSION)
namespace details::cppwinrt
{
    inline WINRT_OBJ_REF(WDJ::IJsonValue) Parse(const std::wstring& json)
    {
        return WDJ::JsonValue::Parse(json);
    }

    inline WINRT_OBJ_REF(WDJ::IJsonValue) CreateNumberValue(double value)
    {
        return WDJ::JsonValue::CreateNumberValue(value);
    }

    inline WINRT_OBJ_REF(WDJ::IJsonValue) CreateBooleanValue(bool value)
    {
        return WDJ::JsonValue::CreateBooleanValue(value);
    }

    inline WINRT_OBJ_REF(WDJ::IJsonValue) CreateStringValue(const std::wstring& value)
    {
        return WDJ::JsonValue::CreateStringValue(value);
    }

    inline WINRT_OBJ_REF(WDJ::IJsonValue) CreateNullValue()
    {
        return WDJ::JsonValue::CreateNullValue();
    }

    inline WINRT_OBJ_REF(WDJ_JsonArray) CreateJsonArray()
    {
        return WDJ_JsonArray();
    }

    inline WINRT_OBJ_REF(WDJ_JsonObject) CreateJsonObject()
    {
        return WDJ_JsonObject();
    }

    inline void Append(WINRT_OBJ_CONST_REF(WDJ_JsonArray) target, WINRT_OBJ_CONST_REF(WDJ::IJsonValue) value)
    {
        target.Append(value);
    }

    inline void Insert(WINRT_OBJ_CONST_REF(WDJ_JsonObject) target, const std::wstring& key, WINRT_OBJ_CONST_REF(WDJ::IJsonValue) value)
    {
        target.Insert(key, value);
    }

    inline std::wstring GetString(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
    {
        return target.GetString().data();
    }

    inline double GetNumber(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
    {
        return target.GetNumber();
    }

    inline bool GetBoolean(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
    {
        return target.GetBoolean();
    }

    inline WINRT_OBJ_REF(WDJ_JsonArray) GetArray(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
    {
        return target.GetArray();
    }

    inline WINRT_OBJ_REF(WDJ_JsonObject) GetObject(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
    {
        return target.GetObject();
    }

    inline WINRT_OBJ_REF(WDJ::IJsonValue) GetAt(WINRT_OBJ_CONST_REF(WDJ_JsonArray) target, uint32_t index)
    {
        return target.GetAt(index);
    }

    inline bool HasKey(WINRT_OBJ_CONST_REF(WDJ_JsonObject) target, const std::wstring& key)
    {
        return target.HasKey(key);
    }

    inline WINRT_OBJ_REF(WDJ::IJsonValue) GetNamedValue(WINRT_OBJ_CONST_REF(WDJ_JsonObject) target, const std::wstring& key)
    {
        return target.GetNamedValue(key);
    }

    inline uint32_t Size(WINRT_OBJ_CONST_REF(WDJ_JsonArray) target)
    {
        return target.Size();
    }

    inline WDJ::JsonValueType ValueType(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
    {
        return target.ValueType();
    }

    inline std::wstring Stringify(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
    {
        return target.Stringify().data();
    }

    inline WINRT_OBJ_REF(WDJ::IJsonValue) CastToJsonValue(WINRT_OBJ_CONST_REF(WDJ_JsonObject) target)
    {
        return target;
    }

    inline WINRT_OBJ_REF(WDJ::IJsonValue) CastToJsonValue(WINRT_OBJ_CONST_REF(WDJ_JsonArray) target)
    {
        return target;
    }
}
#elif defined(USE_WRL)
namespace details
{
    namespace wrl
    {
#ifndef THROW_IF_FAILED
#define THROW_IF_FAILED(hr) if (FAILED(hr)) throw std::runtime_error("HRESULT indicated failure.");
#endif

        namespace MWRL = Microsoft::WRL;
        namespace MWRLW = Microsoft::WRL::Wrappers;
        namespace WF = Windows::Foundation;
        namespace WFC = ABI::Windows::Foundation::Collections;

        inline MWRL::ComPtr<WDJ::IJsonValueStatics> JsonValueStaticsInstance()
        {
            static MWRLW::CriticalSection csJsonValueStatics;
            static MWRL::ComPtr<WDJ::IJsonValueStatics> spJsonValueStatics;
            if (!spJsonValueStatics)
            {
                auto lock = csJsonValueStatics.Lock();
                if (!spJsonValueStatics)
                {
                    THROW_IF_FAILED(WF::GetActivationFactory(MWRLW::HStringReference(RuntimeClass_Windows_Data_Json_JsonValue).Get(), spJsonValueStatics.GetAddressOf()));
                }
            }

            return spJsonValueStatics;
        }

        inline WINRT_OBJ_REF(WDJ::IJsonValue) Parse(const std::wstring& json)
        {
            MWRL::ComPtr<WDJ::IJsonValue> spResult;
            THROW_IF_FAILED(JsonValueStaticsInstance()->Parse(MWRLW::HStringReference(json.data()).Get(), spResult.GetAddressOf()));
            return spResult;
        }

        inline WINRT_OBJ_REF(WDJ::IJsonValue) CreateNumberValue(double value)
        {
            MWRL::ComPtr<WDJ::IJsonValue> spResult;
            THROW_IF_FAILED(JsonValueStaticsInstance()->CreateNumberValue(value, spResult.GetAddressOf()));
            return spResult;
        }

        inline WINRT_OBJ_REF(WDJ::IJsonValue) CreateBooleanValue(bool value)
        {
            MWRL::ComPtr<WDJ::IJsonValue> spResult;
            THROW_IF_FAILED(JsonValueStaticsInstance()->CreateBooleanValue(value, spResult.GetAddressOf()));
            return spResult;
        }

        inline WINRT_OBJ_REF(WDJ::IJsonValue) CreateStringValue(const std::wstring& value)
        {
            MWRL::ComPtr<WDJ::IJsonValue> spResult;
            THROW_IF_FAILED(JsonValueStaticsInstance()->CreateStringValue(MWRLW::HStringReference(value.data()).Get(), spResult.GetAddressOf()));
            return spResult;
        }

        inline WINRT_OBJ_REF(WDJ::IJsonValue) CreateNullValue()
        {
            MWRL::ComPtr<WDJ::IJsonValueStatics2> spJsonValueStatics2;
            THROW_IF_FAILED(JsonValueStaticsInstance().As(&spJsonValueStatics2));
            MWRL::ComPtr<WDJ::IJsonValue> spResult;
            THROW_IF_FAILED(spJsonValueStatics2->CreateNullValue(spResult.GetAddressOf()));
            return spResult;
        }

        inline WINRT_OBJ_REF(WDJ_JsonArray) CreateJsonArray()
        {
            MWRL::ComPtr<WDJ::IJsonArray> spResult;
            THROW_IF_FAILED(WF::ActivateInstance(MWRLW::HStringReference(RuntimeClass_Windows_Data_Json_JsonArray).Get(), spResult.GetAddressOf()));
            return spResult;
        }

        inline WINRT_OBJ_REF(WDJ_JsonObject) CreateJsonObject()
        {
            MWRL::ComPtr<WDJ_JsonObject> spResult;
            THROW_IF_FAILED(WF::ActivateInstance(MWRLW::HStringReference(RuntimeClass_Windows_Data_Json_JsonObject).Get(), spResult.GetAddressOf()));
            return spResult;
        }

        inline void Append(WINRT_OBJ_CONST_REF(WDJ_JsonArray) target, WINRT_OBJ_CONST_REF(WDJ::IJsonValue) value)
        {
            MWRL::ComPtr<WFC::IVector<WDJ::IJsonValue*>> spJsonArrayVector;
            THROW_IF_FAILED(target->QueryInterface(__uuidof(WFC::IVector< WDJ::IJsonValue* >), reinterpret_cast<void**>(spJsonArrayVector.GetAddressOf())));
            THROW_IF_FAILED(spJsonArrayVector->Append(value.Get()));
        }

        inline void Insert(WINRT_OBJ_CONST_REF(WDJ_JsonObject) target, const std::wstring& key, WINRT_OBJ_CONST_REF(WDJ::IJsonValue) value)
        {
            MWRL::ComPtr<WFC::IMap<HSTRING, WDJ::IJsonValue*>> spJsonObjectMap;
            THROW_IF_FAILED(target->QueryInterface(__uuidof(WFC::IMap<HSTRING, WDJ::IJsonValue*>), reinterpret_cast<void**>(spJsonObjectMap.GetAddressOf())));
            boolean replaced = false;
            THROW_IF_FAILED(spJsonObjectMap->Insert(MWRLW::HStringReference(key.data()).Get(), value.Get(), &replaced));
        }

        inline std::wstring GetString(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
        {
            MWRLW::HString value;
            THROW_IF_FAILED(target->GetString(value.GetAddressOf()));
            return value.GetRawBuffer(nullptr);
        }

        inline double GetNumber(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
        {
            double value;
            THROW_IF_FAILED(target->GetNumber(&value));
            return value;
        }

        inline bool GetBoolean(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
        {
            boolean value;
            THROW_IF_FAILED(target->GetBoolean(&value));
            return value;
        }

        inline WINRT_OBJ_REF(WDJ_JsonArray) GetArray(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
        {
            MWRL::ComPtr<WDJ::IJsonArray> spResult;
            THROW_IF_FAILED(target->GetArray(spResult.GetAddressOf()));
            return spResult;
        }

        inline WINRT_OBJ_REF(WDJ_JsonObject) GetObject(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
        {
            MWRL::ComPtr<WDJ::IJsonObject> spResult;
            THROW_IF_FAILED(target->GetObject(spResult.GetAddressOf()));
            return spResult;
        }

        inline WINRT_OBJ_REF(WDJ::IJsonValue) GetAt(WINRT_OBJ_CONST_REF(WDJ_JsonArray) target, uint32_t index)
        {
            MWRL::ComPtr<WFC::IVector<WDJ::IJsonValue*>> spJsonArrayVector;
            THROW_IF_FAILED(target->QueryInterface(__uuidof(WFC::IVector< WDJ::IJsonValue* >), reinterpret_cast<void**>(spJsonArrayVector.GetAddressOf())));
            MWRL::ComPtr<WDJ::IJsonValue> spResult;
            THROW_IF_FAILED(spJsonArrayVector->GetAt(index, spResult.GetAddressOf()));
            return spResult;
        }

        inline bool HasKey(WINRT_OBJ_CONST_REF(WDJ_JsonObject) target, const std::wstring& key)
        {
            MWRL::ComPtr<WFC::IMap<HSTRING, WDJ::IJsonValue*>> spJsonObjectMap;
            THROW_IF_FAILED(target->QueryInterface(__uuidof(WFC::IMap<HSTRING, WDJ::IJsonValue*>), reinterpret_cast<void**>(spJsonObjectMap.GetAddressOf())));
            boolean result;
            THROW_IF_FAILED(spJsonObjectMap->HasKey(MWRLW::HStringReference(key.data()).Get(), &result));
            return result;
        }

        inline WINRT_OBJ_REF(WDJ::IJsonValue) GetNamedValue(WINRT_OBJ_CONST_REF(WDJ_JsonObject) target, const std::wstring& key)
        {
            MWRL::ComPtr<WDJ::IJsonValue> spResult;
            THROW_IF_FAILED(target->GetNamedValue(MWRLW::HStringReference(key.data()).Get(), spResult.GetAddressOf()));
            return spResult;
        }

        inline uint32_t Size(WINRT_OBJ_CONST_REF(WDJ_JsonArray) target)
        {
            MWRL::ComPtr<WFC::IVector<WDJ::IJsonValue*>> spJsonArrayVector;
            THROW_IF_FAILED(target->QueryInterface(__uuidof(WFC::IVector< WDJ::IJsonValue* >), reinterpret_cast<void**>(spJsonArrayVector.GetAddressOf())));
            unsigned int size;
            THROW_IF_FAILED(spJsonArrayVector->get_Size(&size));
            return size;
        }

        inline WDJ::JsonValueType ValueType(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
        {
            WDJ::JsonValueType valueType;
            THROW_IF_FAILED(target->get_ValueType(&valueType));
            return valueType;
        }

        inline std::wstring Stringify(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
        {
            MWRLW::HString value;
            THROW_IF_FAILED(target->Stringify(value.GetAddressOf()));
            return value.GetRawBuffer(nullptr);
        }

        inline WINRT_OBJ_REF(WDJ::IJsonValue) CastToJsonValue(WINRT_OBJ_CONST_REF(WDJ_JsonObject) target)
        {
            MWRL::ComPtr<WDJ::IJsonValue> spResult;
            THROW_IF_FAILED(target.As(&spResult));
            return spResult;
        }

        inline WINRT_OBJ_REF(WDJ::IJsonValue) CastToJsonValue(WINRT_OBJ_CONST_REF(WDJ_JsonArray) target)
        {
            MWRL::ComPtr<WDJ::IJsonValue> spResult;
            THROW_IF_FAILED(target.As(&spResult));
            return spResult;
        }
    }
}
#endif

class JValue
{
public:
    static JValue Parse(const std::wstring& json)
    {
        return JValue(DETAILS_NS::Parse(json));
    }

    JValue(WINRT_OBJ_REF(WDJ::IJsonValue) jsonValue)
        : _jsonValue(jsonValue)
    {
    }

    template<typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
    JValue(T value)
        : _jsonValue{ DETAILS_NS::CreateNumberValue(static_cast<double>(value)) }
    {
    }

    // To support this conversion, implement a method in the namespace of the object you want to serialize
    // that matches this pattern: void Serialize(JValue& json, const T& value);
    template<typename T, std::enable_if_t<!std::is_arithmetic_v<T> && !is_ijsonvalue<T>::value, int> = 0>
    JValue(T value)
    {
        JValue json(nullptr);
        Serialize(json, value);
        _jsonValue = json._jsonValue;
        _omit = json._omit;
    }

    // This can't be marked as explicit, otherwise implicit conversions from bool to JValue
    // won't work, which means methods accepting JValue won't be able to accept bool values.
    JValue(bool value)
        : _jsonValue{ DETAILS_NS::CreateBooleanValue(value) }
    {
    }

    JValue(std::wstring value)
        : _jsonValue(DETAILS_NS::CreateStringValue(value))
    {
    }

    // This is required to ensure string literals and other wchar_t* instances don't get
    // incorrectly deduced as booleans by the compiler, which gets picked over automatic
    // conversion to std::wstring
    JValue(const wchar_t* value)
    {
        if (value == nullptr)
        {
            throw std::invalid_argument("key");
        }

        _jsonValue = DETAILS_NS::CreateStringValue(value);
    }

#ifdef ENABLE_STD_OPTIONAL
    template<typename T>
    JValue(std::optional<T> value)
    {
        if (value.has_value())
        {
            _jsonValue = JValue(value.value());
        }
        else
        {
            _omit = true;
        }
}
#endif ENABLE_STD_OPTIONAL

    template<typename T>
    JValue(std::vector<T> arrayValue)
    {
        auto jarray = DETAILS_NS::CreateJsonArray();
        std::for_each(arrayValue.begin(), arrayValue.end(), [jarray](JValue value) {
            DETAILS_NS::Append(jarray, value);
        });
        _jsonValue = DETAILS_NS::CastToJsonValue(jarray);
    }

    JValue(nullptr_t)
        : _jsonValue{ DETAILS_NS::CreateNullValue() }
    {
    }

    operator WINRT_OBJ_REF(WDJ::IJsonValue)() const
    {
        return _jsonValue;
    }

    operator std::wstring() const
    {
        return DETAILS_NS::GetString(_jsonValue);
    }

    template<typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
    operator T() const
    {
        return static_cast<T>(DETAILS_NS::GetNumber(_jsonValue));
    }

    // To support this conversion, implement a method in the namespace of the object you want to deserialize
    // that matches this pattern: void Deserialize(const JValue& json, T& value);
    template<typename T, std::enable_if_t<!std::is_arithmetic_v<T>, int> = 0>
    operator T() const
    {
        T value;
        Deserialize(*this, value);
        return value;
    }

    // This is required to ensure the compiler doesn't select the
    // numerical overload, as is_arithmetic is true for bool
    operator bool() const
    {
        return DETAILS_NS::GetBoolean(_jsonValue);
    }

    template<typename TElement>
    operator std::vector<TElement>() const
    {
        auto jsonArray = DETAILS_NS::GetArray(_jsonValue);
        std::vector<TElement> valueVector;
        for (unsigned int i = 0; i < DETAILS_NS::Size(jsonArray); i++)
        {
            WINRT_OBJ_REF(WDJ::IJsonValue) value = DETAILS_NS::GetAt(jsonArray, i);
            valueVector.push_back(JValue(value));
        }

        return valueVector;
    }

    operator std::vector<JValue>() const
    {
        auto jsonArray = DETAILS_NS::GetArray(_jsonValue);
        std::vector<JValue> valueVector;
        for (unsigned int i = 0; i < DETAILS_NS::Size(jsonArray); i++)
        {
            WINRT_OBJ_REF(WDJ::IJsonValue) value = DETAILS_NS::GetAt(jsonArray, i);
            valueVector.push_back(JValue(value));
        }

        return valueVector;
    }

#ifdef ENABLE_STD_OPTIONAL
    template<typename T, std::enable_if_t<!is_wchart<T>::value, int> = 0>
    std::optional<T> value_or_opt() const
    {
        if (IsNull())
        {
            return std::nullopt;
        }

#pragma warning(push)
#pragma warning(disable:4127) // Compiler incorrectly suggests using constexpr, then fails if it is used
        if (is_bool_integral<T>::value && !IsValueType(JSON_VALUE_TYPE(Boolean)))
        {
            return std::nullopt;
        }

        if (std::_Is_nonbool_integral<T>::value && !IsValueType(JSON_VALUE_TYPE(Number)))
        {
            return std::nullopt;
        }

        if (is_string<T>::value && !IsValueType(JSON_VALUE_TYPE(String)))
        {
            return std::nullopt;
        }
#pragma warning(pop)

        // Convert from JValue to T, before converting to optional<T>
        try
        {
            T value = *this;
            return value;
        }
        catch (...)
        {
            return std::nullopt;
        }
    }

    template<typename T, std::enable_if_t<!is_wchart<T>::value, int> = 0>
    T value_or(T defaultValue) const
    {
        std::optional<T> valueOpt = value_or_opt<T>();
        return valueOpt.value_or(defaultValue);
    }

    std::wstring value_or(std::wstring defaultValue) const
    {
        std::optional<std::wstring> valueOpt = value_or_opt<std::wstring>();
        return valueOpt.value_or(defaultValue);
    }
#else
    template<typename T, std::enable_if_t<!is_wchart<T>::value, int> = 0>
    T value_or(T defaultValue) const
    {
        if (IsNull())
        {
            return defaultValue;
        }

#pragma warning(push)
#pragma warning(disable:4127) // Compiler incorrectly suggests using constexpr, then fails if it is used
        if (is_bool_integral<T>::value && !IsValueType(JSON_VALUE_TYPE(Boolean)))
        {
            return defaultValue;
        }

        if (std::_Is_nonbool_integral<T>::value && !IsValueType(JSON_VALUE_TYPE(Number)))
        {
            return defaultValue;
        }
#pragma warning(pop)

        // Convert from JValue to T, before converting to optional<T>
        try
        {
            T value = *this;
            return value;
        }
        catch (...)
        {
            return defaultValue;
        }
    }

    std::wstring value_or(std::wstring defaultValue) const
    {
        if (!IsValueType(JSON_VALUE_TYPE(String)))
        {
            return defaultValue;
        }

        return *this;
    }
#endif ENABLE_STD_OPTIONAL

    std::vector<JValue> values_or(std::vector<JValue> defaultValue = std::vector<JValue>()) const
    {
        if (IsNull() || !IsValueType(JSON_VALUE_TYPE(Array)))
        {
            return defaultValue;
        }

        return *this;
    }

    template<typename TElement>
    std::vector<TElement> values_or(std::vector<TElement> defaultValue = std::vector<TElement>(), bool skipInvalidElements = true) const
    {
        if (IsNull() || !IsValueType(JSON_VALUE_TYPE(Array)))
        {
            return defaultValue;
        }

        auto jsonArray = DETAILS_NS::GetArray(_jsonValue);
        std::vector<TElement> valueVector;
        for (unsigned int i = 0; i < DETAILS_NS::Size(jsonArray); i++)
        {
            WINRT_OBJ_REF(WDJ::IJsonValue) value = DETAILS_NS::GetAt(jsonArray, i);
            if (skipInvalidElements)
            {
#if defined(ENABLE_STD_OPTIONAL)
                std::optional<TElement> elementValueOrOpt = JValue(value).value_or_opt<TElement>();
                if (elementValueOrOpt.has_value())
                {
                    valueVector.push_back(std::move(elementValueOrOpt.value()));
                }
#else
                TElement defaultValue = TElement();
                TElement elementValueOrDefault = JValue(value).value_or(defaultValue);
                if (elementValueOrDefault != defaultValue)
                {
                    valueVector.push_back(std::move(elementValueOrDefault));
                }
#endif
            }
            else
            {
                valueVector.push_back(JValue(value));
            }
        }

        return valueVector;
    }

    template<typename TElement>
    std::vector<TElement> values_or(TElement elementFallbackValue, std::vector<TElement> defaultValue = std::vector<TElement>()) const
    {
        if (IsNull() || !IsValueType(JSON_VALUE_TYPE(Array)))
        {
            return defaultValue;
        }

        auto jsonArray = DETAILS_NS::GetArray(_jsonValue);
        std::vector<TElement> valueVector;
        for (unsigned int i = 0; i < DETAILS_NS::Size(jsonArray); i++)
        {
            WINRT_OBJ_REF(WDJ::IJsonValue) value = DETAILS_NS::GetAt(jsonArray, i);
            valueVector.push_back(JValue(value).value_or(elementFallbackValue));
        }

        return valueVector;
    }

    // Note: if a key doesn't exist, the return will be a Null JValue
    // this allows null propogation like so:
    // responseJson["key"]["secondKey"].value_or(L"")
    // in this case, if "key" doesn't exist, this will still return the final default
    // value L"", instead of throwing when attempting to lookup "secondKey".
    JValue operator[](const wchar_t* key) const
    {
        if (key == nullptr)
        {
            throw std::invalid_argument("key");
        }

        std::wstring pKey = key;
        if (IsValueType(JSON_VALUE_TYPE(Object)) && DETAILS_NS::HasKey(DETAILS_NS::GetObject(_jsonValue), pKey))
        {
            return DETAILS_NS::GetNamedValue(DETAILS_NS::GetObject(_jsonValue), pKey);
        }
        else
        {
            return DETAILS_NS::CreateNullValue();
        }
    }

    JValue operator[](int index) const
    {
        // Parameter type can't be unsigned int, because compiler gets confused between this
        // and the wchar_t overload if the caller doesn't explicitly use an unsigned int literal (i.e. 0u)
        if (index < 0)
        {
            throw std::invalid_argument("index");
        }

        unsigned int unsignedIndex = (unsigned int)index;

        if (IsValueType(JSON_VALUE_TYPE(Array)) && DETAILS_NS::Size(DETAILS_NS::GetArray(_jsonValue)) > unsignedIndex)
        {
            return DETAILS_NS::GetAt(DETAILS_NS::GetArray(_jsonValue), unsignedIndex);
        }
        else
        {
            return DETAILS_NS::CreateNullValue();
        }
    }

    void Insert(const wchar_t* key, JValue value)
    {
        if (!IsValueType(JSON_VALUE_TYPE(Object)))
        {
            throw std::logic_error("JValue is not a JSON object");
        }

        if (key == nullptr)
        {
            throw std::invalid_argument("key");
        }

        DETAILS_NS::Insert(DETAILS_NS::GetObject(_jsonValue), key, value);
    }

    void Append(JValue value)
    {
        if (!IsValueType(JSON_VALUE_TYPE(Array)))
        {
            throw std::logic_error("JValue is not a JSON array");
        }

        DETAILS_NS::Append(DETAILS_NS::GetArray(_jsonValue), value);
    }

    bool IsNull() const
    {
        return _jsonValue == nullptr || DETAILS_NS::ValueType(_jsonValue) == JSON_VALUE_TYPE(Null);
    }

    bool IsValueType(WDJ::JsonValueType valueType) const
    {
        return _jsonValue != nullptr && DETAILS_NS::ValueType(_jsonValue) == valueType;
    }

    JValue(std::initializer_list<std::pair<std::wstring, JValue>> map)
    {
        WINRT_OBJ_REF(WDJ_JsonObject) jObject = DETAILS_NS::CreateJsonObject();
        for (auto& pair : map)
        {
            JValue jvalue = pair.second;
            if (!jvalue._omit)
            {
                DETAILS_NS::Insert(jObject, pair.first, jvalue);
            }
        }

        _jsonValue = DETAILS_NS::CastToJsonValue(jObject);
    }

    std::wstring ToString() const
    {
        return DETAILS_NS::Stringify(_jsonValue);
    }
private:
    WINRT_OBJ_REF(WDJ::IJsonValue) _jsonValue;
    bool _omit = false;
};

#undef WINRT_OBJ_REF
#undef WINRT_OBJ_CONST_REF
#undef DETAILS_NS
#undef JSON_VALUE_TYPE
#undef ENABLE_STD_OPTIONAL
#undef USE_WRL

#endif // defined(__cplusplus_winrt) || defined(CPPWINRT_VERSION) || defined(USE_WRL)
