module OUI
  module Blendish
    # Blendish theme settings
    class Theme
      # @!attribute background_color
      #   @return [Nanovg::Color]
      attr_accessor :background_color
      # @!attribute regular_theme
      #   @return [WidgetTheme]
      attr_accessor :regular_theme
      # @!attribute tool_theme
      #   @return [WidgetTheme]
      attr_accessor :tool_theme
      # @!attribute radio_theme
      #   @return [WidgetTheme]
      attr_accessor :radio_theme
      # @!attribute text_field_theme
      #   @return [WidgetTheme]
      attr_accessor :text_field_theme
      # @!attribute option_theme
      #   @return [WidgetTheme]
      attr_accessor :option_theme
      # @!attribute choice_theme
      #   @return [WidgetTheme]
      attr_accessor :choice_theme
      # @!attribute number_field_theme
      #   @return [WidgetTheme]
      attr_accessor :number_field_theme
      # @!attribute slider_theme
      #   @return [WidgetTheme]
      attr_accessor :slider_theme
      # @!attribute scroll_bar_theme
      #   @return [WidgetTheme]
      attr_accessor :scroll_bar_theme
      # @!attribute tooltip_theme
      #   @return [WidgetTheme]
      attr_accessor :tooltip_theme
      # @!attribute menu_theme
      #   @return [WidgetTheme]
      attr_accessor :menu_theme
      # @!attribute menu_item_theme
      #   @return [WidgetTheme]
      attr_accessor :menu_item_theme
      # @!attribute node_theme
      #   @return [NodeTheme]
      attr_accessor :node_theme

      def initialize
      end

      # @param [Theme] other
      def initialize_copy(other)
      end
    end
  end
end
