puts Process.pid
i = 0
loop do
  Probe.probe(i)
  i += 1
  sleep 1
end
