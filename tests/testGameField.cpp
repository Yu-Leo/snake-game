#include "CppUnitTest.h"

#include "../snake-game/GameField.h"
#include "../snake-game/Size.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests {
    TEST_CLASS(TestGameField) {
    public:

        TEST_METHOD(TestDefaultConstructor) {
            GameField game_field;
            Assert::IsTrue(game_field.get_size() == Size(20, 20));
            Assert::IsTrue(game_field.get_game_status() ==
                GameField::GameStatus::STARTED);

            Assert::IsTrue(game_field.get_score() == 0);

        }

        TEST_METHOD(TestConstructor) {
            GameField game_field_1(Size(10, 19));
            Assert::IsTrue(game_field_1.get_size() == Size(10, 19));

            GameField game_field_2(Size(100, 10));
            Assert::IsTrue(game_field_2.get_size() == Size(100, 10));
        }

        TEST_METHOD(TestStart) {
            GameField game_field;
            game_field.start();
            Assert::IsTrue(game_field.get_game_status() ==
                GameField::GameStatus::STARTED);
        }

        TEST_METHOD(TestFinish) {
            GameField game_field;
            game_field.finish();
            Assert::IsTrue(game_field.get_game_status() ==
                GameField::GameStatus::FINISHED);
        }

        TEST_METHOD(TestPause) {
            GameField game_field;
            game_field.pause();
            Assert::IsTrue(game_field.get_game_status() ==
                GameField::GameStatus::PAUSE);
        }

        TEST_METHOD(TestUnpause) {
            GameField game_field;
            game_field.unpause();
            Assert::IsTrue(game_field.get_game_status() ==
                GameField::GameStatus::ACTIVE);
        }

    };
}
