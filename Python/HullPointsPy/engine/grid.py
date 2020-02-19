import pygame
from engine.coordinates import coord_to_screen

grid_major = (0, 60, 0)
grid_minor = (0, 40, 0)


def render_grid(screen, width, height, sector):
    topleft = coord_to_screen(sector, -0.5, -0.5, width, height)
    bottomright = coord_to_screen(sector, 0.5, 0.5, width, height)
    x_spacing = (bottomright[0] - topleft[0]) / sector.grid_width
    x_spacing_minor = x_spacing / sector.minorGranularity
    y_spacing = (bottomright[1] - topleft[1]) / sector.grid_height
    y_spacing_minor = y_spacing / sector.minorGranularity

    # Minor verticalsGood
    x = topleft[0]
    y1 = topleft[1]
    y2 = bottomright[1]
    for posX in range(sector.grid_width * sector.minorGranularity):
        if posX % sector.minorGranularity != 0:
            pygame.draw.line(screen, grid_minor, [x, y1], [x, y2])
        x += x_spacing_minor

    # Major verticals
    x = topleft[0]
    for posX in range(sector.grid_width + 1):
        pygame.draw.line(screen, grid_major, [x, y1], [x, y2])
        x += x_spacing

    # Minor horizontals
    y = topleft[1]
    x1 = topleft[0]
    x2 = bottomright[0]
    for posY in range(sector.grid_height * sector.minorGranularity):
        if posY % sector.minorGranularity != 0:
            pygame.draw.line(screen, grid_minor, [x1, y], [x2, y])
        y += y_spacing_minor

    # Major Horizontals
    y = topleft[1]
    for posY in range(sector.grid_height + 1):
        pygame.draw.line(screen, grid_major, [x1, y], [x2, y])
        y += y_spacing
