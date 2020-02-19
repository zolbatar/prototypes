local system = {}

function system.init()
  print "Initialising system"
end

function system.render()
  for x = -1, 1, 0.1 do
    print(x)
  end
end

return system
  