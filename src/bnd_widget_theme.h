#ifndef MRUBY_BND_WIDGET_THEME_H
#define MRUBY_BND_WIDGET_THEME_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

#include "bnd_common.h"

MRB_BND_EXTERN const struct mrb_data_type mrb_bnd_widget_theme_type;

MRB_BND_EXTERN void mrb_bnd_widget_theme_init(mrb_state *mrb, struct RClass *mod);
MRB_BND_EXTERN mrb_value mrb_bnd_widget_theme_value(mrb_state *mrb, BNDwidgetTheme theme);

#endif
