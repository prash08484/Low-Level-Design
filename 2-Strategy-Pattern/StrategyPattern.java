/* 

Strategy Pattenr is applied when have to encapsulate the set of algorithms is seprate classes 
user decide at runtime type of strategy.

The Strategy Pattern encapsulates different algorithms behind a common interface so 
they can be selected interchangeably at runtime. It replaces large conditional logic 
with polymorphism, follows the Open/Closed Principle and Dependency Inversion Principle,
and favors composition over inheritance. A common example is supporting multiple payment
methods such as UPI, Card, and PayPal, where the client injects the desired payment 
strategy without changing the payment service

*/
public class StrategyPattern {

    // Violations , bloated if-else, OCP Fails, DIP Fails 
    class PaymentService {

        public void pay(String paymentType, int amount) {

            if (paymentType.equals("UPI")) {
                System.out.println("Paid using UPI");
            } else if (paymentType.equals("CARD")) {
                System.out.println("Paid using Card");
            } else if (paymentType.equals("PAYPAL")) {
                System.out.println("Paid using Paypal");
            } else if (paymentType.equals("NETBANKING")) {
                System.out.println("Paid using Net Banking");
            }

        }
    }

    // Following

    interface Payment {
        void pay(int amount);
    }

    class UPI implements Payment {
        public void pay(int amount) {
            // perform pay through UPI
        }
    }

    class CredidCard implements Payment {
        public void pay(int amount) {
            // perform pay through CreditCard
        }
    }

    class PaymentServices {
        private Payment payment;

        PaymentServices(Payment payment) {
            this.payment = payment;
        }

        void setStategy(Payment payment) {
            this.payment = payment;
        }

        void process(int amount) {
            payment.pay(amount);
        }
    }

}