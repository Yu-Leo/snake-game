#include "CppUnitTest.h"

#include "../snake-game/mechanics/Snake.h"
#include "../snake-game/mechanics/Size.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests {
    TEST_CLASS(TestSnake) {
    public:

        TEST_METHOD(TestDefaultConstructor) {
            Snake s;
            Assert::IsTrue(s.get_length() == 3);
            Assert::IsTrue(s.get_direction() == Snake::Directions::RIGHT);
            Assert::IsTrue(s.get_head_pos() == Point(s.get_length() - 1 + 3, 3));
        }

        TEST_METHOD(TestChangeOfDirection) {
            Snake s;
            s.change_direction(Snake::Directions::DOWN);
            Assert::IsTrue(s.get_direction() == Snake::Directions::DOWN);
            s.change_direction(Snake::Directions::LEFT);
            Assert::IsTrue(s.get_direction() == Snake::Directions::LEFT);
            s.change_direction(Snake::Directions::RIGHT);
            Assert::IsTrue(s.get_direction() == Snake::Directions::RIGHT);
            s.change_direction(Snake::Directions::UP);
            Assert::IsTrue(s.get_direction() == Snake::Directions::UP);
        }

        TEST_METHOD(TestHeadMovement) {
            Snake s;
            s.set_field_size(Size(20, 20));
            Point old_pos, new_pos;
            
            s.change_direction(Snake::Directions::RIGHT);
            old_pos = s.get_head_pos();
            s.move_head();
            new_pos = s.get_head_pos();
            Assert::IsTrue(new_pos.x == old_pos.x + 1);
            Assert::IsTrue(new_pos.y == old_pos.y);

            s.change_direction(Snake::Directions::DOWN);
            old_pos = s.get_head_pos();
            s.move_head();
            new_pos = s.get_head_pos();
            Assert::IsTrue(new_pos.x == old_pos.x);
            Assert::IsTrue(new_pos.y == old_pos.y + 1);

            s.change_direction(Snake::Directions::LEFT);
            old_pos = s.get_head_pos();
            s.move_head();
            new_pos = s.get_head_pos();
            Assert::IsTrue(new_pos.x == old_pos.x - 1);
            Assert::IsTrue(new_pos.y == old_pos.y);

            s.change_direction(Snake::Directions::UP);
            old_pos = s.get_head_pos();
            s.move_head();
            new_pos = s.get_head_pos();
            Assert::IsTrue(new_pos.x == old_pos.x);
            Assert::IsTrue(new_pos.y == old_pos.y - 1);
        }

        TEST_METHOD(TestIncreaseLength) {
            Snake s;
            int old_length = s.get_length();
            s.increase_length();
            int new_length = s.get_length();
            Assert::IsTrue(new_length = old_length + 1);
        }

    };
}
