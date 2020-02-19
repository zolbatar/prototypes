window.start = () ->

    @graphics = new window.Graphics
    @graphics.grid()
    @layer = new Kinetic.Layer
    @graphics.addToStage @layer

    # Create random fighters
    @fighters = []
    for x in [0..1000]
        f = new window.EntityFighter @layer
        f.setPosition Math.random() * @graphics.stage.getAttr('width'), Math.random() * @graphics.stage.getAttr('height')
        f.setRotation Math.random() * 360.0
        @fighters.push f
    setInterval(update, 25)

update = () ->
    for f in @fighters
        f.move Math.random() * 2.0 - 1.0, Math.random() * 2.0 - 1.0
        f.rotate Math.random() * 5.0
    @layer.draw()
    
