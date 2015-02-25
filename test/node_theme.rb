assert 'OUI::Blendish::NodeTheme type' do
  assert_kind_of Class, OUI::Blendish::NodeTheme
end

assert 'OUI::Blendish::NodeTheme#initialize' do
  t = OUI::Blendish::NodeTheme.new
end

assert 'OUI::Blendish::NodeTheme#initialize_copy' do
  t = OUI::Blendish::NodeTheme.new
  t2 = t.dup
  assert_kind_of OUI::Blendish::NodeTheme, t2
end

assert 'OUI::Blendish::NodeTheme#node_selected_color' do
  t = OUI::Blendish::NodeTheme.new
  assert_kind_of NVG::Color, t.node_selected_color
  t.node_selected_color = NVG.rgb(128, 196, 128)
end

assert 'OUI::Blendish::NodeTheme#wires_color' do
  t = OUI::Blendish::NodeTheme.new
  assert_kind_of NVG::Color, t.wires_color
  t.wires_color = NVG.rgb(128, 196, 128)
end

assert 'OUI::Blendish::NodeTheme#text_selected_color' do
  t = OUI::Blendish::NodeTheme.new
  assert_kind_of NVG::Color, t.text_selected_color
  t.text_selected_color = NVG.rgb(128, 196, 128)
end

assert 'OUI::Blendish::NodeTheme#active_node_color' do
  t = OUI::Blendish::NodeTheme.new
  assert_kind_of NVG::Color, t.active_node_color
  t.active_node_color = NVG.rgb(128, 196, 128)
end

assert 'OUI::Blendish::NodeTheme#wire_select_color' do
  t = OUI::Blendish::NodeTheme.new
  assert_kind_of NVG::Color, t.wire_select_color
  t.wire_select_color = NVG.rgb(128, 196, 128)
end

assert 'OUI::Blendish::NodeTheme#node_backdrop_color' do
  t = OUI::Blendish::NodeTheme.new
  assert_kind_of NVG::Color, t.node_backdrop_color
  t.node_backdrop_color = NVG.rgb(128, 196, 128)
end

assert 'OUI::Blendish::NodeTheme#noodle_curving' do
  t = OUI::Blendish::NodeTheme.new
  assert_kind_of Integer, t.noodle_curving
  t.noodle_curving = 2
  assert_equal 2, t.noodle_curving
end
