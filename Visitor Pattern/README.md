# Embedded Systems Design Patterns: Visitor Pattern Example

This repository demonstrates the **Visitor Design Pattern** in the context of **embedded systems programming** using modern C++. It shows how you can manage multiple hardware components (like motors and sensors) in a clean, extensible way.

---

## Overview

The **Visitor Pattern** allows you to separate **operations** from the **objects** they operate on. In embedded systems, you often have multiple hardware components that need similar operations, such as:

- Starting or stopping devices  
- Running diagnostics  
- Collecting status information  

Instead of putting all these operations into every hardware class, the Visitor Pattern allows you to define **visitors** that implement the operations, keeping your hardware classes **simple and maintainable**.

---

## Advantages

- **Separation of concerns**: The operation logic is outside of the hardware classes.  
- **Open/Closed Principle**: You can add new operations without modifying existing hardware classes.  
- **Scalability**: Adding new types of hardware or operations is straightforward.  
- **Maintainability**: Code is cleaner and easier to read.

---

## Disadvantages

- **Tight coupling between visitors and elements**: Every visitor needs to know all hardware types.  
- **More boilerplate**: Adding a new hardware type requires updating all visitors.  
- **Slight runtime overhead**: There is some indirection due to dynamic dispatch.

---

## Embedded Hardware Example

This example simulates a small embedded hardware system with two types of devices:

- **Motor**: Has a running status and a RPM value.  
- **Sensor**: Has an active status and a measured value.  

### Implemented Visitors

1. **HardwareRunner**: Starts all devices.  
2. **HardwareStopper**: Stops all devices.  
3. **HardwareDiagnostic**: Prints device status and metrics.

### Example Usage

```cpp
// Create a vector of hardware devices
vector<std::unique_ptr<HardwareInterface>> hardwareDevices;
hardwareDevices.push_back(std::make_unique<Motor>());
hardwareDevices.push_back(std::make_unique<Sensor>());

// Visitor for running all devices
HardwareRunner runner;

// Apply visitor to all devices
for(auto& device : hardwareDevices) {
    device->acceptVisitor(runner);
}

This approach demonstrates how new operations can be added **without modifying the Motor or Sensor classes**.

---

## How to Run

1. **Clone the repository:**
```bash
git clone https://github.com/yourusername/visitor-embedded.git
