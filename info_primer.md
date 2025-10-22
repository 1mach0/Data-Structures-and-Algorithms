# Memory Allocation in C — A Deep Primer

C has **four main storage regions** in a running program:

```
|---------------------------|
|   Code / Text Segment     | ← your compiled machine code
|---------------------------|
|   Static / Global Memory  | ← global vars, static vars
|---------------------------|
|   Heap                    | ← malloc(), calloc(), realloc()
|---------------------------|
|   Stack                   | ← local vars, function frames
|---------------------------|
```

---

## 1. Stack Allocation

### Example:

```c
void foo() {
    int x = 10;
    char s[20] = "Hi";
}
```

### What happens:

* `x` and `s` live on the **stack**.
* They exist **only while the function is running**.
* When `foo()` returns, that memory is automatically reclaimed.

### Pros:

* Fast — compiler manages it automatically.
* No manual freeing needed.

### Cons / Errors:

* If you return a pointer to a stack variable → **dangling pointer**.
* Stack size is limited → **stack overflow** possible with deep recursion or large arrays.

### Common Mistake:

```c
int* bad() {
    int x = 10;
    return &x;   // ❌ returns address of local variable
}
```

When `bad()` exits, `x` no longer exists. Using that pointer later = **undefined behavior**.

---

## 2. Heap Allocation

### Example:

```c
int *p = malloc(5 * sizeof(int));
p[0] = 42;
free(p);
```

### What happens:

* Memory is taken from the **heap**, not tied to any function’s lifetime.
* You manage it manually.
* You must `free()` it when done.

### Pros:

* Flexible size, lifetime can exceed a function scope.

### Cons / Errors:

* Forgetting to free → **memory leak**.
* Freeing twice → **double free**.
* Using memory after freeing → **use-after-free**.
* Losing the pointer before freeing → **leak**.

### Common Mistake:

```c
int *p = malloc(10 * sizeof(int));
p = malloc(20 * sizeof(int));  // ❌ leaked the first allocation
free(p); // only frees second block
```

---

## 3. Static / Global Allocation

### Example:

```c
int counter = 0;          // global
static int internal = 42; // file-scoped static

void func() {
    static int once = 1;  // function-scoped static
}
```

### What happens:

* These live for the **entire program duration**.
* Allocated at compile time (in the **.data** or **.bss** sections).
* Automatically freed when the program ends.

### Pros:

* Persistent state without dynamic memory.

### Cons / Errors:

* Can cause bugs if state unintentionally persists between calls.
* Not thread-safe unless carefully managed.
* Can cause hidden dependencies (hard to debug in large code).

---

## 4. String Literals and Read-Only Data

### Example:

```c
char *msg = "Hello";
```

### What happens:

* `"Hello"` lives in **read-only** memory (text or rodata segment).
* `msg` points to that literal.
* You must **not modify** the contents.

### Common Error:

```c
msg[0] = 'h';  // ❌ segmentation fault
```

If you need writable strings:

```c
char msg[] = "Hello";  // ✅ stored on stack, modifiable
```

---

## 5. Dynamic Stack Allocation (since C99) — `alloca()`

### Example:

```c
#include <alloca.h>

void f(int n) {
    int *arr = alloca(n * sizeof(int));
}
```

### What happens:

* Allocates memory on the **stack**, not heap.
* Freed automatically when function exits.
* Dangerous if used in loops or with large allocations.

### Cons:

* Non-portable (not standard in older C).
* Can cause **stack overflow** if used carelessly.

---

# How Different Allocations Can Induce Errors

| Error Type                 | Where it Happens | Example                                                | Why it Happens                       |
| -------------------------- | ---------------- | ------------------------------------------------------ | ------------------------------------ |
| **Dangling pointer**       | Stack or Heap    | Return address of local variable, or use freed pointer | Memory no longer valid               |
| **Memory leak**            | Heap             | Lose pointer before freeing                            | Allocated memory unreachable         |
| **Use-after-free**         | Heap             | Access pointer after `free()`                          | Freed block reused or corrupted      |
| **Double free**            | Heap             | Free same pointer twice                                | Corrupts heap allocator state        |
| **Invalid free**           | Stack or literal | `free()` something not from `malloc`                   | Undefined behavior                   |
| **Buffer overflow**        | Stack or Heap    | Write beyond array bounds                              | Overwrites memory, potential exploit |
| **Writing string literal** | Read-only data   | `"Hello"[0] = 'h';`                                    | Segfault (read-only memory)          |

---

## 6. Sanity Rules to Avoid 95% of Bugs

1. **Initialize every pointer to `NULL`** when you declare it.
   This prevents random garbage addresses.

2. **Always `free()` everything you `malloc()`**, exactly once.

3. **Set pointer to `NULL` after freeing**, to avoid accidental reuse.

4. **Never `free()` stack or string literal memory.**

5. **Avoid returning pointers to local (stack) variables.**

6. **Use tools like `valgrind` or `AddressSanitizer`** to check for leaks or invalid memory use.

---

## 7. Visual Summary

```
|-------------------------|
| Code / Text Segment     | → compiled functions
|-------------------------|
| Read-only Data (.rodata)| → "Hello World", constants
|-------------------------|
| Static / Global (.data) | → globals, statics
|-------------------------|
| Heap                    | → malloc() / free()
|-------------------------|
| Stack                   | → function calls, locals
|-------------------------|
```


