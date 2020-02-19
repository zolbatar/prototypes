package bz.ui;

import java.util.*;

public class ClickList {
    private List<ClickItem> items = new ArrayList<>(64);
    
    public void Clear() {
        items.clear();
    }
    
    private class ClickItem {
        public int x1, y1, x2, y2;
        public String code;
    }
    
    public void AddItem(int x1, int y1, int x2, int y2, String code) {
        ClickItem ci = new ClickItem();
        ci.x1 = x1;
        ci.y1 = y1;
        ci.x2 = x1 + x2;
        ci.y2 = y1 + y2;
        ci.code = code;
        items.add(ci);
    }
    
    public String CheckClick(int x, int y) {
        for (ClickItem ci : items) {
            if (x > ci.x1 && x < ci.x2 && y > ci.y1 && y < ci.y2) {
                return ci.code;
            }
        }
        return null;
    }
    
}
