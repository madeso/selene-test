#include "test.h"

#include "selene.h"

void SilenceScriptErrors(int sd, std::string message, std::exception_ptr ex) {
}

TEST(test_basic) {
  sel::State state(true);
  state.HandleExceptionsWith(SilenceScriptErrors);

  if (state("res = 1+") != false) throw "expected syntax error";

  if (state("res = 1+2") != true) throw "expected return true";

  int res = state["res"];
  if (res != 3) throw "expected value 3";
}
