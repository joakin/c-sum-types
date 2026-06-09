#ifndef SUM_TYPE_NAME
#error "SUM_TYPE_NAME must be defined before including sum_type.h"
#endif

#ifndef SUM_TYPE
#error "SUM_TYPE must be defined before including sum_type.h"
#endif

#include <assert.h>

#define JOINK(a, sep, b) a##sep##b
#define JOIN(a, sep, b) JOINK(a, sep, b)
#define STRK(value) #value
#define STR(value) STRK(value)

#define VARIANT(name, fields) JOIN(SUM_TYPE_NAME, _Kind_, name),

typedef enum { SUM_TYPE } JOIN(SUM_TYPE_NAME, _, Kind);

#undef VARIANT
#define FIELD(type, name) type name;
#define VARIANT(name, fields)                                                  \
  typedef struct {                                                             \
    fields                                                                     \
  } JOIN(SUM_TYPE_NAME, _, name);

SUM_TYPE

#undef FIELD
#undef VARIANT
#define VARIANT(name, fields) JOIN(SUM_TYPE_NAME, _, name) name;

typedef struct {
  JOIN(SUM_TYPE_NAME, _, Kind) kind;
  union {
    SUM_TYPE
  };
} SUM_TYPE_NAME;

#undef VARIANT
#define VARIANT(name, fields)                                                  \
  static inline JOIN(SUM_TYPE_NAME, _, name) *                                 \
      JOIN(SUM_TYPE_NAME, _as_, name)(SUM_TYPE_NAME *sum) {                    \
    assert(sum->kind == JOIN(SUM_TYPE_NAME, _Kind_, name) &&                   \
           STR(JOIN(SUM_TYPE_NAME, _as_, name)) " called with wrong kind");    \
    return &sum->name;                                                         \
  }

SUM_TYPE

#undef VARIANT

#ifndef Sum
#define Sum(type, variant, data)                                               \
  (type) {                                                                     \
    .kind = JOIN(type, _Kind_, variant),                                       \
    .variant = (JOIN(type, _, variant))data                                    \
  }
#endif

#undef FIELD
#undef VARIANT
#undef SUM_TYPE
#undef SUM_TYPE_NAME
#undef STR
#undef STRK
