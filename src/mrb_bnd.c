#include <mruby.h>
#include <mruby/array.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/string.h>
#include <mruby/value.h>

#include "mrb_bnd.h"
#include "bnd_common.h"
#include "bnd_widget_theme.h"
#include "bnd_node_theme.h"
#include "bnd_theme.h"

#include "mrb_helper_macros.h"

static struct RClass *oui_module;
static struct RClass *bnd_module;
static struct RClass *bnd_ctx_class;
static struct RClass *bnd_icon_module;

static inline char*
maybe_string(mrb_state *mrb, mrb_value str)
{
  if (mrb_nil_p(str)) {
    return NULL;
  }
  return mrb_str_to_cstr(mrb, str);
}

static mrb_value
bnd_set_theme(mrb_state *mrb, mrb_value self)
{
  BNDtheme *theme;
  mrb_get_args(mrb, "d", &theme, &mrb_bnd_theme_type);
  bndSetTheme(*theme);
  return self;
}

static mrb_value
bnd_get_theme(mrb_state *mrb, mrb_value self)
{
  return mrb_bnd_theme_value(mrb, *bndGetTheme());
}

nd_DEF_FUNC_N1(bnd_set_icon_image, bndSetIconImage, "i", mrb_int);
nd_DEF_FUNC_N1(bnd_set_font, bndSetFont, "i", mrb_int);

static mrb_value
bnd_label(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_int iconid;
  mrb_value label;
  mrb_get_args(mrb, "dffffio",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &iconid, &label);
  bndLabel(ctx, x, y, w, h, iconid, maybe_string(mrb, label));
  return self;
}

static mrb_value
bnd_tool_button(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_int flags;
  mrb_int state;
  mrb_int iconid;
  mrb_value label;
  mrb_get_args(mrb, "dffffiiio",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &flags, &state,
                    &iconid, &label);
  bndToolButton(ctx, x, y, w, h, flags, state, iconid, maybe_string(mrb, label));
  return self;
}

static mrb_value
bnd_radio_button(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_int flags;
  mrb_int state;
  mrb_int iconid;
  mrb_value label;
  mrb_get_args(mrb, "dffffiiio",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &flags, &state,
                    &iconid, &label);
  bndRadioButton(ctx, x, y, w, h, flags, state, iconid, maybe_string(mrb, label));
  return self;
}

static mrb_value
bnd_text_field_text_position(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_int iconid;
  mrb_value text;
  mrb_int px;
  mrb_int py;
  mrb_get_args(mrb, "dffffioii",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &iconid, &text,
                    &px, &py);
  return mrb_fixnum_value(bndTextFieldTextPosition(ctx, x, y, w, h, iconid, maybe_string(mrb, text), px, py));
}

static mrb_value
bnd_text_field(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_int flags;
  mrb_int state;
  mrb_int iconid;
  mrb_value text;
  mrb_int cbegin;
  mrb_int cend;
  mrb_get_args(mrb, "dffffiiioii",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &flags, &state, &iconid,
                    &text, &cbegin, &cend);
  bndTextField(ctx, x, y, w, h, flags, state, iconid, maybe_string(mrb, text), cbegin, cend);
  return self;
}

static mrb_value
bnd_option_button(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_int state;
  mrb_value label;
  mrb_get_args(mrb, "dffffio",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &state,
                    &label);
  bndOptionButton(ctx, x, y, w, h, state, maybe_string(mrb, label));
  return self;
}

static mrb_value
bnd_choice_button(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_int flags;
  mrb_int state;
  mrb_int iconid;
  mrb_value label;
  mrb_get_args(mrb, "dffffiiio",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &flags, &state, &iconid,
                    &label);
  bndChoiceButton(ctx, x, y, w, h, flags, state, iconid, maybe_string(mrb, label));
  return self;
}

static mrb_value
bnd_color_button(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_int flags;
  NVGcolor *color;
  mrb_get_args(mrb, "dffffid",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &flags,
                    &color, &mrb_nvg_color_type);
  bndColorButton(ctx, x, y, w, h, flags, *color);
  return self;
}

static mrb_value
bnd_number_field(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_int flags;
  mrb_int state;
  mrb_value label;
  mrb_value value;
  mrb_get_args(mrb, "dffffiioo",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &flags, &state,
                    &label, &value);
  bndNumberField(ctx, x, y, w, h, flags, state, maybe_string(mrb, label), maybe_string(mrb, value));
  return self;
}

static mrb_value
bnd_slider(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_int flags;
  mrb_int state;
  mrb_float progress;
  mrb_value label;
  mrb_value value;
  mrb_get_args(mrb, "dffffiifoo",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &flags, &state,
                    &progress,
                    &label, &value);
  bndSlider(ctx, x, y, w, h, flags, state, progress, maybe_string(mrb, label), maybe_string(mrb, value));
  return self;
}

static mrb_value
bnd_scroll_bar(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_int state;
  mrb_float offset;
  mrb_float size;
  mrb_get_args(mrb, "dffffiff",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &state,
                    &offset, &size);
  bndScrollBar(ctx, x, y, w, h, state, offset, size);
  return self;
}

static mrb_value
bnd_menu_background(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_int flags;
  mrb_get_args(mrb, "dffffi",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &flags);
  bndMenuBackground(ctx, x, y, w, h, flags);
  return self;
}

static mrb_value
bnd_menu_label(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_int iconid;
  mrb_value label;
  mrb_get_args(mrb, "dffffio",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &iconid,
                    &label);
  bndMenuLabel(ctx, x, y, w, h, iconid, maybe_string(mrb, label));
  return self;
}

static mrb_value
bnd_menu_item(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_int state;
  mrb_int iconid;
  mrb_value label;
  mrb_get_args(mrb, "dffffiio",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &state, &iconid,
                    &label);
  bndMenuItem(ctx, x, y, w, h, state, iconid, maybe_string(mrb, label));
  return self;
}

static mrb_value
bnd_tooltip_background(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_get_args(mrb, "dffff",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h);
  bndTooltipBackground(ctx, x, y, w, h);
  return self;
}

static mrb_value
bnd_node_port(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_int state;
  NVGcolor *color;
  mrb_get_args(mrb, "dffid",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y,
                    &state,
                    &color, &mrb_nvg_color_type);
  bndNodePort(ctx, x, y, state, *color);
  return self;
}

static mrb_value
bnd_node_wire(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x0;
  mrb_float y0;
  mrb_float x1;
  mrb_float y1;
  mrb_int state0;
  mrb_int state1;
  mrb_get_args(mrb, "dffffii",
                    &ctx, &mrb_nvg_context_type,
                    &x0, &y0, &x1, &y1,
                    &state0, &state1);
  bndNodeWire(ctx, x0, y0, x1, y1, state0, state1);
  return self;
}

static mrb_value
bnd_colored_node_wire(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x0;
  mrb_float y0;
  mrb_float x1;
  mrb_float y1;
  NVGcolor *color0;
  NVGcolor *color1;
  mrb_get_args(mrb, "dffffdd",
                    &ctx, &mrb_nvg_context_type,
                    &x0, &y0, &x1, &y1,
                    &color0, &mrb_nvg_color_type,
                    &color1, &mrb_nvg_color_type);
  bndColoredNodeWire(ctx, x0, y0, x1, y1, *color0, *color1);
  return self;
}

static mrb_value
bnd_node_background(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_int state;
  mrb_int iconid;
  mrb_value label;
  NVGcolor *title_color;
  mrb_get_args(mrb, "dffffiiod",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &state, &iconid,
                    &label,
                    &title_color, &mrb_nvg_color_type);
  bndNodeBackground(ctx, x, y, w, h, state, iconid, maybe_string(mrb, label), *title_color);
  return self;
}

static mrb_value
bnd_splitter_widgets(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_get_args(mrb, "dffff",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h);
  bndSplitterWidgets(ctx, x, y, w, h);
  return self;
}

static mrb_value
bnd_join_area_overlay(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_bool vertical;
  mrb_bool mirror;
  mrb_get_args(mrb, "dffffbb",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &vertical,
                    &mirror);
  bndJoinAreaOverlay(ctx, x, y, w, h, vertical, mirror);
  return self;
}

static mrb_value
bnd_label_width(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_int iconid;
  mrb_value label;
  mrb_get_args(mrb, "dio",
                    &ctx, &mrb_nvg_context_type,
                    &iconid,
                    &label);
  return mrb_float_value(mrb, bndLabelWidth(ctx, iconid, maybe_string(mrb, label)));
}

static mrb_value
bnd_label_height(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_int iconid;
  mrb_value label;
  mrb_float width;
  mrb_get_args(mrb, "diof",
                    &ctx, &mrb_nvg_context_type,
                    &iconid,
                    &label,
                    &width);
  return mrb_float_value(mrb, bndLabelHeight(ctx, iconid, maybe_string(mrb, label), width));
}

static mrb_value
bnd_transparent(mrb_state *mrb, mrb_value self)
{
  NVGcolor *color;
  mrb_get_args(mrb, "d", &color, &mrb_nvg_color_type);
  return mrb_nvg_color_value(mrb, bndTransparent(*color));
}

static mrb_value
bnd_offset_color(mrb_state *mrb, mrb_value self)
{
  NVGcolor *color;
  mrb_int delta;
  mrb_get_args(mrb, "di", &color, &mrb_nvg_color_type, &delta);
  return mrb_nvg_color_value(mrb, bndOffsetColor(*color, delta));
}

static mrb_value
bnd_select_corners(mrb_state *mrb, mrb_value self)
{
  float radiuses[4];
  mrb_float r;
  mrb_int flags;
  mrb_value vals[4];
  mrb_get_args(mrb, "fi", &r, &flags);
  bndSelectCorners(radiuses, r, flags);
  vals[0] = mrb_float_value(mrb, radiuses[0]);
  vals[1] = mrb_float_value(mrb, radiuses[1]);
  vals[2] = mrb_float_value(mrb, radiuses[2]);
  vals[3] = mrb_float_value(mrb, radiuses[3]);
  return mrb_ary_new_from_values(mrb, 4, vals);
}

static mrb_value
bnd_inner_colors(mrb_state *mrb, mrb_value self)
{
  BNDwidgetTheme *theme;
  mrb_int state;
  mrb_bool flip_active;
  NVGcolor shade_top;
  NVGcolor shade_down;
  mrb_value vals[2];
  mrb_get_args(mrb, "dib", &theme, &mrb_bnd_widget_theme_type,
                           &state,
                           &flip_active);
  bndInnerColors(&shade_top, &shade_down, theme, state, flip_active);
  vals[0] = mrb_nvg_color_value(mrb, shade_top);
  vals[1] = mrb_nvg_color_value(mrb, shade_down);
  return mrb_ary_new_from_values(mrb, 2, vals);
}

static mrb_value
bnd_text_color(mrb_state *mrb, mrb_value self)
{
  mrb_int state;
  BNDwidgetTheme *theme;
  mrb_get_args(mrb, "di", &theme, &mrb_bnd_widget_theme_type, &state);
  return mrb_nvg_color_value(mrb, bndTextColor(theme, state));
}

static mrb_value
bnd_scroll_handle_rect(mrb_state *mrb, mrb_value self)
{
  mrb_float x_in;
  mrb_float y_in;
  mrb_float w_in;
  mrb_float h_in;
  mrb_float offset;
  mrb_float size;
  mrb_value vals[4];
  float x_out;
  float y_out;
  float w_out;
  float h_out;
  mrb_get_args(mrb, "ffffff", &x_in, &y_in, &w_in, &h_in, &offset, &size);
  x_out = x_in;
  y_out = y_in;
  w_out = w_in;
  h_out = h_in;
  bndScrollHandleRect(&x_out, &y_out, &w_out, &h_out, offset, size);
  vals[0] = mrb_float_value(mrb, x_out);
  vals[1] = mrb_float_value(mrb, y_out);
  vals[2] = mrb_float_value(mrb, w_out);
  vals[3] = mrb_float_value(mrb, h_out);
  return mrb_ary_new_from_values(mrb, 4, vals);
}

static mrb_value
bnd_rounded_box(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_float cr0;
  mrb_float cr1;
  mrb_float cr2;
  mrb_float cr3;
  mrb_get_args(mrb, "dffffffff",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &cr0, &cr1, &cr2, &cr3);
  bndRoundedBox(ctx, x, y, w, h, cr0, cr1, cr2, cr3);
  return self;
}

static mrb_value
bnd_background(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_get_args(mrb, "dffff",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h);
  bndBackground(ctx, x, y, w, h);
  return self;
}

static mrb_value
bnd_bevel(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_get_args(mrb, "dffff",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h);
  bndBevel(ctx, x, y, w, h);
  return self;
}

static mrb_value
bnd_bevel_inset(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_float cr2;
  mrb_float cr3;
  mrb_get_args(mrb, "dffffff",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &cr2, &cr3);
  bndBevelInset(ctx, x, y, w, h, cr2, cr3);
  return self;
}

static mrb_value
bnd_icon(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_int iconid;
  mrb_get_args(mrb, "dffi",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y,
                    &iconid);
  bndIcon(ctx, x, y, iconid);
  return self;
}

static mrb_value
bnd_drop_shadow(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_float r;
  mrb_float feather;
  mrb_float alpha;
  mrb_get_args(mrb, "dfffffff",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &r, &feather, &alpha);
  bndDropShadow(ctx, x, y, w, h, r, feather, alpha);
  return self;
}

static mrb_value
bnd_inner_box(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_float cr0;
  mrb_float cr1;
  mrb_float cr2;
  mrb_float cr3;
  NVGcolor *shade_top;
  NVGcolor *shade_down;
  mrb_get_args(mrb, "dffffffffdd",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &cr0, &cr1, &cr2, &cr3,
                    &shade_top, &mrb_nvg_color_type,
                    &shade_down, &mrb_nvg_color_type);
  bndInnerBox(ctx, x, y, w, h, cr0, cr1, cr2, cr3, *shade_top, *shade_down);
  return self;
}

static mrb_value
bnd_outline_box(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_float cr0;
  mrb_float cr1;
  mrb_float cr2;
  mrb_float cr3;
  NVGcolor *color;
  mrb_get_args(mrb, "dffffffffd",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &cr0, &cr1, &cr2, &cr3,
                    &color, &mrb_nvg_color_type);
  bndOutlineBox(ctx, x, y, w, h, cr0, cr1, cr2, cr3, *color);
  return self;
}

static mrb_value
bnd_icon_label_value(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_int iconid;
  NVGcolor *color;
  mrb_int align;
  mrb_float fontsize;
  mrb_value label;
  mrb_value value;
  mrb_get_args(mrb, "dffffidifoo",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &iconid,
                    &color, &mrb_nvg_color_type,
                    &align,
                    &fontsize,
                    &label, &value);
  bndIconLabelValue(ctx, x, y, w, h, iconid, *color, align, fontsize, maybe_string(mrb, label), maybe_string(mrb, value));
  return self;
}

static mrb_value
bnd_node_icon_label(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_int iconid;
  NVGcolor *color;
  NVGcolor *shadow_color;
  mrb_int align;
  mrb_float fontsize;
  mrb_value label;
  mrb_get_args(mrb, "dffffiddifo",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &iconid,
                    &color, &mrb_nvg_color_type,
                    &shadow_color, &mrb_nvg_color_type,
                    &align,
                    &fontsize,
                    &label);
  bndNodeIconLabel(ctx, x, y, w, h, iconid, *color, *shadow_color, align, fontsize, maybe_string(mrb, label));
  return self;
}

static mrb_value
bnd_icon_label_text_position(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_int iconid;
  mrb_float fontsize;
  mrb_value label;
  mrb_int px;
  mrb_int py;
  mrb_get_args(mrb, "dffffifoii",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &iconid,
                    &fontsize,
                    &label,
                    &px, &py);
  return mrb_fixnum_value(bndIconLabelTextPosition(ctx, x, y, w, h, iconid, fontsize, maybe_string(mrb, label), px, py));
}

static mrb_value
bnd_icon_label_caret(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_int iconid;
  NVGcolor *color;
  mrb_float fontsize;
  mrb_value label;
  NVGcolor *caretcolor;
  mrb_int cbegin;
  mrb_int cend;
  mrb_get_args(mrb, "dffffidfodii",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &w, &h,
                    &iconid,
                    &color, &mrb_nvg_color_type,
                    &fontsize,
                    &label,
                    &caretcolor, &mrb_nvg_color_type,
                    &cbegin, &cend);
  bndIconLabelCaret(ctx, x, y, w, h, iconid, *color, fontsize, maybe_string(mrb, label), *caretcolor, cbegin, cend);
  return self;
}

static mrb_value
bnd_check(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float ox;
  mrb_float oy;
  NVGcolor *color;
  mrb_get_args(mrb, "dffd",
                    &ctx, &mrb_nvg_context_type,
                    &ox, &oy,
                    &color, &mrb_nvg_color_type);
  bndCheck(ctx, ox, oy, *color);
  return self;
}

static mrb_value
bnd_arrow(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float s;
  NVGcolor *color;
  mrb_get_args(mrb, "dfffd",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &s,
                    &color, &mrb_nvg_color_type);
  bndArrow(ctx, x, y, s, *color);
  return self;
}

static mrb_value
bnd_up_down_arrow(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float s;
  NVGcolor *color;
  mrb_get_args(mrb, "dfffd",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &s,
                    &color, &mrb_nvg_color_type);
  bndUpDownArrow(ctx, x, y, s, *color);
  return self;
}

static mrb_value
bnd_node_arrow_down(mrb_state *mrb, mrb_value self)
{
  NVGcontext *ctx;
  mrb_float x;
  mrb_float y;
  mrb_float s;
  NVGcolor *color;
  mrb_get_args(mrb, "dfffd",
                    &ctx, &mrb_nvg_context_type,
                    &x, &y, &s,
                    &color, &mrb_nvg_color_type);
  bndNodeArrowDown(ctx, x, y, s, *color);
  return self;
}

static mrb_value
bnd_node_wire_color(mrb_state *mrb, mrb_value self)
{
  mrb_int state;
  BNDnodeTheme *theme;
  mrb_get_args(mrb, "di", &theme, &mrb_bnd_node_theme_type, &state);
  return mrb_nvg_color_value(mrb, bndNodeWireColor(theme, state));
}

void
mrb_mruby_blendish_gem_init(mrb_state* mrb)
{
  oui_module = mrb_define_module(mrb, "OUI");
  bnd_module = mrb_define_module_under(mrb, oui_module, "Blendish");
  bnd_ctx_class = mrb_define_class_under(mrb, bnd_module, "Context", mrb->object_class);
  bnd_icon_module = mrb_define_module_under(mrb, bnd_module, "Icon");

  mrb_define_method(mrb, bnd_ctx_class, "theme=",                   bnd_set_theme,                MRB_ARGS_REQ(1));
  mrb_define_method(mrb, bnd_ctx_class, "theme",                    bnd_get_theme,                MRB_ARGS_NONE());
  mrb_define_method(mrb, bnd_ctx_class, "icon_image=",              bnd_set_icon_image,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, bnd_ctx_class, "font=",                    bnd_set_font,                 MRB_ARGS_REQ(1));
  mrb_define_method(mrb, bnd_ctx_class, "label",                    bnd_label,                    MRB_ARGS_REQ(7));
  mrb_define_method(mrb, bnd_ctx_class, "tool_button",              bnd_tool_button,              MRB_ARGS_REQ(9));
  mrb_define_method(mrb, bnd_ctx_class, "radio_button",             bnd_radio_button,             MRB_ARGS_REQ(9));
  mrb_define_method(mrb, bnd_ctx_class, "text_field_text_position", bnd_text_field_text_position, MRB_ARGS_REQ(9));
  mrb_define_method(mrb, bnd_ctx_class, "text_field",               bnd_text_field,               MRB_ARGS_REQ(11));
  mrb_define_method(mrb, bnd_ctx_class, "option_button",            bnd_option_button,            MRB_ARGS_REQ(7));
  mrb_define_method(mrb, bnd_ctx_class, "choice_button",            bnd_choice_button,            MRB_ARGS_REQ(9));
  mrb_define_method(mrb, bnd_ctx_class, "color_button",             bnd_color_button,             MRB_ARGS_REQ(7));
  mrb_define_method(mrb, bnd_ctx_class, "number_field",             bnd_number_field,             MRB_ARGS_REQ(9));
  mrb_define_method(mrb, bnd_ctx_class, "slider",                   bnd_slider,                   MRB_ARGS_REQ(10));
  mrb_define_method(mrb, bnd_ctx_class, "scroll_bar",               bnd_scroll_bar,               MRB_ARGS_REQ(8));
  mrb_define_method(mrb, bnd_ctx_class, "menu_background",          bnd_menu_background,          MRB_ARGS_REQ(6));
  mrb_define_method(mrb, bnd_ctx_class, "menu_label",               bnd_menu_label,               MRB_ARGS_REQ(7));
  mrb_define_method(mrb, bnd_ctx_class, "menu_item",                bnd_menu_item,                MRB_ARGS_REQ(8));
  mrb_define_method(mrb, bnd_ctx_class, "tooltip_background",       bnd_tooltip_background,       MRB_ARGS_REQ(5));
  mrb_define_method(mrb, bnd_ctx_class, "node_port",                bnd_node_port,                MRB_ARGS_REQ(5));
  mrb_define_method(mrb, bnd_ctx_class, "node_wire",                bnd_node_wire,                MRB_ARGS_REQ(7));
  mrb_define_method(mrb, bnd_ctx_class, "colored_node_wire",        bnd_colored_node_wire,        MRB_ARGS_REQ(7));
  mrb_define_method(mrb, bnd_ctx_class, "node_background",          bnd_node_background,          MRB_ARGS_REQ(9));
  mrb_define_method(mrb, bnd_ctx_class, "splitter_widgets",         bnd_splitter_widgets,         MRB_ARGS_REQ(5));
  mrb_define_method(mrb, bnd_ctx_class, "join_area_overlay",        bnd_join_area_overlay,        MRB_ARGS_REQ(7));
  mrb_define_method(mrb, bnd_ctx_class, "label_width",              bnd_label_width,              MRB_ARGS_REQ(3));
  mrb_define_method(mrb, bnd_ctx_class, "label_height",             bnd_label_height,             MRB_ARGS_REQ(4));
  mrb_define_method(mrb, bnd_ctx_class, "transparent",              bnd_transparent,              MRB_ARGS_REQ(1));
  mrb_define_method(mrb, bnd_ctx_class, "offset_color",             bnd_offset_color,             MRB_ARGS_REQ(2));
  mrb_define_method(mrb, bnd_ctx_class, "select_corners",           bnd_select_corners,           MRB_ARGS_REQ(2));
  mrb_define_method(mrb, bnd_ctx_class, "inner_colors",             bnd_inner_colors,             MRB_ARGS_REQ(5));
  mrb_define_method(mrb, bnd_ctx_class, "text_color",               bnd_text_color,               MRB_ARGS_REQ(2));
  mrb_define_method(mrb, bnd_ctx_class, "scroll_handle_rect",       bnd_scroll_handle_rect,       MRB_ARGS_REQ(6));
  mrb_define_method(mrb, bnd_ctx_class, "rounded_box",              bnd_rounded_box,              MRB_ARGS_REQ(9));
  mrb_define_method(mrb, bnd_ctx_class, "background",               bnd_background,               MRB_ARGS_REQ(5));
  mrb_define_method(mrb, bnd_ctx_class, "bevel",                    bnd_bevel,                    MRB_ARGS_REQ(5));
  mrb_define_method(mrb, bnd_ctx_class, "bevel_inset",              bnd_bevel_inset,              MRB_ARGS_REQ(7));
  mrb_define_method(mrb, bnd_ctx_class, "icon",                     bnd_icon,                     MRB_ARGS_REQ(4));
  mrb_define_method(mrb, bnd_ctx_class, "drop_shadow",              bnd_drop_shadow,              MRB_ARGS_REQ(8));
  mrb_define_method(mrb, bnd_ctx_class, "inner_box",                bnd_inner_box,                MRB_ARGS_REQ(11));
  mrb_define_method(mrb, bnd_ctx_class, "outline_box",              bnd_outline_box,              MRB_ARGS_REQ(10));
  mrb_define_method(mrb, bnd_ctx_class, "icon_label_value",         bnd_icon_label_value,         MRB_ARGS_REQ(11));
  mrb_define_method(mrb, bnd_ctx_class, "node_icon_label",          bnd_node_icon_label,          MRB_ARGS_REQ(11));
  mrb_define_method(mrb, bnd_ctx_class, "icon_label_text_position", bnd_icon_label_text_position, MRB_ARGS_REQ(10));
  mrb_define_method(mrb, bnd_ctx_class, "icon_label_caret",         bnd_icon_label_caret,         MRB_ARGS_REQ(12));
  mrb_define_method(mrb, bnd_ctx_class, "check",                    bnd_check,                    MRB_ARGS_REQ(4));
  mrb_define_method(mrb, bnd_ctx_class, "arrow",                    bnd_arrow,                    MRB_ARGS_REQ(5));
  mrb_define_method(mrb, bnd_ctx_class, "up_down_arrow",            bnd_up_down_arrow,            MRB_ARGS_REQ(5));
  mrb_define_method(mrb, bnd_ctx_class, "node_arrow_down",          bnd_node_arrow_down,          MRB_ARGS_REQ(5));
  mrb_define_method(mrb, bnd_ctx_class, "node_wire_color",          bnd_node_wire_color,          MRB_ARGS_REQ(2));

  mrb_bnd_widget_theme_init(mrb, bnd_module);
  mrb_bnd_node_theme_init(mrb, bnd_module);
  mrb_bnd_theme_init(mrb, bnd_module);

  /* More */
  mrb_define_const(mrb, bnd_module, "DISABLED_ALPHA", mrb_float_value(mrb, BND_DISABLED_ALPHA));
  /* BNDtextAlignment */
  mrb_define_const(mrb, bnd_module, "LEFT", mrb_fixnum_value(BND_LEFT));
  mrb_define_const(mrb, bnd_module, "CENTER", mrb_fixnum_value(BND_CENTER));
  /* BNDwidgetState */
  mrb_define_const(mrb, bnd_module, "DEFAULT", mrb_fixnum_value(BND_DEFAULT));
  mrb_define_const(mrb, bnd_module, "HOVER", mrb_fixnum_value(BND_HOVER));
  mrb_define_const(mrb, bnd_module, "ACTIVE", mrb_fixnum_value(BND_ACTIVE));
  /* BNDcornerFlags */
  mrb_define_const(mrb, bnd_module, "CORNER_NONE", mrb_fixnum_value(BND_CORNER_NONE));
  mrb_define_const(mrb, bnd_module, "CORNER_TOP_LEFT", mrb_fixnum_value(BND_CORNER_TOP_LEFT));
  mrb_define_const(mrb, bnd_module, "CORNER_TOP_RIGHT", mrb_fixnum_value(BND_CORNER_TOP_RIGHT));
  mrb_define_const(mrb, bnd_module, "CORNER_DOWN_RIGHT", mrb_fixnum_value(BND_CORNER_DOWN_RIGHT));
  mrb_define_const(mrb, bnd_module, "CORNER_DOWN_LEFT", mrb_fixnum_value(BND_CORNER_DOWN_LEFT));
  mrb_define_const(mrb, bnd_module, "CORNER_ALL", mrb_fixnum_value(BND_CORNER_ALL));
  mrb_define_const(mrb, bnd_module, "CORNER_TOP", mrb_fixnum_value(BND_CORNER_TOP));
  mrb_define_const(mrb, bnd_module, "CORNER_DOWN", mrb_fixnum_value(BND_CORNER_DOWN));
  mrb_define_const(mrb, bnd_module, "CORNER_LEFT", mrb_fixnum_value(BND_CORNER_LEFT));
  mrb_define_const(mrb, bnd_module, "CORNER_RIGHT", mrb_fixnum_value(BND_CORNER_RIGHT));
  /* Some other stuff */
  mrb_define_const(mrb, bnd_module, "WIDGET_HEIGHT", mrb_fixnum_value(BND_WIDGET_HEIGHT));
  mrb_define_const(mrb, bnd_module, "TOOL_WIDTH", mrb_fixnum_value(BND_TOOL_WIDTH));
  mrb_define_const(mrb, bnd_module, "NODE_PORT_RADIUS", mrb_fixnum_value(BND_NODE_PORT_RADIUS));
  mrb_define_const(mrb, bnd_module, "NODE_MARGIN_TOP", mrb_fixnum_value(BND_NODE_MARGIN_TOP));
  mrb_define_const(mrb, bnd_module, "NODE_MARGIN_DOWN", mrb_fixnum_value(BND_NODE_MARGIN_DOWN));
  mrb_define_const(mrb, bnd_module, "NODE_MARGIN_SIDE", mrb_fixnum_value(BND_NODE_MARGIN_SIDE));
  mrb_define_const(mrb, bnd_module, "NODE_TITLE_HEIGHT", mrb_fixnum_value(BND_NODE_TITLE_HEIGHT));
  mrb_define_const(mrb, bnd_module, "NODE_ARROW_AREA_WIDTH", mrb_fixnum_value(BND_NODE_ARROW_AREA_WIDTH));
  mrb_define_const(mrb, bnd_module, "SPLITTER_AREA_SIZE", mrb_fixnum_value(BND_SPLITTER_AREA_SIZE));
  mrb_define_const(mrb, bnd_module, "SCROLLBAR_WIDTH", mrb_fixnum_value(BND_SCROLLBAR_WIDTH));
  mrb_define_const(mrb, bnd_module, "SCROLLBAR_HEIGHT", mrb_fixnum_value(BND_SCROLLBAR_HEIGHT));
  mrb_define_const(mrb, bnd_module, "VSPACING", mrb_fixnum_value(BND_VSPACING));
  mrb_define_const(mrb, bnd_module, "VSPACING_GROUP", mrb_fixnum_value(BND_VSPACING_GROUP));
  mrb_define_const(mrb, bnd_module, "HSPACING", mrb_fixnum_value(BND_HSPACING));
  /* BNDicon */
  mrb_define_const(mrb, bnd_icon_module, "NONE", mrb_fixnum_value(BND_ICON_NONE));
  mrb_define_const(mrb, bnd_icon_module, "QUESTION", mrb_fixnum_value(BND_ICON_QUESTION));
  mrb_define_const(mrb, bnd_icon_module, "ERROR", mrb_fixnum_value(BND_ICON_ERROR));
  mrb_define_const(mrb, bnd_icon_module, "CANCEL", mrb_fixnum_value(BND_ICON_CANCEL));
  mrb_define_const(mrb, bnd_icon_module, "TRIA_RIGHT", mrb_fixnum_value(BND_ICON_TRIA_RIGHT));
  mrb_define_const(mrb, bnd_icon_module, "TRIA_DOWN", mrb_fixnum_value(BND_ICON_TRIA_DOWN));
  mrb_define_const(mrb, bnd_icon_module, "TRIA_LEFT", mrb_fixnum_value(BND_ICON_TRIA_LEFT));
  mrb_define_const(mrb, bnd_icon_module, "TRIA_UP", mrb_fixnum_value(BND_ICON_TRIA_UP));
  mrb_define_const(mrb, bnd_icon_module, "ARROW_LEFTRIGHT", mrb_fixnum_value(BND_ICON_ARROW_LEFTRIGHT));
  mrb_define_const(mrb, bnd_icon_module, "PLUS", mrb_fixnum_value(BND_ICON_PLUS));
  mrb_define_const(mrb, bnd_icon_module, "DISCLOSURE_TRI_DOWN", mrb_fixnum_value(BND_ICON_DISCLOSURE_TRI_DOWN));
  mrb_define_const(mrb, bnd_icon_module, "DISCLOSURE_TRI_RIGHT", mrb_fixnum_value(BND_ICON_DISCLOSURE_TRI_RIGHT));
  mrb_define_const(mrb, bnd_icon_module, "RADIOBUT_OFF", mrb_fixnum_value(BND_ICON_RADIOBUT_OFF));
  mrb_define_const(mrb, bnd_icon_module, "RADIOBUT_ON", mrb_fixnum_value(BND_ICON_RADIOBUT_ON));
  mrb_define_const(mrb, bnd_icon_module, "MENU_PANEL", mrb_fixnum_value(BND_ICON_MENU_PANEL));
  mrb_define_const(mrb, bnd_icon_module, "BLENDER", mrb_fixnum_value(BND_ICON_BLENDER));
  mrb_define_const(mrb, bnd_icon_module, "GRIP", mrb_fixnum_value(BND_ICON_GRIP));
  mrb_define_const(mrb, bnd_icon_module, "DOT", mrb_fixnum_value(BND_ICON_DOT));
  mrb_define_const(mrb, bnd_icon_module, "COLLAPSEMENU", mrb_fixnum_value(BND_ICON_COLLAPSEMENU));
  mrb_define_const(mrb, bnd_icon_module, "X", mrb_fixnum_value(BND_ICON_X));
  mrb_define_const(mrb, bnd_icon_module, "GO_LEFT", mrb_fixnum_value(BND_ICON_GO_LEFT));
  mrb_define_const(mrb, bnd_icon_module, "PLUG", mrb_fixnum_value(BND_ICON_PLUG));
  mrb_define_const(mrb, bnd_icon_module, "UI", mrb_fixnum_value(BND_ICON_UI));
  mrb_define_const(mrb, bnd_icon_module, "NODE", mrb_fixnum_value(BND_ICON_NODE));
  mrb_define_const(mrb, bnd_icon_module, "NODE_SEL", mrb_fixnum_value(BND_ICON_NODE_SEL));
  mrb_define_const(mrb, bnd_icon_module, "FULLSCREEN", mrb_fixnum_value(BND_ICON_FULLSCREEN));
  mrb_define_const(mrb, bnd_icon_module, "SPLITSCREEN", mrb_fixnum_value(BND_ICON_SPLITSCREEN));
  mrb_define_const(mrb, bnd_icon_module, "RIGHTARROW_THIN", mrb_fixnum_value(BND_ICON_RIGHTARROW_THIN));
  mrb_define_const(mrb, bnd_icon_module, "BORDERMOVE", mrb_fixnum_value(BND_ICON_BORDERMOVE));
  mrb_define_const(mrb, bnd_icon_module, "VIEWZOOM", mrb_fixnum_value(BND_ICON_VIEWZOOM));
  mrb_define_const(mrb, bnd_icon_module, "ZOOMIN", mrb_fixnum_value(BND_ICON_ZOOMIN));
  mrb_define_const(mrb, bnd_icon_module, "ZOOMOUT", mrb_fixnum_value(BND_ICON_ZOOMOUT));
  mrb_define_const(mrb, bnd_icon_module, "PANEL_CLOSE", mrb_fixnum_value(BND_ICON_PANEL_CLOSE));
  mrb_define_const(mrb, bnd_icon_module, "COPY_ID", mrb_fixnum_value(BND_ICON_COPY_ID));
  mrb_define_const(mrb, bnd_icon_module, "EYEDROPPER", mrb_fixnum_value(BND_ICON_EYEDROPPER));
  mrb_define_const(mrb, bnd_icon_module, "LINK_AREA", mrb_fixnum_value(BND_ICON_LINK_AREA));
  mrb_define_const(mrb, bnd_icon_module, "AUTO", mrb_fixnum_value(BND_ICON_AUTO));
  mrb_define_const(mrb, bnd_icon_module, "CHECKBOX_DEHLT", mrb_fixnum_value(BND_ICON_CHECKBOX_DEHLT));
  mrb_define_const(mrb, bnd_icon_module, "CHECKBOX_HLT", mrb_fixnum_value(BND_ICON_CHECKBOX_HLT));
  mrb_define_const(mrb, bnd_icon_module, "UNLOCKED", mrb_fixnum_value(BND_ICON_UNLOCKED));
  mrb_define_const(mrb, bnd_icon_module, "LOCKED", mrb_fixnum_value(BND_ICON_LOCKED));
  mrb_define_const(mrb, bnd_icon_module, "UNPINNED", mrb_fixnum_value(BND_ICON_UNPINNED));
  mrb_define_const(mrb, bnd_icon_module, "PINNED", mrb_fixnum_value(BND_ICON_PINNED));
  mrb_define_const(mrb, bnd_icon_module, "SCREEN_BACK", mrb_fixnum_value(BND_ICON_SCREEN_BACK));
  mrb_define_const(mrb, bnd_icon_module, "RIGHTARROW", mrb_fixnum_value(BND_ICON_RIGHTARROW));
  mrb_define_const(mrb, bnd_icon_module, "DOWNARROW_HLT", mrb_fixnum_value(BND_ICON_DOWNARROW_HLT));
  mrb_define_const(mrb, bnd_icon_module, "DOTSUP", mrb_fixnum_value(BND_ICON_DOTSUP));
  mrb_define_const(mrb, bnd_icon_module, "DOTSDOWN", mrb_fixnum_value(BND_ICON_DOTSDOWN));
  mrb_define_const(mrb, bnd_icon_module, "LINK", mrb_fixnum_value(BND_ICON_LINK));
  mrb_define_const(mrb, bnd_icon_module, "INLINK", mrb_fixnum_value(BND_ICON_INLINK));
  mrb_define_const(mrb, bnd_icon_module, "PLUGIN", mrb_fixnum_value(BND_ICON_PLUGIN));
  mrb_define_const(mrb, bnd_icon_module, "HELP", mrb_fixnum_value(BND_ICON_HELP));
  mrb_define_const(mrb, bnd_icon_module, "GHOST_ENABLED", mrb_fixnum_value(BND_ICON_GHOST_ENABLED));
  mrb_define_const(mrb, bnd_icon_module, "COLOR", mrb_fixnum_value(BND_ICON_COLOR));
  mrb_define_const(mrb, bnd_icon_module, "LINKED", mrb_fixnum_value(BND_ICON_LINKED));
  mrb_define_const(mrb, bnd_icon_module, "UNLINKED", mrb_fixnum_value(BND_ICON_UNLINKED));
  mrb_define_const(mrb, bnd_icon_module, "HAND", mrb_fixnum_value(BND_ICON_HAND));
  mrb_define_const(mrb, bnd_icon_module, "ZOOM_ALL", mrb_fixnum_value(BND_ICON_ZOOM_ALL));
  mrb_define_const(mrb, bnd_icon_module, "ZOOM_SELECTED", mrb_fixnum_value(BND_ICON_ZOOM_SELECTED));
  mrb_define_const(mrb, bnd_icon_module, "ZOOM_PREVIOUS", mrb_fixnum_value(BND_ICON_ZOOM_PREVIOUS));
  mrb_define_const(mrb, bnd_icon_module, "ZOOM_IN", mrb_fixnum_value(BND_ICON_ZOOM_IN));
  mrb_define_const(mrb, bnd_icon_module, "ZOOM_OUT", mrb_fixnum_value(BND_ICON_ZOOM_OUT));
  mrb_define_const(mrb, bnd_icon_module, "RENDER_REGION", mrb_fixnum_value(BND_ICON_RENDER_REGION));
  mrb_define_const(mrb, bnd_icon_module, "BORDER_RECT", mrb_fixnum_value(BND_ICON_BORDER_RECT));
  mrb_define_const(mrb, bnd_icon_module, "BORDER_LASSO", mrb_fixnum_value(BND_ICON_BORDER_LASSO));
  mrb_define_const(mrb, bnd_icon_module, "FREEZE", mrb_fixnum_value(BND_ICON_FREEZE));
  mrb_define_const(mrb, bnd_icon_module, "STYLUS_PRESSURE", mrb_fixnum_value(BND_ICON_STYLUS_PRESSURE));
  mrb_define_const(mrb, bnd_icon_module, "GHOST_DISABLED", mrb_fixnum_value(BND_ICON_GHOST_DISABLED));
  mrb_define_const(mrb, bnd_icon_module, "NEW", mrb_fixnum_value(BND_ICON_NEW));
  mrb_define_const(mrb, bnd_icon_module, "FILE_TICK", mrb_fixnum_value(BND_ICON_FILE_TICK));
  mrb_define_const(mrb, bnd_icon_module, "QUIT", mrb_fixnum_value(BND_ICON_QUIT));
  mrb_define_const(mrb, bnd_icon_module, "URL", mrb_fixnum_value(BND_ICON_URL));
  mrb_define_const(mrb, bnd_icon_module, "RECOVER_LAST", mrb_fixnum_value(BND_ICON_RECOVER_LAST));
  mrb_define_const(mrb, bnd_icon_module, "FULLSCREEN_ENTER", mrb_fixnum_value(BND_ICON_FULLSCREEN_ENTER));
  mrb_define_const(mrb, bnd_icon_module, "FULLSCREEN_EXIT", mrb_fixnum_value(BND_ICON_FULLSCREEN_EXIT));
  mrb_define_const(mrb, bnd_icon_module, "BLANK1", mrb_fixnum_value(BND_ICON_BLANK1));
  mrb_define_const(mrb, bnd_icon_module, "LAMP", mrb_fixnum_value(BND_ICON_LAMP));
  mrb_define_const(mrb, bnd_icon_module, "MATERIAL", mrb_fixnum_value(BND_ICON_MATERIAL));
  mrb_define_const(mrb, bnd_icon_module, "TEXTURE", mrb_fixnum_value(BND_ICON_TEXTURE));
  mrb_define_const(mrb, bnd_icon_module, "ANIM", mrb_fixnum_value(BND_ICON_ANIM));
  mrb_define_const(mrb, bnd_icon_module, "WORLD", mrb_fixnum_value(BND_ICON_WORLD));
  mrb_define_const(mrb, bnd_icon_module, "SCENE", mrb_fixnum_value(BND_ICON_SCENE));
  mrb_define_const(mrb, bnd_icon_module, "EDIT", mrb_fixnum_value(BND_ICON_EDIT));
  mrb_define_const(mrb, bnd_icon_module, "GAME", mrb_fixnum_value(BND_ICON_GAME));
  mrb_define_const(mrb, bnd_icon_module, "RADIO", mrb_fixnum_value(BND_ICON_RADIO));
  mrb_define_const(mrb, bnd_icon_module, "SCRIPT", mrb_fixnum_value(BND_ICON_SCRIPT));
  mrb_define_const(mrb, bnd_icon_module, "PARTICLES", mrb_fixnum_value(BND_ICON_PARTICLES));
  mrb_define_const(mrb, bnd_icon_module, "PHYSICS", mrb_fixnum_value(BND_ICON_PHYSICS));
  mrb_define_const(mrb, bnd_icon_module, "SPEAKER", mrb_fixnum_value(BND_ICON_SPEAKER));
  mrb_define_const(mrb, bnd_icon_module, "TEXTURE_SHADED", mrb_fixnum_value(BND_ICON_TEXTURE_SHADED));
  mrb_define_const(mrb, bnd_icon_module, "VIEW3D", mrb_fixnum_value(BND_ICON_VIEW3D));
  mrb_define_const(mrb, bnd_icon_module, "IPO", mrb_fixnum_value(BND_ICON_IPO));
  mrb_define_const(mrb, bnd_icon_module, "OOPS", mrb_fixnum_value(BND_ICON_OOPS));
  mrb_define_const(mrb, bnd_icon_module, "BUTS", mrb_fixnum_value(BND_ICON_BUTS));
  mrb_define_const(mrb, bnd_icon_module, "FILESEL", mrb_fixnum_value(BND_ICON_FILESEL));
  mrb_define_const(mrb, bnd_icon_module, "IMAGE_COL", mrb_fixnum_value(BND_ICON_IMAGE_COL));
  mrb_define_const(mrb, bnd_icon_module, "INFO", mrb_fixnum_value(BND_ICON_INFO));
  mrb_define_const(mrb, bnd_icon_module, "SEQUENCE", mrb_fixnum_value(BND_ICON_SEQUENCE));
  mrb_define_const(mrb, bnd_icon_module, "TEXT", mrb_fixnum_value(BND_ICON_TEXT));
  mrb_define_const(mrb, bnd_icon_module, "IMASEL", mrb_fixnum_value(BND_ICON_IMASEL));
  mrb_define_const(mrb, bnd_icon_module, "SOUND", mrb_fixnum_value(BND_ICON_SOUND));
  mrb_define_const(mrb, bnd_icon_module, "ACTION", mrb_fixnum_value(BND_ICON_ACTION));
  mrb_define_const(mrb, bnd_icon_module, "NLA", mrb_fixnum_value(BND_ICON_NLA));
  mrb_define_const(mrb, bnd_icon_module, "SCRIPTWIN", mrb_fixnum_value(BND_ICON_SCRIPTWIN));
  mrb_define_const(mrb, bnd_icon_module, "TIME", mrb_fixnum_value(BND_ICON_TIME));
  mrb_define_const(mrb, bnd_icon_module, "NODETREE", mrb_fixnum_value(BND_ICON_NODETREE));
  mrb_define_const(mrb, bnd_icon_module, "LOGIC", mrb_fixnum_value(BND_ICON_LOGIC));
  mrb_define_const(mrb, bnd_icon_module, "CONSOLE", mrb_fixnum_value(BND_ICON_CONSOLE));
  mrb_define_const(mrb, bnd_icon_module, "PREFERENCES", mrb_fixnum_value(BND_ICON_PREFERENCES));
  mrb_define_const(mrb, bnd_icon_module, "CLIP", mrb_fixnum_value(BND_ICON_CLIP));
  mrb_define_const(mrb, bnd_icon_module, "ASSET_MANAGER", mrb_fixnum_value(BND_ICON_ASSET_MANAGER));
  mrb_define_const(mrb, bnd_icon_module, "OBJECT_DATAMODE", mrb_fixnum_value(BND_ICON_OBJECT_DATAMODE));
  mrb_define_const(mrb, bnd_icon_module, "EDITMODE_HLT", mrb_fixnum_value(BND_ICON_EDITMODE_HLT));
  mrb_define_const(mrb, bnd_icon_module, "FACESEL_HLT", mrb_fixnum_value(BND_ICON_FACESEL_HLT));
  mrb_define_const(mrb, bnd_icon_module, "VPAINT_HLT", mrb_fixnum_value(BND_ICON_VPAINT_HLT));
  mrb_define_const(mrb, bnd_icon_module, "TPAINT_HLT", mrb_fixnum_value(BND_ICON_TPAINT_HLT));
  mrb_define_const(mrb, bnd_icon_module, "WPAINT_HLT", mrb_fixnum_value(BND_ICON_WPAINT_HLT));
  mrb_define_const(mrb, bnd_icon_module, "SCULPTMODE_HLT", mrb_fixnum_value(BND_ICON_SCULPTMODE_HLT));
  mrb_define_const(mrb, bnd_icon_module, "POSE_HLT", mrb_fixnum_value(BND_ICON_POSE_HLT));
  mrb_define_const(mrb, bnd_icon_module, "PARTICLEMODE", mrb_fixnum_value(BND_ICON_PARTICLEMODE));
  mrb_define_const(mrb, bnd_icon_module, "LIGHTPAINT", mrb_fixnum_value(BND_ICON_LIGHTPAINT));
  mrb_define_const(mrb, bnd_icon_module, "SCENE_DATA", mrb_fixnum_value(BND_ICON_SCENE_DATA));
  mrb_define_const(mrb, bnd_icon_module, "RENDERLAYERS", mrb_fixnum_value(BND_ICON_RENDERLAYERS));
  mrb_define_const(mrb, bnd_icon_module, "WORLD_DATA", mrb_fixnum_value(BND_ICON_WORLD_DATA));
  mrb_define_const(mrb, bnd_icon_module, "OBJECT_DATA", mrb_fixnum_value(BND_ICON_OBJECT_DATA));
  mrb_define_const(mrb, bnd_icon_module, "MESH_DATA", mrb_fixnum_value(BND_ICON_MESH_DATA));
  mrb_define_const(mrb, bnd_icon_module, "CURVE_DATA", mrb_fixnum_value(BND_ICON_CURVE_DATA));
  mrb_define_const(mrb, bnd_icon_module, "META_DATA", mrb_fixnum_value(BND_ICON_META_DATA));
  mrb_define_const(mrb, bnd_icon_module, "LATTICE_DATA", mrb_fixnum_value(BND_ICON_LATTICE_DATA));
  mrb_define_const(mrb, bnd_icon_module, "LAMP_DATA", mrb_fixnum_value(BND_ICON_LAMP_DATA));
  mrb_define_const(mrb, bnd_icon_module, "MATERIAL_DATA", mrb_fixnum_value(BND_ICON_MATERIAL_DATA));
  mrb_define_const(mrb, bnd_icon_module, "TEXTURE_DATA", mrb_fixnum_value(BND_ICON_TEXTURE_DATA));
  mrb_define_const(mrb, bnd_icon_module, "ANIM_DATA", mrb_fixnum_value(BND_ICON_ANIM_DATA));
  mrb_define_const(mrb, bnd_icon_module, "CAMERA_DATA", mrb_fixnum_value(BND_ICON_CAMERA_DATA));
  mrb_define_const(mrb, bnd_icon_module, "PARTICLE_DATA", mrb_fixnum_value(BND_ICON_PARTICLE_DATA));
  mrb_define_const(mrb, bnd_icon_module, "LIBRARY_DATA_DIRECT", mrb_fixnum_value(BND_ICON_LIBRARY_DATA_DIRECT));
  mrb_define_const(mrb, bnd_icon_module, "GROUP", mrb_fixnum_value(BND_ICON_GROUP));
  mrb_define_const(mrb, bnd_icon_module, "ARMATURE_DATA", mrb_fixnum_value(BND_ICON_ARMATURE_DATA));
  mrb_define_const(mrb, bnd_icon_module, "POSE_DATA", mrb_fixnum_value(BND_ICON_POSE_DATA));
  mrb_define_const(mrb, bnd_icon_module, "BONE_DATA", mrb_fixnum_value(BND_ICON_BONE_DATA));
  mrb_define_const(mrb, bnd_icon_module, "CONSTRAINT", mrb_fixnum_value(BND_ICON_CONSTRAINT));
  mrb_define_const(mrb, bnd_icon_module, "SHAPEKEY_DATA", mrb_fixnum_value(BND_ICON_SHAPEKEY_DATA));
  mrb_define_const(mrb, bnd_icon_module, "CONSTRAINT_BONE", mrb_fixnum_value(BND_ICON_CONSTRAINT_BONE));
  mrb_define_const(mrb, bnd_icon_module, "CAMERA_STEREO", mrb_fixnum_value(BND_ICON_CAMERA_STEREO));
  mrb_define_const(mrb, bnd_icon_module, "PACKAGE", mrb_fixnum_value(BND_ICON_PACKAGE));
  mrb_define_const(mrb, bnd_icon_module, "UGLYPACKAGE", mrb_fixnum_value(BND_ICON_UGLYPACKAGE));
  mrb_define_const(mrb, bnd_icon_module, "BRUSH_DATA", mrb_fixnum_value(BND_ICON_BRUSH_DATA));
  mrb_define_const(mrb, bnd_icon_module, "IMAGE_DATA", mrb_fixnum_value(BND_ICON_IMAGE_DATA));
  mrb_define_const(mrb, bnd_icon_module, "FILE", mrb_fixnum_value(BND_ICON_FILE));
  mrb_define_const(mrb, bnd_icon_module, "FCURVE", mrb_fixnum_value(BND_ICON_FCURVE));
  mrb_define_const(mrb, bnd_icon_module, "FONT_DATA", mrb_fixnum_value(BND_ICON_FONT_DATA));
  mrb_define_const(mrb, bnd_icon_module, "RENDER_RESULT", mrb_fixnum_value(BND_ICON_RENDER_RESULT));
  mrb_define_const(mrb, bnd_icon_module, "SURFACE_DATA", mrb_fixnum_value(BND_ICON_SURFACE_DATA));
  mrb_define_const(mrb, bnd_icon_module, "EMPTY_DATA", mrb_fixnum_value(BND_ICON_EMPTY_DATA));
  mrb_define_const(mrb, bnd_icon_module, "SETTINGS", mrb_fixnum_value(BND_ICON_SETTINGS));
  mrb_define_const(mrb, bnd_icon_module, "RENDER_ANIMATION", mrb_fixnum_value(BND_ICON_RENDER_ANIMATION));
  mrb_define_const(mrb, bnd_icon_module, "RENDER_STILL", mrb_fixnum_value(BND_ICON_RENDER_STILL));
  mrb_define_const(mrb, bnd_icon_module, "BOIDS", mrb_fixnum_value(BND_ICON_BOIDS));
  mrb_define_const(mrb, bnd_icon_module, "STRANDS", mrb_fixnum_value(BND_ICON_STRANDS));
  mrb_define_const(mrb, bnd_icon_module, "LIBRARY_DATA_INDIRECT", mrb_fixnum_value(BND_ICON_LIBRARY_DATA_INDIRECT));
  mrb_define_const(mrb, bnd_icon_module, "GREASEPENCIL", mrb_fixnum_value(BND_ICON_GREASEPENCIL));
  mrb_define_const(mrb, bnd_icon_module, "LINE_DATA", mrb_fixnum_value(BND_ICON_LINE_DATA));
  mrb_define_const(mrb, bnd_icon_module, "GROUP_BONE", mrb_fixnum_value(BND_ICON_GROUP_BONE));
  mrb_define_const(mrb, bnd_icon_module, "GROUP_VERTEX", mrb_fixnum_value(BND_ICON_GROUP_VERTEX));
  mrb_define_const(mrb, bnd_icon_module, "GROUP_VCOL", mrb_fixnum_value(BND_ICON_GROUP_VCOL));
  mrb_define_const(mrb, bnd_icon_module, "GROUP_UVS", mrb_fixnum_value(BND_ICON_GROUP_UVS));
  mrb_define_const(mrb, bnd_icon_module, "RNA", mrb_fixnum_value(BND_ICON_RNA));
  mrb_define_const(mrb, bnd_icon_module, "RNA_ADD", mrb_fixnum_value(BND_ICON_RNA_ADD));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_OB_EMPTY", mrb_fixnum_value(BND_ICON_OUTLINER_OB_EMPTY));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_OB_MESH", mrb_fixnum_value(BND_ICON_OUTLINER_OB_MESH));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_OB_CURVE", mrb_fixnum_value(BND_ICON_OUTLINER_OB_CURVE));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_OB_LATTICE", mrb_fixnum_value(BND_ICON_OUTLINER_OB_LATTICE));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_OB_META", mrb_fixnum_value(BND_ICON_OUTLINER_OB_META));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_OB_LAMP", mrb_fixnum_value(BND_ICON_OUTLINER_OB_LAMP));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_OB_CAMERA", mrb_fixnum_value(BND_ICON_OUTLINER_OB_CAMERA));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_OB_ARMATURE", mrb_fixnum_value(BND_ICON_OUTLINER_OB_ARMATURE));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_OB_FONT", mrb_fixnum_value(BND_ICON_OUTLINER_OB_FONT));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_OB_SURFACE", mrb_fixnum_value(BND_ICON_OUTLINER_OB_SURFACE));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_OB_SPEAKER", mrb_fixnum_value(BND_ICON_OUTLINER_OB_SPEAKER));
  mrb_define_const(mrb, bnd_icon_module, "RESTRICT_VIEW_OFF", mrb_fixnum_value(BND_ICON_RESTRICT_VIEW_OFF));
  mrb_define_const(mrb, bnd_icon_module, "RESTRICT_VIEW_ON", mrb_fixnum_value(BND_ICON_RESTRICT_VIEW_ON));
  mrb_define_const(mrb, bnd_icon_module, "RESTRICT_SELECT_OFF", mrb_fixnum_value(BND_ICON_RESTRICT_SELECT_OFF));
  mrb_define_const(mrb, bnd_icon_module, "RESTRICT_SELECT_ON", mrb_fixnum_value(BND_ICON_RESTRICT_SELECT_ON));
  mrb_define_const(mrb, bnd_icon_module, "RESTRICT_RENDER_OFF", mrb_fixnum_value(BND_ICON_RESTRICT_RENDER_OFF));
  mrb_define_const(mrb, bnd_icon_module, "RESTRICT_RENDER_ON", mrb_fixnum_value(BND_ICON_RESTRICT_RENDER_ON));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_DATA_EMPTY", mrb_fixnum_value(BND_ICON_OUTLINER_DATA_EMPTY));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_DATA_MESH", mrb_fixnum_value(BND_ICON_OUTLINER_DATA_MESH));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_DATA_CURVE", mrb_fixnum_value(BND_ICON_OUTLINER_DATA_CURVE));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_DATA_LATTICE", mrb_fixnum_value(BND_ICON_OUTLINER_DATA_LATTICE));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_DATA_META", mrb_fixnum_value(BND_ICON_OUTLINER_DATA_META));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_DATA_LAMP", mrb_fixnum_value(BND_ICON_OUTLINER_DATA_LAMP));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_DATA_CAMERA", mrb_fixnum_value(BND_ICON_OUTLINER_DATA_CAMERA));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_DATA_ARMATURE", mrb_fixnum_value(BND_ICON_OUTLINER_DATA_ARMATURE));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_DATA_FONT", mrb_fixnum_value(BND_ICON_OUTLINER_DATA_FONT));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_DATA_SURFACE", mrb_fixnum_value(BND_ICON_OUTLINER_DATA_SURFACE));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_DATA_SPEAKER", mrb_fixnum_value(BND_ICON_OUTLINER_DATA_SPEAKER));
  mrb_define_const(mrb, bnd_icon_module, "OUTLINER_DATA_POSE", mrb_fixnum_value(BND_ICON_OUTLINER_DATA_POSE));
  mrb_define_const(mrb, bnd_icon_module, "MESH_PLANE", mrb_fixnum_value(BND_ICON_MESH_PLANE));
  mrb_define_const(mrb, bnd_icon_module, "MESH_CUBE", mrb_fixnum_value(BND_ICON_MESH_CUBE));
  mrb_define_const(mrb, bnd_icon_module, "MESH_CIRCLE", mrb_fixnum_value(BND_ICON_MESH_CIRCLE));
  mrb_define_const(mrb, bnd_icon_module, "MESH_UVSPHERE", mrb_fixnum_value(BND_ICON_MESH_UVSPHERE));
  mrb_define_const(mrb, bnd_icon_module, "MESH_ICOSPHERE", mrb_fixnum_value(BND_ICON_MESH_ICOSPHERE));
  mrb_define_const(mrb, bnd_icon_module, "MESH_GRID", mrb_fixnum_value(BND_ICON_MESH_GRID));
  mrb_define_const(mrb, bnd_icon_module, "MESH_MONKEY", mrb_fixnum_value(BND_ICON_MESH_MONKEY));
  mrb_define_const(mrb, bnd_icon_module, "MESH_CYLINDER", mrb_fixnum_value(BND_ICON_MESH_CYLINDER));
  mrb_define_const(mrb, bnd_icon_module, "MESH_TORUS", mrb_fixnum_value(BND_ICON_MESH_TORUS));
  mrb_define_const(mrb, bnd_icon_module, "MESH_CONE", mrb_fixnum_value(BND_ICON_MESH_CONE));
  mrb_define_const(mrb, bnd_icon_module, "LAMP_POINT", mrb_fixnum_value(BND_ICON_LAMP_POINT));
  mrb_define_const(mrb, bnd_icon_module, "LAMP_SUN", mrb_fixnum_value(BND_ICON_LAMP_SUN));
  mrb_define_const(mrb, bnd_icon_module, "LAMP_SPOT", mrb_fixnum_value(BND_ICON_LAMP_SPOT));
  mrb_define_const(mrb, bnd_icon_module, "LAMP_HEMI", mrb_fixnum_value(BND_ICON_LAMP_HEMI));
  mrb_define_const(mrb, bnd_icon_module, "LAMP_AREA", mrb_fixnum_value(BND_ICON_LAMP_AREA));
  mrb_define_const(mrb, bnd_icon_module, "META_EMPTY", mrb_fixnum_value(BND_ICON_META_EMPTY));
  mrb_define_const(mrb, bnd_icon_module, "META_PLANE", mrb_fixnum_value(BND_ICON_META_PLANE));
  mrb_define_const(mrb, bnd_icon_module, "META_CUBE", mrb_fixnum_value(BND_ICON_META_CUBE));
  mrb_define_const(mrb, bnd_icon_module, "META_BALL", mrb_fixnum_value(BND_ICON_META_BALL));
  mrb_define_const(mrb, bnd_icon_module, "META_ELLIPSOID", mrb_fixnum_value(BND_ICON_META_ELLIPSOID));
  mrb_define_const(mrb, bnd_icon_module, "META_CAPSULE", mrb_fixnum_value(BND_ICON_META_CAPSULE));
  mrb_define_const(mrb, bnd_icon_module, "SURFACE_NCURVE", mrb_fixnum_value(BND_ICON_SURFACE_NCURVE));
  mrb_define_const(mrb, bnd_icon_module, "SURFACE_NCIRCLE", mrb_fixnum_value(BND_ICON_SURFACE_NCIRCLE));
  mrb_define_const(mrb, bnd_icon_module, "SURFACE_NSURFACE", mrb_fixnum_value(BND_ICON_SURFACE_NSURFACE));
  mrb_define_const(mrb, bnd_icon_module, "SURFACE_NCYLINDER", mrb_fixnum_value(BND_ICON_SURFACE_NCYLINDER));
  mrb_define_const(mrb, bnd_icon_module, "SURFACE_NSPHERE", mrb_fixnum_value(BND_ICON_SURFACE_NSPHERE));
  mrb_define_const(mrb, bnd_icon_module, "SURFACE_NTORUS", mrb_fixnum_value(BND_ICON_SURFACE_NTORUS));
  mrb_define_const(mrb, bnd_icon_module, "CURVE_BEZCURVE", mrb_fixnum_value(BND_ICON_CURVE_BEZCURVE));
  mrb_define_const(mrb, bnd_icon_module, "CURVE_BEZCIRCLE", mrb_fixnum_value(BND_ICON_CURVE_BEZCIRCLE));
  mrb_define_const(mrb, bnd_icon_module, "CURVE_NCURVE", mrb_fixnum_value(BND_ICON_CURVE_NCURVE));
  mrb_define_const(mrb, bnd_icon_module, "CURVE_NCIRCLE", mrb_fixnum_value(BND_ICON_CURVE_NCIRCLE));
  mrb_define_const(mrb, bnd_icon_module, "CURVE_PATH", mrb_fixnum_value(BND_ICON_CURVE_PATH));
  mrb_define_const(mrb, bnd_icon_module, "COLOR_RED", mrb_fixnum_value(BND_ICON_COLOR_RED));
  mrb_define_const(mrb, bnd_icon_module, "COLOR_GREEN", mrb_fixnum_value(BND_ICON_COLOR_GREEN));
  mrb_define_const(mrb, bnd_icon_module, "COLOR_BLUE", mrb_fixnum_value(BND_ICON_COLOR_BLUE));
  mrb_define_const(mrb, bnd_icon_module, "FORCE_FORCE", mrb_fixnum_value(BND_ICON_FORCE_FORCE));
  mrb_define_const(mrb, bnd_icon_module, "FORCE_WIND", mrb_fixnum_value(BND_ICON_FORCE_WIND));
  mrb_define_const(mrb, bnd_icon_module, "FORCE_VORTEX", mrb_fixnum_value(BND_ICON_FORCE_VORTEX));
  mrb_define_const(mrb, bnd_icon_module, "FORCE_MAGNETIC", mrb_fixnum_value(BND_ICON_FORCE_MAGNETIC));
  mrb_define_const(mrb, bnd_icon_module, "FORCE_HARMONIC", mrb_fixnum_value(BND_ICON_FORCE_HARMONIC));
  mrb_define_const(mrb, bnd_icon_module, "FORCE_CHARGE", mrb_fixnum_value(BND_ICON_FORCE_CHARGE));
  mrb_define_const(mrb, bnd_icon_module, "FORCE_LENNARDJONES", mrb_fixnum_value(BND_ICON_FORCE_LENNARDJONES));
  mrb_define_const(mrb, bnd_icon_module, "FORCE_TEXTURE", mrb_fixnum_value(BND_ICON_FORCE_TEXTURE));
  mrb_define_const(mrb, bnd_icon_module, "FORCE_CURVE", mrb_fixnum_value(BND_ICON_FORCE_CURVE));
  mrb_define_const(mrb, bnd_icon_module, "FORCE_BOID", mrb_fixnum_value(BND_ICON_FORCE_BOID));
  mrb_define_const(mrb, bnd_icon_module, "FORCE_TURBULENCE", mrb_fixnum_value(BND_ICON_FORCE_TURBULENCE));
  mrb_define_const(mrb, bnd_icon_module, "FORCE_DRAG", mrb_fixnum_value(BND_ICON_FORCE_DRAG));
  mrb_define_const(mrb, bnd_icon_module, "FORCE_SMOKEFLOW", mrb_fixnum_value(BND_ICON_FORCE_SMOKEFLOW));
  mrb_define_const(mrb, bnd_icon_module, "MODIFIER", mrb_fixnum_value(BND_ICON_MODIFIER));
  mrb_define_const(mrb, bnd_icon_module, "MOD_WAVE", mrb_fixnum_value(BND_ICON_MOD_WAVE));
  mrb_define_const(mrb, bnd_icon_module, "MOD_BUILD", mrb_fixnum_value(BND_ICON_MOD_BUILD));
  mrb_define_const(mrb, bnd_icon_module, "MOD_DECIM", mrb_fixnum_value(BND_ICON_MOD_DECIM));
  mrb_define_const(mrb, bnd_icon_module, "MOD_MIRROR", mrb_fixnum_value(BND_ICON_MOD_MIRROR));
  mrb_define_const(mrb, bnd_icon_module, "MOD_SOFT", mrb_fixnum_value(BND_ICON_MOD_SOFT));
  mrb_define_const(mrb, bnd_icon_module, "MOD_SUBSURF", mrb_fixnum_value(BND_ICON_MOD_SUBSURF));
  mrb_define_const(mrb, bnd_icon_module, "HOOK", mrb_fixnum_value(BND_ICON_HOOK));
  mrb_define_const(mrb, bnd_icon_module, "MOD_PHYSICS", mrb_fixnum_value(BND_ICON_MOD_PHYSICS));
  mrb_define_const(mrb, bnd_icon_module, "MOD_PARTICLES", mrb_fixnum_value(BND_ICON_MOD_PARTICLES));
  mrb_define_const(mrb, bnd_icon_module, "MOD_BOOLEAN", mrb_fixnum_value(BND_ICON_MOD_BOOLEAN));
  mrb_define_const(mrb, bnd_icon_module, "MOD_EDGESPLIT", mrb_fixnum_value(BND_ICON_MOD_EDGESPLIT));
  mrb_define_const(mrb, bnd_icon_module, "MOD_ARRAY", mrb_fixnum_value(BND_ICON_MOD_ARRAY));
  mrb_define_const(mrb, bnd_icon_module, "MOD_UVPROJECT", mrb_fixnum_value(BND_ICON_MOD_UVPROJECT));
  mrb_define_const(mrb, bnd_icon_module, "MOD_DISPLACE", mrb_fixnum_value(BND_ICON_MOD_DISPLACE));
  mrb_define_const(mrb, bnd_icon_module, "MOD_CURVE", mrb_fixnum_value(BND_ICON_MOD_CURVE));
  mrb_define_const(mrb, bnd_icon_module, "MOD_LATTICE", mrb_fixnum_value(BND_ICON_MOD_LATTICE));
  mrb_define_const(mrb, bnd_icon_module, "CONSTRAINT_DATA", mrb_fixnum_value(BND_ICON_CONSTRAINT_DATA));
  mrb_define_const(mrb, bnd_icon_module, "MOD_ARMATURE", mrb_fixnum_value(BND_ICON_MOD_ARMATURE));
  mrb_define_const(mrb, bnd_icon_module, "MOD_SHRINKWRAP", mrb_fixnum_value(BND_ICON_MOD_SHRINKWRAP));
  mrb_define_const(mrb, bnd_icon_module, "MOD_CAST", mrb_fixnum_value(BND_ICON_MOD_CAST));
  mrb_define_const(mrb, bnd_icon_module, "MOD_MESHDEFORM", mrb_fixnum_value(BND_ICON_MOD_MESHDEFORM));
  mrb_define_const(mrb, bnd_icon_module, "MOD_BEVEL", mrb_fixnum_value(BND_ICON_MOD_BEVEL));
  mrb_define_const(mrb, bnd_icon_module, "MOD_SMOOTH", mrb_fixnum_value(BND_ICON_MOD_SMOOTH));
  mrb_define_const(mrb, bnd_icon_module, "MOD_SIMPLEDEFORM", mrb_fixnum_value(BND_ICON_MOD_SIMPLEDEFORM));
  mrb_define_const(mrb, bnd_icon_module, "MOD_MASK", mrb_fixnum_value(BND_ICON_MOD_MASK));
  mrb_define_const(mrb, bnd_icon_module, "MOD_CLOTH", mrb_fixnum_value(BND_ICON_MOD_CLOTH));
  mrb_define_const(mrb, bnd_icon_module, "MOD_EXPLODE", mrb_fixnum_value(BND_ICON_MOD_EXPLODE));
  mrb_define_const(mrb, bnd_icon_module, "MOD_FLUIDSIM", mrb_fixnum_value(BND_ICON_MOD_FLUIDSIM));
  mrb_define_const(mrb, bnd_icon_module, "MOD_MULTIRES", mrb_fixnum_value(BND_ICON_MOD_MULTIRES));
  mrb_define_const(mrb, bnd_icon_module, "MOD_SMOKE", mrb_fixnum_value(BND_ICON_MOD_SMOKE));
  mrb_define_const(mrb, bnd_icon_module, "MOD_SOLIDIFY", mrb_fixnum_value(BND_ICON_MOD_SOLIDIFY));
  mrb_define_const(mrb, bnd_icon_module, "MOD_SCREW", mrb_fixnum_value(BND_ICON_MOD_SCREW));
  mrb_define_const(mrb, bnd_icon_module, "MOD_VERTEX_WEIGHT", mrb_fixnum_value(BND_ICON_MOD_VERTEX_WEIGHT));
  mrb_define_const(mrb, bnd_icon_module, "MOD_DYNAMICPAINT", mrb_fixnum_value(BND_ICON_MOD_DYNAMICPAINT));
  mrb_define_const(mrb, bnd_icon_module, "MOD_REMESH", mrb_fixnum_value(BND_ICON_MOD_REMESH));
  mrb_define_const(mrb, bnd_icon_module, "MOD_OCEAN", mrb_fixnum_value(BND_ICON_MOD_OCEAN));
  mrb_define_const(mrb, bnd_icon_module, "MOD_WARP", mrb_fixnum_value(BND_ICON_MOD_WARP));
  mrb_define_const(mrb, bnd_icon_module, "MOD_SKIN", mrb_fixnum_value(BND_ICON_MOD_SKIN));
  mrb_define_const(mrb, bnd_icon_module, "MOD_TRIANGULATE", mrb_fixnum_value(BND_ICON_MOD_TRIANGULATE));
  mrb_define_const(mrb, bnd_icon_module, "MOD_WIREFRAME", mrb_fixnum_value(BND_ICON_MOD_WIREFRAME));
  mrb_define_const(mrb, bnd_icon_module, "REC", mrb_fixnum_value(BND_ICON_REC));
  mrb_define_const(mrb, bnd_icon_module, "PLAY", mrb_fixnum_value(BND_ICON_PLAY));
  mrb_define_const(mrb, bnd_icon_module, "FF", mrb_fixnum_value(BND_ICON_FF));
  mrb_define_const(mrb, bnd_icon_module, "REW", mrb_fixnum_value(BND_ICON_REW));
  mrb_define_const(mrb, bnd_icon_module, "PAUSE", mrb_fixnum_value(BND_ICON_PAUSE));
  mrb_define_const(mrb, bnd_icon_module, "PREV_KEYFRAME", mrb_fixnum_value(BND_ICON_PREV_KEYFRAME));
  mrb_define_const(mrb, bnd_icon_module, "NEXT_KEYFRAME", mrb_fixnum_value(BND_ICON_NEXT_KEYFRAME));
  mrb_define_const(mrb, bnd_icon_module, "PLAY_AUDIO", mrb_fixnum_value(BND_ICON_PLAY_AUDIO));
  mrb_define_const(mrb, bnd_icon_module, "PLAY_REVERSE", mrb_fixnum_value(BND_ICON_PLAY_REVERSE));
  mrb_define_const(mrb, bnd_icon_module, "PREVIEW_RANGE", mrb_fixnum_value(BND_ICON_PREVIEW_RANGE));
  mrb_define_const(mrb, bnd_icon_module, "ACTION_TWEAK", mrb_fixnum_value(BND_ICON_ACTION_TWEAK));
  mrb_define_const(mrb, bnd_icon_module, "PMARKER_ACT", mrb_fixnum_value(BND_ICON_PMARKER_ACT));
  mrb_define_const(mrb, bnd_icon_module, "PMARKER_SEL", mrb_fixnum_value(BND_ICON_PMARKER_SEL));
  mrb_define_const(mrb, bnd_icon_module, "PMARKER", mrb_fixnum_value(BND_ICON_PMARKER));
  mrb_define_const(mrb, bnd_icon_module, "MARKER_HLT", mrb_fixnum_value(BND_ICON_MARKER_HLT));
  mrb_define_const(mrb, bnd_icon_module, "MARKER", mrb_fixnum_value(BND_ICON_MARKER));
  mrb_define_const(mrb, bnd_icon_module, "SPACE2", mrb_fixnum_value(BND_ICON_SPACE2));
  mrb_define_const(mrb, bnd_icon_module, "SPACE3", mrb_fixnum_value(BND_ICON_SPACE3));
  mrb_define_const(mrb, bnd_icon_module, "KEYINGSET", mrb_fixnum_value(BND_ICON_KEYINGSET));
  mrb_define_const(mrb, bnd_icon_module, "KEY_DEHLT", mrb_fixnum_value(BND_ICON_KEY_DEHLT));
  mrb_define_const(mrb, bnd_icon_module, "KEY_HLT", mrb_fixnum_value(BND_ICON_KEY_HLT));
  mrb_define_const(mrb, bnd_icon_module, "MUTE_IPO_OFF", mrb_fixnum_value(BND_ICON_MUTE_IPO_OFF));
  mrb_define_const(mrb, bnd_icon_module, "MUTE_IPO_ON", mrb_fixnum_value(BND_ICON_MUTE_IPO_ON));
  mrb_define_const(mrb, bnd_icon_module, "VISIBLE_IPO_OFF", mrb_fixnum_value(BND_ICON_VISIBLE_IPO_OFF));
  mrb_define_const(mrb, bnd_icon_module, "VISIBLE_IPO_ON", mrb_fixnum_value(BND_ICON_VISIBLE_IPO_ON));
  mrb_define_const(mrb, bnd_icon_module, "DRIVER", mrb_fixnum_value(BND_ICON_DRIVER));
  mrb_define_const(mrb, bnd_icon_module, "SOLO_OFF", mrb_fixnum_value(BND_ICON_SOLO_OFF));
  mrb_define_const(mrb, bnd_icon_module, "SOLO_ON", mrb_fixnum_value(BND_ICON_SOLO_ON));
  mrb_define_const(mrb, bnd_icon_module, "FRAME_PREV", mrb_fixnum_value(BND_ICON_FRAME_PREV));
  mrb_define_const(mrb, bnd_icon_module, "FRAME_NEXT", mrb_fixnum_value(BND_ICON_FRAME_NEXT));
  mrb_define_const(mrb, bnd_icon_module, "NLA_PUSHDOWN", mrb_fixnum_value(BND_ICON_NLA_PUSHDOWN));
  mrb_define_const(mrb, bnd_icon_module, "IPO_CONSTANT", mrb_fixnum_value(BND_ICON_IPO_CONSTANT));
  mrb_define_const(mrb, bnd_icon_module, "IPO_LINEAR", mrb_fixnum_value(BND_ICON_IPO_LINEAR));
  mrb_define_const(mrb, bnd_icon_module, "IPO_BEZIER", mrb_fixnum_value(BND_ICON_IPO_BEZIER));
  mrb_define_const(mrb, bnd_icon_module, "IPO_SINE", mrb_fixnum_value(BND_ICON_IPO_SINE));
  mrb_define_const(mrb, bnd_icon_module, "IPO_QUAD", mrb_fixnum_value(BND_ICON_IPO_QUAD));
  mrb_define_const(mrb, bnd_icon_module, "IPO_CUBIC", mrb_fixnum_value(BND_ICON_IPO_CUBIC));
  mrb_define_const(mrb, bnd_icon_module, "IPO_QUART", mrb_fixnum_value(BND_ICON_IPO_QUART));
  mrb_define_const(mrb, bnd_icon_module, "IPO_QUINT", mrb_fixnum_value(BND_ICON_IPO_QUINT));
  mrb_define_const(mrb, bnd_icon_module, "IPO_EXPO", mrb_fixnum_value(BND_ICON_IPO_EXPO));
  mrb_define_const(mrb, bnd_icon_module, "IPO_CIRC", mrb_fixnum_value(BND_ICON_IPO_CIRC));
  mrb_define_const(mrb, bnd_icon_module, "IPO_BOUNCE", mrb_fixnum_value(BND_ICON_IPO_BOUNCE));
  mrb_define_const(mrb, bnd_icon_module, "IPO_ELASTIC", mrb_fixnum_value(BND_ICON_IPO_ELASTIC));
  mrb_define_const(mrb, bnd_icon_module, "IPO_BACK", mrb_fixnum_value(BND_ICON_IPO_BACK));
  mrb_define_const(mrb, bnd_icon_module, "IPO_EASE_IN", mrb_fixnum_value(BND_ICON_IPO_EASE_IN));
  mrb_define_const(mrb, bnd_icon_module, "IPO_EASE_OUT", mrb_fixnum_value(BND_ICON_IPO_EASE_OUT));
  mrb_define_const(mrb, bnd_icon_module, "IPO_EASE_IN_OUT", mrb_fixnum_value(BND_ICON_IPO_EASE_IN_OUT));
  mrb_define_const(mrb, bnd_icon_module, "VERTEXSEL", mrb_fixnum_value(BND_ICON_VERTEXSEL));
  mrb_define_const(mrb, bnd_icon_module, "EDGESEL", mrb_fixnum_value(BND_ICON_EDGESEL));
  mrb_define_const(mrb, bnd_icon_module, "FACESEL", mrb_fixnum_value(BND_ICON_FACESEL));
  mrb_define_const(mrb, bnd_icon_module, "LOOPSEL", mrb_fixnum_value(BND_ICON_LOOPSEL));
  mrb_define_const(mrb, bnd_icon_module, "ROTATE", mrb_fixnum_value(BND_ICON_ROTATE));
  mrb_define_const(mrb, bnd_icon_module, "CURSOR", mrb_fixnum_value(BND_ICON_CURSOR));
  mrb_define_const(mrb, bnd_icon_module, "ROTATECOLLECTION", mrb_fixnum_value(BND_ICON_ROTATECOLLECTION));
  mrb_define_const(mrb, bnd_icon_module, "ROTATECENTER", mrb_fixnum_value(BND_ICON_ROTATECENTER));
  mrb_define_const(mrb, bnd_icon_module, "ROTACTIVE", mrb_fixnum_value(BND_ICON_ROTACTIVE));
  mrb_define_const(mrb, bnd_icon_module, "ALIGN", mrb_fixnum_value(BND_ICON_ALIGN));
  mrb_define_const(mrb, bnd_icon_module, "SMOOTHCURVE", mrb_fixnum_value(BND_ICON_SMOOTHCURVE));
  mrb_define_const(mrb, bnd_icon_module, "SPHERECURVE", mrb_fixnum_value(BND_ICON_SPHERECURVE));
  mrb_define_const(mrb, bnd_icon_module, "ROOTCURVE", mrb_fixnum_value(BND_ICON_ROOTCURVE));
  mrb_define_const(mrb, bnd_icon_module, "SHARPCURVE", mrb_fixnum_value(BND_ICON_SHARPCURVE));
  mrb_define_const(mrb, bnd_icon_module, "LINCURVE", mrb_fixnum_value(BND_ICON_LINCURVE));
  mrb_define_const(mrb, bnd_icon_module, "NOCURVE", mrb_fixnum_value(BND_ICON_NOCURVE));
  mrb_define_const(mrb, bnd_icon_module, "RNDCURVE", mrb_fixnum_value(BND_ICON_RNDCURVE));
  mrb_define_const(mrb, bnd_icon_module, "PROP_OFF", mrb_fixnum_value(BND_ICON_PROP_OFF));
  mrb_define_const(mrb, bnd_icon_module, "PROP_ON", mrb_fixnum_value(BND_ICON_PROP_ON));
  mrb_define_const(mrb, bnd_icon_module, "PROP_CON", mrb_fixnum_value(BND_ICON_PROP_CON));
  mrb_define_const(mrb, bnd_icon_module, "SCULPT_DYNTOPO", mrb_fixnum_value(BND_ICON_SCULPT_DYNTOPO));
  mrb_define_const(mrb, bnd_icon_module, "PARTICLE_POINT", mrb_fixnum_value(BND_ICON_PARTICLE_POINT));
  mrb_define_const(mrb, bnd_icon_module, "PARTICLE_TIP", mrb_fixnum_value(BND_ICON_PARTICLE_TIP));
  mrb_define_const(mrb, bnd_icon_module, "PARTICLE_PATH", mrb_fixnum_value(BND_ICON_PARTICLE_PATH));
  mrb_define_const(mrb, bnd_icon_module, "MAN_TRANS", mrb_fixnum_value(BND_ICON_MAN_TRANS));
  mrb_define_const(mrb, bnd_icon_module, "MAN_ROT", mrb_fixnum_value(BND_ICON_MAN_ROT));
  mrb_define_const(mrb, bnd_icon_module, "MAN_SCALE", mrb_fixnum_value(BND_ICON_MAN_SCALE));
  mrb_define_const(mrb, bnd_icon_module, "MANIPUL", mrb_fixnum_value(BND_ICON_MANIPUL));
  mrb_define_const(mrb, bnd_icon_module, "SNAP_OFF", mrb_fixnum_value(BND_ICON_SNAP_OFF));
  mrb_define_const(mrb, bnd_icon_module, "SNAP_ON", mrb_fixnum_value(BND_ICON_SNAP_ON));
  mrb_define_const(mrb, bnd_icon_module, "SNAP_NORMAL", mrb_fixnum_value(BND_ICON_SNAP_NORMAL));
  mrb_define_const(mrb, bnd_icon_module, "SNAP_INCREMENT", mrb_fixnum_value(BND_ICON_SNAP_INCREMENT));
  mrb_define_const(mrb, bnd_icon_module, "SNAP_VERTEX", mrb_fixnum_value(BND_ICON_SNAP_VERTEX));
  mrb_define_const(mrb, bnd_icon_module, "SNAP_EDGE", mrb_fixnum_value(BND_ICON_SNAP_EDGE));
  mrb_define_const(mrb, bnd_icon_module, "SNAP_FACE", mrb_fixnum_value(BND_ICON_SNAP_FACE));
  mrb_define_const(mrb, bnd_icon_module, "SNAP_VOLUME", mrb_fixnum_value(BND_ICON_SNAP_VOLUME));
  mrb_define_const(mrb, bnd_icon_module, "STICKY_UVS_LOC", mrb_fixnum_value(BND_ICON_STICKY_UVS_LOC));
  mrb_define_const(mrb, bnd_icon_module, "STICKY_UVS_DISABLE", mrb_fixnum_value(BND_ICON_STICKY_UVS_DISABLE));
  mrb_define_const(mrb, bnd_icon_module, "STICKY_UVS_VERT", mrb_fixnum_value(BND_ICON_STICKY_UVS_VERT));
  mrb_define_const(mrb, bnd_icon_module, "CLIPUV_DEHLT", mrb_fixnum_value(BND_ICON_CLIPUV_DEHLT));
  mrb_define_const(mrb, bnd_icon_module, "CLIPUV_HLT", mrb_fixnum_value(BND_ICON_CLIPUV_HLT));
  mrb_define_const(mrb, bnd_icon_module, "SNAP_PEEL_OBJECT", mrb_fixnum_value(BND_ICON_SNAP_PEEL_OBJECT));
  mrb_define_const(mrb, bnd_icon_module, "GRID", mrb_fixnum_value(BND_ICON_GRID));
  mrb_define_const(mrb, bnd_icon_module, "PASTEDOWN", mrb_fixnum_value(BND_ICON_PASTEDOWN));
  mrb_define_const(mrb, bnd_icon_module, "COPYDOWN", mrb_fixnum_value(BND_ICON_COPYDOWN));
  mrb_define_const(mrb, bnd_icon_module, "PASTEFLIPUP", mrb_fixnum_value(BND_ICON_PASTEFLIPUP));
  mrb_define_const(mrb, bnd_icon_module, "PASTEFLIPDOWN", mrb_fixnum_value(BND_ICON_PASTEFLIPDOWN));
  mrb_define_const(mrb, bnd_icon_module, "SNAP_SURFACE", mrb_fixnum_value(BND_ICON_SNAP_SURFACE));
  mrb_define_const(mrb, bnd_icon_module, "AUTOMERGE_ON", mrb_fixnum_value(BND_ICON_AUTOMERGE_ON));
  mrb_define_const(mrb, bnd_icon_module, "AUTOMERGE_OFF", mrb_fixnum_value(BND_ICON_AUTOMERGE_OFF));
  mrb_define_const(mrb, bnd_icon_module, "RETOPO", mrb_fixnum_value(BND_ICON_RETOPO));
  mrb_define_const(mrb, bnd_icon_module, "UV_VERTEXSEL", mrb_fixnum_value(BND_ICON_UV_VERTEXSEL));
  mrb_define_const(mrb, bnd_icon_module, "UV_EDGESEL", mrb_fixnum_value(BND_ICON_UV_EDGESEL));
  mrb_define_const(mrb, bnd_icon_module, "UV_FACESEL", mrb_fixnum_value(BND_ICON_UV_FACESEL));
  mrb_define_const(mrb, bnd_icon_module, "UV_ISLANDSEL", mrb_fixnum_value(BND_ICON_UV_ISLANDSEL));
  mrb_define_const(mrb, bnd_icon_module, "UV_SYNC_SELECT", mrb_fixnum_value(BND_ICON_UV_SYNC_SELECT));
  mrb_define_const(mrb, bnd_icon_module, "BBOX", mrb_fixnum_value(BND_ICON_BBOX));
  mrb_define_const(mrb, bnd_icon_module, "WIRE", mrb_fixnum_value(BND_ICON_WIRE));
  mrb_define_const(mrb, bnd_icon_module, "SOLID", mrb_fixnum_value(BND_ICON_SOLID));
  mrb_define_const(mrb, bnd_icon_module, "SMOOTH", mrb_fixnum_value(BND_ICON_SMOOTH));
  mrb_define_const(mrb, bnd_icon_module, "POTATO", mrb_fixnum_value(BND_ICON_POTATO));
  mrb_define_const(mrb, bnd_icon_module, "ORTHO", mrb_fixnum_value(BND_ICON_ORTHO));
  mrb_define_const(mrb, bnd_icon_module, "LOCKVIEW_OFF", mrb_fixnum_value(BND_ICON_LOCKVIEW_OFF));
  mrb_define_const(mrb, bnd_icon_module, "LOCKVIEW_ON", mrb_fixnum_value(BND_ICON_LOCKVIEW_ON));
  mrb_define_const(mrb, bnd_icon_module, "AXIS_SIDE", mrb_fixnum_value(BND_ICON_AXIS_SIDE));
  mrb_define_const(mrb, bnd_icon_module, "AXIS_FRONT", mrb_fixnum_value(BND_ICON_AXIS_FRONT));
  mrb_define_const(mrb, bnd_icon_module, "AXIS_TOP", mrb_fixnum_value(BND_ICON_AXIS_TOP));
  mrb_define_const(mrb, bnd_icon_module, "NDOF_DOM", mrb_fixnum_value(BND_ICON_NDOF_DOM));
  mrb_define_const(mrb, bnd_icon_module, "NDOF_TURN", mrb_fixnum_value(BND_ICON_NDOF_TURN));
  mrb_define_const(mrb, bnd_icon_module, "NDOF_FLY", mrb_fixnum_value(BND_ICON_NDOF_FLY));
  mrb_define_const(mrb, bnd_icon_module, "NDOF_TRANS", mrb_fixnum_value(BND_ICON_NDOF_TRANS));
  mrb_define_const(mrb, bnd_icon_module, "LAYER_USED", mrb_fixnum_value(BND_ICON_LAYER_USED));
  mrb_define_const(mrb, bnd_icon_module, "LAYER_ACTIVE", mrb_fixnum_value(BND_ICON_LAYER_ACTIVE));
  mrb_define_const(mrb, bnd_icon_module, "SORTALPHA", mrb_fixnum_value(BND_ICON_SORTALPHA));
  mrb_define_const(mrb, bnd_icon_module, "SORTBYEXT", mrb_fixnum_value(BND_ICON_SORTBYEXT));
  mrb_define_const(mrb, bnd_icon_module, "SORTTIME", mrb_fixnum_value(BND_ICON_SORTTIME));
  mrb_define_const(mrb, bnd_icon_module, "SORTSIZE", mrb_fixnum_value(BND_ICON_SORTSIZE));
  mrb_define_const(mrb, bnd_icon_module, "LONGDISPLAY", mrb_fixnum_value(BND_ICON_LONGDISPLAY));
  mrb_define_const(mrb, bnd_icon_module, "SHORTDISPLAY", mrb_fixnum_value(BND_ICON_SHORTDISPLAY));
  mrb_define_const(mrb, bnd_icon_module, "GHOST", mrb_fixnum_value(BND_ICON_GHOST));
  mrb_define_const(mrb, bnd_icon_module, "IMGDISPLAY", mrb_fixnum_value(BND_ICON_IMGDISPLAY));
  mrb_define_const(mrb, bnd_icon_module, "SAVE_AS", mrb_fixnum_value(BND_ICON_SAVE_AS));
  mrb_define_const(mrb, bnd_icon_module, "SAVE_COPY", mrb_fixnum_value(BND_ICON_SAVE_COPY));
  mrb_define_const(mrb, bnd_icon_module, "BOOKMARKS", mrb_fixnum_value(BND_ICON_BOOKMARKS));
  mrb_define_const(mrb, bnd_icon_module, "FONTPREVIEW", mrb_fixnum_value(BND_ICON_FONTPREVIEW));
  mrb_define_const(mrb, bnd_icon_module, "FILTER", mrb_fixnum_value(BND_ICON_FILTER));
  mrb_define_const(mrb, bnd_icon_module, "NEWFOLDER", mrb_fixnum_value(BND_ICON_NEWFOLDER));
  mrb_define_const(mrb, bnd_icon_module, "OPEN_RECENT", mrb_fixnum_value(BND_ICON_OPEN_RECENT));
  mrb_define_const(mrb, bnd_icon_module, "FILE_PARENT", mrb_fixnum_value(BND_ICON_FILE_PARENT));
  mrb_define_const(mrb, bnd_icon_module, "FILE_REFRESH", mrb_fixnum_value(BND_ICON_FILE_REFRESH));
  mrb_define_const(mrb, bnd_icon_module, "FILE_FOLDER", mrb_fixnum_value(BND_ICON_FILE_FOLDER));
  mrb_define_const(mrb, bnd_icon_module, "FILE_BLANK", mrb_fixnum_value(BND_ICON_FILE_BLANK));
  mrb_define_const(mrb, bnd_icon_module, "FILE_BLEND", mrb_fixnum_value(BND_ICON_FILE_BLEND));
  mrb_define_const(mrb, bnd_icon_module, "FILE_IMAGE", mrb_fixnum_value(BND_ICON_FILE_IMAGE));
  mrb_define_const(mrb, bnd_icon_module, "FILE_MOVIE", mrb_fixnum_value(BND_ICON_FILE_MOVIE));
  mrb_define_const(mrb, bnd_icon_module, "FILE_SCRIPT", mrb_fixnum_value(BND_ICON_FILE_SCRIPT));
  mrb_define_const(mrb, bnd_icon_module, "FILE_SOUND", mrb_fixnum_value(BND_ICON_FILE_SOUND));
  mrb_define_const(mrb, bnd_icon_module, "FILE_FONT", mrb_fixnum_value(BND_ICON_FILE_FONT));
  mrb_define_const(mrb, bnd_icon_module, "FILE_TEXT", mrb_fixnum_value(BND_ICON_FILE_TEXT));
  mrb_define_const(mrb, bnd_icon_module, "RECOVER_AUTO", mrb_fixnum_value(BND_ICON_RECOVER_AUTO));
  mrb_define_const(mrb, bnd_icon_module, "SAVE_PREFS", mrb_fixnum_value(BND_ICON_SAVE_PREFS));
  mrb_define_const(mrb, bnd_icon_module, "LINK_BLEND", mrb_fixnum_value(BND_ICON_LINK_BLEND));
  mrb_define_const(mrb, bnd_icon_module, "APPEND_BLEND", mrb_fixnum_value(BND_ICON_APPEND_BLEND));
  mrb_define_const(mrb, bnd_icon_module, "IMPORT", mrb_fixnum_value(BND_ICON_IMPORT));
  mrb_define_const(mrb, bnd_icon_module, "EXPORT", mrb_fixnum_value(BND_ICON_EXPORT));
  mrb_define_const(mrb, bnd_icon_module, "EXTERNAL_DATA", mrb_fixnum_value(BND_ICON_EXTERNAL_DATA));
  mrb_define_const(mrb, bnd_icon_module, "LOAD_FACTORY", mrb_fixnum_value(BND_ICON_LOAD_FACTORY));
  mrb_define_const(mrb, bnd_icon_module, "LOOP_BACK", mrb_fixnum_value(BND_ICON_LOOP_BACK));
  mrb_define_const(mrb, bnd_icon_module, "LOOP_FORWARDS", mrb_fixnum_value(BND_ICON_LOOP_FORWARDS));
  mrb_define_const(mrb, bnd_icon_module, "BACK", mrb_fixnum_value(BND_ICON_BACK));
  mrb_define_const(mrb, bnd_icon_module, "FORWARD", mrb_fixnum_value(BND_ICON_FORWARD));
  mrb_define_const(mrb, bnd_icon_module, "FILE_BACKUP", mrb_fixnum_value(BND_ICON_FILE_BACKUP));
  mrb_define_const(mrb, bnd_icon_module, "DISK_DRIVE", mrb_fixnum_value(BND_ICON_DISK_DRIVE));
  mrb_define_const(mrb, bnd_icon_module, "MATPLANE", mrb_fixnum_value(BND_ICON_MATPLANE));
  mrb_define_const(mrb, bnd_icon_module, "MATSPHERE", mrb_fixnum_value(BND_ICON_MATSPHERE));
  mrb_define_const(mrb, bnd_icon_module, "MATCUBE", mrb_fixnum_value(BND_ICON_MATCUBE));
  mrb_define_const(mrb, bnd_icon_module, "MONKEY", mrb_fixnum_value(BND_ICON_MONKEY));
  mrb_define_const(mrb, bnd_icon_module, "HAIR", mrb_fixnum_value(BND_ICON_HAIR));
  mrb_define_const(mrb, bnd_icon_module, "ALIASED", mrb_fixnum_value(BND_ICON_ALIASED));
  mrb_define_const(mrb, bnd_icon_module, "ANTIALIASED", mrb_fixnum_value(BND_ICON_ANTIALIASED));
  mrb_define_const(mrb, bnd_icon_module, "MAT_SPHERE_SKY", mrb_fixnum_value(BND_ICON_MAT_SPHERE_SKY));
  mrb_define_const(mrb, bnd_icon_module, "WORDWRAP_OFF", mrb_fixnum_value(BND_ICON_WORDWRAP_OFF));
  mrb_define_const(mrb, bnd_icon_module, "WORDWRAP_ON", mrb_fixnum_value(BND_ICON_WORDWRAP_ON));
  mrb_define_const(mrb, bnd_icon_module, "SYNTAX_OFF", mrb_fixnum_value(BND_ICON_SYNTAX_OFF));
  mrb_define_const(mrb, bnd_icon_module, "SYNTAX_ON", mrb_fixnum_value(BND_ICON_SYNTAX_ON));
  mrb_define_const(mrb, bnd_icon_module, "LINENUMBERS_OFF", mrb_fixnum_value(BND_ICON_LINENUMBERS_OFF));
  mrb_define_const(mrb, bnd_icon_module, "LINENUMBERS_ON", mrb_fixnum_value(BND_ICON_LINENUMBERS_ON));
  mrb_define_const(mrb, bnd_icon_module, "SCRIPTPLUGINS", mrb_fixnum_value(BND_ICON_SCRIPTPLUGINS));
  mrb_define_const(mrb, bnd_icon_module, "SEQ_SEQUENCER", mrb_fixnum_value(BND_ICON_SEQ_SEQUENCER));
  mrb_define_const(mrb, bnd_icon_module, "SEQ_PREVIEW", mrb_fixnum_value(BND_ICON_SEQ_PREVIEW));
  mrb_define_const(mrb, bnd_icon_module, "SEQ_LUMA_WAVEFORM", mrb_fixnum_value(BND_ICON_SEQ_LUMA_WAVEFORM));
  mrb_define_const(mrb, bnd_icon_module, "SEQ_CHROMA_SCOPE", mrb_fixnum_value(BND_ICON_SEQ_CHROMA_SCOPE));
  mrb_define_const(mrb, bnd_icon_module, "SEQ_HISTOGRAM", mrb_fixnum_value(BND_ICON_SEQ_HISTOGRAM));
  mrb_define_const(mrb, bnd_icon_module, "SEQ_SPLITVIEW", mrb_fixnum_value(BND_ICON_SEQ_SPLITVIEW));
  mrb_define_const(mrb, bnd_icon_module, "IMAGE_RGB", mrb_fixnum_value(BND_ICON_IMAGE_RGB));
  mrb_define_const(mrb, bnd_icon_module, "IMAGE_RGB_ALPHA", mrb_fixnum_value(BND_ICON_IMAGE_RGB_ALPHA));
  mrb_define_const(mrb, bnd_icon_module, "IMAGE_ALPHA", mrb_fixnum_value(BND_ICON_IMAGE_ALPHA));
  mrb_define_const(mrb, bnd_icon_module, "IMAGE_ZDEPTH", mrb_fixnum_value(BND_ICON_IMAGE_ZDEPTH));
  mrb_define_const(mrb, bnd_icon_module, "IMAGEFILE", mrb_fixnum_value(BND_ICON_IMAGEFILE));
}

void
mrb_mruby_blendish_gem_final(mrb_state* mrb)
{
  //
}
