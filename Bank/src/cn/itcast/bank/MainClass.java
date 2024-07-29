package cn.itcast.bank;

import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class MainClass{
    public static void main(String[] args) {
        for(int i = 1; i< 5;i++){
            ServiceWindow commonWindow = new ServiceWindow();
            commonWindow.setWindowId(1);
            commonWindow.start();
        }

        ServiceWindow expressWindow = new ServiceWindow();
        expressWindow.setType(CustomerType.EXPRESS);
        expressWindow.start();

        ServiceWindow vipWindow = new ServiceWindow();
        vipWindow.setType(CustomerType.VIP);
        vipWindow.start();

        Executors.newScheduledThreadPool(1).scheduleAtFixedRate(
                new Runnable() {
                    @Override
                    public void run() {
                        Integer number = NumberMachine.getInstance().getCommonManager().generateNewManager();
                        System.out.println(number + "号普通客户等待服务");
                    }
                },
                0,
                Constants.COMMON_CUSTOMER_INTERVAL_TIME,
                TimeUnit.SECONDS
        );

        Executors.newScheduledThreadPool(1).scheduleAtFixedRate(
                new Runnable() {
                    @Override
                    public void run() {
                        Integer number = NumberMachine.getInstance().getExpressManager().generateNewManager();
                        System.out.println(number + "号快速客户等待服务");
                    }
                },
                0,
                Constants.COMMON_CUSTOMER_INTERVAL_TIME * 2,
                TimeUnit.SECONDS
        );

        Executors.newScheduledThreadPool(1).scheduleAtFixedRate(
                new Runnable() {
                    @Override
                    public void run() {
                        Integer number = NumberMachine.getInstance().getVipManager().generateNewManager();
                        System.out.println(number + "号VIP客户等待服务");
                    }
                },
                0,
                Constants.COMMON_CUSTOMER_INTERVAL_TIME * 6,
                TimeUnit.SECONDS
        );


    }
}
