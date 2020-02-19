import pygame
import random


def perf_test(screen, width, height):
    for x in range(1000):
        pygame.draw.line(screen, (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)), [random.randint(0, width), random.randint(
            0, height)], [random.randint(0, width), random.randint(0, height)])
