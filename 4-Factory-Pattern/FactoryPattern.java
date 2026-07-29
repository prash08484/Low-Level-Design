
public class FactoryPattern{

    interface Notification {
        void send();
    }

    static class EmailNotification implements Notification {
        public void send() {
            System.out.println("Email Sent");
        }
    }

    static class SMSNotification implements Notification {
        public void send() {
            System.out.println("SMS Sent");
        }
    }

    static class PushNotification implements Notification {
        public void send() {
            System.out.println("Push Notification Sent");
        }
    }

    public class NotificationFactory {

        public static Notification createNotification(String type) {

            if (type.equalsIgnoreCase("EMAIL"))
                return new EmailNotification();

            if (type.equalsIgnoreCase("SMS"))
                return new SMSNotification();

            if (type.equalsIgnoreCase("PUSH"))
                return new PushNotification();

            throw new IllegalArgumentException("Invalid Notification Type");

        }

    }

    public static void main(String[] args) {

        Notification notification = NotificationFactory.createNotification("EMAIL");

        notification.send();
    }
}