#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/value.h>

#include "oui_helper_macros.h"
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

void
mrb_bnd_widget_theme_init(mrb_state *mrb, struct RClass *mod)
{
  widget_theme_class = mrb_define_class_under(mrb, mod, "WidgetTheme", mrb->object_class);
  MRB_SET_INSTANCE_TT(widget_theme_class, MRB_TT_DATA);

  mrb_define_method(mrb, widget_theme_class, "initialize",            widget_theme_initialize,               MRB_ARGS_NONE());

  mrb_define_method(mrb, widget_theme_class, "outline_color",         widget_theme_outline_color_get,        MRB_ARGS_NONE());
  mrb_define_method(mrb, widget_theme_class, "item_color",            widget_theme_item_color_get,           MRB_ARGS_NONE());
  mrb_define_method(mrb, widget_theme_class, "inner_color",           widget_theme_inner_color_get,          MRB_ARGS_NONE());
  mrb_define_method(mrb, widget_theme_class, "inner_selected_color",  widget_theme_inner_selected_color_get, MRB_ARGS_NONE());
  mrb_define_method(mrb, widget_theme_class, "text_color",            widget_theme_text_color_get,           MRB_ARGS_NONE());
  mrb_define_method(mrb, widget_theme_class, "text_selected_color",   widget_theme_text_selected_color_get,  MRB_ARGS_NONE());
  mrb_define_method(mrb, widget_theme_class, "shade_top",             widget_theme_shade_top_get,            MRB_ARGS_NONE());
  mrb_define_method(mrb, widget_theme_class, "shade_down",            widget_theme_shade_down_get,           MRB_ARGS_NONE());

  mrb_define_method(mrb, widget_theme_class, "outline_color=",        widget_theme_outline_color_set,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, widget_theme_class, "item_color=",           widget_theme_item_color_set,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, widget_theme_class, "inner_color=",          widget_theme_inner_color_set,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, widget_theme_class, "inner_selected_color=", widget_theme_inner_selected_color_set, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, widget_theme_class, "text_color=",           widget_theme_text_color_set,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, widget_theme_class, "text_selected_color=",  widget_theme_text_selected_color_set,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, widget_theme_class, "shade_top=",            widget_theme_shade_top_set,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, widget_theme_class, "shade_down=",           widget_theme_shade_down_set,           MRB_ARGS_REQ(1));
}
