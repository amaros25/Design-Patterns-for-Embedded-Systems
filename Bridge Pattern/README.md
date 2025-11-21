# Bridge Pattern with Embedded Example

This repository demonstrates the **Bridge Design Pattern** applied to an **embedded system motor control architecture**.  
The goal is to separate *what* a `Motor` does from *how* it is controlled (PWM, UART, CAN).

This separation makes the system flexible, testable, and hardware-independent.

---

## Why Bridge Pattern?

The **Bridge Pattern** decouples an abstraction (`Motor`) from its implementation (`MotorController`).  
This allows both sides to develop and change **independently**.

In embedded development, this is extremely useful because:

- You may need to support **different motor driver chips**  
- You may switch communication interfaces later (PWM → CAN → UART)  
- You can simulate or mock hardware easily in testing  
- Your application logic becomes **independent from the hardware layer**

---

## Concept Overview

### Abstraction
`Motor`  
- Represents the high-level motor behavior  
- Calls `start_motor()`, `stop_motor()`, and `set_speed()`  

### Implementor
`MotorController` (interface)
- Defines how the motor is controlled at low-level  
- Does *not* know anything about the Motor class  

### Concrete Implementors
Different communication bus implementations:

| Motor Controller Type | Typical Hardware | Description |
|-----------------------|------------------|-------------|
| **PWM**               | MOSFET drivers, H-bridges (e.g. L298N, DRV8833) | Simple analog-like motor control via duty cycle |
| **UART**              | Smart motor drivers (e.g. TMC2209, BLDC ESCs) | Digital protocol, set speed via serial commands |
| **CAN**               | Automotive ECUs, BLDC CAN ESCs, industrial controllers | Robust multi-node communication bus |

Each controller implements the same interface but performs different low-level actions.

---

##  Advantages in Embedded Development
### ✔ 1. Hardware Independence

Your application doesn't care whether the motor uses PWM, CAN, or UART.

You can switch hardware drivers without touching the core logic.

### ✔ 2. Easier Porting

Moving from an STM32 to ESP32 or a different motor driver chip becomes easier:
only the low-level controller class changes.

### ✔ 3. Great for Unit Testing

You can replace real controllers with a MockMotorController.
### ✔ 4. Cleaner Architecture

No if (CAN) { ... } else if (UART) { ... } inside your Motor class.
No mixing of business logic and hardware details.

### ✔ 5. Scalable for Future Extensions

Add new motor communication types by simply creating another class:
 
