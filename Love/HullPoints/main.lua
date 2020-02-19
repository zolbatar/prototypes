ship = require "ship"
system = require "system"

function love.load()
  system.init()
  ship.init()
end

function love.update()
end

function love.draw()
  ship.render()
  love.graphics.print("Hello World!", 400, 300)
end
