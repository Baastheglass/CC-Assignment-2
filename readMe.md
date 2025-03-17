# LLVM IR Generation with C++

## Purpose
This assignment demonstrates how to use the LLVM API in C++ to dynamically generate LLVM Intermediate Representation (IR) code. The program constructs an LLVM module, defines functions, and emits IR code that represents arithmetic operations and a basic "Hello, World!" print statement.

## How the Program Works
The program utilizes the LLVM API to:
- Create an `LLVMContext` and a `Module`.
- Use an `IRBuilder` to construct LLVM IR instructions.
- Define an arithmetic function that takes two integers and performs addition, subtraction, multiplication, and division.
- Utilize LLVM's external linkage to link to C's `printf` function for printing results.
- Create a `main` function that prints "Hello, World!" and calls the arithmetic function with constant values.
- Print the generated LLVM IR to standard output.

## Compilation and Execution Instructions
### Prerequisites
Ensure you have LLVM installed. If not, install it using:
```bash
sudo apt install llvm clang
```

### Steps
1. **Clone the repository (if applicable):**
   ```bash
   git clone <https://github.com/Baastheglass/CC-Assignment-2.git>
   cd <CC-Assignment-2>
   ```
2. **Compile the program using Makefile:**
   ```bash
   make
   ```
3. **Run the executable:**
   ```bash
   make run
   ```
4. **Clean up generated files (optional):**
   ```bash
   make clean
   ```

## Challenges and Solutions
### 1. Downloading LLVM
- Challenge: Finding the correct command to download LLVM was very time taking and difficult.
- Solution: Scoured the internet for solutions.

### 2. Function returns from Arithmetic and Printf
- Challenge: Trying to emit 4 values from the arithmetic function and using the printf functionality in LLVM.
- Solution: Defined a function signature for `printf` and used `CreateCall` to print values.

### 3. Handling Integer Division
- Challenge: Using `CreateFDiv` on integer types caused errors.
- Solution: Used `CreateSDiv` for signed integer division instead.
