class Entity:
    angle = 0

    def __init__(self, assets, type, index, x, y, size, parallex, rotate_speed):
        self.image = assets.get_asset(type)
        self.index = index
        self.x = x
        self.y = y
        self.size = size
        self.parallex = parallex
        self.rotate_speed = rotate_speed

    def get_position_and_size(self):
        return (self.x, self.y, self.size)

    def render(self, screen, x, y, size):
        self.image.render(screen, self.index, x, y, size, self.angle)

    def update(self, frame_time):
        self.angle += self.rotate_speed * frame_time
