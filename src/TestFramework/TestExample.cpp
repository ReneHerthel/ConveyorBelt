//
// Created by Silt on 23.04.2017.
//

#include <iostream>
#include "TestExample.h"

SETUP(TestExample){
    SET_TEST_CASE_ID(1);
    SET_TEST_CASE_BRIEF("This is an example TestCase");
    REG_TEST(&test1, 1, "Test1 Brief");
    REG_TEST(&test2, 2, "Test2 Brief");
    REG_TEST(&test3, 4, "Test3 Brief");
};

BEFORE_TC(TestExample){
    return 1;
};

AFTER_TC(TestExample){
    return 1;
};

BEFORE(TestExample){
    return 1;
};

AFTER(TestExample){
    return 1;
};

TEST_IMPL(TestExample, test1){
    std::cout << "Hier ist Test1 " << std::endl;
    return PASSED;
}

TEST_IMPL(TestExample, test2){
    std::cout << "Hier ist Test2 " << std::endl;
    return WARNING;
}

TEST_IMPL(TestExample, test3){
    std::cout << "Hier ist Test3 " << std::endl;
    return FAILED;
}