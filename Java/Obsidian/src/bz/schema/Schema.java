package bz.schema;

import java.util.*;

public class Schema {
    private final Map<String, Location> locations = new HashMap<>();
    private final Map<String, Resource> resources = new HashMap<>();
    private final Map<String, Task> tasks = new HashMap<>();
    
    public Location getLocation(String id) {
        return locations.get(id);
    }

    public Resource getResource(String id) {
        return resources.get(id);
    }

    public Task getTask(String id) {
        return tasks.get(id);
    }
}
