#include "test.h"

#include <functional>
#include <iostream>

namespace {

int fails = 0;
int tests = 0;

void print_exception() {
  try {
    throw;
  }
  catch (std::runtime_error& err) {
    std::cout << err.what() << std::endl;
  }
  catch (const char* const err) {
    std::cout << err << std::endl;
  }
  catch (...) {
    std::cout << "Unknown error" << std::endl;
  }
}
 
void run_test(std::function<TestPtr ()> f) {
  ++tests;
  try {
    TestPtr test = f();
    std::cout << test->name();
    test->test();
    std::cout << " Passed." << std::endl;
  }
  catch (...) {
    std::cout << " Failed." << std::endl;
    ++fails;
    print_exception();
    std::cout << std::endl;
  }
}

}

TestPtr basic_test();

void main() {
  run_test(basic_test);
}
