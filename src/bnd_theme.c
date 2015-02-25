#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/value.h>

#include "mrb_helper_macros.h"
#include "bnd_common.h"
#include "bnd_theme.h"
#include "bnd_node_theme.h"
#include "bnd_widget_theme.h"

static struct RClass *theme_class;

static void
theme_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    mrb_free(mrb, ptr);
  }
}

const struct mrb_data_type mrb_bnd_theme_type = { "BNDtheme", theme_free };

mrb_value
mrb_bnd_theme_value(mrb_state *mrb, BNDtheme theme)
{
  BNDtheme *utheme;
  mrb_value result = mrb_obj_new(mrb, theme_class, 0, NULL);
  utheme = (BNDtheme*)DATA_PTR(result);
  *utheme = theme;
  return result;
}

static mrb_value
theme_initialize(mrb_state *mrb, mrb_value self)
{
  extmrb_data_cleanup(mrb, self, theme_free);
  mrb_data_init(self, extmrb_malloc_setzero(mrb, sizeof(BNDtheme)), &mrb_bnd_theme_type);
  return self;
}

static mrb_value
theme_initialize_copy(mrb_state *mrb, mrb_value self)
{
  BNDtheme *theme;
  BNDtheme *other;
  mrb_get_args(mrb, "d", &other, &mrb_bnd_theme_type);
  extmrb_data_cleanup(mrb, self, theme_free);
  theme = mrb_malloc(mrb, sizeof(BNDtheme));
  memcpy(theme, other, sizeof(BNDtheme));
  mrb_data_init(self, theme, &mrb_bnd_theme_type);
  return self;
}

base_DEF_ATTR_ACCESSOR_NVGcolor(theme_background_color, &mrb_bnd_theme_type, BNDtheme, backgroundColor);
base_DEF_ATTR_ACCESSOR_BNDwidgetTheme(theme_regular_theme, &mrb_bnd_theme_type, BNDtheme, regularTheme);
base_DEF_ATTR_ACCESSOR_BNDwidgetTheme(theme_tool_theme, &mrb_bnd_theme_type, BNDtheme, toolTheme);
base_DEF_ATTR_ACCESSOR_BNDwidgetTheme(theme_radio_theme, &mrb_bnd_theme_type, BNDtheme, radioTheme);
base_DEF_ATTR_ACCESSOR_BNDwidgetTheme(theme_text_field_theme, &mrb_bnd_theme_type, BNDtheme, textFieldTheme);
base_DEF_ATTR_ACCESSOR_BNDwidgetTheme(theme_option_theme, &mrb_bnd_theme_type, BNDtheme, optionTheme);
base_DEF_ATTR_ACCESSOR_BNDwidgetTheme(theme_choice_theme, &mrb_bnd_theme_type, BNDtheme, choiceTheme);
base_DEF_ATTR_ACCESSOR_BNDwidgetTheme(theme_number_field_theme, &mrb_bnd_theme_type, BNDtheme, numberFieldTheme);
base_DEF_ATTR_ACCESSOR_BNDwidgetTheme(theme_slider_theme, &mrb_bnd_theme_type, BNDtheme, sliderTheme);
base_DEF_ATTR_ACCESSOR_BNDwidgetTheme(theme_scroll_bar_theme, &mrb_bnd_theme_type, BNDtheme, scrollBarTheme);
base_DEF_ATTR_ACCESSOR_BNDwidgetTheme(theme_tooltip_theme, &mrb_bnd_theme_type, BNDtheme, tooltipTheme);
base_DEF_ATTR_ACCESSOR_BNDwidgetTheme(theme_menu_theme, &mrb_bnd_theme_type, BNDtheme, menuTheme);
base_DEF_ATTR_ACCESSOR_BNDwidgetTheme(theme_menu_item_theme, &mrb_bnd_theme_type, BNDtheme, menuItemTheme);
base_DEF_ATTR_ACCESSOR_BNDnodeTheme(theme_node_theme, &mrb_bnd_theme_type, BNDtheme, nodeTheme);

void
mrb_bnd_theme_init(mrb_state *mrb, struct RClass *mod)
{
  theme_class = mrb_define_class_under(mrb, mod, "Theme", mrb->object_class);
  MRB_SET_INSTANCE_TT(theme_class, MRB_TT_DATA);
  mrb_define_method(mrb, theme_class, "initialize",          theme_initialize,             MRB_ARGS_NONE());
  mrb_define_method(mrb, theme_class, "initialize_copy",     theme_initialize_copy,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, theme_class, "background_color",    theme_background_color_get,   MRB_ARGS_NONE());
  mrb_define_method(mrb, theme_class, "background_color=",   theme_background_color_set,   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, theme_class, "regular_theme",       theme_regular_theme_get,      MRB_ARGS_NONE());
  mrb_define_method(mrb, theme_class, "regular_theme=",      theme_regular_theme_set,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, theme_class, "tool_theme",          theme_tool_theme_get,         MRB_ARGS_NONE());
  mrb_define_method(mrb, theme_class, "tool_theme=",         theme_tool_theme_set,         MRB_ARGS_REQ(1));
  mrb_define_method(mrb, theme_class, "radio_theme",         theme_radio_theme_get,        MRB_ARGS_NONE());
  mrb_define_method(mrb, theme_class, "radio_theme=",        theme_radio_theme_set,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, theme_class, "text_field_theme",    theme_text_field_theme_get,   MRB_ARGS_NONE());
  mrb_define_method(mrb, theme_class, "text_field_theme=",   theme_text_field_theme_set,   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, theme_class, "option_theme",        theme_option_theme_get,       MRB_ARGS_NONE());
  mrb_define_method(mrb, theme_class, "option_theme=",       theme_option_theme_set,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, theme_class, "choice_theme",        theme_choice_theme_get,       MRB_ARGS_NONE());
  mrb_define_method(mrb, theme_class, "choice_theme=",       theme_choice_theme_set,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, theme_class, "number_field_theme",  theme_number_field_theme_get, MRB_ARGS_NONE());
  mrb_define_method(mrb, theme_class, "number_field_theme=", theme_number_field_theme_set, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, theme_class, "slider_theme",        theme_slider_theme_get,       MRB_ARGS_NONE());
  mrb_define_method(mrb, theme_class, "slider_theme=",       theme_slider_theme_set,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, theme_class, "scroll_bar_theme",    theme_scroll_bar_theme_get,   MRB_ARGS_NONE());
  mrb_define_method(mrb, theme_class, "scroll_bar_theme=",   theme_scroll_bar_theme_set,   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, theme_class, "tooltip_theme",       theme_tooltip_theme_get,      MRB_ARGS_NONE());
  mrb_define_method(mrb, theme_class, "tooltip_theme=",      theme_tooltip_theme_set,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, theme_class, "menu_theme",          theme_menu_theme_get,         MRB_ARGS_NONE());
  mrb_define_method(mrb, theme_class, "menu_theme=",         theme_menu_theme_set,         MRB_ARGS_REQ(1));
  mrb_define_method(mrb, theme_class, "menu_item_theme",     theme_menu_item_theme_get,    MRB_ARGS_NONE());
  mrb_define_method(mrb, theme_class, "menu_item_theme=",    theme_menu_item_theme_set,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, theme_class, "node_theme",          theme_node_theme_get,         MRB_ARGS_NONE());
  mrb_define_method(mrb, theme_class, "node_theme=",         theme_node_theme_set,         MRB_ARGS_REQ(1));
}
