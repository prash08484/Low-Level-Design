/*
   Abstract Factory Pattern provides an interface for creating families of related 
   or dependent objects without specifying their concrete classes.
*/

public class AbstractFactoryPatternViolation {

    // ================= Product Interfaces =================

    interface Button {
        void paint();
    }

    interface Checkbox {
        void paint();
    }

    // ================= Windows Products =================

    static class WindowsButton implements Button {

        @Override
        public void paint() {
            System.out.println("Windows Button");
        }
    }

    static class WindowsCheckbox implements Checkbox {

        @Override
        public void paint() {
            System.out.println("Windows Checkbox");
        }
    }

    // ================= Mac Products =================

    static class MacButton implements Button {

        @Override
        public void paint() {
            System.out.println("Mac Button");
        }
    }

    static class MacCheckbox implements Checkbox {

        @Override
        public void paint() {
            System.out.println("Mac Checkbox");
        }
    }

    // ================= Business Class =================

    static class Application {

        private Button button;
        private Checkbox checkbox;

        public Application(String os) {

            // ❌ VIOLATION:
            // Business class is deciding WHICH objects to create.

            if (os.equalsIgnoreCase("Windows")) {

                button = new WindowsButton();
                checkbox = new WindowsCheckbox();

            } else if (os.equalsIgnoreCase("Mac")) {

                button = new MacButton();
                checkbox = new MacCheckbox();

            } else {

                throw new IllegalArgumentException("Unsupported OS");
            }
        }

        public void renderUI() {

            System.out.println("\nRendering UI...\n");

            button.paint();
            checkbox.paint();
        }
    }

    // ================= Main =================

    public static void main(String[] args) {

        Application windowsApp = new Application("Windows");
        windowsApp.renderUI();

        System.out.println("--------------------");

        Application macApp = new Application("Mac");
        macApp.renderUI();
    }
}