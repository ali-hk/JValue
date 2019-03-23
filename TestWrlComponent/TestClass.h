#pragma once
namespace ABI
{
    namespace TestWrlComponent
    {
        class TestClass WrlFinal
            : public Microsoft::WRL::RuntimeClass < ITestClass, Microsoft::WRL::FtmBase >
        {
            // Note: InspectableClass changes visibility to private:, so change it as needed after
            InspectableClass(RuntimeClass_TestWrlComponent_TestClass, BaseTrust);

        public:
            TestClass();
            ~TestClass();

            IFACEMETHOD(TestMethod)() override;
        };

        ActivatableClass(TestClass);
    }
}