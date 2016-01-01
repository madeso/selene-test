#include "test.h"

#include "selene.h"

#include <sstream>
#include <string>

namespace {
void StopScriptErrors(int sd, std::string message, std::exception_ptr ex) {
  if (ex) {
    std::rethrow_exception(ex);
  }
  else throw message;
}
}

namespace {
  std::string last_print;
  void CustomPrintFunction(const std::string& str) {
    last_print = str;
  }

  int custom_print_function_glue(lua_State* L) {
    int nargs = lua_gettop(L);
    
    const std::string sep = " ";
    
    std::ostringstream ss;
    bool first = true;

    for (int i = 1; i <= nargs; i++) {
      const char* c = lua_tostring(L, i);
      const std::string str = c ? c : "<nil>";
      if (first) first = false;
      else ss << sep;
      ss << str;
    }

    CustomPrintFunction(ss.str());

    return 0;
  }

  int luaopen_printlib(lua_State* L) {
    static const luaL_Reg printlib[] = { { "custom_print", custom_print_function_glue },{ NULL, NULL } };

    luaL_newlib(L, printlib);
    return 1;
  }

  class CustomPrintFunctorGlue : public sel::BaseFun {
    int Apply(lua_State* L) override {
      return custom_print_function_glue(L);
    }
  };
}

TEST(test_custom_print) {
  sel::State state(true);
  state.HandleExceptionsWith(StopScriptErrors);

  state.OpenLib("printlib", &luaopen_printlib);
  state("require \"printlib\"");
  state("print = printlib.custom_print");

  state("print(\"dog\", 1)");
  if (last_print != "dog 1") throw "failed to print dog 1";

  // todo: try to bind CustomPrintFunctorGlue
  // state["myprint"] = CustomPrintFunctorGlue(); // only accepts proper functors that will be rebound/remapped to lua arguments/types
  // state("myprint(\"cat\", 2)");
  // if (last_print != "cat 2") throw "failed to print cat 2";
}
