#include<iostream>
#include<vector>

using namespace std;


enum OrderStatus{  
    PLACED,
    CONFIRMED,
    PREPARING,
    OUT_FOR_DELIVERY,
    DELIVERED,
    CANCELLED
};

// user account information 
struct UserAccountInfo
{
    string name; 
    string contactNumber; 
    string emailId;
    string address;
    int UserId;

    UserAccountInfo(){}

    UserAccountInfo(string name, string contactNumber, string emailId, string address, int UserId){
        this->UserId = UserId;
        this->name=name; 
        this->contactNumber=contactNumber; 
        this->emailId=emailId; 
        this->address=address;    
    }
    
};

// delivery partner account information 
struct DeliveryPartnerAccountInfo
{
    string name; 
    string contactNumber;  
    bool available;
    int DeliveryPartnerId;

    DeliveryPartnerAccountInfo(){}

    DeliveryPartnerAccountInfo(string name, string contactNumber, int DeliveryPartnerId){
        this->DeliveryPartnerId = DeliveryPartnerId;
        this->name=name; 
        this->contactNumber=contactNumber;  
        available=0; 
    }    
};

// order information 
struct OrderInfo{

    static int orderCount; 
    int orderId; 
    OrderStatus status = PREPARING;
    int customerId;
    int restaurantId;
    vector< tuple<string,double,int> > order;  // item price count

    double totalAmount=0;

    OrderInfo(int customerId, int restaurantId){
        this->customerId = customerId; 
        this->restaurantId = restaurantId; 
    }
    OrderInfo( ){ }

    void showOrder(){ 
        for(auto &[itemName, itemPrice, itemCount ]: order){
            cout<<itemName<<" : "<<itemPrice<<" X "<<itemCount<<'\n'; 
        } 
        cout<<"total amout : "<<totalAmount<<'\n';
        cout<<"-----------\n";
    }

    void addItem(tuple<string,double,int> item){ 
        order.push_back(item); 
        auto [itemName, itemPrice, itemCount ] = item;
        totalAmount+=itemPrice*itemCount;
    }
    void updateStatus(OrderStatus status){
        this->status = status;
    }

};     

// Restaurants menu
struct RestaurantMenu{
    
    vector<pair<string,double>> menu; 
    
    void addMenu(pair<string,double> item){  
        menu.push_back(item);
    }    

    void showMenu(){
        for(auto &[itemName, itemPrice]: menu){
            cout<<itemName<<" : "<<itemPrice<<'\n';
        }
        cout<<"-----------\n";
    }
    OrderInfo OrderMenu(int userId, int restaurantsId){
        
        OrderInfo userOrder(userId,restaurantsId); 

        // user enter the index it's count 
        cout<<"Select the item, and items count [ enter -1 to exit ] : \n"; 

        while(1){
            int itemId;  cin>>itemId; 
            int itemCount; cin>>itemCount;
            if(itemId<0 or itemId>= menu.size()) break;
            else {
                tuple<string,double,int> item = {menu[itemId].first, menu[itemId].second, itemCount};
                userOrder.addItem(item);
            } 
        } 

        // apply discount before payments 

        return userOrder; 

    }
};

class Restaurants{
    private: 

    static int RestaurantCount;

    int RestaurantID;
    string Name;
    string Address; 
    RestaurantMenu Menu; 

    public: 
    Restaurants(string Name, string Address){
        this->Name = Name; 
        this->Address = Address; 
    }

    // Menu related services to user 
    void addItem(pair<string,double> item){
        Menu.addMenu(item);
    }
    void showMenu(){
       Menu.showMenu();
    }
    void OrderMenu(int userId){ 

        OrderInfo userOrder = Menu.OrderMenu(userId, RestaurantID);
        // apply discouunts 

        // userOrder with type of payment attached
        
        // execute the payment 

        /*
         now task is to take the payment after that handover the delivery to delivery class
         and tell him type of payment like of COD  then notification of payment made 
         after delivered 
         else before payment 
        
        */
    }







};

// payment and it's strategy 
class Payments{
    public: 
    virtual void pay(int amount) = 0; 
}; 
class UPI : public Payments{
    public: 
    void pay(int amount) override{
        cout<<"amount : "<<amount<<" payed by UPI \n";
    }
};
class CreditCard : public Payments{
    public: 
    void pay(int amount) override{
        cout<<"amount : "<<amount<<" payed by CreditCard \n";
    }
};
class CashOnDelivery : public Payments{
    public: 
    void pay(int amount) override{
        cout<<"amount : "<<amount<<" payed by Cash-On-Delivery \n";
    }
};

// notification and it's strategy 
class Notifications{
    public: 
    virtual void notify(int userId, string msg="") = 0; 
}; 
class EmailNotification : public Notifications{
    public: 
    void notify(int userId,  string msg="") override{
        cout<<"userId : "<<userId<<" notifyed by EmailNotification \n";
    }
};
class SMSNotification : public Notifications{
    public: 
    void notify(int userId,  string msg="") override{
        cout<<"userId : "<<userId<<" notifyed by SMSNotification \n";
    }
};

class DeliveryServices{
    private: 

    // store array of DeliveryPartnerAccountInfo
    // assign the them orders using proper stategy 
    //

    public:

};

// delivery and it's strategy 
class Delivery{
    public: 
    virtual void deliver(OrderInfo userOrder) = 0; 
}; 
class NearestDeliveryPartner : public Delivery{
    public: 
    void deliver(OrderInfo userOrder) override{
        cout<<"Order "<<userOrder.orderId<<" Delivered using NearestDeliveryPartner\n";
        userOrder.showOrder();
    }
};
class LeastBusyDeliveyPartner : public Delivery{
    public: 
    void deliver(OrderInfo userOrder) override{
         cout<<"Order "<<userOrder.orderId<<" Delivered using LeastBusyDeliveyPartner\n";
        userOrder.showOrder();
    }
};
class RandomDeliveryPartner : public Delivery{
    public: 
    void deliver(OrderInfo userOrder) override{
         cout<<"Order "<<userOrder.orderId<<" Delivered using RandomDeliveryPartner\n";
        userOrder.showOrder();
    }
};





// Customer Services 
class CustomerServices{

    private: 

    UserAccountInfo user;
    static int UserCount; // auto increament
    
    public: 

    CustomerServices(string name, string contactNumber, string emailId, string address){
        user = UserAccountInfo(name, contactNumber, emailId, address, UserCount++);
        greet();
    }
    void greet(){
        cout<<"Account Created Successfully\n";
    }




}; 


// Customer::customerCount=0;

int main(){







    return 0;
}