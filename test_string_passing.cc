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
  std::string dog() {
    return "dog";
  }

  bool getdog(const std::string& dog) {
    return dog == "dog";
  }
}

TEST(test_string_passing) {
  sel::State state(true);
  state.HandleExceptionsWith(StopScriptErrors);

  state["dog"] = &dog;
  state["getdog"] = &getdog;

  state("res = dog()");
  std::string res = state["res"];
  if (res != "dog") throw "failed to dog";

  state("isdog = getdog(\"dog\")");
  bool isdog = state["isdog"];
  if (isdog != true) throw "failed to isdog";
}
