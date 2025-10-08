# Variant-Type 🛠️

This project implements a custom `Variant` class in C++, capable of holding `int`, `float`, or `string` values with dynamic type tracking. The class supports:

- 🔹 Constructors for each type  
- 🔹 Assignment operators  
- 🔹 Getters with optional-based safe type conversion  
- 🔹 Arithmetic and comparison operators with implicit type conversion  
- 🔹 Stream output via `operator<<` 📤  

## Deliverables 📂

1. `Variant.h` and `Variant.cpp` implementing the class  
2. 🧪 Test suite verifying all functionality  
3. 👀 Code review of a peer's submission  

## Key Features ✨

- 🛡️ Type-safe container with `enum` type tracking  
- 🔄 Supports implicit conversion between types  
- ➕➖✖️➗ Full operator overloads: +, -, *, /, ==, !=, <, <=, >, >=  
- 📤 Streamable output for easy debugging  
- ✅ Optional-based getters to prevent invalid access  

## Instructions 📝

- 📂 All code is in the `Source/` directory  
- 🧪 Tests implemented using `Testable` or Google `gtest`  

## License 📝

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
