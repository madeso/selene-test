#include "test.h"

#include "selene.h"

namespace {
void StopScriptErrors(int sd, std::string message, std::exception_ptr ex) {
  if (ex) {
    std::rethrow_exception(ex);
  }
  else throw message;
}
}

namespace {
  struct Foo {
    int x;
    Foo(int x_) : x(x_) {}

    int DoubleAdd(int y) { return 2 * (x + y); }
    void SetX(int x_) { x = x_; }
  };
}

TEST(test_obj_readme) {
  sel::State state(true);
  state.HandleExceptionsWith(StopScriptErrors);

  Foo foo(2);

  state["foo"].SetObj(foo,
    "double_add", &Foo::DoubleAdd,
    "x", &Foo::x);

  state("test = foo.x()");
  int test = state["test"];
  if (test != 2) throw "failed to get 2";
  
  state("foo.set_x(4)");
  if(foo.x != 4) throw "failed to set_x";

  state("result = foo.double_add(3)");
  int result = state["result"];
  if(result != 14) throw "failed to add";
}
