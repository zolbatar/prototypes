package bz.ecs;

import org.magnos.entity.Control;
import org.magnos.entity.Controller;
import org.magnos.entity.Entity;
import org.magnos.entity.Ents;

public class Controllers {
    public static final Controller PHYSICS = Ents.newController("physics", new Control() {
        public void update(Entity e, Object updateState) {
            float dt = (Float) updateState;
            Vector pos = e.get(Components.POSITION);
            Vector vel = e.get(Components.VELOCITY);
            pos.add(dt, vel);
        }
    });

    public static final Controller PHYSICS_ACCELERATION = Ents.newControllerAlternative(PHYSICS, new Control() {
        public void update(Entity e, Object updateState) {
            float dt = (Float) updateState;
            Vector pos = e.get(Components.POSITION);
            Vector vel = e.get(Components.VELOCITY);
            Vector acc = e.get(Components.ACCELERATION);
            vel.add(dt, acc);
            pos.add(dt, vel);
        }
    });
}


