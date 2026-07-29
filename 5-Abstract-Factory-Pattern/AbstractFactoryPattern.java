public class AbstractFactoryPattern {

    // ==========================
    // Product Interfaces
    // ==========================

    interface Button {
        void paint();
    }

    interface Checkbox {
        void paint();
    }

    // ==========================
    // Windows Products
    // ==========================

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

    // ==========================
    // Mac Products
    // ==========================

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

    // ==========================
    // Abstract Factory
    // ==========================

    interface GUIFactory {

        Button createButton();

        Checkbox createCheckbox();
    }

    // ==========================
    // Windows Factory
    // ==========================

    static class WindowsFactory implements GUIFactory {

        @Override
        public Button createButton() {
            return new WindowsButton();
        }

        @Override
        public Checkbox createCheckbox() {
            return new WindowsCheckbox();
        }
    }

    // ==========================
    // Mac Factory
    // ==========================

    static class MacFactory implements GUIFactory {

        @Override
        public Button createButton() {
            return new MacButton();
        }

        @Override
        public Checkbox createCheckbox() {
            return new MacCheckbox();
        }
    }

    // ==========================
    // Business Class
    // ==========================

    static class Application {

        private Button button;
        private Checkbox checkbox;

        Application(GUIFactory factory) {

            // No object creation logic here
            button = factory.createButton();
            checkbox = factory.createCheckbox();
        }

        public void renderUI() {

            System.out.println("\nRendering UI...\n");

            button.paint();
            checkbox.paint();
        }
    }

    // ==========================
    // Main
    // ==========================

    public static void main(String[] args) {

        GUIFactory factory;

        String os = "Windows";

        if (os.equalsIgnoreCase("Windows")) {
            factory = new WindowsFactory();
        } else {
            factory = new MacFactory();
        }

        Application app = new Application(factory);

        app.renderUI();
    }
}