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
  struct Obj {
    std::string mydog;

    std::string dog() {
      return mydog;
    }

    void faildog(const std::string& dog) {
      if (dog != mydog) {
        throw std::runtime_error("dog is not dog");
      }
    }
  };
}

TEST(test_obj) {
  sel::State state(true);
  state.HandleExceptionsWith(StopScriptErrors);

  Obj obj;
  obj.mydog = "dog";

  state["obj"].SetObj(obj, "dog", &Obj::dog, "faildog", &Obj::faildog);

  state("res = obj.dog()");
  // state("res = obj:dog()");
  std::string res = state["res"];
  if (res != "dog") throw "failed to dog";

  // state("obj:faildog(\"dog\")"); // exception: dog is not dog (\x5\x1)
  state("obj.faildog(\"dog\")"); // [string "obj.faildog("dog")"]:1: bad argument #1 to 'faildog' (unregistered type expected, got string)
}
