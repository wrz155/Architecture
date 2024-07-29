package cn.itcast.bank;

import java.util.Random;
import java.util.concurrent.Executors;

public class ServiceWindow {
    private int windowId = 1;
    private CustomerType type = CustomerType.COMMON;       // 窗口类型3种

    public void setWindowId(int windowId) {
        this.windowId = windowId;
    }

    public void setType(CustomerType type) {
        this.type = type;
    }

    public void start(){
        Executors.newSingleThreadExecutor().execute(new Runnable() {
            @Override
            public void run() {
                switch (type){
                    case COMMON:
                        commonService();
                        break;
                    case EXPRESS:
                        expressService();
                        break;
                    case VIP:
                        vipService();
                        break;
                }
            }
        });
    }

    private void commonService() {
        String windowName = "第" + windowId + "号" + type + "窗口";
        Integer number = NumberMachine.getInstance().getCommonManager().fetchServiceNumber();
        System.out.println(windowName + "正在获取任务");
        if(number != null){
            System.out.println(windowName + "为第" + number + "个" + type + "客户服务");
            long beginTime = System.currentTimeMillis();
            int maxServerTime = Constants.MAX_SERVICE_TIME - Constants.MIN_SERVICE_TIME;
            long serverTime = new Random().nextInt(maxServerTime) + 1 + Constants.MIN_SERVICE_TIME;
            try {
                Thread.sleep(serverTime);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            long costTime = System.currentTimeMillis() - beginTime;
            System.out.println(windowName + "为第" + number + "个" + type + "客户完成服务，耗时" + costTime / 1000 + "秒");
        }
        else {
            System.out.println(windowName + "没有接到任务, 休息1秒");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    private void expressService() {
        String windowName = "第" + windowId + "号" + type + "窗口";
        Integer number = NumberMachine.getInstance().getExpressManager().fetchServiceNumber();
        System.out.println(windowName + "正在获取任务");
        if(number != null){
            System.out.println(windowName + "为第" + number + "个" + type + "客户服务");
            long beginTime = System.currentTimeMillis();
            //int maxServerTime = Constants.MAX_SERVICE_TIME - Constants.MIN_SERVICE_TIME;
            //long serverTime = new Random().nextInt(maxServerTime) + 1 + Constants.MIN_SERVICE_TIME;
            try {
                Thread.sleep(Constants.MIN_SERVICE_TIME);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            long costTime = System.currentTimeMillis() - beginTime;
            System.out.println(windowName + "为第" + number + "个" + type + "客户完成服务，耗时" + costTime / 1000 + "秒");
        }
        else {
            System.out.println(windowName + "没有接到任务");
            commonService();
        }
    }

    private void vipService() {
        String windowName = "第" + windowId + "号" + type + "窗口";
        Integer number = NumberMachine.getInstance().getVipManager().fetchServiceNumber();
        System.out.println(windowName + "正在获取任务");
        if(number != null){
            System.out.println(windowName + "为第" + number + "个" + type + "客户服务");
            long beginTime = System.currentTimeMillis();
            int maxServerTime = Constants.MAX_SERVICE_TIME - Constants.MIN_SERVICE_TIME;
            long serverTime = new Random().nextInt(maxServerTime) + 1 + Constants.MIN_SERVICE_TIME;
            try {
                Thread.sleep(serverTime);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            long costTime = System.currentTimeMillis() - beginTime;
            System.out.println(windowName + "为第" + number + "个" + type + "客户完成服务，耗时" + costTime / 1000 + "秒");
        }
        else {
            System.out.println(windowName + "没有接到任务");
            commonService();
        }
    }

}
