assert 'OUI::Blendish type' do
  assert_kind_of Module, OUI::Blendish
end

assert 'OUI::Blendish aliased as BND' do
  assert_equal OUI::Blendish, BND
end
