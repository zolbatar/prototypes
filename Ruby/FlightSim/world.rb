require "rubygems"
require "rubygame"
require_relative "player.rb"

class World
  @@horizon = 15
  @@width = 100
  @@height = 100
  @@step = 1
  @@size = 20
  @@screen_x_width = 25
  @@screen_x_adjust = 0.05
  @@screen_y_height = 200
  @@screen_y_adjust = 0.05
  @@screen_y_shrink = 1000.0

  def initialize(resolution)
    @resolution = resolution
    @world = Array.new(@@width)
    for x in 0.upto(@@width)
      y_array = Array.new(@@height,0)
      @world[x] = y_array
      for y in 0.step(@@height,@@step)
        y_array[y] = rand(10000)
      end
    end
    @player = Player.new
  end

  def render(surface)

    # We want to view out to the horizon
    for x in (@player.x - @@horizon).upto(@player.x + @@horizon)
      x_array = @world[x]
      x_arrayR = @world[x+1]
      for z in (@player.z).upto(@player.z + @@horizon)
        z_array = x_array[z]
        z_arrayR = x_array[z+1]
        render_polys(surface,x-@player.x,z-@player.z,x_array[z+1],x_arrayR[z+1],x_array[z],x_arrayR[z])
      end
    end
  end

  def get_or_build_x_hash(x)
#    if !@worldX.has_key? x
#      @worldX[x] = Hash.new 
#    end
#    @worldX[x]
  end

  def get_or_build_z(x_hash,z)
#    if !x_hash.has_key? z
#      v = rand(10000)
#      if z < 0
#        v = x_hash[z + 1] if x_hash.has_key? (z + 1)
#      else
#        v = x_hash[z - 1] if x_hash.has_key? (z - 1)
#      end if 
#      x_hash[z] = rand(1000) + v 
#    end  
#    x_hash[z]
  end

  def perspective(x,z,y)
    puts y if y != 0
    d_x = (@resolution[0] / 2) + ((1.0 - (z * @@screen_y_adjust)) * (x * @@screen_x_width))
    d_y = (@resolution[1] / 2) + ((1.0 - (z * @@screen_y_adjust)) * @@screen_y_height) - (y / @@screen_y_shrink)
    [d_x, d_y]
  end

  def render_polys(surface,x,z,y1,y2,y3,y4)
    points = 
      [
        perspective(x,z,y1),
        perspective(x+1,z,y2),
        perspective(x,z+1,y3)
      ]
    surface.draw_polygon(points,[200,0,0])

    points = 
      [
        perspective(x+1,z,y2),
        perspective(x,z+1,y3),
        perspective(x+1,z+1,y4)
      ]
    surface.draw_polygon(points,[0,0,200])
  end

  def animate
  end

end