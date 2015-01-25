#ifndef MRUBY_BND_COMMON_H
#define MRUBY_BND_COMMON_H

#include <mruby.h>
#include <mruby/value.h>
#include <mruby/data.h>

#include <nanovg.h>
#include <oui.h>
#define BLENDISH_NO_NVG_TYPEDEFS
#include <blendish.h>

extern mrb_value mrb_nvg_color_value(mrb_state*, NVGcolor);
extern const struct mrb_data_type mrb_nvg_color_type;
extern const struct mrb_data_type mrb_nvg_context_type;

#endif
