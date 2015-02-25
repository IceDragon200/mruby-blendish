assert 'OUI::Blendish::Theme type' do
  assert_kind_of Class, OUI::Blendish::Theme
end

assert 'OUI::Blendish::Theme#initialize' do
  t = OUI::Blendish::Theme.new
end
