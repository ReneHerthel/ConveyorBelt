#include <iostream>
#include <list>
#include "TestFramework.h"
#include "TestCase.h"
#include "TestExample.h"

int main() {
    TestCase* tc = new TestExample();
    tc->run(FAILED, "F:\\log_test.txt");
}
