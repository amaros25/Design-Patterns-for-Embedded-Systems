#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <memory>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

// Forward declarations
class Motor;
class Sensor;

// Visitor interface — base class for all "Visitors"
class Visitor{
    public:
        virtual void visit(Motor& motor) = 0;   // Visit a Motor
        virtual void visit(Sensor& sensor) = 0; // Visit a Sensor
        virtual ~Visitor() = default;
};

// Abstract hardware interface
class HardwareInterface{
    public:
        virtual void acceptVisitor(Visitor& visitor) = 0; // Accept a visitor
        virtual string getHardwareName() const = 0;       // Return hardware name
        virtual void run() = 0;                           // Start hardware
        virtual void stop() = 0;                          // Stop hardware
        virtual ~HardwareInterface() = default;
};

// Concrete Motor class
class Motor: public HardwareInterface{
    private:
        bool isRunning = false;
        double rpm = 0.0;

    public:
        void acceptVisitor(Visitor& visitor) override {
            visitor.visit(*this); // Let visitor operate on this Motor
        }

        string getHardwareName()const override {
            return "Motor";
        }

        void run() override {
            isRunning = true;
            rpm = 1000.0 + (rand() % 1000); // Random RPM
        }

        void stop() override {
            isRunning = false;
            rpm = 0;
            cout << "Motor is stopped" << endl; 
        }

        bool getStatus() const { return isRunning; } // Return running status
        double getRpm() const { return rpm; }       // Return current RPM
};

// Concrete Sensor class
class Sensor: public HardwareInterface{
    private:
        bool isActive = false;
        double lastValue = 0.0;

    public:
        void acceptVisitor(Visitor& visitor){
            visitor.visit(*this); // Let visitor operate on this Sensor
        }

        string getHardwareName()const override{
            return "Sensor";
        }
 
        void run() override{
            isActive = true;
            lastValue = 20.0 + static_cast<double>(rand() % 1000) / 50; // Random value
        }

        void stop() override{
            isActive = false;
            lastValue = 0.0;
        }

        bool getStatus() const {return isActive;}
        double getValue() const { return lastValue;}
};

// Visitor 1: Run all devices
class HardwareRunner: public Visitor{
    public:
        void visit(Motor& motor){
            motor.run();
        }

        void visit(Sensor& sensor){
            sensor.run();
        }
};

// Visitor 2: Stop all devices
class HardwareStopper: public Visitor{
    public: 
        void visit(Motor& motor){
            motor.stop();
        }

        void visit(Sensor& sensor){
            sensor.stop();
        }
};

// Visitor 3: Diagnostic visitor — prints status of hardware
class HardwareDiagnostic: public Visitor{
    public:
        void visit(Motor& motor) override{
            motor.run(); 
            cout << "Hardware: " << motor.getHardwareName()
                 << ", status: " << ((motor.getStatus()) ? "Running" : "Stopped")
                 << ", current Rpm: " << motor.getRpm() << endl;
        }

        void visit(Sensor& sensor) override{
            sensor.run(); 
            cout << "Hardware: " << sensor.getHardwareName()
                 << ", status: " << ((sensor.getStatus()) ? "Running" : "Stopped")
                 << ", lastValue: " << sensor.getValue() << endl;
        }
};

int main(){
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed for rand()
    
    // Create visitors
    HardwareRunner hardwareRunner;
    HardwareStopper hardwareStopper;
    HardwareDiagnostic hardwareDiagnostic;

    // Vector of hardware devices using smart pointers
    vector<std::unique_ptr<HardwareInterface>> hardwareDevices;
    hardwareDevices.push_back(std::make_unique<Motor>());
    hardwareDevices.push_back(std::make_unique<Sensor>());

    string command;

    cout << "Available commands: start || stop || diag || exit " << endl;
    while (true){
        cin >> command ;
        if (command == "start"){
            cout << "Start Devices" << endl;
            for (auto& device: hardwareDevices){
                device->acceptVisitor(hardwareRunner); // Start each device
            }
        } else if(command == "stop"){
            cout << "Stop Devices" << endl;
            for(auto& device : hardwareDevices){
                device->acceptVisitor(hardwareStopper); // Stop each device
            }
        } else if(command == "exit"){
            cout << "Exit Program" << endl;
            break;
        } else if(command == "diag"){
           for(auto& device : hardwareDevices){
                device->acceptVisitor(hardwareDiagnostic); // Run diagnostics
            }
        } else{
            cout << "Unknown command" << endl;
        }
    }
    return 0;
}
