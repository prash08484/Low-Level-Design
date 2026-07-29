
// Clients should not be forced to depend on interfaces they do not use.
class InterfaceSegregationPrinciple {

// Violations
/*
    interface Machine {
        void print();
        void scan();
        void fax();
    }

    class BasicPrinter implements Machine {
        public void print() {
            System.out.println("Printing...");
        }
        public void scan() {
            throw new UnsupportedOperationException();
        }
        public void fax() {
            throw new UnsupportedOperationException();
        }
    }

    // A lot of functions in interface but limit it , always feature increase never reduce 
*/

    // Following
    interface Printer {
        void print();
    }

    interface Scanner {
        void scan();
    }

    interface Fax {
        void fax();
    }

    class BasicPrinter implements Printer {

        @Override
        public void print() {
            System.out.println("Printing...");
        }
    }
}