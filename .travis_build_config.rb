MRuby::Build.new do |conf|
  toolchain :gcc
  conf.gembox 'default'
  conf.gem core: 'mruby-io'
  conf.gem core: 'mruby-sleep'
  conf.gem github: 'iij/mruby-process'
  conf.gem File.expand_path(File.dirname(__FILE__))
  conf.enable_test

  if ENV['DEBUG'] == 'true'
    conf.enable_debug
    conf.cc.defines = %w(MRB_ENABLE_DEBUG_HOOK)
    conf.gem core: 'mruby-bin-debugger'
  end
end
