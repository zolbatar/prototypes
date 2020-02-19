import os
import pygame


class ImageSet:

    def __init__(self, folder, name, num, convert):
        self.name = name
        self.images = []
        for x in range(num):
            filename = name + str(x + 1) + '.png'
            image = pygame.image.load(os.path.join(folder, filename))
            if convert == True:
                image = image.convert()
            self.images.append(image)
        self.size = self.images[0].get_rect()[2]

    def render(self, screen, index, x, y, size, angle):
        size = int(size)
        scale = size / self.images[index].get_width()
        image = pygame.transform.rotozoom(self.images[index], angle, scale)
        image_rect = image.get_rect().center
        x_offset = image_rect[0] - size / 2
        y_offset = image_rect[1] - size / 2
        screen.blit(image, [x - (size / 2) - x_offset,
                            y - (size / 2) - y_offset, size, size])

    def render_direct(self, screen, index, x, y, width, height):
        screen.blit(self.images[index], [x, y, width, height])
