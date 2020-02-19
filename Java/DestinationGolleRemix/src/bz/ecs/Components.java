package bz.ecs;

import org.magnos.entity.Component;
import org.magnos.entity.Ents;

public class Components {
    public static final Component<Vector> POSITION = Ents.newComponent("position", new Vector());
    public static final Component<Vector> VELOCITY = Ents.newComponent("velocity", new Vector());
    public static final Component<Vector> ACCELERATION = Ents.newComponent("acceleration", new Vector());
}
