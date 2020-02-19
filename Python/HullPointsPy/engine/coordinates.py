def size_to_screen(sector, size, width, height):
    return size * width * sector.scaleX

def size_to_screen_parallex(sector, size, width, height, parallex):
    return size * width * adjusted_scale(sector, sector.scaleX, parallex)

def adjusted_scale(sector, scale, parallex):
    return (((scale - 0.8) * parallex) + 0.8)

def coord_to_screen(sector, x, y, width, height):
    m = min(width, height)
    centreXR = sector.centreX * width
    centreYR = sector.centreY * height
    offsetX = (x * sector.scaleX) * m
    offsetY = (y * sector.scaleY) * m
    return (centreXR + offsetX, centreYR + offsetY)

def coord_to_screen_parallex(sector, x, y, width, height, parallex):
    m = min(width, height)
    centreXR = (((sector.centreX - 0.5) * parallex) + 0.5) * width
    centreYR = (((sector.centreY - 0.5) * parallex) + 0.5) * height
    offsetX = (x * adjusted_scale(sector, sector.scaleX, parallex)) * m
    offsetY = (y * adjusted_scale(sector, sector.scaleY, parallex)) * m
    return (centreXR + offsetX, centreYR + offsetY)
