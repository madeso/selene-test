#ifndef TEST_H_
#define TEST_H_

#include <string>
#include <memory>

class Test {
public:
  ~Test() {}

  virtual void test() = 0;
  virtual std::string name() = 0;
};

typedef std::shared_ptr<Test> TestPtr;

#define TEST(NAME) class class_##NAME : public Test { std::string name() override {return #NAME;} void test() override; }; TestPtr NAME() { TestPtr t(new class_##NAME()); return t; } void class_##NAME::test()

#endif
