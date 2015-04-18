#include <mruby.h>
#include <mruby/array.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/value.h>

#include "mrb_helper_macros.h"
#include "bnd_common.h"
#include "bnd_widget_theme.h"

static struct RClass *widget_theme_class;

static void
widget_theme_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    mrb_free(mrb, ptr);
  }
}

const struct mrb_data_type mrb_bnd_widget_theme_type = { "BNDwidgetTheme", widget_theme_free };

static inline BNDwidgetTheme*
get_widget_theme(mrb_state *mrb, mrb_value self)
{
  return (BNDwidgetTheme*)mrb_data_get_ptr(mrb, self, &mrb_bnd_widget_theme_type);
}

mrb_value
mrb_bnd_widget_theme_value(mrb_state *mrb, BNDwidgetTheme theme)
{
  BNDwidgetTheme *utheme;
  mrb_value result = mrb_obj_new(mrb, widget_theme_class, 0, NULL);
  utheme = (BNDwidgetTheme*)DATA_PTR(result);
  *utheme = theme;
  return result;
}

static mrb_value
widget_theme_initialize(mrb_state *mrb, mrb_value self)
{
  extmrb_data_cleanup(mrb, self, widget_theme_free);
  mrb_data_init(self, extmrb_malloc_setzero(mrb, sizeof(BNDwidgetTheme)), &mrb_bnd_widget_theme_type);
  return self;
}

static mrb_value
widget_theme_initialize_copy(mrb_state *mrb, mrb_value self)
{
  BNDwidgetTheme *theme;
  BNDwidgetTheme *other;
  mrb_get_args(mrb, "d", &other, &mrb_bnd_widget_theme_type);
  extmrb_data_cleanup(mrb, self, widget_theme_free);
  theme = mrb_malloc(mrb, sizeof(BNDwidgetTheme));
  memcpy(theme, other, sizeof(BNDwidgetTheme));
  mrb_data_init(self, theme, &mrb_bnd_widget_theme_type);
  return self;
}

base_DEF_ATTR_ACCESSOR_NVGcolor(widget_theme_outline_color, &mrb_bnd_widget_theme_type, BNDwidgetTheme, outlineColor);
base_DEF_ATTR_ACCESSOR_NVGcolor(widget_theme_item_color, &mrb_bnd_widget_theme_type, BNDwidgetTheme, itemColor);
base_DEF_ATTR_ACCESSOR_NVGcolor(widget_theme_inner_color, &mrb_bnd_widget_theme_type, BNDwidgetTheme, innerColor);
base_DEF_ATTR_ACCESSOR_NVGcolor(widget_theme_inner_selected_color, &mrb_bnd_widget_theme_type, BNDwidgetTheme, innerSelectedColor);
base_DEF_ATTR_ACCESSOR_NVGcolor(widget_theme_text_color, &mrb_bnd_widget_theme_type, BNDwidgetTheme, textColor);
base_DEF_ATTR_ACCESSOR_NVGcolor(widget_theme_text_selected_color, &mrb_bnd_widget_theme_type, BNDwidgetTheme, textSelectedColor);
base_DEF_ATTR_ACCESSOR_i(widget_theme_shade_top, &mrb_bnd_widget_theme_type, BNDwidgetTheme, shadeTop);
base_DEF_ATTR_ACCESSOR_i(widget_theme_shade_down, &mrb_bnd_widget_theme_type, BNDwidgetTheme, shadeDown);

static mrb_value
widget_theme_inner_colors(mrb_state *mrb, mrb_value self)
{
  BNDwidgetTheme *theme;
  mrb_int state;
  mrb_bool flip_active;
  NVGcolor shade_top;
  NVGcolor shade_down;
  mrb_value result[2];
  mrb_get_args(mrb, "ib", &state, &flip_active);
  theme = get_widget_theme(mrb, self);
  bndInnerColors(&shade_top, &shade_down, theme, state, flip_active);
  result[0] = mrb_nvg_color_value(mrb, shade_top);
  result[1] = mrb_nvg_color_value(mrb, shade_down);
  return mrb_ary_new_from_values(mrb, 2, result);
}

static mrb_value
widget_theme_text_color(mrb_state *mrb, mrb_value self)
{
  BNDwidgetTheme *theme;
  mrb_int state;
  mrb_get_args(mrb, "i", &state);
  theme = get_widget_theme(mrb, self);
  return mrb_nvg_color_value(mrb, bndTextColor(theme, state));
}

void
mrb_bnd_widget_theme_init(mrb_state *mrb, struct RClass *mod)
{
  widget_theme_class = mrb_define_class_under(mrb, mod, "WidgetTheme", mrb->object_class);
  MRB_SET_INSTANCE_TT(widget_theme_class, MRB_TT_DATA);
  mrb_define_method(mrb, widget_theme_class, "initialize",            widget_theme_initialize,               MRB_ARGS_NONE());
  mrb_define_method(mrb, widget_theme_class, "initialize_copy",       widget_theme_initialize_copy,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, widget_theme_class, "outline_color",         widget_theme_outline_color_get,        MRB_ARGS_NONE());
  mrb_define_method(mrb, widget_theme_class, "outline_color=",        widget_theme_outline_color_set,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, widget_theme_class, "item_color",            widget_theme_item_color_get,           MRB_ARGS_NONE());
  mrb_define_method(mrb, widget_theme_class, "item_color=",           widget_theme_item_color_set,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, widget_theme_class, "inner_color",           widget_theme_inner_color_get,          MRB_ARGS_NONE());
  mrb_define_method(mrb, widget_theme_class, "inner_color=",          widget_theme_inner_color_set,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, widget_theme_class, "inner_selected_color",  widget_theme_inner_selected_color_get, MRB_ARGS_NONE());
  mrb_define_method(mrb, widget_theme_class, "inner_selected_color=", widget_theme_inner_selected_color_set, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, widget_theme_class, "text_color",            widget_theme_text_color_get,           MRB_ARGS_NONE());
  mrb_define_method(mrb, widget_theme_class, "text_color=",           widget_theme_text_color_set,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, widget_theme_class, "text_selected_color",   widget_theme_text_selected_color_get,  MRB_ARGS_NONE());
  mrb_define_method(mrb, widget_theme_class, "text_selected_color=",  widget_theme_text_selected_color_set,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, widget_theme_class, "shade_top",             widget_theme_shade_top_get,            MRB_ARGS_NONE());
  mrb_define_method(mrb, widget_theme_class, "shade_top=",            widget_theme_shade_top_set,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, widget_theme_class, "shade_down",            widget_theme_shade_down_get,           MRB_ARGS_NONE());
  mrb_define_method(mrb, widget_theme_class, "shade_down=",           widget_theme_shade_down_set,           MRB_ARGS_REQ(1));

  mrb_define_method(mrb, widget_theme_class, "inner_colors",          widget_theme_inner_colors,             MRB_ARGS_REQ(4));
  mrb_define_method(mrb, widget_theme_class, "text_color",            widget_theme_text_color,               MRB_ARGS_REQ(1));
}
