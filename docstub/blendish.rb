module OUI
  # Blendish is a UI drawing framework based on Blender.
  module Blendish
    # @return [Float]
    DISABLED_ALPHA = 0.5

    # @!group BNDtextAlignment
    # @return [Integer]
    LEFT = 0
    # @return [Integer]
    CENTER = 1
    # @!endgroup

    # @!group BNDwidgetState
    # @return [Integer]
    DEFAULT = 0
    # @return [Integer]
    HOVER = 1
    # @return [Integer]
    ACTIVE = 2
    # @!endgroup

    # @!group BNDcornerFlags
    # @return [Integer]
    CORNER_NONE = 0
    # @return [Integer]
    CORNER_TOP_LEFT = 1
    # @return [Integer]
    CORNER_TOP_RIGHT = 2
    # @return [Integer]
    CORNER_DOWN_RIGHT = 4
    # @return [Integer]
    CORNER_DOWN_LEFT = 8
    # @return [Integer]
    CORNER_ALL = 15
    # @return [Integer]
    CORNER_TOP = 3
    # @return [Integer]
    CORNER_DOWN = 12
    # @return [Integer]
    CORNER_LEFT = 9
    # @return [Integer]
    CORNER_RIGHT = 6
    # @!endgroup

    # @!group Some other stuff
    # @return [Integer]
    WIDGET_HEIGHT = 21
    # @return [Integer]
    TOOL_WIDTH = 20
    # @return [Integer]
    NODE_PORT_RADIUS = 5
    # @return [Integer]
    NODE_MARGIN_TOP = 25
    # @return [Integer]
    NODE_MARGIN_DOWN = 5
    # @return [Integer]
    NODE_MARGIN_SIDE = 10
    # @return [Integer]
    NODE_TITLE_HEIGHT = 20
    # @return [Integer]
    NODE_ARROW_AREA_WIDTH = 20
    # @return [Integer]
    SPLITTER_AREA_SIZE = 12
    # @return [Integer]
    SCROLLBAR_WIDTH = 13
    # @return [Integer]
    SCROLLBAR_HEIGHT = 14
    # @return [Integer]
    VSPACING = 1
    # @return [Integer]
    VSPACING_GROUP = 8
    # @return [Integer]
    HSPACING = 8
    # @!endgroup
  end
end
