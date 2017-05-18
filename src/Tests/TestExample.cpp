//
// Created by Silt on 23.04.2017.
//

#include "TestExample.h"

SETUP(TestExample){
    REG_TEST(test1, 1, "Test1 Brief");
    REG_TEST(test2, 2, "Test2 Brief");
    REG_TEST(test3, 3, "Test3 Brief");
};

BEFORE_TC(TestExample){
    testint = 56789;
    return 1;
};

AFTER_TC(TestExample){
    std::cout << "Der TestCase hat fertig" <<std::endl;
    return 1;
};

BEFORE(TestExample){
    std::cout << "Passiert vor jedem Test"  <<std::endl;
    return 1;
};

AFTER(TestExample){
    std::cout << "Passiert nach jedem Test" <<std::endl;
    return 1;
};

TEST_IMPL(TestExample, test1){
    std::cout << "Hier ist Test1, guckmal wurde gaendert: " << testint<<std::endl;
    return TEST_PASSED;
}

TEST_IMPL(TestExample, test2){
    std::cout << "Hier ist Test2 " << std::endl;
    return TEST_WARNING;
}

TEST_IMPL(TestExample, test3){
    std::cout << "Hier ist Test3 " << std::endl;
    return TEST_FAILED;
}
