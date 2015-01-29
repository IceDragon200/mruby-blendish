module OUI
  class Blendish
    def self.iconid(x, y)
      (x) | ((y) << 8)
    end
  end
end

# alias
BND = OUI::Blendish
