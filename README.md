# JValue

A convenience wrapper for UWP C++ Json APIs (Windows::Data::Json)

Supports C++/WinRT and C++/CX.

## Usage

Add the header file (`JValue.h`) to your project and include it.

## Examples

- **Basic parsing**

```cpp
std::wstring jsonString = LR"|({ "test": { "value1": true, "value2": "yes" } })|";
JValue test = JValue::Parse(jsonString);
bool result = test[L"test"][L"value1"];
```

- **Extracting nested values with null coalescing:**

```cpp
std::optional<int> targetValue = jvalue[L"root"][L"key"][L"subKey"][L"subSubKey"].value_or_opt<int>();
```

or

```cpp
int targetValue = jvalue[L"root"][L"key"][L"subKey"][L"subSubKey"].value_or(5);
```

or

```cpp
JValue targetValue = jvalue[L"root"][L"key"][L"subKey"][L"subSubKey"];
if (targetValue.IsNull()) { /* some logic */ }
```

- **Implicit conversion to types**

```cpp
std::wstring stringValue = jvalue[L"key"];`
```

- **Custom converstion to complex types (see below for details)**

```cpp
std::shared_ptr<MyCustomType> customTypeValue = jvalue[L"key"];
```

- **Easy JSON blob creation**
  - Note: if a value is a std::optional<T> and the optional does not have a value (i.e. `optionalValue.has_value() == false`), the key will automatically be omitted.
  - Note: to explicitly specify a null value for a key, use `JValue(nullptr)`
  - Note: for custom serialization of complex objects see below

```cpp
JValue testJvalue =
    {
        { L"root",
            {
                { L"Key",
                  {
                    { L"SubKey", 1 }
                  }
                },
                { L"Key2", false },
                { L"Key3", L"stringValue" },
                { L"Key4", optionalValue },
                { L"Key5", customComplexTypeValue }
            }
        }
    };

std::wstring serializedJson = testJavlue.ToString();
```

- **Iterate over JSON arrays**

```cpp
std::vector<JValue> array = jvalue[L"array"];
for (auto& value : array) { }
```

- **Parse arrays as a type**

```cpp
std::vector<std::wstring> number = jvalue[L"arrayOfStrings"];
```

## Support for implicilty serializing and deserializing custom types

In order to provide implicit serailization and deserialization for a custom type, declare methods in the same namespace with the following signatures (but outside of the class or struct declaration). This will enable automatic implicit serialization and deserialization of your types without calling these methods (see above for usage).

```cpp
void Serialize(JValue& json, const T& value);
void Deserialize(const JValue& json, T& value);
```

For example, given a type `Point`:

```cpp
namespace Geometry
{
  class Point
  {
    public:
      int x;
      int y;

      Point(int x, int y)
      {
        this.x = x;
        this.y = y;
      }
  };

  void Serialize(JValue& json, const Point& value)
  {
    json = {
      { L"x", x },
      { L"y", y }
    }
  }

  void Deserialize(const JValue& json, Point& value)
  {
    value = Point(json[L"x"], json[L"y"]);
  }
}
```

Alternatively, the deserialize method can use a `std::shared_ptr`:

```cpp
  void Deserialize(const JValue& json, std::shared_ptr<Point>& value)
  {
    value = std::make_shared<Point>(json[L"x"], json[L"y"]);
  }
```

Now, you can serialize and deserialize your custom class like so:

```cpp
Point point(5, 3);
JValue jsonPoint = point;
std::wstring serializedPoint = jsonPoint.ToString();

JValue deserializedJsonPoint = JValue::Parse(serializedPoint);
Point deserializedPoint = deserializedJsonPoint;
```
