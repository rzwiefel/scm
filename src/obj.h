#ifndef OBJ_H
#define OBJ_H

typedef struct obj_t obj_t;

typedef obj_t *(*fn_eval)(obj_t *expr, obj_t **env);
typedef int (*fn_equal)(obj_t *a, obj_t *b);
typedef void (*fn_write)(obj_t *o);
typedef void (*fn_mark)(obj_t *o);
typedef void (*fn_free)(obj_t *o);

typedef struct {
  fn_eval  eval;
  fn_equal equal;
  fn_write write;
  fn_mark  mark;
  fn_free  free;
} iobj_t;

struct obj_t {
  iobj_t *vtable;
};

obj_t *obj_eval(obj_t *expr, obj_t **env);
int obj_equal(obj_t *a, obj_t *b);
void obj_write(obj_t *o);
void obj_mark(obj_t *o);
void obj_free(obj_t *o);

#define defn(name) static obj_t *name(obj_t *o, obj_t **env)

#endif
