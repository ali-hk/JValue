#pragma once

#include <optional>
#include <string>
#include <type_traits>
#include <vector>

#if _MSVC_LANG >= 201703L 
#define ENABLE_STD_OPTIONAL
#endif

#if defined(__cplusplus_winrt) || defined(CPPWINRT_VERSION)

#ifdef __cplusplus_winrt
namespace WDJ = Windows::Data::Json;
#define STRING_T Platform::String^
#define WINRT_OBJ_REF ^
#define DEREF ->
#define PROPERTY_SUFFIX
#define TO_PLAT_STRING(value) ref new Platform::String(value.data())
#define WCHAR_TO_PLAT_STRING(value) ref new Platform::String(value)
#define TO_WSTRING(value) value->Data()
#define INSTANTIATE ref new
#elif defined(CPPWINRT_VERSION)
#include <winrt/Windows.Data.Json.h>
namespace WDJ = winrt::Windows::Data::Json;
#define STRING_T winrt::hstring
#define WINRT_OBJ_REF
#define DEREF .
#define PROPERTY_SUFFIX ()
#define TO_PLAT_STRING(value) value
#define WCHAR_TO_PLAT_STRING(value) value
#define TO_WSTRING(value) value.data()
#define INSTANTIATE
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
std::bool_constant<std::is_same_v<std::decay_t<_Ty>, WDJ::IJsonValue WINRT_OBJ_REF>
    || std::is_same_v<std::decay_t<_Ty>, WDJ::JsonValue WINRT_OBJ_REF>
    || std::is_same_v<std::decay_t<_Ty>, WDJ::JsonObject WINRT_OBJ_REF>
>;

class JValue
{
public:
    static JValue Parse(std::wstring json)
    {
        return JValue(WDJ::JsonValue::Parse(TO_PLAT_STRING(json)));
    }

    JValue(WDJ::IJsonValue WINRT_OBJ_REF jsonValue)
        : _jsonValue(jsonValue)
    {
    }

    template<typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
    JValue(T value)
        : _jsonValue{ WDJ::JsonValue::CreateNumberValue(static_cast<double>(value)) }
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
        : _jsonValue{ WDJ::JsonValue::CreateBooleanValue(value) }
    {
    }

    JValue(std::wstring value)
        : _jsonValue(WDJ::JsonValue::CreateStringValue(TO_PLAT_STRING(value)))
    {
    }

    // This is required to ensure string literals and other wchar_t* instances don't get
    // incorrectly deduced as booleans by the compiler, which gets picked over automatic
    // conversion to std::wstring
    JValue(const wchar_t* value)
        : _jsonValue{ WDJ::JsonValue::CreateStringValue(WCHAR_TO_PLAT_STRING(value)) }
    {
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
        auto jarray = INSTANTIATE WDJ::JsonArray();
        std::for_each(arrayValue.begin(), arrayValue.end(), [jarray](JValue value) {
            jarray DEREF Append(value);
        });
        _jsonValue = jarray;
    }

    JValue(nullptr_t)
        : _jsonValue{ WDJ::JsonValue::CreateNullValue() }
    {
    }

    operator WDJ::IJsonValue WINRT_OBJ_REF() const
    {
        return _jsonValue;
    }

    operator std::wstring() const
    {
        return TO_WSTRING(_jsonValue DEREF GetString());
    }

    template<typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
    operator T() const
    {
        return static_cast<T>(_jsonValue DEREF GetNumber());
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
        return _jsonValue DEREF GetBoolean();
    }

    template<typename TElement>
    operator std::vector<TElement>() const
    {
        auto jsonArray = _jsonValue DEREF GetArray();
        std::vector<TElement> valueVector;
        for (unsigned int i = 0; i < jsonArray DEREF Size PROPERTY_SUFFIX; i++)
        {
            WDJ::IJsonValue WINRT_OBJ_REF value = jsonArray DEREF GetAt(i);
            valueVector.push_back(JValue(value));
        }

        return valueVector;
    }

    operator std::vector<JValue>() const
    {
        auto jsonArray = _jsonValue DEREF GetArray();
        std::vector<JValue> valueVector;
        for (unsigned int i = 0; i < jsonArray DEREF Size PROPERTY_SUFFIX; i++)
        {
            WDJ::IJsonValue WINRT_OBJ_REF value = jsonArray DEREF GetAt(i);
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
        if (is_bool_integral<T>::value && !IsValueType(WDJ::JsonValueType::Boolean))
        {
            return std::nullopt;
        }

        if (std::_Is_nonbool_integral<T>::value && !IsValueType(WDJ::JsonValueType::Number))
        {
            return std::nullopt;
        }

        if (is_string<T>::value && !IsValueType(WDJ::JsonValueType::String))
        {
            return std::nullopt;
        }
#pragma warning(pop)

        // Convert from JValue to T, before converting to optional<T>
        T value = *this;
        return value;
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
        if (is_bool_integral<T>::value && !IsValueType(WDJ::JsonValueType::Boolean))
        {
            return defaultValue;
        }

        if (std::_Is_nonbool_integral<T>::value && !IsValueType(WDJ::JsonValueType::Number))
        {
            return defaultValue;
        }
#pragma warning(pop)

        // Convert from JValue to T, before converting to optional<T>
        T value = *this;
        return value;
    }

    std::wstring value_or(std::wstring defaultValue) const
    {
        if (!IsValueType(WDJ::JsonValueType::String))
        {
            return defaultValue;
        }

        return *this;
    }
#endif ENABLE_STD_OPTIONAL

    std::vector<JValue> values_or(std::vector<JValue> defaultValue = std::vector<JValue>()) const
    {
        if (IsNull() || !IsValueType(WDJ::JsonValueType::Array))
        {
            return defaultValue;
        }

        return *this;
    }

    template<typename TElement>
    std::vector<TElement> values_or(std::vector<TElement> defaultValue = std::vector<TElement>()) const
    {
        if (IsNull() || !IsValueType(WDJ::JsonValueType::Array))
        {
            return defaultValue;
        }

        return *this;
    }

    // Note: if a key doesn't exist, the return will be a Null JValue
    // this allows null propogation like so:
    // responseJson["key"]["secondKey"].value_or(L"")
    // in this case, if "key" doesn't exist, this will still return the final default
    // value L"", instead of throwing when attempting to lookup "secondKey".
    JValue operator[](const wchar_t* key) const
    {
        auto pKey = WCHAR_TO_PLAT_STRING(key);
        if (IsValueType(WDJ::JsonValueType::Object) && _jsonValue DEREF GetObject() DEREF HasKey(pKey))
        {
            return _jsonValue DEREF GetObject() DEREF GetNamedValue(pKey);
        }
        else
        {
            return WDJ::JsonValue::CreateNullValue();
        }
    }

    JValue operator[](int index) const
    {
        if (IsValueType(WDJ::JsonValueType::Array) && ((int)_jsonValue DEREF GetArray() DEREF Size PROPERTY_SUFFIX) > index)
        {
            return _jsonValue DEREF GetArray() DEREF GetAt(index);
        }
        else
        {
            return WDJ::JsonValue::CreateNullValue();
        }
    }

    void Insert(const wchar_t* key, JValue value)
    {
        if (!IsValueType(WDJ::JsonValueType::Object))
        {
            throw std::logic_error("JValue is not a JSON object");
        }

        _jsonValue DEREF GetObject() DEREF Insert(WCHAR_TO_PLAT_STRING(key), value);
    }

    void Append(JValue value)
    {
        if (!IsValueType(WDJ::JsonValueType::Array))
        {
            throw std::logic_error("JValue is not a JSON array");
        }

        _jsonValue DEREF GetArray() DEREF Append(value);
    }

    bool IsNull() const
    {
        return _jsonValue == nullptr || _jsonValue DEREF ValueType PROPERTY_SUFFIX == WDJ::JsonValueType::Null;
    }

    bool IsValueType(WDJ::JsonValueType valueType) const
    {
        return _jsonValue != nullptr && _jsonValue DEREF ValueType PROPERTY_SUFFIX == valueType;
    }

    JValue(std::initializer_list<std::pair<std::wstring, JValue>> map)
    {
        WDJ::JsonObject WINRT_OBJ_REF jObject = INSTANTIATE WDJ::JsonObject();
        for (auto& pair : map)
        {
            JValue jvalue = pair.second;
            if (!jvalue._omit)
            {
                jObject DEREF Insert(TO_PLAT_STRING(pair.first), jvalue);
            }
        }

        _jsonValue = jObject;
    }

    std::wstring ToString() const
    {
        return TO_WSTRING(_jsonValue DEREF Stringify());
    }
private:
    WDJ::IJsonValue  WINRT_OBJ_REF _jsonValue;
    bool _omit = false;
};

#undef STRING_T
#undef WINRT_OBJ_REF
#undef DEREF
#undef PROPERTY_SUFFIX
#undef TO_PLAT_STRING
#undef WCHAR_TO_PLAT_STRING
#undef TO_WSTRING

#endif // defined(__cplusplus_winrt) || defined(CPPWINRT_VERSION)
