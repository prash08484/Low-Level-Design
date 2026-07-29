/*
   In Decorator Pattern adding topping/extra feature without modifying previous code 
   It's Strucutral Pattern, follow open/closed Principle. 

*/

public class DecoratorPattern{
    interface Coffee {
        String getDescription();

        double cost();
    }

    static public class SimpleCoffee implements Coffee {
        public String getDescription() {
            return "Simple Coffee";
        }

        public double cost() {
            return 100;
        }
    }

    abstract static class CoffeeDecorator implements Coffee {
        protected Coffee coffee;

        CoffeeDecorator(Coffee coffee) {
            this.coffee = coffee;
        }
    }

    public static class MilkDecorator extends CoffeeDecorator {
        MilkDecorator(Coffee coffee) {
            super(coffee);
        }

        public String getDescription() {
            return coffee.getDescription() + " Milk";
        }

        public double cost() {
            return coffee.cost() + 50;
        }
    }

    public static class CreamDecorator extends CoffeeDecorator {
        CreamDecorator(Coffee coffee) {
            super(coffee);
        }

        public String getDescription() {
            return coffee.getDescription() + " Creame";
        }

        public double cost() {
            return coffee.cost() + 20;
        }
    } 

    public static void main(String[] args) {

        Coffee coffee = new SimpleCoffee();

        coffee = new MilkDecorator(coffee);

        coffee = new CreamDecorator(coffee);

        System.out.println(coffee.getDescription());

        System.out.println(coffee.cost());
    }
}
