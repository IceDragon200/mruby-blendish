MRuby::Gem::Specification.new('mruby-blendish') do |spec|
  spec.license = 'MIT'
  spec.authors = ['Corey Powell']
  spec.version = '0.0.0'
  spec.summary = 'oui-blendish bindings'
  spec.description = 'A oui-blendish binding for mruby'
  spec.homepage = 'https://github.com/IceDragon200/mruby-blendish'
  # compiler config
  spec.cc.include_paths << ["#{build.root}/src"]
  # Treat all warnings as errors, forces you to write compliant code
  spec.cc.flags << '-Werror'
  # I think we inherited the parent flags, might as well flatten the array to
  # be sure we're working with Array<String> and not Array<String, Array<String>>
  spec.cc.flags = spec.cc.flags.flatten
  # the blendish code is written in C99 style,
  # the declaration-after-statement warning will cause it to flip out, since
  # I treat all warnings as errors...
  spec.cc.flags.reject! { |s| s.include?('-Wdeclaration-after-statement') }
  # OUI
  add_dependency 'mruby-oui',    github: 'IceDragon200/mruby-oui'
  # last but not least, this gem requires nanovg
  add_dependency 'mruby-nanovg', github: 'IceDragon200/mruby-nanovg'
end
