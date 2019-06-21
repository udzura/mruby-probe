##
## Probe Test
##

assert("Probe#hello") do
  t = Probe.new "hello"
  assert_equal("hello", t.hello)
end

assert("Probe#bye") do
  t = Probe.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("Probe.hi") do
  assert_equal("hi!!", Probe.hi)
end
