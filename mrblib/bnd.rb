module OUI
  module Blendish
    CORNER_HORZ = CORNER_LEFT | CORNER_RIGHT
    CORNER_VERT = CORNER_TOP | CORNER_DOWN

    def self.iconid(x, y)
      (x) | ((y) << 8)
    end
  end
end

# alias
BND = OUI::Blendish
