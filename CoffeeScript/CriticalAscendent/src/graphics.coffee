class window.Graphics
    constructor: () ->
        @stage = new Kinetic.Stage container: 'container', width: window.innerWidth, height: window.innerHeight
        @layer = new Kinetic.Layer
        @addToStage @layer
        @offset_x = 0
        @offset_y = 0

        # Grid
        @layer_grid = new Kinetic.Layer
        @grid_spacing = 50
        @grid_minorspacing = 10
        @grid_colour = 'gray'
        @grid_width = 1
        @grid_opacity = 0.4
        @grid_opacityminor = 0.25
        @grid_dash = [1,1]
    addToStage: (o) -> @stage.add o
    addToTopLayer: (o) -> @layer.add o
    addToLayer: (layer, o) -> layer.add o
    test: () ->
        rect = new Kinetic.Rect
            x: 239,
            y: 75,
            width: 100,
            height: 50,
            fill: 'green',
            stroke: 'black',
            strokeWidth: 4
        @addToTopLayer rect
        @layer.draw()
    grid: () ->
        @addToStage @layer_grid
        points = []
        for y in [0..@stage.getAttr('height')] by @grid_minorspacing
            line = new Kinetic.Line
                points: [0, y, @stage.getAttr('width'), y]
                stroke: @grid_colour
                strokeWidth: @grid_width
                opacity: @grid_opacityminor
                dashArray: @grid_dash
            @addToLayer @layer_grid, line
        for y in [0..@stage.getAttr('height')] by @grid_spacing
            line = new Kinetic.Line
                points: [0, y, @stage.getAttr('width'), y]
                stroke: @grid_colour
                strokeWidth: @grid_width
                opacity: @grid_opacity
            @addToLayer @layer_grid, line
        for x in [0..@stage.getAttr('width')] by @grid_minorspacing
            line = new Kinetic.Line
                points: [x, 0, x, @stage.getAttr('height')]
                stroke: @grid_colour
                strokeWidth: @grid_width
                opacity: @grid_opacityminor
                dashArray: @grid_dash
            @addToLayer @layer_grid, line
        for x in [0..@stage.getAttr('width')] by @grid_spacing
            line = new Kinetic.Line
                points: [x, 0, x, @stage.getAttr('height')]
                stroke: @grid_colour
                strokeWidth: @grid_width
                opacity: @grid_opacity
            @addToLayer @layer_grid, line
        @layer_grid.draw()

