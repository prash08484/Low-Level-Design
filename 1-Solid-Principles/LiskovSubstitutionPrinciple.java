
// object of superclass must be replacable by object of subclass with breaking the correctness
// my way: as go down the class specificity increase not feature reduce in subclass 
public class LiskovSubstitutionPrinciple{

// Violate LSP  
/*  
    interface Bird{
        void fly(); 
    }
    class Sparrow implements Bird{
        public void fly(){
            System.out.println("Sparrow is Flying "); 
        }
    }
    class Penguin implements Bird{
        public void fly(){
             throw new RuntimeException("Not supported");
        }
    }
    
    // Bird b=new Penguin(); 
    // b.fly(); through the error
*/


    // Follow LSP Principle 
    interface Bird{ 
        void eat(); 
    }
    interface FlyingBirds extends Bird{
        void fly(); 
    }
    class Sparrow implements FlyingBirds{
       public void eat(){ }
       public void fly(){ }
    }
    class Penguin implements Bird{
       public void eat(){ } 
    }

}