import java.util.*; 

// Definations : 
// The Builder Pattern is a creational design pattern that constructs complex objects step by step.
// It's particularly useful when you need to create objects with many optional parameters or 
// when the construction process should allow different representations of the same object.


// Issues : 

// 1.
// When a class has many optional parameters, you end up with a large number of constructors. This is called
// Telescoping Constructors (Constructor Overload Explosion).

// 2. 
// If you want to make a class immutable (i.e., its fields are final), you cannot use setters.
// Creating test objects becomes increasingly complex and verbose without builders, particularly
// when many fields are optional.
// Violates the Single Responsibility Principle (SRP) because the class manages both data 
// storage and construction logic.


public class BuilderPatternViolations{

    // class that invole the violations of builder pattern 



    

    public static void main(String []args){
        Scanner sc=new Scanner(System.in); 


        sc.close();
    }
}