if Object.const_defined?(:Crand)
  puts "Using Crand"

  def crand
    Crand.rand
  end

  def csrand(seed)
    Crand.srand(seed)
  end
else
  puts "Using Ruby rand wrapper"

  def crand
    (rand * 0x7F_FF_FF_FF).to_i
  end

  def csrand(seed)
    srand(seed)
  end
end

class Integer
  def pred
    self - 1
  end unless method_defined?(:pred)

  def round(*a)
    to_f.round(*a)
  end

  def masked?(flag)
    if flag == 0
      self == 0
    else
      (self & flag) == flag
    end
  end
end

class Example
  module SubType
    LABEL = 0
    BUTTON = 1
    RADIO = 2
    SLIDER = 3
    COLUMN = 4
    ROW = 5
    CHECK = 6
    PANEL = 7
    TEXT = 8
    IGNORE = 9
    DEMOSTUFF = 10
    RECT = 11
    HBOX = 12
    VBOX = 13
  end
  ST = SubType

  class UIData
    attr_accessor :subtype
    attr_accessor :handler
  end

  class UIRectData < UIData
    attr_accessor :label
    attr_accessor :color
  end

  class UIButtonData < UIData
    attr_accessor :iconid
    attr_accessor :label
  end

  class UICheckData < UIData
    attr_accessor :label
    attr_accessor :option
  end

  class UIRadioData < UIData
    attr_accessor :iconid
    attr_accessor :label
    attr_accessor :value
  end

  class UISliderData < UIData
    attr_accessor :label
    attr_accessor :progress
  end

  class UITextData < UIData
    attr_accessor :text
    attr_accessor :maxsize
  end

  class Option
    include Comparable

    attr_accessor :v

    def initialize(v)
      @v = v
    end

    def set(v)
      @v = v
    end

    def <=>(value)
      @v <=> value
    end

    def to_int
      @v.to_int
    end

    def to_i
      @v.to_i
    end

    def to_f
      @v.to_f
    end

    def to_s
      @v.to_s
    end

    def to_a
      @v.to_a
    end

    def to_bool
      @v.to_bool
    end
  end

  def initialize
    @bnd = BND::Context.new
    create_ui
    @handles = {}
    @choice = Option.new(-1)
    @enum1 = Option.new(-1)
    @sliderstart = Option.new(0.0)
    @progress1 = Option.new(0.25)
    @progress2 = Option.new(0.75)
    @option1 = Option.new(true)
    @option2 = Option.new(false)
    @option3 = Option.new(false)
    @textbuffer = "The quick brown fox."
    init_handlers
  end

  def create_ui
    @ui = OUI::Context.new(4096, 1 << 20)
  end

  def init_handlers
    @demohandler = lambda do |item, event|
      data = get_handle(item)
      printf("clicked: %s %s\n", data, data.label)
    end

    @checkhandler = lambda do |item, event|
      data = get_handle(item)
      data.option.v = !data.option.v
    end

    @sliderhandler = lambda do |item, event|
      data = get_handle(item)
      case event
      when OUI::BUTTON0_DOWN
        @sliderstart = data.progress.to_f
      when OUI::BUTTON0_CAPTURE
        pos = @ui.cursor_start_delta
        rc = @ui.rect(item)
        value = @sliderstart + (pos.x.to_f / rc.w)
        data.progress.set(value)
      end
    end

    @textboxhandler = lambda do |item, event|
      data = get_handle(item)
      case event
      when OUI::BUTTON0_DOWN
        @ui.focus(item)
      when OUI::KEY_DOWN
        key = @ui.key
        case key
        when GLFW::KEY_BACKSPACE
          size = data.text.size
          return if size <= 0
          data.text.slice!(0, size - 1)
        when GLFW::KEY_ENTER
          @ui.focus(-1)
        end
      when OUI::CHAR
        key = @ui.key
        return if key > 255 || key < 32
        size = data.text.size
        return if size > data.maxsize - 1
        data.text[size] = key.chr
      end
    end

    @radiohandler = lambda do |item, event|
      data = get_handle(item)
      data.value.set(item)
    end

    @roothandler = lambda do |item, event|
      case event
      when OUI::SCROLL
        pos = @ui.scroll
        printf("scroll %d %d\n", pos.x, pos.y)
      when OUI::BUTTON0_DOWN
        printf("%d clicks\n", @ui.clicks)
      end
    end
  end

  def set_handle(item, handle)
    @handles[item] = handle
    handle
  end

  def get_handle(item)
    @handles[item]
  end

  def ui_handler(item, event)
    handle = get_handle(item)
    if handle && handle.handler
      handle.handler.call(item, event)
    end
  end

  def init(vg)
    @bnd.font = vg.create_font('system', 'DejaVuSans.ttf')
    @bnd.icon_image = vg.create_image('blender_icons16.png', 0)
  end

  def testrect(vg, rect)
  end

  def draw_ui_items(vg, item, corners)
    kid = @ui.first_child(item)
    while kid > 0
      draw_ui(vg, kid, corners)
      kid = @ui.next_sibling(kid)
    end
  end

  def draw_ui_items_hbox(vg, item)
    kid = @ui.first_child(item)
    return if (kid < 0)
    next_kid = @ui.next_sibling(kid)
    if next_kid < 0
      draw_ui(vg, kid, BND::CORNER_NONE)
    else
      draw_ui(vg, kid, BND::CORNER_RIGHT)
      kid = next_kid
      while @ui.next_sibling(kid) > 0
        draw_ui(vg, kid, BND::CORNER_ALL)
        kid = @ui.next_sibling(kid)
      end
      draw_ui(vg, kid, BND::CORNER_LEFT)
    end
  end

  def draw_ui_items_vbox(vg, item)
    kid = @ui.first_child(item)
    return if (kid < 0)
    next_kid = @ui.next_sibling(kid)
    if next_kid < 0
      draw_ui(vg, kid, BND::CORNER_NONE)
    else
      draw_ui(vg, kid, BND::CORNER_DOWN)
      kid = next_kid
      while @ui.next_sibling(kid) > 0
        draw_ui(vg, kid, BND::CORNER_ALL)
        kid = @ui.next_sibling(kid)
      end
      draw_ui(vg, kid, BND::CORNER_TOP)
    end
  end

  def draw_ui(vg, item, corners)
    head = get_handle(item)
    rect = @ui.rect(item)
    if @ui.state(item) == OUI::FROZEN
      vg.global_alpha BND::DISABLED_ALPHA
    end

    if head
      case head.subtype
      when ST::HBOX
        draw_ui_items_hbox(vg, item)
      when ST::VBOX
        draw_ui_items_vbox(vg, item)
      when ST::PANEL
        @bnd.bevel(vg, rect.x, rect.y, rect.w, rect.h)
        draw_ui_items(vg, item, corners)
      when ST::LABEL
        fail unless head.is_a?(UIButtonData)
        data = head
        @bnd.label(vg, rect.x, rect.y, rect.w, rect.h, data.iconid, data.label)
      when ST::BUTTON
        fail unless head.is_a?(UIButtonData)
        data = head
        @bnd.tool_button(vg, rect.x, rect.y, rect.w, rect.h, corners, @ui.state(item), data.iconid, data.label)
      when ST::CHECK
        fail unless head.is_a?(UICheckData)
        data = head
        state = @ui.state(item)
        if data.option.v
          state = BND::ACTIVE
        end
        @bnd.option_button(vg, rect.x, rect.y, rect.w, rect.h, state, data.label)
      when ST::RADIO
        fail unless head.is_a?(UIRadioData)
        data = head
        state = @ui.state(item)
        if data.value.v == item
          state = BND::ACTIVE
        end
        @bnd.radio_button(vg, rect.x, rect.y, rect.w, rect.h, corners, state, data.iconid, data.label)
      when ST::SLIDER
        fail unless head.is_a?(UISliderData)
        data = head
        state = @ui.state(item)
        value = sprintf("%.0f%%", data.progress.v * 100.0)
        @bnd.slider(vg, rect.x, rect.y, rect.w, rect.h, corners, state, data.progress.v, data.label, value)
      when ST::TEXT
        fail unless head.is_a?(UITextData)
        data = head
        state = @ui.state(item)
        idx = data.text.size
        @bnd.text_field(vg, rect.x, rect.y, rect.w, rect.h, corners, state, -1, data.text, idx, idx)
      when ST::DEMOSTUFF
        draw_demostuff(vg, rect.x, rect.y, rect.w, rect.h)
      when ST::RECT
        fail unless head.is_a?(UIRectData)
        data = head
        if rect.w != 0 && rect.h != 0
          state = @ui.state(item)
          vg.spork do
            vg.stroke_color(NVG.rgbaf(data.color.r, data.color.g, data.color.b, 0.9))
            if state != BND::DEFAULT
              vg.fill_color(NVG.rgbaf(data.color.r, data.color.g, data.color.b, 0.5))
            else
              vg.fill_color(NVG.rgbaf(data.color.r, data.color.g, data.color.b, 0.1))
            end
            vg.stroke_width(2)
            vg.path do
              vg.rounded_rect(rect.x, rect.y, rect.w, rect.h, 3)
              vg.fill
              vg.stroke
            end

            if state != BND::DEFAULT
              vg.fill_color(NVG.rgbaf(0, 0, 0, 1))
              vg.font_size(15.0)
              vg.path do
                vg.text_align(NVG::ALIGN_TOP | NVG::ALIGN_CENTER)
                vg.text_box(rect.x, rect.y + rect.h * 0.3, rect.w, data.label)
              end
            end
          end
        end

        vg.spork do
          vg.intersect_scissor(rect.x, rect.y, rect.w, rect.h)

          draw_ui_items(vg, item, corners)
        end
      else
        testrect(vg, rect)
        draw_ui_items(vg, item, corners)
      end
    else
      testrect(vg, rect)
      draw_ui_items(vg, item, corners)
    end

    if @ui.state(item) == OUI::FROZEN
      vg.global_alpha 1.0
    end
  end

  def colorrect(label, color)
    item = @ui.item
    data = set_handle(item, UIRectData.new)
    data.subtype = ST::RECT
    data.handler = nil
    data.label = label
    data.color = color
    @ui.set_events item, OUI::BUTTON0_DOWN
    item
  end

  def label(iconid, label)
    item = @ui.item
    @ui.set_size(item, 0, BND::WIDGET_HEIGHT)
    data = set_handle(item, UIButtonData.new)
    data.subtype = ST::LABEL
    data.handler = nil
    data.iconid = iconid
    data.label = label
    item
  end

  def button(iconid, label, handler)
    item = @ui.item
    @ui.set_size(item, 0, BND::WIDGET_HEIGHT)
    @ui.set_events(item, OUI::BUTTON0_HOT_UP)
    data = set_handle(item, UIButtonData.new)
    data.subtype = ST::BUTTON
    data.handler = handler
    data.iconid = iconid
    data.label = label
    item
  end

  def check(label, option)
    item = @ui.item
    @ui.set_size(item, 0, BND::WIDGET_HEIGHT)
    @ui.set_events(item, OUI::BUTTON0_DOWN)
    data = set_handle(item, UICheckData.new)
    data.subtype = ST::CHECK
    data.handler = @checkhandler
    data.label = label
    data.option = option
    item
  end

  def slider(label, progress)
    item = @ui.item
    @ui.set_size(item, 0, BND::WIDGET_HEIGHT)
    @ui.set_events(item, OUI::BUTTON0_DOWN | OUI::BUTTON0_CAPTURE)
    data = set_handle(item, UISliderData.new)
    data.subtype = ST::SLIDER
    data.handler = @sliderhandler
    data.label = label
    data.progress = progress
    item
  end

  def textbox(text, maxsize)
    item = @ui.item
    @ui.set_size(item, 0, BND::WIDGET_HEIGHT)
    @ui.set_events(item, OUI::BUTTON0_DOWN | OUI::KEY_DOWN | OUI::CHAR)
    data = set_handle(item, UITextData.new)
    data.subtype = ST::TEXT
    data.handler = @textboxhandler
    data.text = text
    data.maxsize = maxsize
    item
  end

  def radio(iconid, label, value)
    item = @ui.item
    @ui.set_size(item, label ? 0 : BND::TOOL_WIDTH, BND::WIDGET_HEIGHT)
    data = set_handle(item, UIRadioData.new)
    data.subtype = ST::RADIO
    data.handler = @radiohandler
    data.iconid = iconid
    data.label = label
    data.value = value
    @ui.set_events(item, OUI::BUTTON0_DOWN)
    item
  end

  def panel
    item = @ui.item
    data = set_handle(item, UIData.new)
    data.subtype = ST::PANEL
    data.handler = nil
    item
  end

  def hbox
    item = @ui.item
    data = set_handle(item, UIData.new)
    data.subtype = ST::HBOX
    data.handler = nil
    @ui.set_box(item, OUI::ROW)
    item
  end

  def vbox
    item = @ui.item
    data = set_handle(item, UIData.new)
    data.subtype = ST::VBOX
    data.handler = nil
    @ui.set_box(item, OUI::COLUMN)
    item
  end

  def column_append(parent, item)
    @ui.insert(parent, item)
    @ui.set_layout(item, OUI::HFILL)
    @ui.set_margins(item, 0, 1, 0, 0)
    item
  end

  def column
    item = @ui.item
    @ui.set_box(item, OUI::COLUMN)
    item
  end

  def vgroup_append(parent, item)
    @ui.insert(parent, item)
    @ui.set_layout(item, OUI::HFILL)
    item
  end

  def vgroup
    item = @ui.item
    @ui.set_box(item, OUI::COLUMN)
    item
  end

  def hgroup_append(parent, item)
    @ui.insert(parent, item)
    @ui.set_layout(item, OUI::HFILL)
    item
  end

  def hgroup_append_fixed(parent, item)
    @ui.insert(parent, item)
    item
  end

  def hgroup
    item = @ui.item
    @ui.set_box(item, OUI::ROW)
    item
  end

  def row_append(parent, item)
    @ui.insert(parent, item)
    @ui.set_layout(item, OUI::HFILL)
    item
  end

  def row
    item = @ui.item
    @ui.set_box(item, OUI::ROW)
    item
  end

  def draw_noodles(vg, x, y)
    w = 200
    s = 70

    @bnd.node_background(vg, x + w, y - 50, 100, 200, BND::DEFAULT, BND.iconid(6, 3),
                         "Default", NVG.rgbf(0.392, 0.392, 0.392))

    @bnd.node_background(vg, x + w + 120, y - 50, 100, 200, BND::HOVER, BND.iconid(6, 3),
                         "Hover", NVG.rgbf(0.392, 0.392, 0.392))

    @bnd.node_background(vg, x + w + 240, y - 50, 100, 200, BND::ACTIVE, BND.iconid(6, 3),
                         "Active", NVG.rgbf(0.392, 0.392, 0.392))

    9.times do |i|
      a = i % 3
      b = (i / 3).to_i
      @bnd.node_wire(vg, x, y + s * a, x + w, y + s * b, a, b)
    end

    @bnd.node_port(vg, x, y, BND::DEFAULT, NVG.rgbf(0.5, 0.5, 0.5))
    @bnd.node_port(vg, x+w, y, BND::DEFAULT, NVG.rgbf(0.5, 0.5, 0.5))
    @bnd.node_port(vg, x, y+s, BND::HOVER, NVG.rgbf(0.5, 0.5, 0.5))
    @bnd.node_port(vg, x+w, y+s, BND::HOVER, NVG.rgbf(0.5, 0.5, 0.5))
    @bnd.node_port(vg, x, y+2*s, BND::ACTIVE, NVG.rgbf(0.5, 0.5, 0.5))
    @bnd.node_port(vg, x+w, y+2*s, BND::ACTIVE, NVG.rgbf(0.5, 0.5, 0.5))
  end

  def draw_demostuff(vg, x, y, w, h)
    vg.spork do
      vg.translate(x, y)
      @bnd.splitter_widgets(vg, 0, 0, w, h)

      x = 10
      y = 10

      @bnd.tool_button(vg, x, y, 120, BND::WIDGET_HEIGHT, BND::CORNER_NONE, BND::DEFAULT,
                       BND.iconid(6, 3), "Default")
      y += 25
      @bnd.tool_button(vg, x, y, 120, BND::WIDGET_HEIGHT, BND::CORNER_NONE, BND::HOVER,
                       BND.iconid(6, 3), "Hovered")
      y += 25
      @bnd.tool_button(vg, x, y, 120, BND::WIDGET_HEIGHT, BND::CORNER_NONE, BND::ACTIVE,
                       BND.iconid(6, 3), "Active")

      y += 40
      @bnd.radio_button(vg, x, y, 120, BND::WIDGET_HEIGHT, BND::CORNER_NONE, BND::DEFAULT,
                       -1, "Default")
      y += 25
      @bnd.radio_button(vg, x, y, 120, BND::WIDGET_HEIGHT, BND::CORNER_NONE, BND::HOVER,
                       -1, "Hovered")
      y += 25
      @bnd.radio_button(vg, x, y, 120, BND::WIDGET_HEIGHT, BND::CORNER_NONE, BND::ACTIVE,
                       -1, "Active")

      y += 25
      @bnd.label(vg, x, y, 120, BND::WIDGET_HEIGHT, -1, "Label:")
      y += BND::WIDGET_HEIGHT
      @bnd.choice_button(vg, x, y, 80, BND::WIDGET_HEIGHT, BND::CORNER_NONE, BND::DEFAULT,
        -1, "Default")
      y += 25
      @bnd.choice_button(vg, x, y, 80, BND::WIDGET_HEIGHT, BND::CORNER_NONE, BND::HOVER,
          -1, "Hovered")
      y += 25
      @bnd.choice_button(vg, x, y, 80, BND::WIDGET_HEIGHT, BND::CORNER_NONE, BND::ACTIVE,
          -1, "Active")

      y += 25
      ry = y
      rx = x

      y = 10
      x += 130
      @bnd.option_button(vg,x,y,120,BND::WIDGET_HEIGHT,BND::DEFAULT,"Default")
      y += 25
      @bnd.option_button(vg,x,y,120,BND::WIDGET_HEIGHT,BND::HOVER,"Hovered")
      y += 25
      @bnd.option_button(vg,x,y,120,BND::WIDGET_HEIGHT,BND::ACTIVE,"Active")

      y += 40
      @bnd.number_field(vg,x,y,120,BND::WIDGET_HEIGHT,BND::CORNER_DOWN,BND::DEFAULT,
          "Top","100")
      y += BND::WIDGET_HEIGHT-2
      @bnd.number_field(vg,x,y,120,BND::WIDGET_HEIGHT,BND::CORNER_ALL,BND::DEFAULT,
          "Center","100")
      y += BND::WIDGET_HEIGHT-2
      @bnd.number_field(vg,x,y,120,BND::WIDGET_HEIGHT,BND::CORNER_TOP,BND::DEFAULT,
          "Bottom","100")

      mx = x - 30
      my = y - 12
      mw = 120
      @bnd.menu_background(vg,mx,my,mw,120,BND::CORNER_TOP)
      @bnd.menu_label(vg,mx,my,mw,BND::WIDGET_HEIGHT,-1,"Menu Title")
      my += BND::WIDGET_HEIGHT-2
      @bnd.menu_item(vg,mx,my,mw,BND::WIDGET_HEIGHT,BND::DEFAULT,
          BND.iconid(17,3),"Default")
      my += BND::WIDGET_HEIGHT-2
      @bnd.menu_item(vg,mx,my,mw,BND::WIDGET_HEIGHT,BND::HOVER,
          BND.iconid(18,3),"Hovered")
      my += BND::WIDGET_HEIGHT-2
      @bnd.menu_item(vg,mx,my,mw,BND::WIDGET_HEIGHT,BND::ACTIVE,
          BND.iconid(19,3),"Active")

      y = 10
      x += 130
      ox = x
      @bnd.number_field(vg,x,y,120,BND::WIDGET_HEIGHT,BND::CORNER_NONE,BND::DEFAULT,
          "Default","100")
      y += 25
      @bnd.number_field(vg,x,y,120,BND::WIDGET_HEIGHT,BND::CORNER_NONE,BND::HOVER,
          "Hovered","100")
      y += 25
      @bnd.number_field(vg,x,y,120,BND::WIDGET_HEIGHT,BND::CORNER_NONE,BND::ACTIVE,
          "Active","100")

      y += 40
      @bnd.radio_button(vg,x,y,60,BND::WIDGET_HEIGHT,BND::CORNER_RIGHT,BND::DEFAULT,
          -1,"One")
      x += 60-1
      @bnd.radio_button(vg,x,y,60,BND::WIDGET_HEIGHT,BND::CORNER_ALL,BND::DEFAULT,
          -1,"Two")
      x += 60-1
      @bnd.radio_button(vg,x,y,60,BND::WIDGET_HEIGHT,BND::CORNER_ALL,BND::DEFAULT,
          -1,"Three")
      x += 60-1
      @bnd.radio_button(vg,x,y,60,BND::WIDGET_HEIGHT,BND::CORNER_LEFT,BND::ACTIVE,
          -1,"Butts")

      x = ox
      y += 40
      progress_value = (GLFW.time / 10.0) % 1.0
      progress_label = sprintf("%d%%", progress_value * 100 + 0.5)
      @bnd.slider(vg,x,y,240,BND::WIDGET_HEIGHT,BND::CORNER_NONE,BND::DEFAULT,
          progress_value,"Default",progress_label)
      y += 25
      @bnd.slider(vg,x,y,240,BND::WIDGET_HEIGHT,BND::CORNER_NONE,BND::HOVER,
          progress_value,"Hovered",progress_label)
      y += 25
      @bnd.slider(vg,x,y,240,BND::WIDGET_HEIGHT,BND::CORNER_NONE,BND::ACTIVE,
          progress_value,"Active",progress_label)

      rw = x+240-rx
      s_offset = Math.sin(GLFW.time / 2.0) * 0.5 + 0.5
      s_size = Math.cos(GLFW.time / 3.11) * 0.5 + 0.5

      @bnd.scroll_bar(vg,rx,ry,rw,BND::SCROLLBAR_HEIGHT,BND::DEFAULT,s_offset,s_size)
      ry += 20
      @bnd.scroll_bar(vg,rx,ry,rw,BND::SCROLLBAR_HEIGHT,BND::HOVER,s_offset,s_size)
      ry += 20
      @bnd.scroll_bar(vg,rx,ry,rw,BND::SCROLLBAR_HEIGHT,BND::ACTIVE,s_offset,s_size)

      edit_text = "The quick brown fox"
      textlen = edit_text.size + 1
      t = (GLFW.time * 2).to_i
      idx1 = (t / textlen) % textlen
      idx2 = idx1 + (t % (textlen - idx1))

      ry += 25
      @bnd.text_field(vg,rx,ry,240,BND::WIDGET_HEIGHT,BND::CORNER_NONE,BND::DEFAULT,
          -1, edit_text, idx1, idx2)
      ry += 25
      @bnd.text_field(vg,rx,ry,240,BND::WIDGET_HEIGHT,BND::CORNER_NONE,BND::HOVER,
          -1, edit_text, idx1, idx2)
      ry += 25
      @bnd.text_field(vg,rx,ry,240,BND::WIDGET_HEIGHT,BND::CORNER_NONE,BND::ACTIVE,
          -1, edit_text, idx1, idx2)

      draw_noodles(vg, 20, ry + 50)

      rx += rw + 20
      ry = 10
      @bnd.scroll_bar(vg,rx,ry,BND::SCROLLBAR_WIDTH,240,BND::DEFAULT,s_offset,s_size)
      rx += 20
      @bnd.scroll_bar(vg,rx,ry,BND::SCROLLBAR_WIDTH,240,BND::HOVER,s_offset,s_size)
      rx += 20
      @bnd.scroll_bar(vg,rx,ry,BND::SCROLLBAR_WIDTH,240,BND::ACTIVE,s_offset,s_size)

      x = ox
      y += 40
      @bnd.tool_button(vg,x,y,BND::TOOL_WIDTH,BND::WIDGET_HEIGHT,BND::CORNER_RIGHT,
          BND::DEFAULT,BND.iconid(0,10),nil)
      x += BND::TOOL_WIDTH-1
      @bnd.tool_button(vg,x,y,BND::TOOL_WIDTH,BND::WIDGET_HEIGHT,BND::CORNER_ALL,
          BND::DEFAULT,BND.iconid(1,10),nil)
      x += BND::TOOL_WIDTH-1
      @bnd.tool_button(vg,x,y,BND::TOOL_WIDTH,BND::WIDGET_HEIGHT,BND::CORNER_ALL,
          BND::DEFAULT,BND.iconid(2,10),nil)
      x += BND::TOOL_WIDTH-1
      @bnd.tool_button(vg,x,y,BND::TOOL_WIDTH,BND::WIDGET_HEIGHT,BND::CORNER_ALL,
          BND::DEFAULT,BND.iconid(3,10),nil)
      x += BND::TOOL_WIDTH-1
      @bnd.tool_button(vg,x,y,BND::TOOL_WIDTH,BND::WIDGET_HEIGHT,BND::CORNER_ALL,
          BND::DEFAULT,BND.iconid(4,10),nil)
      x += BND::TOOL_WIDTH-1
      @bnd.tool_button(vg,x,y,BND::TOOL_WIDTH,BND::WIDGET_HEIGHT,BND::CORNER_LEFT,
          BND::DEFAULT,BND.iconid(5,10),nil)
      x += BND::TOOL_WIDTH-1
      x += 5
      @bnd.radio_button(vg,x,y,BND::TOOL_WIDTH,BND::WIDGET_HEIGHT,BND::CORNER_RIGHT,
          BND::DEFAULT,BND.iconid(0,11),nil)
      x += BND::TOOL_WIDTH-1
      @bnd.radio_button(vg,x,y,BND::TOOL_WIDTH,BND::WIDGET_HEIGHT,BND::CORNER_ALL,
          BND::DEFAULT,BND.iconid(1,11),nil)
      x += BND::TOOL_WIDTH-1
      @bnd.radio_button(vg,x,y,BND::TOOL_WIDTH,BND::WIDGET_HEIGHT,BND::CORNER_ALL,
          BND::DEFAULT,BND.iconid(2,11),nil)
      x += BND::TOOL_WIDTH-1
      @bnd.radio_button(vg,x,y,BND::TOOL_WIDTH,BND::WIDGET_HEIGHT,BND::CORNER_ALL,
          BND::DEFAULT,BND.iconid(3,11),nil)
      x += BND::TOOL_WIDTH-1
      @bnd.radio_button(vg,x,y,BND::TOOL_WIDTH,BND::WIDGET_HEIGHT,BND::CORNER_ALL,
          BND::ACTIVE,BND.iconid(4,11),nil)
      x += BND::TOOL_WIDTH-1
      @bnd.radio_button(vg,x,y,BND::TOOL_WIDTH,BND::WIDGET_HEIGHT,BND::CORNER_LEFT,
          BND::DEFAULT,BND.iconid(5,11),nil)
    end
  end

  def build_democontent(parent)
    col = column

    @ui.insert(parent, col)
    @ui.set_margins(col, 10, 10, 10, 10)
    @ui.set_layout(col, OUI::TOP | OUI::HFILL)

    column_append(col, button(BND::Icon::GHOST, "Item 1", @demohandler))

    if @option3.v
      column_append(col, button(BND::Icon::GHOST, "Item 2", @demohandler))
    end

    begin
      h = column_append(col, hbox)
      hgroup_append(h, radio(BND::Icon::GHOST, "Item 3.0", @enum1))

      if @option2.v
        @ui.set_margins(hgroup_append_fixed(h, radio(BND::Icon::REC, nil, @enum1)), -1, 0, 0, 0)
      end
      @ui.set_margins(hgroup_append_fixed(h, radio(BND::Icon::PLAY, nil, @enum1)), -1, 0, 0, 0)
      @ui.set_margins(hgroup_append(h, radio(BND::Icon::GHOST, "Item 3.3", @enum1)), -1, 0, 0, 0)
    end

    begin
      rows = column_append(col, row)
      coll = row_append(rows, vgroup)
      vgroup_append(coll, label(-1, "Items 4.0:"))
      coll = vgroup_append(coll, vbox)
      vgroup_append(coll, button(BND::Icon::GHOST, "Item 4.0.0", @demohandler))
      @ui.set_margins(vgroup_append(coll, button(BND::Icon::GHOST, "Item 4.0.1", @demohandler)), 0, -2, 0, 0)
      colr = row_append(rows, vgroup)
      @ui.set_margins(colr, 8, 0, 0, 0)
      @ui.set_frozen(colr, @option1.v)
      vgroup_append(colr, label(-1, "Items 4.1:"))
      colr = vgroup_append(colr, vbox)
      vgroup_append(colr, slider("Item 4.1.0", @progress1))
      @ui.set_margins(vgroup_append(colr, slider("Item 4.1.1", @progress2)), 0, -2, 0, 0)
    end

    column_append(col, button(BND::Icon::GHOST, "Item 5", nil))

    column_append(col, textbox(@textbuffer, 1024))

    column_append(col, check("Frozen", @option1))
    column_append(col, check("Item 7", @option2))
    column_append(col, check("Item 8", @option3))
  end

  def demorect(parent, label, hue, box, layout, w, h, m1, m2, m3, m4)
    item = colorrect(label, NVG.hsl(hue, 1.0, 0.8))
    @ui.set_layout(item, layout)
    @ui.set_box(item, box)
    @ui.set_margins(item, m1, m2, m3, m4)
    @ui.set_size(item, w, h)
    @ui.insert(parent, item)
    item
  end


  def build_layoutdemo(parent)
    m = 10
    s = 150

    box = demorect(parent, "Box( OUI::LAYOUT )\nLayout( OUI::FILL )", 0.6, OUI::LAYOUT, OUI::FILL, 0, 0, m, m, m, m)
    demorect(box, "Layout( OUI::HFILL | OUI::TOP )", 0.7, 0, OUI::HFILL|OUI::TOP, s, s+m, m, m, m, 0)
    demorect(box, "Layout( OUI::HFILL )", 0.7, 0, OUI::HFILL, s, s+2*m, m, 0, m, 0)
    demorect(box, "Layout( OUI::HFILL | OUI::DOWN )", 0.7, 0, OUI::HFILL|OUI::DOWN, s, s+m, m, 0, m, m)

    demorect(box, "Layout( OUI::LEFT | OUI::VFILL )", 0.7, 0, OUI::LEFT|OUI::VFILL, s+m, s, m, m, 0, m)
    demorect(box, "Layout( OUI::VFILL )", 0.7, 0, OUI::VFILL, s+2*m, s, 0, m, 0, m)
    demorect(box, "Layout( OUI::RIGHT | OUI::VFILL )", 0.7, 0, OUI::RIGHT|OUI::VFILL, s+m, s, 0, m, m, m)

    demorect(box, "Layout( OUI::LEFT | OUI::TOP )", 0.55, 0, OUI::LEFT|OUI::TOP, s, s, m, m, 0, 0)
    demorect(box, "Layout( OUI::TOP )", 0.57, 0, OUI::TOP, s, s, 0, m, 0, 0)
    demorect(box, "Layout( OUI::RIGHT | OUI::TOP )", 0.55, 0, OUI::RIGHT|OUI::TOP, s, s, 0, m, m, 0)
    demorect(box, "Layout( OUI::LEFT )", 0.57, 0, OUI::LEFT, s, s, m, 0, 0, 0)
    demorect(box, "Layout( OUI::CENTER )", 0.59, 0, OUI::CENTER, s, s, 0, 0, 0, 0)
    demorect(box, "Layout( OUI::RIGHT )", 0.57, 0, OUI::RIGHT, s, s, 0, 0, m, 0)
    demorect(box, "Layout( OUI::LEFT | OUI::DOWN )", 0.55, 0, OUI::LEFT|OUI::DOWN, s, s, m, 0, 0, m)
    demorect(box, "Layout( OUI::DOWN)", 0.57, 0, OUI::DOWN, s, s, 0, 0, 0, m)
    demorect(box, "Layout( OUI::RIGHT | OUI::DOWN )", 0.55, 0, OUI::RIGHT|OUI::DOWN, s, s, 0, 0, m, m)
  end

  def build_rowdemo(parent)
    @ui.set_box(parent, OUI::COLUMN)
    m = 10
    s = 200
    t = 100

    begin
      box = demorect(parent, "Box( OUI::ROW )\nLayout( OUI::LEFT | OUI::VFILL )", 0.6, OUI::ROW, OUI::LEFT | OUI::VFILL, 0, s, m, m, m, m)

      demorect(box, "Layout( OUI::TOP )", 0.05, 0, OUI::TOP, t, t, m, m, m, 0)
      demorect(box, "Layout( OUI::VCENTER )", 0.1, 0, OUI::VCENTER, t, t, 0, 0, m, 0)
      demorect(box, "Layout( OUI::VFILL )", 0.15, 0, OUI::VFILL, t, t, 0, m, m, m)
      demorect(box, "Layout( OUI::DOWN )", 0.25, 0, OUI::DOWN, t, t, 0, 0, m, m)
    end
    begin
      box = demorect(parent, "Box( OUI::ROW | OUI::JUSTIFY )\nLayout( OUI::FILL )", 0.6, OUI::ROW | OUI::JUSTIFY, OUI::FILL, 0, s, m, 0, m, m)

      demorect(box, "Layout( OUI::TOP )", 0.05, 0, OUI::TOP, t, t, m, m, m, 0)
      demorect(box, "Layout( OUI::VCENTER )", 0.1, 0, OUI::VCENTER, t, t, 0, 0, m, 0)
      demorect(box, "Layout( OUI::VFILL )", 0.15, 0, OUI::VFILL, t, t, 0, m, m, m)
      demorect(box, "Layout( OUI::DOWN )", 0.25, 0, OUI::DOWN, t, t, 0, 0, m, m)
    end
    begin
      box = demorect(parent, "Box( OUI::ROW )\nLayout( OUI::FILL )", 0.6, OUI::ROW, OUI::FILL, 0, s, m, 0, m, m)

      demorect(box, "Layout( OUI::TOP )", 0.05, 0, OUI::TOP, t, t, m, m, m, 0)
      demorect(box, "Layout( OUI::VCENTER )", 0.1, 0, OUI::VCENTER, t, t, 0, 0, m, 0)
      demorect(box, "Layout( OUI::VFILL )", 0.15, 0, OUI::VFILL, t, t, 0, m, m, m)
      demorect(box, "Layout( OUI::HFILL )", 0.2, 0, OUI::HFILL, t, t, 0, 0, m, 0)
      demorect(box, "Layout( OUI::HFILL )", 0.2, 0, OUI::HFILL, t, t, 0, 0, m, 0)
      demorect(box, "Layout( OUI::HFILL )", 0.2, 0, OUI::HFILL, t, t, 0, 0, m, 0)
      demorect(box, "Layout( OUI::DOWN )", 0.25, 0, OUI::DOWN, t, t, 0, 0, m, m)
    end
  end

  def build_columndemo(parent)
    @ui.set_box(parent, OUI::ROW)

    m = 10
    s = 200
    t = 100

    begin
      box = demorect(parent, "Box( OUI::COLUMN )\nLayout( OUI::TOP | OUI::HFILL )", 0.6, OUI::COLUMN, OUI::TOP | OUI::HFILL, s, 0, m, m, m, m)

      demorect(box, "Layout( OUI::LEFT )", 0.05, 0, OUI::LEFT, t, t, m, m, 0, m)
      demorect(box, "Layout( OUI::HCENTER )", 0.1, 0, OUI::HCENTER, t, t, 0, 0, 0, m)
      demorect(box, "Layout( OUI::HFILL )", 0.15, 0, OUI::HFILL, t, t, m, 0, m, m)
      demorect(box, "Layout( OUI::RIGHT )", 0.25, 0, OUI::RIGHT, t, t, 0, 0, m, m)
    end
    begin
      box = demorect(parent, "Box( OUI::COLUMN )\nLayout( OUI::FILL )", 0.6, OUI::COLUMN, OUI::FILL, s, 0, 0, m, m, m)

      demorect(box, "Layout( OUI::LEFT )", 0.05, 0, OUI::LEFT, t, t, m, m, 0, m)
      demorect(box, "Layout( OUI::HCENTER )", 0.1, 0, OUI::HCENTER, t, t, 0, 0, 0, m)
      demorect(box, "Layout( OUI::HFILL )", 0.15, 0, OUI::HFILL, t, t, m, 0, m, m)
      demorect(box, "Layout( OUI::RIGHT )", 0.25, 0, OUI::RIGHT, t, t, 0, 0, m, m)
    end
    begin
      box = demorect(parent, "Box( OUI::COLUMN )\nLayout( OUI::FILL )", 0.6, OUI::COLUMN, OUI::FILL, s, 0, 0, m, m, m)

      demorect(box, "Layout( OUI::LEFT )", 0.05, 0, OUI::LEFT, t, t, m, m, 0, m)
      demorect(box, "Layout( OUI::HCENTER )", 0.1, 0, OUI::HCENTER, t, t, 0, 0, 0, m)
      demorect(box, "Layout( OUI::HFILL )", 0.15, 0, OUI::HFILL, t, t, m, 0, m, m)
      demorect(box, "Layout( OUI::VFILL )", 0.2, 0, OUI::VFILL, t, t, 0, 0, 0, m)
      demorect(box, "Layout( OUI::VFILL )", 0.2, 0, OUI::VFILL, t, t, 0, 0, 0, m)
      demorect(box, "Layout( OUI::VFILL )", 0.2, 0, OUI::VFILL, t, t, 0, 0, 0, m)
      demorect(box, "Layout( OUI::RIGHT )", 0.25, 0, OUI::RIGHT, t, t, 0, 0, m, m)
    end
  end

  SRAND_VALUE = 303

  def fill_wrap_row_box(box)
    m = 5
    t = 50

    csrand(SRAND_VALUE)
    20.times do |i|
      hue = (crand % 360) / 360.0
      width = 10 + (crand % 5) * 10

      u = case crand % 4
      when 0
        demorect(box, "Layout( OUI::TOP )",
                 hue, 0, OUI::TOP, width, t, m, m, m, m)
      when 1
        demorect(box, "Layout( OUI::VCENTER )",
                 hue, 0, OUI::VCENTER, width, t/2, m, m, m, m)
      when 2
        demorect(box, "Layout( OUI::VFILL )",
                 hue, 0, OUI::VFILL, width, t, m, m, m, m)
      when 3
        demorect(box, "Layout( OUI::DOWN )",
                 hue, 0, OUI::DOWN, width, t/2, m, m, m, m)
      end

      if (crand % 10) == 0
        @ui.set_layout(u, @ui.layout(u) | OUI::BREAK)
      end
    end
  end

  def fill_wrap_column_box(box)
    m = 5
    t = 50

    csrand(SRAND_VALUE)
    20.times do |i|
      hue = (crand % 360) % 360.0
      height = 10 + (crand % 5) * 10

      u = case crand % 4
      when 0
        demorect(box, "Layout( OUI::LEFT )",
                 hue, 0, OUI::LEFT, t, height, m, m, m, m)
      when 1
        demorect(box, "Layout( OUI::HCENTER )",
                 hue, 0, OUI::HCENTER, t/2, height, m, m, m, m)
      when 2
        demorect(box, "Layout( OUI::HFILL )",
                 hue, 0, OUI::HFILL, t, height, m, m, m, m)
      when 3
        demorect(box, "Layout( OUI::RIGHT )",
                 hue, 0, OUI::RIGHT, t/2, height, m, m, m, m)
      end

      if (crand % 10) == 0
        @ui.set_layout(u, @ui.layout(u) | OUI::BREAK)
      end
    end
  end

  def build_wrapdemo(parent)
    col = @ui.item
    @ui.insert(parent, col)
    @ui.set_box(col, OUI::COLUMN)
    @ui.set_layout(col, OUI::FILL)

    m = 5

    box = demorect(col, "Box( OUI::ROW | OUI::WRAP | OUI::START )\nLayout( OUI::HFILL | OUI::TOP )",
            0.6, OUI::ROW | OUI::WRAP | OUI::START, OUI::TOP, 0, 0, m, m, m, m)
    fill_wrap_row_box(box)

    box = demorect(col, "Box( OUI::ROW | OUI::WRAP | OUI::MIDDLE )\nLayout( OUI::HFILL | OUI::TOP )",
            0.6, OUI::ROW | OUI::WRAP, OUI::HFILL | OUI::TOP, 0, 0, m, m, m, m)
    fill_wrap_row_box(box)

    box = demorect(col, "Box( OUI::ROW | OUI::WRAP | OUI::END )\nLayout( OUI::HFILL | OUI::TOP )",
            0.6, OUI::ROW | OUI::WRAP | OUI::END, OUI::HFILL | OUI::TOP, 0, 0, m, m, m, m)
    fill_wrap_row_box(box)

    box = demorect(col, "Box( OUI::ROW | OUI::WRAP | OUI::JUSTIFY )\nLayout( OUI::HFILL | OUI::TOP )",
            0.6, OUI::ROW | OUI::WRAP | OUI::JUSTIFY, OUI::HFILL | OUI::TOP, 0, 0, m, m, m, m)
    fill_wrap_row_box(box)

    box = demorect(col, "Box( OUI::COLUMN | OUI::WRAP | OUI::START )\nLayout( OUI::LEFT | OUI::VFILL )",
            0.6, OUI::COLUMN | OUI::WRAP | OUI::START, OUI::LEFT | OUI::VFILL, 0, 0, m, m, m, m)
    fill_wrap_column_box(box)
  end

  def add_menu_option(parent, name, choice)
    opt = radio(-1, name, choice)
    @ui.insert(parent, opt)
    @ui.set_layout(opt, OUI::HFILL | OUI::TOP)
    @ui.set_margins(opt, 1, 1, 1, 1)
    opt
  end

  def draw(vg, w, h)
    opt_blendish_demo = nil
    opt_oui_demo = nil
    opt_layouts = nil
    opt_row = nil
    opt_column = nil
    opt_wrap = nil

    @bnd.background(vg, 0, 0, w, h)

    @ui.create_layout do
      @handles.clear
      root = panel

      @ui.set_size(0, w, h)
      get_handle(root).handler = @roothandler
      @ui.set_events(root, OUI::SCROLL | OUI::BUTTON0_DOWN)
      @ui.set_box(root, OUI::COLUMN)

      menu = @ui.item
      @ui.set_layout(menu, OUI::HFILL | OUI::TOP)
      @ui.set_box(menu, OUI::ROW)
      @ui.insert(root, menu)

      opt_blendish_demo = add_menu_option(menu, "Blendish Demo", @choice)
      opt_oui_demo = add_menu_option(menu, "OUI Demo", @choice)
      opt_layouts = add_menu_option(menu, "OUI::LAYOUT", @choice)
      opt_row = add_menu_option(menu, "OUI::ROW", @choice)
      opt_column = add_menu_option(menu, "OUI::COLUMN", @choice)
      opt_wrap = add_menu_option(menu, "OUI::WRAP", @choice)

      if @choice.v < 0
        @choice.set(opt_blendish_demo)
      end

      content = @ui.item
      @ui.set_layout(content, OUI::FILL)
      @ui.insert(root, content)

      case @choice.v
      when opt_blendish_demo
        democontent = @ui.item
        @ui.set_layout(democontent, OUI::FILL)
        @ui.insert(content, democontent)

        data = set_handle(democontent, UIData.new)
        data.handler = nil
        data.subtype = ST::DEMOSTUFF
      when opt_oui_demo
        democontent = @ui.item
        @ui.set_layout(democontent, OUI::TOP)
        @ui.set_size(democontent, 250, 0)
        @ui.insert(content, democontent)

        build_democontent(democontent)
      when opt_layouts
        build_layoutdemo(content)
      when opt_row
        build_rowdemo(content)
      when opt_column
        build_columndemo(content)
      when opt_wrap
        build_wrapdemo(content)
      end
    end

    draw_ui(vg, 0, BND::CORNER_NONE)

    if @choice == opt_blendish_demo
      cursor = @ui.cursor
      cursor.x -= w / 2
      cursor.y -= h / 2

      if cursor.x.abs > (w / 3)
        @bnd.join_area_overlay(vg, 0, 0, w, h, false, (cursor.x > 0))
      elsif cursor.y.abs > (w / 3)
        @bnd.join_area_overlay(vg, 0, 0, w, h, true, (cursor.y > 0))
      end
    end

    @ui.process((GLFW.time * 1000.0).to_i)
  end

  def main
    @ui.set_handler do |ui, item, event|
      ui_handler(item, event)
    end

    GLFW.init

    #GLFW.window_hint(GLFW::CONTEXT_VERSION_MAJOR, 3)
    #GLFW.window_hint(GLFW::CONTEXT_VERSION_MINOR, 2)
    #GLFW.window_hint(GLFW::OPENGL_FORWARD_COMPAT, GL2::GL_TRUE)
    #GLFW.window_hint(GLFW::OPENGL_PROFILE, GLFW::OPENGL_CORE_PROFILE)
    GLFW.window_hint(GLFW::CONTEXT_VERSION_MAJOR, 2)
    GLFW.window_hint(GLFW::CONTEXT_VERSION_MINOR, 1)
    #GLFW.window_hint(GLFW::OPENGL_FORWARD_COMPAT, GL2::GL_TRUE)
    #GLFW.window_hint(GLFW::OPENGL_PROFILE, GLFW::OPENGL_CORE_PROFILE)
    GLFW.window_hint(GLFW::OPENGL_DEBUG_CONTEXT, 1)

    window = GLFW::Window.new(650, 650, 'OUI Blendish Demo')

    window.set_key_callback do |w, k, _, a, m|
      if k == GLFW::KEY_ESCAPE && a == GLFW::PRESS
        w.should_close = true
      end
      @ui.set_key(k, m, a)
    end

    window.set_char_callback do |_, v|
      @ui.set_char(v)
    end

    window.set_cursor_pos_callback do |_, x, y|
      @ui.set_cursor(x, y)
    end

    window.set_mouse_button_callback do |_, b, a, m|
      case b
      when 1 then b = 2
      when 2 then b = 1
      end
      @ui.set_button b, m, a == GLFW::PRESS
    end

    window.set_scroll_callback do |_, x, y|
      @ui.set_scroll(x, y)
    end

    window.make_current

    printf "OpenGL v%d.%d\n", window.window_attrib(GLFW::CONTEXT_VERSION_MAJOR),
                            window.window_attrib(GLFW::CONTEXT_VERSION_MINOR)
    puts "GLSL v" + GL2.glGetString(GL2::GL_SHADING_LANGUAGE_VERSION)
    puts "GLFW v" + GLFW.version_string

    GLEW.init

    vg = NVG::Context.new(NVG::ANTIALIAS)
    init(vg)

    GLFW.swap_interval = 0
    GLFW.time = 0

    c = 0.0
    total = 0
    peak_items = 0
    peak_alloc = 0

    until window.should_close?
      mx, my = window.cursor_pos
      win_width, win_height = window.window_size
      fb_width, fb_height = window.framebuffer_size
      px_ratio = fb_width.to_f / win_width

      GL2.glViewport(0, 0, fb_width, fb_height)
      GL2.glClearColor(0, 0, 0, 1)
      GL2.glClear(GL2::GL_COLOR_BUFFER_BIT | GL2::GL_DEPTH_BUFFER_BIT | GL2::GL_STENCIL_BUFFER_BIT)

      t = GLFW.time
      vg.draw(win_width, win_height, px_ratio) do
        draw(vg, win_width, win_height)
        peak_items = peak_items > @ui.item_count ? peak_items : @ui.item_count
        peak_alloc = peak_alloc > @ui.alloc_size ? peak_alloc : @ui.alloc_size
      end

      t2 = GLFW.time
      c += t2 - t
      total += 1
      if (total > (1 * 60))
        printf("%fms\n", (c.to_f / total) * 1000.0)
        total = 0
        c = 0.0
      end

      window.swap_buffers
      GLFW.poll_events
    end

    s = 8 + 4 + 4 + 4 + 8 + 4
    printf("Peak item count: %i (%i bytes)\nPeak allocated handles: %i bytes\n",
           peak_items, peak_items * s, peak_alloc)
  end
end

def main
  example = Example.new
  example.main
end

main
