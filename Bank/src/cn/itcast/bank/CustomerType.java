package cn.itcast.bank;

public enum CustomerType {
    COMMON,EXPRESS,VIP;

    @Override
    public String toString() {
        switch (this){
            case COMMON:
                return "普通";
            case EXPRESS:
                return "快速";
            case VIP:
                return "vip";
            default:
                return null;
        }
    }
}
