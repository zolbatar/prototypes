from render.imageset import ImageSet


class Assets:
    assets = dict()

    def __init__(self):
        self.assets['Background'] = ImageSet('assets/images', 'Background', 1, True)
        self.assets['Sun'] = ImageSet('assets/suns', 'sun', 4, False)
        self.assets['Planet'] = ImageSet('assets/planets', 'planet', 8, False)
        self.assets['Carrier'] = ImageSet('assets/vessels', 'carrier', 1, False)
        self.assets['Battleship'] = ImageSet('assets/vessels', 'battleship', 1, False)
        self.assets['Frigate'] = ImageSet('assets/vessels', 'frigate', 1, False)
        self.assets['Exhaust'] = ImageSet('assets/vessels', 'exhaust', 1, False)

    def get_asset(self, type):
        return self.assets[type]
