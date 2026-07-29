
// High-level modules should not depend on low-level modules. Both should depend on abstractions.
// Depend on interface not on concrete class

// e.g. for notification  
// if using specific service like send specificly call mail then its highly-coupled 
// need to free like whenever whatsapp,email,sms, etc. not

public class DependencyInverionPrinciple {

// Violations

/*  
    class WiredKeyboard {
        public void type() {
            System.out.println("using Wired-Keyboard");
        }
    }

    class Computer {
        private WiredKeyboard keyboard = new WiredKeyboard();
        public void work() {
            keyboard.type();
        }
    }

    // in future if different keyboard req. then need to modify classes 

*/

    // Following
    interface Keyboard{
        void type(); 
    }
    class Wired implements Keyboard{
        public void type(){
            // using wired-keyboard
        }
    }
    class Bluetooth implements Keyboard{
        public void type(){
            // using Bluetooth-keyboard
        }
    }
    class Virtual implements Keyboard{
        public void type(){
            // using Virtual-keyboard
        }
    }
    class Computer {
        Keyboard kwd; 
        Computer(Keyboard kwd){
            this.kwd=kwd;
        }
        void work(){
            kwd.type(); 
        }
    }

}