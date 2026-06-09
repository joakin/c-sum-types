#include <inttypes.h>
#include <stdio.h>

#define SUM_TYPE_NAME Msg
#define SUM_TYPE                                                               \
  VARIANT(Increment, )                                                         \
  VARIANT(Decrement, )                                                         \
  VARIANT(Set_Name, FIELD(char *, name))
#include "sum_type.h"

void dbg_msg(Msg *msg) {
  if (msg->kind == Msg_Kind_Set_Name) {
    printf("checked name: %s\n", Msg_as_Set_Name(msg)->name);
  }

  switch (msg->kind) {
  case Msg_Kind_Increment:
    printf("Increment\n");
    break;
  case Msg_Kind_Decrement:
    printf("Decrement\n");
    break;
  case Msg_Kind_Set_Name:
    printf("Set_Name %s\n", Msg_as_Set_Name(msg)->name);
    break;
  }
}

int main(int32_t argc, char *argv[]) {
  printf("Hello\n\n");

  Msg msg = Sum(Msg, Increment, {});
  Msg msg2 = Sum(Msg, Set_Name, {.name = "Banana"});
  Msg msg3 = Sum(Msg, Decrement, {});

  dbg_msg(&msg);
  dbg_msg(&msg2);
  dbg_msg(&msg3);
}
