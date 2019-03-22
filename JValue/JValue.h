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
#define WINRT_OBJ_REF(type) type^
#define WINRT_OBJ_CONST_REF(type) type^
#define DETAIL_NS detail::cx
#elif defined(CPPWINRT_VERSION)
#include <winrt/Windows.Data.Json.h>
namespace WDJ = winrt::Windows::Data::Json;
#define WINRT_OBJ_REF(type) type
#define WINRT_OBJ_CONST_REF(type) const type&
#define DETAIL_NS detail::cppwinrt
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
    || std::is_same_v<std::decay_t<_Ty>, WINRT_OBJ_REF(WDJ::JsonObject)>
>;

#ifdef __cplusplus_winrt
namespace detail::cx
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

    inline WINRT_OBJ_REF(WDJ::JsonArray) CreateJsonArray()
    {
        return ref new WDJ::JsonArray();
    }

    inline WINRT_OBJ_REF(WDJ::JsonObject) CreateJsonObject()
    {
        return ref new WDJ::JsonObject();
    }

    inline void Append(WINRT_OBJ_CONST_REF(WDJ::JsonArray) target, WINRT_OBJ_CONST_REF(WDJ::IJsonValue) value)
    {
        target->Append(value);
    }

    inline void Insert(WINRT_OBJ_CONST_REF(WDJ::JsonObject) target, const std::wstring& key, WINRT_OBJ_CONST_REF(WDJ::IJsonValue) value)
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

    inline WINRT_OBJ_REF(WDJ::JsonArray) GetArray(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
    {
        return target->GetArray();
    }

    inline WINRT_OBJ_REF(WDJ::JsonObject) GetObject(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
    {
        return target->GetObject();
    }

    inline WINRT_OBJ_REF(WDJ::IJsonValue) GetAt(WINRT_OBJ_CONST_REF(WDJ::JsonArray) target, uint32_t index)
    {
        return target->GetAt(index);
    }

    inline bool HasKey(WINRT_OBJ_CONST_REF(WDJ::JsonObject) target, const std::wstring& key)
    {
        return target->HasKey(ref new Platform::String(key.data()));
    }

    inline WINRT_OBJ_REF(WDJ::IJsonValue) GetNamedValue(WINRT_OBJ_CONST_REF(WDJ::JsonObject) target, const std::wstring& key)
    {
        return target->GetNamedValue(ref new Platform::String(key.data()));
    }

    inline uint32_t Size(WINRT_OBJ_CONST_REF(WDJ::JsonArray) target)
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
}
#elif defined(CPPWINRT_VERSION)
namespace detail::cppwinrt
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

    inline WINRT_OBJ_REF(WDJ::JsonArray) CreateJsonArray()
    {
        return WDJ::JsonArray();
    }

    inline WINRT_OBJ_REF(WDJ::JsonObject) CreateJsonObject()
    {
        return WDJ::JsonObject();
    }

    inline void Append(WINRT_OBJ_CONST_REF(WDJ::JsonArray) target, WINRT_OBJ_CONST_REF(WDJ::IJsonValue) value)
    {
        target.Append(value);
    }

    inline void Insert(WINRT_OBJ_CONST_REF(WDJ::JsonObject) target, const std::wstring& key, WINRT_OBJ_CONST_REF(WDJ::IJsonValue) value)
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

    inline WINRT_OBJ_REF(WDJ::JsonArray) GetArray(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
    {
        return target.GetArray();
    }

    inline WINRT_OBJ_REF(WDJ::JsonObject) GetObject(WINRT_OBJ_CONST_REF(WDJ::IJsonValue) target)
    {
        return target.GetObject();
    }

    inline WINRT_OBJ_REF(WDJ::IJsonValue) GetAt(WINRT_OBJ_CONST_REF(WDJ::JsonArray) target, uint32_t index)
    {
        return target.GetAt(index);
    }

    inline bool HasKey(WINRT_OBJ_CONST_REF(WDJ::JsonObject) target, const std::wstring& key)
    {
        return target.HasKey(key);
    }

    inline WINRT_OBJ_REF(WDJ::IJsonValue) GetNamedValue(WINRT_OBJ_CONST_REF(WDJ::JsonObject) target, const std::wstring& key)
    {
        return target.GetNamedValue(key);
    }

    inline uint32_t Size(WINRT_OBJ_CONST_REF(WDJ::JsonArray) target)
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
}
#endif

class JValue
{
public:
    static JValue Parse(std::wstring json)
    {
        return JValue(DETAIL_NS::Parse(json));
    }

    JValue(WINRT_OBJ_REF(WDJ::IJsonValue) jsonValue)
        : _jsonValue(jsonValue)
    {
    }

    template<typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
    JValue(T value)
        : _jsonValue{ DETAIL_NS::CreateNumberValue(static_cast<double>(value)) }
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
        : _jsonValue{ DETAIL_NS::CreateBooleanValue(value) }
    {
    }

    JValue(std::wstring value)
        : _jsonValue(DETAIL_NS::CreateStringValue(value))
    {
    }

    // This is required to ensure string literals and other wchar_t* instances don't get
    // incorrectly deduced as booleans by the compiler, which gets picked over automatic
    // conversion to std::wstring
    JValue(const wchar_t* value)
        : _jsonValue{ DETAIL_NS::CreateStringValue(value) }
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
        auto jarray = DETAIL_NS::CreateJsonArray();
        std::for_each(arrayValue.begin(), arrayValue.end(), [jarray](JValue value) {
            DETAIL_NS::Append(jarray, value);
        });
        _jsonValue = jarray;
    }

    JValue(nullptr_t)
        : _jsonValue{ DETAIL_NS::CreateNullValue() }
    {
    }

    operator WINRT_OBJ_REF(WDJ::IJsonValue)() const
    {
        return _jsonValue;
    }

    operator std::wstring() const
    {
        return DETAIL_NS::GetString(_jsonValue);
    }

    template<typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
    operator T() const
    {
        return static_cast<T>(DETAIL_NS::GetNumber(_jsonValue));
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
        return DETAIL_NS::GetBoolean(_jsonValue);
    }

    template<typename TElement>
    operator std::vector<TElement>() const
    {
        auto jsonArray = DETAIL_NS::GetArray(_jsonValue);
        std::vector<TElement> valueVector;
        for (unsigned int i = 0; i < DETAIL_NS::Size(jsonArray); i++)
        {
            WINRT_OBJ_REF(WDJ::IJsonValue) value = DETAIL_NS::GetAt(jsonArray);
            valueVector.push_back(JValue(value));
        }

        return valueVector;
    }

    operator std::vector<JValue>() const
    {
        auto jsonArray = DETAIL_NS::GetArray(_jsonValue);
        std::vector<JValue> valueVector;
        for (unsigned int i = 0; i < DETAIL_NS::Size(jsonArray); i++)
        {
            WINRT_OBJ_REF(WDJ::IJsonValue) value = DETAIL_NS::GetAt(jsonArray, i);
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
        std::wstring pKey = key;
        if (IsValueType(WDJ::JsonValueType::Object) && DETAIL_NS::HasKey(DETAIL_NS::GetObject(_jsonValue), pKey))
        {
            return DETAIL_NS::GetNamedValue(DETAIL_NS::GetObject(_jsonValue), pKey);
        }
        else
        {
            return DETAIL_NS::CreateNullValue();
        }
    }

    JValue operator[](uint32_t index) const
    {
        if (IsValueType(WDJ::JsonValueType::Array) && DETAIL_NS::Size(DETAIL_NS::GetArray(_jsonValue)) > index)
        {
            return DETAIL_NS::GetAt(DETAIL_NS::GetArray(_jsonValue), index);
        }
        else
        {
            return DETAIL_NS::CreateNullValue();
        }
    }

    void Insert(const wchar_t* key, JValue value)
    {
        if (!IsValueType(WDJ::JsonValueType::Object))
        {
            throw std::logic_error("JValue is not a JSON object");
        }

        DETAIL_NS::Insert(DETAIL_NS::GetObject(_jsonValue), key, value);
    }

    void Append(JValue value)
    {
        if (!IsValueType(WDJ::JsonValueType::Array))
        {
            throw std::logic_error("JValue is not a JSON array");
        }

        DETAIL_NS::Append(DETAIL_NS::GetArray(_jsonValue), value);
    }

    bool IsNull() const
    {
        return _jsonValue == nullptr || DETAIL_NS::ValueType(_jsonValue) == WDJ::JsonValueType::Null;
    }

    bool IsValueType(WDJ::JsonValueType valueType) const
    {
        return _jsonValue != nullptr && DETAIL_NS::ValueType(_jsonValue) == valueType;
    }

    JValue(std::initializer_list<std::pair<std::wstring, JValue>> map)
    {
        WINRT_OBJ_REF(WDJ::JsonObject) jObject = DETAIL_NS::CreateJsonObject();
        for (auto& pair : map)
        {
            JValue jvalue = pair.second;
            if (!jvalue._omit)
            {
                DETAIL_NS::Insert(jObject, pair.first, jvalue);
            }
        }

        _jsonValue = jObject;
    }

    std::wstring ToString() const
    {
        return DETAIL_NS::Stringify(_jsonValue);
    }
private:
    WINRT_OBJ_REF(WDJ::IJsonValue) _jsonValue;
    bool _omit = false;
};

#undef WINRT_OBJ_REF
#undef WINRT_OBJ_CONST_REF
#undef DETAIL_NS

#endif // defined(__cplusplus_winrt) || defined(CPPWINRT_VERSION)
