from engine.entity import Entity
from vessels.vessel import Vessel


class Battleship(Vessel):

    def __init__(self, entities, assets, x, y):
        entities.append(
            Entity(assets, 'Battleship', 0, x, y, 0.005, 0.0, 0.0))
