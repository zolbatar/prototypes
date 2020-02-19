import pygame


def dim_grid(sector, screen, width, height):
    x1, y1 = sector.coord_to_screen(-0.5, -0.5, width, height)
    x2, y2 = sector.coord_to_screen(0.5, 0.5, width, height)
    w = x2 - x1
    h = y2 - y1
    s = pygame.Surface((w, h))
    s.set_alpha(200)
    s.fill((0, 0, 0))
    screen.blit(s, (x1, y1))


def dim_all(sector, screen, width, height):
    s = pygame.Surface((width, height))
    s.set_alpha(120)
    s.fill((0, 0, 0))
    screen.blit(s, (0, 0))
