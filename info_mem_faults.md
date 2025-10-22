# **Memory Faults in C — The Underlying Mechanism**

---

## **1. What a “fault” means in OS terms**

At the CPU/OS level, a **fault** is an *exception* triggered when your program tries to do something illegal with memory — for example:

* access memory it doesn’t own,
* write to read-only memory,
* dereference a null or dangling pointer,
* jump to a non-executable region.

The OS then raises a **signal** to your process (`SIGSEGV`, `SIGBUS`, etc.).
If unhandled, your program **crashes**.

So every “segmentation fault” or “bus error” you’ve seen is the OS saying:

> “You touched memory that’s not yours.”

---

# **2. Major Fault Types and Their Root Causes**

We’ll go through the most common classes of faults and show you how they arise, what causes them, and what *good code* vs *bad code* looks like.

---

## **A. Segmentation Fault (`SIGSEGV`)**

### **What it is**

You tried to access an invalid or protected memory address.

The OS divides memory into pages and marks them readable/writable/executable.
If you touch a page your process doesn’t own, you segfault.

---

### **Common causes**

#### 1. Dereferencing a `NULL` or uninitialized pointer

```c
int *p;
*p = 5;  // ❌ p points nowhere
```

`p` contains garbage or `NULL`, so dereferencing it triggers a fault.

**Fix:**

```c
int x = 5;
int *p = &x;
*p = 10; // ✅
```

Always initialize pointers before use.

---

#### 2. Writing to read-only memory

```c
char *s = "Hello";
s[0] = 'h';  // ❌ segmentation fault
```

String literals are read-only.

**Fix:**

```c
char s[] = "Hello";  // ✅ writable array
s[0] = 'h';
```

---

#### 3. Accessing freed memory (use-after-free)

```c
int *p = malloc(sizeof(int));
free(p);
*p = 10;  // ❌ accessing freed memory
```

**Fix:**

```c
free(p);
p = NULL;  // ✅ mark it invalid
```

---

#### 4. Array out-of-bounds access

```c
int arr[3] = {1, 2, 3};
printf("%d", arr[5]);  // ❌ invalid index
```

This might crash, or worse — silently corrupt memory.

**Fix:**
Always stay within `[0, n-1]` bounds.

---

#### 5. Returning pointer to local variable

```c
int* bad() {
    int x = 10;
    return &x;  // ❌ stack frame destroyed after return
}
```

**Fix:**
Use `malloc` if you need persistence:

```c
int* good() {
    int *p = malloc(sizeof(int));
    *p = 10;
    return p;  // ✅ valid until freed
}
```

---

## **B. Bus Error**

### **What it is**

The CPU detects **misaligned memory access** or attempts to access a physically invalid address.

---

### **Typical cause:**

```c
char buf[5];
int *p = (int*)buf;
*p = 42;  // ❌ alignment issue on some architectures
```

Fix: always ensure correct alignment when casting pointers or working with raw buffers.

---

## **C. Stack Overflow**

### **What it is**

You used up too much stack memory (e.g., deep recursion or large local arrays).

### **Example**

```c
void recurse() {
    int arr[1000000];  // ❌ huge local array
    recurse();
}
```

Each call adds another 4MB+ to the stack — eventually it overflows.

**Fix:**
Use heap for large allocations:

```c
void recurse() {
    int *arr = malloc(1000000 * sizeof(int));  // ✅
    recurse();
    free(arr);
}
```

---

## **D. Double Free / Invalid Free**

### **What it is**

You call `free()` twice on the same pointer, or on a non-heap pointer.

### **Example**

```c
int *p = malloc(10 * sizeof(int));
free(p);
free(p);  // ❌ double free
```

or

```c
int x;
int *p = &x;
free(p);  // ❌ invalid free (not heap memory)
```

**Fix:**
Set pointers to `NULL` after freeing; only free heap allocations.

---

## **E. Memory Leak**

### **What it is**

You allocated memory but lost the pointer to it (so it can never be freed).

### **Example**

```c
char *s = malloc(10);
s = "hi";  // ❌ leak — old heap memory lost
```

**Fix:**

```c
char *s = malloc(10);
strcpy(s, "hi");  // ✅ copy instead of reassign
free(s);
```

---

# **3. Good Code vs Bad Code — Mental Rules**

| Concept         | Bad Code                               | Good Code                  | Reason                                   |
| --------------- | -------------------------------------- | -------------------------- | ---------------------------------------- |
| Pointer init    | `int *p; *p = 5;`                      | `int x=5; int *p=&x;`      | Never dereference uninitialized pointers |
| Dynamic alloc   | `p = malloc(...); p = something_else;` | Free before reassign       | Prevent memory leaks                     |
| String handling | `char *s="hi"; s[0]='H';`              | `char s[]="hi"; s[0]='H';` | Literals are read-only                   |
| Freeing         | `free(p); free(p);`                    | `free(p); p=NULL;`         | Avoid double free                        |
| Function return | `return &x;`                           | `return malloc(...);`      | Never return stack addresses             |
| Large arrays    | `int a[1000000];`                      | `int *a=malloc(...);`      | Avoid stack overflow                     |

---

# **4. General Mental Model**

When you write C, think like this:

> Every byte of memory belongs to *someone* — the OS, the heap allocator, or the stack frame.
> If you touch memory that’s not yours, or forget to give it back, you break the contract.

So:

* The **compiler** doesn’t protect you.
* The **OS** will terminate you.
* The **allocator** will silently leak or corrupt your heap.
* Only *you* track ownership.

That’s why experienced C programmers think in terms of:

* Who owns this memory?
* Who frees it?
* When does it die?
* What happens if this pointer changes?

---

# **5. Tools to Catch Faults Early**

1. **Valgrind** — detects leaks, invalid reads/writes, use-after-free.

   ```
   valgrind ./your_program
   ```

2. **AddressSanitizer (ASan)** — runtime memory checker, can be used with GCC/Clang:

   ```
   gcc -fsanitize=address -g your.c -o your
   ./your
   ```

3. **GDB** — debugger for tracing segfaults:

   ```
   gdb ./your
   run
   backtrace
   ```

These tools will *literally tell you* what address was touched, why it failed, and which line caused it.

---

# **6. TL;DR Mental Model**

| Fault              | Typical Cause                      | Prevention                              |
| ------------------ | ---------------------------------- | --------------------------------------- |
| Segmentation fault | Invalid/dangling pointer           | Always initialize; never use after free |
| Bus error          | Misaligned or illegal address      | Avoid unsafe casts; align buffers       |
| Stack overflow     | Too much recursion or large locals | Use heap for big data                   |
| Double free        | Freeing same pointer twice         | Nullify after free                      |
| Memory leak        | Losing reference to heap           | Free all allocations                    |
| Buffer overflow    | Writing past array bounds          | Always check indices                    |
