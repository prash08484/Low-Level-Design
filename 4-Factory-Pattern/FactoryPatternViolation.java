
/*
    The Factory Pattern provides a centralized way to create objects without exposing 
    the object creation logic to the client. The client requests an object from the factory
    instead of instantiating it directly.
*/

/*

   Responsibility 1 
   Business Logic
   notification.send(message);
   
   Responsibility 2 

   Object Creation
   new EmailNotification();
   new SMSNotification();
   new PushNotification();

   A business class should not be deciding which object to create.

*/

public class FactoryPatternViolation {

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

    static class ManageNotification {

        public void notifyUser(String type) {

            Notification notification;

            if (type.equalsIgnoreCase("EMAIL")) {
                notification = new EmailNotification();

            } else if (type.equalsIgnoreCase("SMS")) {
                notification = new SMSNotification();

            } else {
                notification = new PushNotification();
            }

            notification.send();
        }
    }

    public static void main(String[] args) {

        ManageNotification manager = new ManageNotification();

        manager.notifyUser("EMAIL");
        manager.notifyUser("SMS");
    }
}
