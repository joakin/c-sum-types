#ifndef SUM_TYPE
#define SUM_TYPE VARIANT(Test_Variant, )
#define SUM_TYPE_NAME Test_Sum
#endif

#define JOINK(a, sep, b) a##sep##b
#define JOIN(a, sep, b) JOINK(a, sep, b)

#define VARIANT(name, fields) JOIN(SUM_TYPE_NAME, _Tag_, name),

typedef enum { SUM_TYPE } JOIN(SUM_TYPE_NAME, _, Tag);

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
  JOIN(SUM_TYPE_NAME, _, Tag) tag;
  union {
    SUM_TYPE
  };
} SUM_TYPE_NAME;

#ifndef Sum
#define Sum(type, variant, data)                                               \
  (type) {                                                                     \
    .tag = JOIN(JOIN(type, _, Tag), _, variant),                               \
    .variant = (JOIN(type, _, variant))data                                    \
  }
#endif

#undef FIELD
#undef VARIANT
#undef SUM_TYPE
#undef SUM_TYPE_NAME
