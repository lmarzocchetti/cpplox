# cpplox

## Chapter that i'm implementing -> 15

### My implementation of CLox programming language from crafting interpreters but in C++20

I'm following the book but i'm trying to convert all the C code to C++ (C++20 standard), so the implementation is really
different from the book. However the content is the same as the original C code, but with some exercise solved.
For now i've implemented these extra parts:

- OP_CONSTANT_LONG: Operation in the VM to index not 1 byte like the standard OP_CONSTANT but 3 bytes (chapter 14, num 2)

### Optimization to implement
These are some optimization that i want implement, but i'm planning to do after i can run some code:
- Run-length-encoding: for line number (Chapter 14: num 1)