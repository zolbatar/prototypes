import os
import pygame

os.environ['SDL_VIDEO_CENTERED'] = '1'


def setup_screen():
    screens = os.popen("xrandr  | grep \* | cut -d' ' -f4").read().split('\n')
    print('Found screens: ', screens)
    screen = screens[0].split('x')
    print('Pygame display modes: ', pygame.display.list_modes())
    fullscreen = False
    if fullscreen == True:
        screen = pygame.display.set_mode(
            (int(screen[0]), int(screen[1])), pygame.FULLSCREEN | pygame.DOUBLEBUF | pygame.HWSURFACE)
    else:
        screen = pygame.display.set_mode(
            (int(screen[0]) - 200, int(screen[1]) - 200))
    print("Driver: ", pygame.display.get_driver())
    print("Screen:", screen)
    return (screen, screen.get_width(), screen.get_height())
