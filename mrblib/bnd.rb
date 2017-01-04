module OUI
  module Blendish
    # Corner both the left and right
    # @return [Integer]
    CORNER_HORZ = CORNER_LEFT | CORNER_RIGHT
    # Corner both the top and down
    # @return [Integer]
    CORNER_VERT = CORNER_TOP | CORNER_DOWN

    # build an icon ID from two coordinates into the icon sheet, where
    # (0,0) designates the upper-leftmost icon, (1,0) the one right next to it,
    # and so on.
    #
    # @param [Integer] x
    # @param [Integer] y
    # @return [Integer]
    def self.iconid(x, y)
      (x) | ((y) << 8)
    end
  end
end

# Alias for OUI::Blendish
BND = OUI::Blendish
