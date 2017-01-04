#ifndef MRUBY_BND_COMMON_H
#define MRUBY_BND_COMMON_H

#include <stdbool.h>
#include <memory.h>

#include <mruby.h>
#include <mruby/value.h>
#include <mruby/data.h>

#include <nanovg.h>
#include <oui.h>
#define BLENDISH_NO_NVG_TYPEDEFS
#include <blendish.h>

#define MRB_BND_EXTERN extern

MRB_BND_EXTERN mrb_value mrb_nvg_color_value(mrb_state*, NVGcolor);
MRB_BND_EXTERN const struct mrb_data_type mrb_nvg_color_type;
MRB_BND_EXTERN const struct mrb_data_type mrb_nvg_context_type;

#endif
