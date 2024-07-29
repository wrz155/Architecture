package cn.itcast.bank;

import java.util.ArrayList;
import java.util.List;

public class NumberManage {
    private int lastNumber = 0;
    private List<Integer> queueNumber = new ArrayList<>();

    public synchronized Integer generateNewManager(){
        queueNumber.add(lastNumber);
        return lastNumber++;
    }

    public synchronized Integer fetchServiceNumber(){
        if(queueNumber.size() > 0)
            return queueNumber.remove(0);
        else
            return null;
    }

}
