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
      def text_field()
      end

      # @param [Nanovg::Context] ctx
      def option_button()
      end

      # @param [Nanovg::Context] ctx
      def choice_button()
      end

      # @param [Nanovg::Context] ctx
      def color_button()
      end

      # @param [Nanovg::Context] ctx
      def number_field()
      end

      # @param [Nanovg::Context] ctx
      def slider()
      end

      # @param [Nanovg::Context] ctx
      def scroll_bar()
      end

      # @param [Nanovg::Context] ctx
      def menu_background()
      end

      # @param [Nanovg::Context] ctx
      def menu_label()
      end

      # @param [Nanovg::Context] ctx
      def menu_item()
      end

      # @param [Nanovg::Context] ctx
      def tooltip_background()
      end

      # @param [Nanovg::Context] ctx
      def node_port()
      end

      # @param [Nanovg::Context] ctx
      def node_wire()
      end

      # @param [Nanovg::Context] ctx
      def colored_node_wire()
      end

      # @param [Nanovg::Context] ctx
      def node_background()
      end

      # @param [Nanovg::Context] ctx
      def splitter_widgets()
      end

      # @param [Nanovg::Context] ctx
      def join_area_overlay()
      end

      # @param [Nanovg::Context] ctx
      def label_width()
      end

      # @param [Nanovg::Context] ctx
      def label_height()
      end

      # @param [Nanovg::Context] ctx
      def transparent()
      end

      # @param [Nanovg::Context] ctx
      def offset_color()
      end

      # @param [Nanovg::Context] ctx
      def select_corners()
      end

      # @param [Nanovg::Context] ctx
      def inner_colors()
      end

      # @param [Nanovg::Context] ctx
      def text_color()
      end

      # @param [Nanovg::Context] ctx
      def scroll_handle_rect()
      end

      # @param [Nanovg::Context] ctx
      def rounded_box()
      end

      # @param [Nanovg::Context] ctx
      def background()
      end

      # @param [Nanovg::Context] ctx
      def bevel()
      end

      # @param [Nanovg::Context] ctx
      def bevel_inset()
      end

      # @param [Nanovg::Context] ctx
      def icon()
      end

      # @param [Nanovg::Context] ctx
      def drop_shadow()
      end

      # @param [Nanovg::Context] ctx
      def inner_box()
      end

      # @param [Nanovg::Context] ctx
      def outline_box()
      end

      # @param [Nanovg::Context] ctx
      def icon_label_value()
      end

      # @param [Nanovg::Context] ctx
      def node_icon_label()
      end

      # @param [Nanovg::Context] ctx
      def icon_label_text_position()
      end

      # @param [Nanovg::Context] ctx
      def icon_label_caret()
      end

      # @param [Nanovg::Context] ctx
      def check()
      end

      # @param [Nanovg::Context] ctx
      def arrow()
      end

      # @param [Nanovg::Context] ctx
      def up_down_arrow()
      end

      # @param [Nanovg::Context] ctx
      def node_arrow_down()
      end

      # @param [Nanovg::Context] ctx
      def node_wire_color()
      end
    end
  end
end
