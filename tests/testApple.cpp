#include "CppUnitTest.h"

#include "../snake-game/mechanics/Apple.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests {
    TEST_CLASS(TestApple) {
    public:
        
        TEST_METHOD(TestDefaultConstructor) {
            Apple a;
            Assert::IsTrue(a.get_coordinates() == Point());
        }

        TEST_METHOD(TestConstructor) {
            Apple a1(Point(2, 3));
            Assert::IsTrue(a1.get_coordinates() == Point(2, 3));

            Apple a2(Point(18, 10));
            Assert::IsTrue(a2.get_coordinates() == Point(18, 10));
        }
    };
}
