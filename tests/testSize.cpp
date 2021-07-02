#include "CppUnitTest.h"

#include "../snake-game/Size.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests {
    TEST_CLASS(TestSize) {
    public:
		
        TEST_METHOD(TestDefaultConstructor) {
            Size s;
            Assert::AreEqual(s.width, 0);
            Assert::AreEqual(s.height, 0);
        }

        TEST_METHOD(TestConstructor) {
            Size s1(100, 20);
            Assert::AreEqual(s1.width, 100);
            Assert::AreEqual(s1.height, 20);

            Size s2(1, 10);
            Assert::AreEqual(s2.width, 1);
            Assert::AreEqual(s2.height, 10);
        }

    };
}
