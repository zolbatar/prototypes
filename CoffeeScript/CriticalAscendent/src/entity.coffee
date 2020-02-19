class window.Entity
    constructor: (layer) ->
        @modules = []
        @group = new Kinetic.Group
        layer.add @group
    addmodule: (m, x, y) ->
        m.setPosition(x, y)
        @modules.push(m)
    setPosition: (x, y) ->
        @group.setAbsolutePosition x, y
    setRotation: (r) ->
        @group.setRotationDeg r
    rotate: (r) ->
        @group.rotateDeg r
    move: (x, y) ->
        @group.move x, y

class window.EntityFighter extends window.Entity
    constructor: (layer) ->
        super layer
        m = new window.ModuleFighter @group
        @addmodule(m, 0, 0)

