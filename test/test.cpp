#include "pch.h"
#include "../source/char_list.h"

class list_test : public ::testing::Test {
protected:
    char_list test_list;

    void SetUp() override {
        test_list.AppendAll("test123");
    }
};

TEST_F(list_test, Length) {
    EXPECT_EQ(test_list.GetLength(), 7);
}

TEST_F(list_test, AddCharacters) {
    test_list.Append('4');
    EXPECT_EQ(test_list.GetLength(), 8);
    EXPECT_EQ(test_list.Get(7), '4');

    test_list.Insert('0', 4);
    EXPECT_EQ(test_list.GetLength(), 9);
    EXPECT_EQ(test_list.Get(4), '0');
}

TEST_F(list_test, Deletion) {
    EXPECT_EQ(test_list.Delete(6), '3');
    EXPECT_EQ(test_list.GetLength(), 6);

    test_list.DeleteAll('t');
    EXPECT_EQ(test_list.GetLength(), 4);
    EXPECT_EQ(test_list.Get(0), 'e');
    EXPECT_EQ(test_list.Get(3), '2');

    test_list.Clear();
    EXPECT_EQ(test_list.GetLength(), 0);
}

TEST_F(list_test, Find) {
    EXPECT_EQ(test_list.FindFirst('t'), 0);
    EXPECT_EQ(test_list.FindLast('t'), 3);
}

TEST_F(list_test, Reverse) {
    test_list.Reverse();
    EXPECT_EQ(test_list.Get(0), '3');
    EXPECT_EQ(test_list.Get(6), 't');
}

TEST_F(list_test, CopyAndExtend) {
    int old_length = test_list.GetLength();
    char_list new_list = test_list.Clone();
    EXPECT_EQ(old_length, new_list.GetLength());

    for (int i = 0; i < old_length; i++) {
        EXPECT_EQ(test_list.Get(i), new_list.Get(i));
    }

    new_list.Append('t');
    EXPECT_NE(old_length, new_list.GetLength());
    EXPECT_NE(test_list.FindLast('t'), new_list.FindLast('t'));

    test_list.Extend(new_list);
    EXPECT_EQ(old_length, test_list.GetLength() - new_list.GetLength());

    std::string test_string = "test123test123t";
    for (int i = 0; i < test_list.GetLength(); i++) {
        EXPECT_EQ(test_list.Get(i), test_string[i]);
    }
}