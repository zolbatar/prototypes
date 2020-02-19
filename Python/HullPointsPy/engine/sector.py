import pygame
import random
import engine.grid
from engine.entity import Entity
from engine.coordinates import size_to_screen, size_to_screen_parallex, coord_to_screen, coord_to_screen_parallex
from engine.dim import dim_grid, dim_all
from vessels.carrier import Carrier
from vessels.battleship import Battleship
from vessels.frigate import Frigate


class Sector:
    zoom_table = [0.8]
    zoom = 0
    zoom_levels = 15
    grid_width = 10
    grid_height = 10
    centreX = 0.5
    centreY = 0.5
    scaleX = zoom_table[zoom]
    scaleY = zoom_table[zoom]
    minorGranularity = 5
    startDragX = 0
    startDragY = 0
    entities = []
    entitiesLive = []

    def __init__(self, assets):
        self.entities.append(
            Entity(assets, 'Sun', 0, -0.35, -0.35, 0.1, 0.01, 0.1))
        self.entities.append(
            Entity(assets, 'Planet', 0, 0.0, 0.0, 0.25, 0.05, 0.25))
        self.entitiesLive.append(Carrier(assets, 0.0, 0.0))
#        Battleship(self.entitiesLive, assets, 0.05, 0.0)
#        Frigate(self.entitiesLive, assets, 0.1, 0.0)

        # Build zoom table, doing this is better than using math at each level to avoid rounding
        v = 0.8
        for x in range(self.zoom_levels - 1):
            v *= 1.25
            self.zoom_table.append(v)

    def render(self, screen, width, height, assets, cinematic):
        bg = assets.get_asset('Background')
        bg.render_direct(screen, 0, 0, 0, width, height)

        # Render background items such as suns, planets. These move in a parallex style
        for e in self.entities:
            x, y, size = e.get_position_and_size()
            xS, yS = coord_to_screen_parallex(
                self, x, y, width, height, e.parallex)
            sizeS = size_to_screen_parallex(
                self, size, width, height, e.parallex)
            e.render(screen, xS, yS, sizeS)

        # Darken down the actual grid area so we can see the stuff rendered on top
        if not cinematic:
            dim_all(self, screen, width, height)

        # Draw grid
        if not cinematic:
            engine.grid.render_grid(screen, width, height, self)

        # Foreground stuff like vessels
        for e in self.entitiesLive:
            x, y, size = e.get_position_and_size()
            xS, yS = coord_to_screen(
                self, x, y, width, height)
            sizeS = size_to_screen(
                self, size, width, height)
            e.render(screen, xS, yS, sizeS)

    def update(self, frame_time):
        for e in self.entities:
            e.update(frame_time)

    def handle_event(self, event, width, height):
        if event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:
                self.startDragX = event.pos[0]
                self.startDragY = event.pos[1]
                return True
        elif event.type == pygame.MOUSEMOTION:
            if event.buttons[0] == 1:
                deltaX = event.pos[0] - self.startDragX
                deltaY = event.pos[1] - self.startDragY
                self.startDragX = event.pos[0]
                self.startDragY = event.pos[1]
                self.centreX += deltaX / width
                self.centreY += deltaY / height
                return True
        elif event.type == pygame.MOUSEBUTTONUP:

            # Zoom out
            if event.button == 5:
                self.zoom = max(0, self.zoom - 1)
            # Zoom in
            elif event.button == 4:
                self.zoom = min(self.zoom_levels - 1, self.zoom + 1)

            self.scaleX = self.zoom_table[self.zoom]
            self.scaleY = self.zoom_table[self.zoom]

            return True
