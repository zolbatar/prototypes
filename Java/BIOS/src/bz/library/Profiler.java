package bz.library;

import java.io.*;
import java.util.concurrent.ConcurrentHashMap;
import bz.Parameters;

public class Profiler {
    private static final ConcurrentHashMap<String, Entry> entries = new ConcurrentHashMap<>(Parameters.CHASHMAP_INITIALCAPACITY, Parameters.CHASHMAP_LOADFACTOR, Parameters.CHASHMAP_CONCURRENCY);
    
    public static void WriteFile() {
        if (Parameters.PROFILE) {
            PrintWriter writer = null;
            try {
                writer = new PrintWriter("profile.csv", "UTF-8");
            } catch (FileNotFoundException | UnsupportedEncodingException ex) {
                System.out.println("Error create profile file");
            }
            for (Entry e : entries.values()) {
                String s = String.format("%s,%d,%f,%f", e.GetName(), e.GetCount(), e.GetTotal(), e.GetAverage());    
                writer.println(s);
            }
            writer.close();
        }
    }
    
    public static void Enter(String f) {
        if (Parameters.PROFILE) {
            Entry e = null;
            if (entries.containsKey(f)) {
                e = entries.get(f);
            } else {
                e = new Entry(f);
                entries.put(f, e);
            }
            e.In();
        }
    }

    public static void Leave(String f) {
        if (Parameters.PROFILE) {
            Entry e = null;
            if (entries.containsKey(f)) {
                e = entries.get(f);
            } else {
                e = new Entry(f);
                entries.put(f, e);
            }
            e.Out();
        }
    }

    private static class Entry {
        private final String name;
        private long time = 0, timeIn;
        private long count = 0;
        
        public Entry(String s) {
            name = s;
        }
        
        public void In() {
            timeIn = System.nanoTime();
        }
        
        public void Out() {
            Add(System.nanoTime() - timeIn);
        }

        private void Add(double t) {
            time += t;
            count++;
        }
        
        public double GetTotal() {
            return (time / 1000000.0);
        }

        public double GetAverage() {
            if (count == 0) {
                return 0.0;
            }
            return time / count / 1000000.0;
        }
        
        public long GetCount() {
            return count;
        }
        
        public String GetName() {
            return name;
        }
    }
}

