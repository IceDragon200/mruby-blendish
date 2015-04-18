module OUI
  module Blendish
    # Theming for Node based widgets
    class NodeTheme
      # @!attribute node_selected_color
      #   @return [Nanovg::Color]
      attr_accessor :node_selected_color
      # @!attribute wires_color
      #   @return [Nanovg::Color]
      attr_accessor :wires_color
      # @!attribute text_selected_color
      #   @return [Nanovg::Color]
      attr_accessor :text_selected_color
      # @!attribute active_node_color
      #   @return [Nanovg::Color]
      attr_accessor :active_node_color
      # @!attribute wire_select_color
      #   @return [Nanovg::Color]
      attr_accessor :wire_select_color
      # @!attribute node_backdrop_color
      #   @return [Nanovg::Color]
      attr_accessor :node_backdrop_color
      # @!attribute noodle_curving
      #   @return [Integer]
      attr_accessor :noodle_curving

      def initialize
      end

      # @param [NodeTheme] other
      def initialize_copy(other)
      end

      # Retrieves the node_wire_color based on the state.
      #
      # @param [Integer] state
      # @return [Nanovg::Color]
      def node_wire_color(state)
      end
    end
  end
end
