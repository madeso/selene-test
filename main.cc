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
  catch (std::exception& err) {
    std::cout << err.what() << std::endl;
  }
  catch (const std::string& err) {
    std::cout << err << std::endl;
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

TestPtr test_basic();
TestPtr test_function();
TestPtr test_string_passing();
TestPtr test_obj();

void main() {
  run_test(test_basic);
  run_test(test_function);
  run_test(test_string_passing);
  run_test(test_obj);

  std::cout << fails << " fails of " << tests << " tests.";
}
