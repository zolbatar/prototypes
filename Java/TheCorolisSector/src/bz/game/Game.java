package bz.game;

import bz.game.universe.Universe;

public class Game {
    private final Universe universe;

    public Game(Difficulty difficulty, GameSize size) {
        universe = new Universe(size);
    }
    
    public Universe GetUniverse() {
        return universe;
    }
    
}
