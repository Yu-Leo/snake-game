#include "CppUnitTest.h"

#include "../snake-game/Point.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests {
    TEST_CLASS(TestPoint) {
public:

    TEST_METHOD(TestDefaultConstructor) {
        Point p;
        Assert::AreEqual(p.x, 0);
        Assert::AreEqual(p.y, 0);
    }

    TEST_METHOD(TestConstructor) {
        Point p1(100, 20);
        Assert::AreEqual(p1.x, 100);
        Assert::AreEqual(p1.y, 20);

        Point p2(1, 10);
        Assert::AreEqual(p2.x, 1);
        Assert::AreEqual(p2.y, 10);
    }

    TEST_METHOD(TestEqualityOperator) {
        Point p1(1, 1);
        Point p2(1, 1);
        Assert::IsTrue(p1 == p2);

        Point p3(1, 0);
        Assert::IsFalse(p1 == p3);

        Point p4(100, 100);
        Assert::IsFalse(p1 == p4);
    }

    };
}
