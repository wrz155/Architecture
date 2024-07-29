package cn.itcast.bank;

public class NumberMachine {
    private NumberManage commonManager = new NumberManage();
    private NumberManage expressManager = new NumberManage();
    private NumberManage vipManager = new NumberManage();

    public NumberManage getCommonManager() {
        return commonManager;
    }

    public NumberManage getExpressManager() {
        return expressManager;
    }

    public NumberManage getVipManager() {
        return vipManager;
    }

    // 单例
    private NumberMachine(){}

    private static NumberMachine instance = new NumberMachine();

    public static NumberMachine getInstance(){
        return instance;
    }
}
