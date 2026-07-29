
// Each class should have single responsibilty and only it's around reason to change 
public class SingleResposibilityPrinciple {

// SRP Violation : multiple reason to change the class User 
/*
    class User {
        void updateProfile(){}
        void saveToDatabase(){}
        void sendEmail(){}
    }
*/
    // SRP Following Rules : Each class is loosely coupled 
    class User {
        void updateProfile() { }
    }

    class UserRepository {
        void save(User user) { } 
    }

    class EmailService {
        void sendWelcomeEmail(User user) { }
    }

}
