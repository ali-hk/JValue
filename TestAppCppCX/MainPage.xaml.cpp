//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace TestAppCppCX;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
    InitializeComponent();
}


void MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
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
                { L"Key2", false }
            }
        }
    };
    OutputDebugString(test2.ToString().data());

    int x = test2[L"root"][L"Key"][L"SubKey"];
    std::wstring nonExistent = test2[L"root"][L"fake"].value_or(L"NONEXISTENT");
}
