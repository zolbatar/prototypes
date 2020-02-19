import cProfile
import time
import pygame
import render.graphics
from engine.sector import Sector
from assets.assets import Assets
from screens.editor import Editor


def main():
    # Setup pygame
    successes, failures = pygame.init()
    print("Init: {0} successes and {1} failures".format(successes, failures))
    screen, width, height = render.graphics.setup_screen()

    # FPS
    clock = pygame.time.Clock()
    FPS = 60  # Frames per second.

    # Setup
    assets = Assets()
    sector = Sector(assets)
    editor = Editor()
    current_screen = editor
    cinematic = False
    while True:
        start = time.time()
        clock.tick(FPS)

        # Events, handle some here and pass the rest to the current screen
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                quit()
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    cinematic = not cinematic
                elif event.key == pygame.K_ESCAPE:
                    quit()
            else:
                current_screen.handle_event(event, width, height, sector)

        # Clear
        screen.fill((0, 0, 0))

        # Render current screen
        current_screen.render(screen, width, height, sector, assets, cinematic)

        # Flip
        pygame.display.update()
        end = time.time()
        frame_time = end - start

        # Update
        current_screen.update(frame_time, sector)


if __name__ == "__main__":
    main()
#    cProfile.run('main()')
