
// Open for Extension and closed for modification 
public class OpenClosedPrinciple {

// Violate OCP 
/*     
    interface Payment {
        String getType();
    }

    class CrediCard implements Payment {
        public String getType() {
            return "CreditCard";
        }
    }

    class Paypal implements Payment {
        public String getType() {
            return "Paypal";
        }
    }

    class PaymentProcessor {
        public void pay(Payment payment, double amonut) {
            if (payment.getType().equals("CreditCard")) {
                System.out.println("Payment through CrediCard");
            } else if (payment.getType().equals("Paypal")) {
                System.out.println("Payment through Paypal");
            } else {
                System.out.println("Invalid Payment Gateway");
            }
        }
    }
*/

    // Follow OCP Principles

    interface Payment {
        void pay(double amount);
    }

    class Paypal implements Payment {
        public void pay(double amount) {
            System.out.println("Payment through Paypal");
        }
    }

    class UPI implements Payment {
        public void pay(double amount) {
            System.out.println("Payment through UPI");
        }
    }

    class CrediCard implements Payment {
        public void pay(double amount) {
            System.out.println("Payment through CrediCard");
        }
    }

    class PaymentProcessor {
        public void process(Payment payment, double amount) {
            payment.pay(amount);
        }
    }

}