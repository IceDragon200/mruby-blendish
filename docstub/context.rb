module OUI
  module Blendish
    class Context
      # @!attribute theme
      #   @return [Theme]
      attr_accessor :theme
      # @!attribute icon_image
      #   @return [Integer]
      attr_writer :icon_image
      # @!attribute icon_image
      #   @return [Integer]
      attr_writer :font

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Integer] iconid
      # @param [String, nil] label
      # @return [self]
      def label(ctx, x, y, w, h, iconid, label)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Integer] flags
      # @param [Integer] state
      # @param [Integer] iconid
      # @param [String, nil] label
      # @return [self]
      def tool_button(ctx, x, y, w, h, flags, state, iconid, label)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Integer] flags
      # @param [Integer] state
      # @param [Integer] iconid
      # @param [String, nil] label
      # @return [self]
      def radio_button(ctx, x, y, w, h, flags, state, iconid, label)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Integer] iconid
      # @param [String, nil] text
      # @param [Integer] px
      # @param [Integer] py
      # @return [Integer]
      def text_field_text_position(ctx, x, y, w, h, iconid, text, px, py)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Integer] flags
      # @param [Integer] state
      # @param [Integer] iconid
      # @param [String, nil] text
      # @param [Integer] cbegin
      # @param [Integer] cend
      # @return [self]
      def text_field(ctx, x, y, w, h, flags, state, iconid, text, cbegin, cend)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Integer] state
      # @param [String, nil] label
      # @return [self]
      def option_button(ctx, x, y, w, h, state, label)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Integer] flags
      # @param [Integer] state
      # @param [Integer] iconid
      # @param [String, nil] label
      # @return [self]
      def choice_button(ctx, x, y, w, h, flags, state, iconid, label)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Integer] flags
      # @param [Nanovg::Color] color
      # @return [self]
      def color_button(ctx, x, y, w, h, flags, color)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Integer] flags
      # @param [Integer] state
      # @param [String, nil] label
      # @param [String, nil] value
      # @return [self]
      def number_field(ctx, x, y, w, h, flags, state, label, value)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Integer] flags
      # @param [Integer] state
      # @param [Float] progress
      # @param [String, nil] label
      # @param [String, nil] value
      # @return [self]
      def slider(ctx, x, y, w, h, flags, state, progress, label, value)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Integer] state
      # @param [Float] offset
      # @param [Float] size
      # @return [self]
      def scroll_bar(ctx, x, y, w, h, state, offset, size)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Integer] flags
      # @return [self]
      def menu_background(ctx, x, y, w, h, flags)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Integer] iconid
      # @param [String, nil] label
      # @return [self]
      def menu_label(ctx, x, y, w, h, iconid, label)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Integer] state
      # @param [Integer] iconid
      # @param [String, nil] label
      # @return [self]
      def menu_item(ctx, x, y, w, h, state, iconid, label)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @return [self]
      def tooltip_background(ctx, x, y, w, h)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Integer] state
      # @param [Nanovg::Color] color
      # @return [self]
      def node_port(ctx, x, y, state, color)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x0
      # @param [Float] y0
      # @param [Float] x1
      # @param [Float] y1
      # @param [Integer] state0
      # @param [Integer] state1
      # @return [self]
      def node_wire(ctx, x0, y0, x1, y1, state0, state1)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x0
      # @param [Float] y0
      # @param [Float] x1
      # @param [Float] y1
      # @param [Nanovg::Color] color0
      # @param [Nanovg::Color] color1
      # @return [self]
      def colored_node_wire(ctx, x0, y0, x1, y1, color0, color1)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Integer] state
      # @param [Integer] iconid
      # @param [String, nil] label
      # @param [Nanovg::Color] title_color
      # @return [self]
      def node_background(ctx, x, y, w, h, state, iconid, label, title_color)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @return [self]
      def splitter_widgets(ctx, x, y, w, h)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Boolean] vertical
      # @param [Boolean] mirror
      # @return [self]
      def join_area_overlay(ctx, x, y, w, h, vertical, mirror)
      end

      # @param [Nanovg::Context] ctx
      # @param [Integer] iconid
      # @param [String] label
      # @return [Float]
      def label_width(ctx, iconid, label)
      end

      # @param [Nanovg::Context] ctx
      # @param [Integer] iconid
      # @param [String] label
      # @param [Float] width
      # @return [Float]
      def label_height(ctx, iconid, label, width)
      end

      # @param [Nanovg::Color] color
      # @return [Nanovg::Color]
      def transparent(color)
      end

      # @param [Nanovg::Color] color
      # @param [Float] delta
      # @return [Nanovg::Color]
      def offset_color(color, delta)
      end

      # @param [Float] r
      # @param [Integer] flags
      # @return [Array<Float>[4]]
      def select_corners(r, flags)
      end

      # @param [WidgetTheme] theme
      # @param [Integer] state
      # @param [Boolean] flip_active
      # @param [Nanovg::Color] shade_top
      # @param [Nanovg::Color] shade_down
      # @return [Array<Nanovg::Color>[2]] the new shade_top and shade_down
      def inner_colors(theme, state, flip_active, shade_top, shade_down)
      end

      # @param [WidgetTheme] theme
      # @param [Integer] state
      # @return [Nanovg::Color]
      def text_color(theme, state)
      end

      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Float] offset
      # @param [Float] size
      # @return [Array<Float>[4]]
      def scroll_handle_rect(x, y, w, h, offset, size)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Float] cr0
      # @param [Float] cr1
      # @param [Float] cr2
      # @param [Float] cr3
      # @return [self]
      def rounded_box()
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @return [self]
      def background(ctx, x, y, w, h)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @return [self]
      def bevel(ctx, x, y, w, h)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Float] cr2
      # @param [Float] cr3
      # @return [self]
      def bevel_inset(ctx, x, y, w, h, cr2, cr3)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Integer] iconid
      # @return [self]
      def icon(ctx, x, y, iconid)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Float] r
      # @param [Float] feather
      # @param [Float] alpha
      # @return [self]
      def drop_shadow(ctx, x, y, w, h, r, feather, alpha)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Float] cr0
      # @param [Float] cr1
      # @param [Float] cr2
      # @param [Float] cr3
      # @param [Nanovg::Color] shade_top
      # @param [Nanovg::Color] shade_down
      # @return [self]
      def inner_box(ctx, x, y, w, h, cr0, cr1, cr2, cr3, shade_top, shade_down)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Float] cr0
      # @param [Float] cr1
      # @param [Float] cr2
      # @param [Float] cr3
      # @param [Nanovg::Color] color
      # @return [self]
      def outline_box(x, y, w, h, cr0, cr1, cr2, cr3, color)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Integer] iconid
      # @param [Nanovg::Color] color
      # @param [Integer] align
      # @param [Float] fontsize
      # @param [String, nil] label
      # @param [String, nil] value
      # @return [self]
      def icon_label_value(ctx, x, y, w, h, iconid, color, align, fontsize, label, value)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Integer] iconid
      # @param [Nanovg::Color] color
      # @param [Nanovg::Color] shadow_color
      # @param [Integer] align
      # @param [Float] fontsize
      # @param [String, nil] label
      # @return [self]
      def node_icon_label(ctx, x, y, w, h, iconid, color, shadow_color)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Integer] iconid
      # @param [Float] fontsize
      # @param [String, nil] label
      # @param [Integer] px
      # @param [Integer] py
      # @return [Integer]
      def icon_label_text_position(ctx, x, y, w, h, iconid, fontsize, label, px, py)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] w
      # @param [Float] h
      # @param [Integer] iconid
      # @param [Nanovg::Color] color
      # @param [Float] fontsize
      # @param [String, nil] label
      # @param [Nanovg::Color] caretcolor
      # @param [Integer] cbegin
      # @param [Integer] cend
      def icon_label_caret(ctx, x, y, w, h, iconid, color, fontsize, label, caretcolor, cbegin, cend)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] ox
      # @param [Float] oy
      # @param [Nanovg::Color] color
      def check(ctx, ox, oy, color)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] s
      # @param [Nanovg::Color] color
      def arrow(ctx, x, y, s, color)
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] s
      # @param [Nanovg::Color] color
      def up_down_arrow()
      end

      # @param [Nanovg::Context] ctx
      # @param [Float] x
      # @param [Float] y
      # @param [Float] s
      # @param [Nanovg::Color] color
      # @return [self]
      def node_arrow_down(ctx, x, y, s, color)
      end

      # @param [NodeTheme] theme
      # @param [Integer] state
      # @return [Nanovg::Color]
      def node_wire_color()
      end
    end
  end
end
