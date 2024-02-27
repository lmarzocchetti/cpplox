# cpplox

## Chapter that i'm implementing -> 16

### My implementation of CLox programming language from crafting interpreters but in C++20

I'm following the book but i'm trying to convert all the C code to C++ (C++20 standard), so the implementation is really
different from the book. However the content is the same as the original C code, but with some exercise solved.
For now i've implemented these extra parts:

- OP_CONSTANT_LONG: Operation in the VM to index not 1 byte like the standard OP_CONSTANT but 3 bytes (chapter 14, num 2)
- Dynamic stack size: Implemented with a c++ standard library stack (chapter 15, num 3)
- Faster OP_NEGATE: Instaed of popping the value, negate and push. I simply took the reference of the top element and negate it (Chapter 15, num 4)

### Optimization to implement
These are some optimization that i want implement, but i'm planning to do after i can run some code:
- Run-length-encoding: for line number (Chapter 14: num 1)
- BINARY_OP C++: Get rid of the C macro for the BINARY_OP, and replace it with a constexpr std::function (only available in c++23)
