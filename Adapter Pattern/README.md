# Adapter Pattern in Modern C++

This repository demonstrates the Adapter Design Pattern in C++ using modern C++ features such as std::unique_ptr and make_unique.

## What is the Adapter Pattern?

The Adapter Pattern is a structural design pattern that allows incompatible interfaces to work together.
It acts like a bridge, letting code that expects one interface work with another without modifying the original classes.

Use cases:

- Integrating legacy code

- Wrapping third-party libraries

- Working with hardware interfaces (e.g., embedded systems)

## Example in this Repository

We have two display classes:

- ```LCD_Display``` – an LCD screen

- ```OLED_Display``` – an OLED screen

Both have ```init()``` and ```display()``` methods but do not share a common interface.

We define an abstract interface ```Display```:
```cpp
class Display {
public:
    virtual void init() noexcept = 0;
    virtual void display(const std::string& text) noexcept = 0;
    virtual ~Display() = default;
};
```
## Adapters

```DisplayLcdAdapter``` wraps ```LCD_Display```

```DisplayOledAdapter``` wraps ```OLED_Display```

This allows us to treat both displays uniformly via ```Display*``` or ```unique_ptr<Display>```.

```cpp
auto display1 = std::make_unique<DisplayLcdAdapter>(std::make_unique<LCD_Display>());
auto display2 = std::make_unique<DisplayOledAdapter>(std::make_unique<OLED_Display>());

display1->init();
display2->init();

display1->display("Text 1");
display2->display("Text 2");
```
Output:

```cpp
init lcd
init oled
display lcd: Text 1
display oled: Text 2
```
## Features Demonstrated

- Modern C++ (unique_ptr, make_unique, move semantics)

- Adapter Pattern to unify incompatible interfaces

- Polymorphism with abstract base classes

- Extensible design for additional display types

## Why Use the Adapter Pattern?

- Integrates legacy or third-party code without modification

- Provides a uniform interface to diverse implementations

- Makes code maintainable and extensible

## Diagram

``` lua

        +-----------------+
        |    Display      | <---- client code
        +-----------------+
          ^           ^
          |           |
  +----------------+  +----------------+
  | LCD Adapter    |  | OLED Adapter   | <-- adapters wrap legacy classes
  +----------------+  +----------------+
          |                 |
   +--------------+   +--------------+
   | LCD_Display  |   | OLED_Display |
   +--------------+   +--------------+

```

- Client code uses Display interface

- Adapters translate calls to legacy classes (LCD_Display, OLED_Display)