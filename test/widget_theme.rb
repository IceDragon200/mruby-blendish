assert 'OUI::Blendish::WidgetTheme type' do
  assert_kind_of Class, OUI::Blendish::WidgetTheme
end

assert 'OUI::Blendish::WidgetTheme#initialize' do
  t = OUI::Blendish::WidgetTheme.new
end
