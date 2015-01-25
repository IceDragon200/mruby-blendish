#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/value.h>

#include "oui_helper_macros.h"
#include "bnd_common.h"
#include "bnd_node_theme.h"

static struct RClass *node_theme_class;

static void
node_theme_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    mrb_free(mrb, ptr);
  }
}

const struct mrb_data_type mrb_bnd_node_theme_type = { "BNDnodeTheme", node_theme_free };

mrb_value
mrb_bnd_node_theme_value(mrb_state *mrb, BNDnodeTheme theme)
{
  BNDnodeTheme *utheme;
  mrb_value result = mrb_obj_new(mrb, node_theme_class, 0, NULL);
  utheme = (BNDnodeTheme*)DATA_PTR(result);
  *utheme = theme;
  return result;
}

static mrb_value
node_theme_initialize(mrb_state *mrb, mrb_value self)
{
  return self;
}

base_DEF_ATTR_ACCESSOR_NVGcolor(node_theme_node_selected_color, &mrb_bnd_node_theme_type, BNDnodeTheme, nodeSelectedColor);
base_DEF_ATTR_ACCESSOR_NVGcolor(node_theme_wires_color, &mrb_bnd_node_theme_type, BNDnodeTheme, wiresColor);
base_DEF_ATTR_ACCESSOR_NVGcolor(node_theme_text_selected_color, &mrb_bnd_node_theme_type, BNDnodeTheme, textSelectedColor);
base_DEF_ATTR_ACCESSOR_NVGcolor(node_theme_active_node_color, &mrb_bnd_node_theme_type, BNDnodeTheme, activeNodeColor);
base_DEF_ATTR_ACCESSOR_NVGcolor(node_theme_wire_select_color, &mrb_bnd_node_theme_type, BNDnodeTheme, wireSelectColor);
base_DEF_ATTR_ACCESSOR_NVGcolor(node_theme_node_backdrop_color, &mrb_bnd_node_theme_type, BNDnodeTheme, nodeBackdropColor);
base_DEF_ATTR_ACCESSOR_i(node_theme_noodle_curving, &mrb_bnd_node_theme_type, BNDnodeTheme, noodleCurving);

void
mrb_bnd_node_theme_init(mrb_state *mrb, struct RClass *mod)
{
  node_theme_class = mrb_define_class_under(mrb, mod, "NodeTheme", mrb->object_class);
  MRB_SET_INSTANCE_TT(node_theme_class, MRB_TT_DATA);

  mrb_define_method(mrb, node_theme_class, "initialize",          node_theme_initialize, MRB_ARGS_NONE());

  mrb_define_method(mrb, node_theme_class, "node_selected_color", node_theme_node_selected_color_get, MRB_ARGS_NONE());
  mrb_define_method(mrb, node_theme_class, "wires_color",         node_theme_wires_color_get, MRB_ARGS_NONE());
  mrb_define_method(mrb, node_theme_class, "text_selected_color", node_theme_text_selected_color_get, MRB_ARGS_NONE());
  mrb_define_method(mrb, node_theme_class, "active_node_color",   node_theme_active_node_color_get, MRB_ARGS_NONE());
  mrb_define_method(mrb, node_theme_class, "wire_select_color",   node_theme_wire_select_color_get, MRB_ARGS_NONE());
  mrb_define_method(mrb, node_theme_class, "node_backdrop_color", node_theme_node_backdrop_color_get, MRB_ARGS_NONE());
  mrb_define_method(mrb, node_theme_class, "noodle_curving",      node_theme_noodle_curving_get, MRB_ARGS_NONE());

  mrb_define_method(mrb, node_theme_class, "node_selected_color=", node_theme_node_selected_color_set, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, node_theme_class, "wires_color=",         node_theme_wires_color_set, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, node_theme_class, "text_selected_color=", node_theme_text_selected_color_set, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, node_theme_class, "active_node_color=",   node_theme_active_node_color_set, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, node_theme_class, "wire_select_color=",   node_theme_wire_select_color_set, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, node_theme_class, "node_backdrop_color=", node_theme_node_backdrop_color_set, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, node_theme_class, "noodle_curving=",      node_theme_noodle_curving_set, MRB_ARGS_REQ(1));
}

