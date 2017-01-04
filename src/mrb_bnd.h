#ifndef MRUBY_BND_H
#define MRUBY_BND_H

#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include "bnd_common.h"

MRB_BND_EXTERN void mrb_bnd_init(mrb_state *mrb, struct RClass *mod);

#endif
