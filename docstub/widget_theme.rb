module OUI
  module Blendish
    # Theming for general widgets
    class WidgetTheme
      # @!attribute outline_color
      #   @return [Nanovg::Color]
      attr_accessor :outline_color
      # @!attribute item_color
      #   @return [Nanovg::Color]
      attr_accessor :item_color
      # @!attribute inner_color
      #   @return [Nanovg::Color]
      attr_accessor :inner_color
      # @!attribute inner_selected_color
      #   @return [Nanovg::Color]
      attr_accessor :inner_selected_color
      # @!attribute text_color
      #   @return [Nanovg::Color]
      attr_accessor :text_color
      # @!attribute text_selected_color
      #   @return [Nanovg::Color]
      attr_accessor :text_selected_color
      # @!attribute shade_top
      #   @return [Integer]
      attr_accessor :shade_top
      # @!attribute shade_down
      #   @return [Integer]
      attr_accessor :shade_down

      def initialize
      end

      # @param [WidgetTheme] other
      def initialize_copy(other)
      end

      # @param [Integer] state
      # @param [Boolean] flip_active
      # @param [Nanovg::Color] shade_top
      # @param [Nanovg::Color] shade_down
      # @return [Array<Nanovg::Color>[2]] the new shade_top and shade_down
      def inner_colors(state, flip_active, shade_top, shade_down)
      end

      # @param [Integer] state
      # @return [Nanovg::Color]
      def text_color(state)
      end
    end
  end
end
