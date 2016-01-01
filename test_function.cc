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
  bool called_function = false;

  void func() {
    called_function = true;
  }

  int meaningoflife(bool life) {
    return life ? 42 : -1;
  }
}

TEST(test_function) {
  sel::State state(true);
  state.HandleExceptionsWith(StopScriptErrors);

  state["func"] = &func;
  state["ans"] = &meaningoflife;

  state("func()");
  if (called_function == false) throw "didn't call function";

  state("meaning = ans(true)");
  int meaning = state["meaning"];
  if (meaning != 42) throw "failed at meaning of life";
}
