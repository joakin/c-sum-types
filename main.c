#include <inttypes.h>
#include <stdio.h>

#define SUM_TYPE_NAME Msg
#define SUM_TYPE                                                               \
  VARIANT(Increment, )                                                         \
  VARIANT(Decrement, )                                                         \
  VARIANT(Set_Name, FIELD(char *, name))
#include "sum_type.h"

void dbg_msg(Msg *msg) {
  switch (msg->tag) {
  case Msg_Tag_Increment:
    printf("Increment\n");
    break;
  case Msg_Tag_Decrement:
    printf("Decrement\n");
    break;
  case Msg_Tag_Set_Name:
    printf("Set_Name %s\n", msg->Set_Name.name);
    break;
  }
}

int main(int32_t argc, char *argv[]) {
  printf("Hello\n\n");

  Msg msg = (Msg){.tag = Msg_Tag_Increment, .Increment = {}};
  Msg msg2 = (Msg){.tag = Msg_Tag_Set_Name, .Set_Name = {.name = "Banana"}};

  Msg msg5 = Sum(Msg, Set_Name, {.name = "Banana"});
  Msg msg6 = Sum(Msg, Increment, {});

  dbg_msg(&msg);
  dbg_msg(&msg2);
}
