from engine.entity import Entity
from vessels.vessel import Vessel


class Frigate(Vessel):

    def __init__(self, entities, assets, x, y):
        entities.append(
            Entity(assets, 'Frigate', 0, x, y, 0.002, 0.0, 0.0))
