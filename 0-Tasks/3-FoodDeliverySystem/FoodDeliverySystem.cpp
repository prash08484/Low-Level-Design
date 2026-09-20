#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <random>
#include <limits>

using namespace std;

// ============================================================
// ENUMS
// ============================================================

enum class OrderStatus {
    PLACED,
    CONFIRMED,
    PREPARING,
    OUT_FOR_DELIVERY,
    DELIVERED,
    CANCELLED
};

enum class PaymentStatus {
    PENDING,
    PAID,
    PAY_ON_DELIVERY
};

string toString(OrderStatus status) {
    switch (status) {
        case OrderStatus::PLACED:             return "PLACED";
        case OrderStatus::CONFIRMED:          return "CONFIRMED";
        case OrderStatus::PREPARING:          return "PREPARING";
        case OrderStatus::OUT_FOR_DELIVERY:   return "OUT_FOR_DELIVERY";
        case OrderStatus::DELIVERED:          return "DELIVERED";
        case OrderStatus::CANCELLED:          return "CANCELLED";
    }

    return "UNKNOWN";
}


// ============================================================
// CUSTOMER
// ============================================================

class Customer {
private:
    static int customerCount;

    int id;
    string name;
    string contactNumber;
    string email;
    string address;

public:
    Customer(
        const string& name,
        const string& contactNumber,
        const string& email,
        const string& address
    )
        : id(customerCount++),
          name(name),
          contactNumber(contactNumber),
          email(email),
          address(address) {}

    int getId() const {
        return id;
    }

    const string& getName() const {
        return name;
    }

    const string& getEmail() const {
        return email;
    }

    const string& getContactNumber() const {
        return contactNumber;
    }

    void showInfo() const {
        cout << "Customer ID   : " << id << '\n';
        cout << "Name          : " << name << '\n';
        cout << "Contact       : " << contactNumber << '\n';
        cout << "Email         : " << email << '\n';
        cout << "Address       : " << address << '\n';
    }
};

int Customer::customerCount = 1;


// ============================================================
// MENU ITEM
// ============================================================

class MenuItem {
private:
    int id;
    string name;
    double price;
    bool available;

public:
    MenuItem(int id, const string& name, double price)
        : id(id),
          name(name),
          price(price),
          available(true) {}

    int getId() const {
        return id;
    }

    const string& getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    bool isAvailable() const {
        return available;
    }

    void setAvailability(bool value) {
        available = value;
    }

    void show() const {
        cout << id << ". "
             << name
             << " - Rs. " << price
             << (available ? " [Available]" : " [Unavailable]")
             << '\n';
    }
};


// ============================================================
// RESTAURANT MENU
//
// Restaurant COMPOSES MenuItems.
// MenuItems are owned by Restaurant.
// ============================================================

class RestaurantMenu {
private:
    vector<MenuItem> items;

public:
    void addItem(const MenuItem& item) {
        items.push_back(item);
    }

    void showMenu() const {
        cout << "\n---------- MENU ----------\n";

        for (const auto& item : items) {
            item.show();
        }

        cout << "--------------------------\n";
    }

    const MenuItem* findItemById(int id) const {

        for (const auto& item : items) {
            if (item.getId() == id) {
                return &item;
            }
        }

        return nullptr;
    }
};


// ============================================================
// RESTAURANT
//
// Restaurant COMPOSES RestaurantMenu.
// ============================================================

class Restaurant {
private:
    static int restaurantCount;

    int id;
    string name;
    string address;

    // COMPOSITION
    RestaurantMenu menu;

public:
    Restaurant(
        const string& name,
        const string& address
    )
        : id(restaurantCount++),
          name(name),
          address(address) {}

    int getId() const {
        return id;
    }

    const string& getName() const {
        return name;
    }

    void addMenuItem(const MenuItem& item) {
        menu.addItem(item);
    }

    void showMenu() const {
        cout << "\nRestaurant: " << name << '\n';
        menu.showMenu();
    }

    const MenuItem* getMenuItem(int itemId) const {
        return menu.findItemById(itemId);
    }
};

int Restaurant::restaurantCount = 1;


// ============================================================
// DELIVERY PARTNER
// ============================================================

class DeliveryPartner {
private:
    int id;
    string name;
    string contactNumber;

    bool available;
    int activeOrders;

    // Lower value = closer to restaurant
    double distanceFromRestaurant;

public:
    DeliveryPartner(
        int id,
        const string& name,
        const string& contactNumber,
        double distanceFromRestaurant
    )
        : id(id),
          name(name),
          contactNumber(contactNumber),
          available(true),
          activeOrders(0),
          distanceFromRestaurant(distanceFromRestaurant) {}

    int getId() const {
        return id;
    }

    const string& getName() const {
        return name;
    }

    bool isAvailable() const {
        return available;
    }

    int getActiveOrders() const {
        return activeOrders;
    }

    double getDistanceFromRestaurant() const {
        return distanceFromRestaurant;
    }

    void assignOrder() {
        activeOrders++;
        available = false;
    }

    void completeOrder() {
        if (activeOrders > 0) {
            activeOrders--;
        }

        if (activeOrders == 0) {
            available = true;
        }
    }

    void show() const {
        cout << "Delivery Partner: "
             << name
             << " | Active orders: "
             << activeOrders
             << " | Available: "
             << (available ? "Yes" : "No")
             << '\n';
    }
};


// ============================================================
// ORDER ITEM
//
// Order COMPOSES OrderItems.
// These items belong specifically to an Order.
// ============================================================

class OrderItem {
private:
    string itemName;
    double price;
    int quantity;

public:
    OrderItem(
        const string& itemName,
        double price,
        int quantity
    )
        : itemName(itemName),
          price(price),
          quantity(quantity) {}

    double getSubtotal() const {
        return price * quantity;
    }

    void show() const {
        cout << itemName
             << " | Rs. " << price
             << " x " << quantity
             << " = Rs. " << getSubtotal()
             << '\n';
    }
};


// ============================================================
// ORDER
//
// ASSOCIATION:
// Order ---> Customer
// Order ---> Restaurant
//
// COMPOSITION:
// Order ---> OrderItems
//
// ASSOCIATION:
// Order ---> DeliveryPartner
// ============================================================

class Order {
private:
    static int orderCount;

    int id;

    // NON-OWNING references.
    // Customer and Restaurant exist independently.
    Customer& customer;
    Restaurant& restaurant;

    // COMPOSITION
    vector<OrderItem> items;

    OrderStatus status;
    PaymentStatus paymentStatus;

    double subtotal;
    double discountAmount;
    double totalAmount;

    // NON-OWNING association.
    DeliveryPartner* deliveryPartner;

    bool canTransition(OrderStatus newStatus) const {

        switch (status) {

            case OrderStatus::PLACED:
                return newStatus == OrderStatus::CONFIRMED ||
                       newStatus == OrderStatus::CANCELLED;

            case OrderStatus::CONFIRMED:
                return newStatus == OrderStatus::PREPARING ||
                       newStatus == OrderStatus::CANCELLED;

            case OrderStatus::PREPARING:
                return newStatus == OrderStatus::OUT_FOR_DELIVERY;

            case OrderStatus::OUT_FOR_DELIVERY:
                return newStatus == OrderStatus::DELIVERED;

            case OrderStatus::DELIVERED:
                return false;

            case OrderStatus::CANCELLED:
                return false;
        }

        return false;
    }

public:

    Order(Customer& customer, Restaurant& restaurant)
        : id(orderCount++),
          customer(customer),
          restaurant(restaurant),
          status(OrderStatus::PLACED),
          paymentStatus(PaymentStatus::PENDING),
          subtotal(0),
          discountAmount(0),
          totalAmount(0),
          deliveryPartner(nullptr) {}

    int getId() const {
        return id;
    }

    Customer& getCustomer() const {
        return customer;
    }

    Restaurant& getRestaurant() const {
        return restaurant;
    }

    OrderStatus getStatus() const {
        return status;
    }

    PaymentStatus getPaymentStatus() const {
        return paymentStatus;
    }

    double getSubtotal() const {
        return subtotal;
    }

    double getDiscount() const {
        return discountAmount;
    }

    double getTotalAmount() const {
        return totalAmount;
    }

    DeliveryPartner* getDeliveryPartner() const {
        return deliveryPartner;
    }

    void addItem(const MenuItem& item, int quantity) {

        if (!item.isAvailable()) {
            cout << item.getName()
                 << " is currently unavailable.\n";
            return;
        }

        if (quantity <= 0) {
            cout << "Invalid quantity.\n";
            return;
        }

        /*
            IMPORTANT:

            We don't store MenuItem& here.

            We copy the required information into OrderItem.

            Why?

            Because an OrderItem represents what was ordered
            at the time of purchase.

            If restaurant later changes the menu price,
            old order should still retain its original price.
        */

        items.emplace_back(
            item.getName(),
            item.getPrice(),
            quantity
        );

        subtotal += item.getPrice() * quantity;
        totalAmount = subtotal - discountAmount;
    }

    void applyDiscount(double amount) {

        discountAmount = min(amount, subtotal);

        totalAmount = subtotal - discountAmount;
    }

    void markPaymentPaid() {
        paymentStatus = PaymentStatus::PAID;
    }

    void markCashOnDelivery() {
        paymentStatus = PaymentStatus::PAY_ON_DELIVERY;
    }

    bool updateStatus(OrderStatus newStatus) {

        if (!canTransition(newStatus)) {
            cout << "Invalid status transition: "
                 << toString(status)
                 << " -> "
                 << toString(newStatus)
                 << '\n';

            return false;
        }

        status = newStatus;
        return true;
    }

    void assignDeliveryPartner(DeliveryPartner* partner) {
        deliveryPartner = partner;
    }

    void showOrder() const {

        cout << "\n====================================\n";
        cout << "Order ID       : " << id << '\n';
        cout << "Customer      : " << customer.getName() << '\n';
        cout << "Restaurant    : " << restaurant.getName() << '\n';
        cout << "Status        : " << toString(status) << '\n';

        cout << "\nItems:\n";

        for (const auto& item : items) {
            item.show();
        }

        cout << "\nSubtotal      : Rs. " << subtotal << '\n';
        cout << "Discount      : Rs. " << discountAmount << '\n';
        cout << "Total         : Rs. " << totalAmount << '\n';

        cout << "Payment       : ";

        if (paymentStatus == PaymentStatus::PAID)
            cout << "PAID\n";
        else if (paymentStatus == PaymentStatus::PAY_ON_DELIVERY)
            cout << "CASH ON DELIVERY\n";
        else
            cout << "PENDING\n";

        if (deliveryPartner != nullptr) {
            cout << "Delivery      : "
                 << deliveryPartner->getName()
                 << '\n';
        }

        cout << "====================================\n";
    }
};

int Order::orderCount = 1;


// ============================================================
// PAYMENT ABSTRACTION
//
// POLYMORPHISM
//
// PaymentMethod
//       |
//       +---- UPI
//       +---- CreditCard
//       +---- CashOnDelivery
// ============================================================

class PaymentMethod {
public:
    virtual bool pay(double amount) = 0;

    virtual string getName() const = 0;

    virtual ~PaymentMethod() = default;
};


class UPI : public PaymentMethod {
public:

    bool pay(double amount) override {

        cout << "\nRs. " << amount
             << " paid using UPI.\n";

        return true;
    }

    string getName() const override {
        return "UPI";
    }
};


class CreditCard : public PaymentMethod {
public:

    bool pay(double amount) override {

        cout << "\nRs. " << amount
             << " paid using Credit Card.\n";

        return true;
    }

    string getName() const override {
        return "Credit Card";
    }
};


class CashOnDelivery : public PaymentMethod {
public:

    bool pay(double amount) override {

        cout << "\nRs. " << amount
             << " will be collected using Cash on Delivery.\n";

        return true;
    }

    string getName() const override {
        return "Cash On Delivery";
    }
};


// ============================================================
// DISCOUNT ABSTRACTION
//
// Strategy Pattern
// ============================================================

class DiscountStrategy {
public:
    virtual double calculateDiscount(double amount) const = 0;

    virtual string getName() const = 0;

    virtual ~DiscountStrategy() = default;
};


class PercentageDiscount : public DiscountStrategy {
private:
    double percentage;

public:

    explicit PercentageDiscount(double percentage)
        : percentage(percentage) {}

    double calculateDiscount(double amount) const override {

        return amount * percentage / 100.0;
    }

    string getName() const override {
        return to_string(static_cast<int>(percentage))
               + "% Discount";
    }
};


class FlatDiscount : public DiscountStrategy {
private:
    double amount;

public:

    explicit FlatDiscount(double amount)
        : amount(amount) {}

    double calculateDiscount(double total) const override {

        return min(amount, total);
    }

    string getName() const override {
        return "Flat Discount";
    }
};


// ============================================================
// NOTIFICATION ABSTRACTION
//
// POLYMORPHISM
// ============================================================

class Notification {
public:
    virtual void notify(
        const Customer& customer,
        const string& message
    ) = 0;

    virtual ~Notification() = default;
};


class EmailNotification : public Notification {
public:

    void notify(
        const Customer& customer,
        const string& message
    ) override {

        cout << "[EMAIL] "
             << customer.getEmail()
             << " -> "
             << message
             << '\n';
    }
};


class SMSNotification : public Notification {
public:

    void notify(
        const Customer& customer,
        const string& message
    ) override {

        cout << "[SMS] "
             << customer.getContactNumber()
             << " -> "
             << message
             << '\n';
    }
};


// ============================================================
// DELIVERY ASSIGNMENT STRATEGY
//
// Strategy Pattern
//
// DeliveryAssignmentStrategy
//           |
//           +---- Nearest
//           +---- LeastBusy
//           +---- Random
// ============================================================

class DeliveryAssignmentStrategy {
public:

    virtual DeliveryPartner* assign(
        const Order& order,
        const vector<DeliveryPartner*>& partners
    ) = 0;

    virtual ~DeliveryAssignmentStrategy() = default;
};


// ------------------------------------------------------------
// Nearest Strategy
// ------------------------------------------------------------

class NearestDeliveryPartnerStrategy
    : public DeliveryAssignmentStrategy {

public:

    DeliveryPartner* assign(
        const Order&,
        const vector<DeliveryPartner*>& partners
    ) override {

        DeliveryPartner* selected = nullptr;

        for (auto* partner : partners) {

            if (!partner->isAvailable())
                continue;

            if (selected == nullptr ||
                partner->getDistanceFromRestaurant()
                <
                selected->getDistanceFromRestaurant()) {

                selected = partner;
            }
        }

        return selected;
    }
};


// ------------------------------------------------------------
// Least Busy Strategy
// ------------------------------------------------------------

class LeastBusyDeliveryPartnerStrategy
    : public DeliveryAssignmentStrategy {

public:

    DeliveryPartner* assign(
        const Order&,
        const vector<DeliveryPartner*>& partners
    ) override {

        DeliveryPartner* selected = nullptr;

        for (auto* partner : partners) {

            if (!partner->isAvailable())
                continue;

            if (selected == nullptr ||
                partner->getActiveOrders()
                <
                selected->getActiveOrders()) {

                selected = partner;
            }
        }

        return selected;
    }
};


// ------------------------------------------------------------
// Random Strategy
// ------------------------------------------------------------

class RandomDeliveryPartnerStrategy
    : public DeliveryAssignmentStrategy {

public:

    DeliveryPartner* assign(
        const Order&,
        const vector<DeliveryPartner*>& partners
    ) override {

        vector<DeliveryPartner*> availablePartners;

        for (auto* partner : partners) {

            if (partner->isAvailable()) {
                availablePartners.push_back(partner);
            }
        }

        if (availablePartners.empty()) {
            return nullptr;
        }

        random_device rd;
        mt19937 gen(rd());

        shuffle(
            availablePartners.begin(),
            availablePartners.end(),
            gen
        );

        return availablePartners[0];
    }
};


// ============================================================
// PAYMENT SERVICE
//
// PaymentService does NOT OWN PaymentMethod.
//
// It only USES it.
//
// Therefore:
// PaymentService ---> PaymentMethod
//
// Dependency / Association
// ============================================================

class PaymentService {
public:

    bool processPayment(
        Order& order,
        PaymentMethod& paymentMethod
    ) {

        cout << "\nProcessing payment using "
             << paymentMethod.getName()
             << "...\n";

        bool success =
            paymentMethod.pay(order.getTotalAmount());

        if (!success) {
            cout << "Payment failed.\n";
            return false;
        }

        if (paymentMethod.getName() == "Cash On Delivery") {
            order.markCashOnDelivery();
        }
        else {
            order.markPaymentPaid();
        }

        return true;
    }
};


// ============================================================
// NOTIFICATION SERVICE
//
// NotificationService does NOT own notification channels.
//
// It merely uses them.
//
// ============================================================

class NotificationService {
private:
    vector<Notification*> channels;

public:

    void addChannel(Notification& channel) {
        channels.push_back(&channel);
    }

    void notifyCustomer(
        const Customer& customer,
        const string& message
    ) {

        for (auto* channel : channels) {
            channel->notify(customer, message);
        }
    }
};


// ============================================================
// DELIVERY SERVICE
//
// DeliveryService uses:
//   1. DeliveryAssignmentStrategy
//   2. DeliveryPartner objects
//
// It does not own either of them.
// ============================================================

class DeliveryService {
private:

    DeliveryAssignmentStrategy& strategy;

    // Non-owning pointers.
    vector<DeliveryPartner*> partners;

public:

    explicit DeliveryService(
        DeliveryAssignmentStrategy& strategy
    )
        : strategy(strategy) {}

    void addPartner(DeliveryPartner& partner) {
        partners.push_back(&partner);
    }

    bool assignDeliveryPartner(Order& order) {

        DeliveryPartner* selected =
            strategy.assign(order, partners);

        if (selected == nullptr) {

            cout << "No delivery partner available.\n";
            return false;
        }

        selected->assignOrder();

        order.assignDeliveryPartner(selected);

        cout << "\nDelivery partner assigned: "
             << selected->getName()
             << '\n';

        return true;
    }

    bool startDelivery(Order& order) {

        if (order.getDeliveryPartner() == nullptr) {

            cout << "No delivery partner assigned.\n";
            return false;
        }

        if (!order.updateStatus(OrderStatus::OUT_FOR_DELIVERY)) {
            return false;
        }

        cout << "Order " << order.getId()
             << " is now OUT_FOR_DELIVERY.\n";

        return true;
    }

    bool completeDelivery(Order& order) {

        if (!order.updateStatus(OrderStatus::DELIVERED)) {
            return false;
        }

        DeliveryPartner* partner =
            order.getDeliveryPartner();

        if (partner != nullptr) {
            partner->completeOrder();
        }

        cout << "Order "
             << order.getId()
             << " delivered successfully.\n";

        return true;
    }
};


// ============================================================
// ORDER SERVICE
//
// This class coordinates the workflow.
//
// It OWNS Orders using unique_ptr.
//
// It USES Customer, Restaurant, PaymentService,
// DiscountStrategy and NotificationService.
//
// ============================================================

class OrderService {
private:

    vector<unique_ptr<Order>> orders;

    PaymentService& paymentService;
    NotificationService& notificationService;

public:

    OrderService(
        PaymentService& paymentService,
        NotificationService& notificationService
    )
        : paymentService(paymentService),
          notificationService(notificationService) {}

    Order& placeOrder(
        Customer& customer,
        Restaurant& restaurant,
        const vector<pair<int, int>>& requestedItems,
        PaymentMethod& paymentMethod,
        DiscountStrategy& discountStrategy
    ) {

        // Create Order.
        auto order =
            make_unique<Order>(customer, restaurant);

        // ----------------------------------------------------
        // Add requested menu items
        // ----------------------------------------------------

        for (const auto& [itemId, quantity] : requestedItems) {

            const MenuItem* menuItem =
                restaurant.getMenuItem(itemId);

            if (menuItem == nullptr) {

                cout << "Menu item "
                     << itemId
                     << " does not exist.\n";

                continue;
            }

            order->addItem(*menuItem, quantity);
        }

        // ----------------------------------------------------
        // Apply discount
        // ----------------------------------------------------

        double discount =
            discountStrategy.calculateDiscount(
                order->getSubtotal()
            );

        order->applyDiscount(discount);

        cout << "\nApplied discount: "
             << discountStrategy.getName()
             << '\n';

        // ----------------------------------------------------
        // Store order
        //
        // OrderService owns the Order.
        // ----------------------------------------------------

        orders.push_back(move(order));

        Order& createdOrder = *orders.back();

        // ----------------------------------------------------
        // Notify order placed
        // ----------------------------------------------------

        notificationService.notifyCustomer(
            customer,
            "Order #" +
            to_string(createdOrder.getId()) +
            " has been placed."
        );

        // ----------------------------------------------------
        // Payment
        // ----------------------------------------------------

        if (!paymentService.processPayment(
                createdOrder,
                paymentMethod)) {

            return createdOrder;
        }

        notificationService.notifyCustomer(
            customer,
            "Payment processed for Order #" +
            to_string(createdOrder.getId())
        );

        // ----------------------------------------------------
        // Confirm Order
        // ----------------------------------------------------

        createdOrder.updateStatus(
            OrderStatus::CONFIRMED
        );

        notificationService.notifyCustomer(
            customer,
            "Order #" +
            to_string(createdOrder.getId()) +
            " has been confirmed."
        );

        return createdOrder;
    }

    void startPreparing(Order& order) {

        if (order.updateStatus(OrderStatus::PREPARING)) {

            notificationService.notifyCustomer(
                order.getCustomer(),
                "Order #" +
                to_string(order.getId()) +
                " is being prepared."
            );
        }
    }

    void cancelOrder(Order& order) {

        if (order.updateStatus(OrderStatus::CANCELLED)) {

            notificationService.notifyCustomer(
                order.getCustomer(),
                "Order #" +
                to_string(order.getId()) +
                " has been cancelled."
            );
        }
    }
};


// ============================================================
// MAIN
//
// This is where objects are CREATED and WIRED together.
//
// This is dependency injection / object wiring.
//
// ============================================================

int main() {

    // ========================================================
    // 1. CREATE CUSTOMER
    // ========================================================

    Customer customer(
        "Prashant",
        "9876543210",
        "prashant@gmail.com",
        "NIT Patna"
    );


    // ========================================================
    // 2. CREATE RESTAURANT
    // ========================================================

    Restaurant restaurant(
        "FoodHub",
        "Patna"
    );


    // Restaurant COMPOSES MenuItems
    restaurant.addMenuItem(
        MenuItem(1, "Burger", 150)
    );

    restaurant.addMenuItem(
        MenuItem(2, "Pizza", 300)
    );

    restaurant.addMenuItem(
        MenuItem(3, "Coke", 50)
    );


    restaurant.showMenu();


    // ========================================================
    // 3. CREATE DELIVERY PARTNERS
    // ========================================================

    DeliveryPartner p1(
        1,
        "Rahul",
        "9000000001",
        2.5
    );

    DeliveryPartner p2(
        2,
        "Amit",
        "9000000002",
        5.0
    );

    DeliveryPartner p3(
        3,
        "Rohit",
        "9000000003",
        1.5
    );


    // ========================================================
    // 4. CREATE PAYMENT METHOD
    // ========================================================

    UPI upi;
    CreditCard card;
    CashOnDelivery cod;


    // ========================================================
    // 5. CREATE DISCOUNT STRATEGY
    // ========================================================

    PercentageDiscount discount10(10);


    // ========================================================
    // 6. CREATE NOTIFICATION CHANNELS
    // ========================================================

    EmailNotification email;
    SMSNotification sms;


    // ========================================================
    // 7. NOTIFICATION SERVICE
    //
    // NotificationService USES email and sms.
    // It doesn't own them.
    // ========================================================

    NotificationService notificationService;

    notificationService.addChannel(email);
    notificationService.addChannel(sms);


    // ========================================================
    // 8. PAYMENT SERVICE
    // ========================================================

    PaymentService paymentService;


    // ========================================================
    // 9. CHOOSE DELIVERY STRATEGY
    //
    // We can easily replace this with:
    //
    // LeastBusyDeliveryPartnerStrategy
    // RandomDeliveryPartnerStrategy
    // ========================================================

    NearestDeliveryPartnerStrategy nearestStrategy;

    DeliveryService deliveryService(nearestStrategy);

    deliveryService.addPartner(p1);
    deliveryService.addPartner(p2);
    deliveryService.addPartner(p3);


    // ========================================================
    // 10. ORDER SERVICE
    //
    // It USES PaymentService and NotificationService.
    // ========================================================

    OrderService orderService(
        paymentService,
        notificationService
    );


    // ========================================================
    // 11. CUSTOMER PLACES ORDER
    //
    // Burger x2
    // Pizza x1
    // ========================================================

    vector<pair<int, int>> requestedItems = {
        {1, 2},   // Burger x2
        {2, 1}    // Pizza x1
    };


    Order& order = orderService.placeOrder(
        customer,
        restaurant,
        requestedItems,
        upi,
        discount10
    );


    order.showOrder();


    // ========================================================
    // 12. ORDER PREPARATION
    // ========================================================

    orderService.startPreparing(order);

    order.showOrder();


    // ========================================================
    // 13. ASSIGN DELIVERY PARTNER
    // ========================================================

    deliveryService.assignDeliveryPartner(order);


    // ========================================================
    // 14. START DELIVERY
    // ========================================================

    deliveryService.startDelivery(order);

    notificationService.notifyCustomer(
        customer,
        "Order #" +
        to_string(order.getId()) +
        " is out for delivery."
    );


    // ========================================================
    // 15. COMPLETE DELIVERY
    // ========================================================

    deliveryService.completeDelivery(order);

    notificationService.notifyCustomer(
        customer,
        "Order #" +
        to_string(order.getId()) +
        " has been delivered."
    );


    // ========================================================
    // FINAL ORDER
    // ========================================================

    order.showOrder();


    return 0;
}