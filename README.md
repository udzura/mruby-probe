# mruby-probe   [![Build Status](https://travis-ci.org/udzura/mruby-probe.svg?branch=master)](https://travis-ci.org/udzura/mruby-probe)
Probe class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'udzura/mruby-probe'
end
```
## example
```ruby
p Probe.hi
#=> "hi!!"
t = Probe.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the MIT License:
- see LICENSE file
