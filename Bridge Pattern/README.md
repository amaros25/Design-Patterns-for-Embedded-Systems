# Bridge Pattern with Embedded Example

This repository demonstrates the **Bridge Design Pattern** applied to an **embedded system motor control architecture**.  
The goal is to separate *what* a `Motor` does from *how* it is controlled (PWM, UART, CAN).

This separation makes the system flexible, testable, and hardware-independent.

---

## 🚀 Why Bridge Pattern?

The **Bridge Pattern** decouples an abstraction (`Motor`) from its implementation (`MotorController`).  
This allows both sides to develop and change **independently**.

In embedded development, this is extremely useful because:

- You may need to support **different motor driver chips**  
- You may switch communication interfaces later (PWM → CAN → UART)  
- You can simulate or mock hardware easily in testing  
- Your application logic becomes **independent from the hardware layer**

---

## 📘 Concept Overview

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