/*
    It have explosion of classes, 2^N classes, not maintainable classes 
    all combination possible for each seprate class 
    NOT follow OCP  
*/

public class DecoratorPatternViolations {

    class Coffee {
        double cost() {
            return 100;
        }
    }

    class MilkCoffee extends Coffee {
        double cost() {
            return 100 + 50;
        }
    }

    class MilkSugarCoffee extends Coffee {
        double cost() {
            return 130;
        }
    }

    class SugarCoffee extends Coffee {
        double cost() {
            return 110;
        }
    }

}
