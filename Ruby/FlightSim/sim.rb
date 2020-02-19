#!/usr/bin/env ruby
 
require "rubygems"
require "rubygame"
require_relative "world.rb"

include Rubygame

# Setup windows
resolution = [1024, 768]
display_resolution = [resolution[0], resolution[1]]
screen = Screen.open display_resolution, 32, [ HWSURFACE, DOUBLEBUF]
screen.title = "Flight Simulator"
event_queue = EventQueue.new
event_queue.enable_new_style_events
screen.show_cursor = false

# New world
world = World.new display_resolution

# Game loop
quit = false
until quit == true
  surface = Surface.new display_resolution

  # Render world
  surface.draw_box_s [0, 0], display_resolution, [0, 0, 0, 255]
  world.render surface
  surface.blit screen, [0, 0]
  screen.flip

  # Animate
  world.animate
 
  # Stop if the user closes the window
  event_queue.each { |event| 
#   p event
    if event.is_a? Rubygame::Events::KeyPressed 
      case event.string
      when "q"
        quit = true
#      when "1", "2"
#        type = Integer(event.string)
      end
    end
  }
end

