#ifndef MRUBY_BND_NODE_THEME_H
#define MRUBY_BND_NODE_THEME_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

extern const struct mrb_data_type mrb_bnd_node_theme_type;

void mrb_bnd_node_theme_init(mrb_state *mrb, struct RClass *mod);
mrb_value mrb_bnd_node_theme_value(mrb_state *mrb, BNDnodeTheme theme);

#endif
