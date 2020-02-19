from engine.entity import Entity
from vessels.vessel import Vessel


class Carrier(Vessel):

    def __init__(self, assets, x, y):
        self.entity = Entity(assets, 'Carrier', 0, x, y, 0.01, 0.0, 0.0)
        self.exhaust = Entity(assets, 'Exhaust', 0, x, y, 0.01, 0.0, 0.0)

    def get_position_and_size(self):
        return self.entity.get_position_and_size()

    def render(self, screen, x, y, size):
        self.entity.render(screen, x, y, size)
        self.exhaust.render(screen, x, y, size)
