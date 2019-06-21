/*
** mrb_probe.c - Probe class
**
** Copyright (c) Uchio Kondo 2019
**
** See Copyright Notice in LICENSE
*/

#include <mruby.h>
#include <mruby/data.h>
#include "mrb_probe.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  char *str;
  int len;
} mrb_probe_data;

static const struct mrb_data_type mrb_probe_data_type = {
  "mrb_probe_data", mrb_free,
};

static mrb_value mrb_probe_init(mrb_state *mrb, mrb_value self)
{
  mrb_probe_data *data;
  char *str;
  int len;

  data = (mrb_probe_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_probe_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "s", &str, &len);
  data = (mrb_probe_data *)mrb_malloc(mrb, sizeof(mrb_probe_data));
  data->str = str;
  data->len = len;
  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_probe_hello(mrb_state *mrb, mrb_value self)
{
  mrb_probe_data *data = DATA_PTR(self);

  return mrb_str_new(mrb, data->str, data->len);
}

static mrb_value mrb_probe_hi(mrb_state *mrb, mrb_value self)
{
  return mrb_str_new_cstr(mrb, "hi!!");
}

void mrb_mruby_probe_gem_init(mrb_state *mrb)
{
  struct RClass *probe;
  probe = mrb_define_module(mrb, "Probe");
  mrb_define_module_function(mrb, probe, "initialize", mrb_probe_init, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, probe, "hello", mrb_probe_hello, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, probe, "hi", mrb_probe_hi, MRB_ARGS_NONE());
  DONE;
}

void mrb_mruby_probe_gem_final(mrb_state *mrb)
{
}
