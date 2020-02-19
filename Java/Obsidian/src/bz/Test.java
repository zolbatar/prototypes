package bz;

import bz.schema.*;
import bz.util.DataGenerate;

public class Test {
    
    public Test() {
        
    }
    
    public void Run() {
        Schema s = DataGenerate.generate(5, 50);
    }
}
