class window.Module
    constructor: () ->
        @points = [0,0]
    build: (group) ->
        @line = new Kinetic.Line
            points: @points
            stroke: 'red'
            strokewidth: 1.5
            opacity: 1
            lineJoin: 'round'
            lineCap: 'round'
        group.add @line
    setPosition: (x, y) -> 
        @line.setAbsolutePosition x, y

class window.ModuleFighter extends window.Module
    constructor: (group) ->
        @points = [-5, -5, 0, 5, 5, -5, -5, -5]
        @build group
