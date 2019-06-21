/*
** mrb_probe.c - Probe class
**
** Copyright (c) Uchio Kondo 2019
**
** See Copyright Notice in LICENSE
*/

#include <stdio.h>
#include <sys/sdt.h>

#include <mruby.h>
#include <mruby/error.h>
#include <mruby/string.h>
#include "mrb_probe.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

static mrb_value mrb_probe_do(mrb_state *mrb, mrb_value self)
{
  mrb_value arg0;
  mrb_get_args(mrb, "o", &arg0);

  if(mrb_fixnum_p(arg0)) {
    /* TODO: app name and probe should be overrided by build_config as cc.defines = ... */
    DTRACE_PROBE1(mruby-probe, mruby, mrb_fixnum(arg0));
  } else if (mrb_string_p(arg0)) {
    DTRACE_PROBE1(mruby-probe, mruby, mrb_str_to_cstr(mrb, arg0));
  } else {
    char buf[32];
    if(snprintf(buf, 32, "mrb_value(%p)", arg0.value.p) < -1) {
      mrb_sys_fail(mrb, "Failed to etting mrb_value pointer");
    } else {
      DTRACE_PROBE1(mruby-probe, mruby, buf);
    }
  }

  return mrb_nil_value();
}

void mrb_mruby_probe_gem_init(mrb_state *mrb)
{
  struct RClass *probe;
  probe = mrb_define_module(mrb, "Probe");
  mrb_define_module_function(mrb, probe, "probe", mrb_probe_do, MRB_ARGS_REQ(1));
  DONE;
}

void mrb_mruby_probe_gem_final(mrb_state *mrb)
{
}
