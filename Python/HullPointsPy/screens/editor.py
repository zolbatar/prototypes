import pygame
import random
from engine.sector import Sector


class Editor:

    def render(self, screen, width, height, sector, assets, cinematic):
        sector.render(screen, width, height, assets, cinematic)

    def update(self, frame_time, sector):
        sector.update(frame_time)

    def handle_event(self, event, width, height, sector):
        handled = sector.handle_event(event, width, height)
#        if not handled:
#            print("Event not handled: ", event)
