# 📌 Arbitrary Precision Calculator (APC)

## 📍 Overview

The **Arbitrary Precision Calculator (APC)** is a C-based project that performs arithmetic operations on integers of *unlimited length*.  
Instead of using built-in data types (`int`, `long`, `long long`), numbers are stored **digit-by-digit using a Doubly Linked List**.

### Supported Operations

| Operation | Symbol | Status |
|----------|--------|--------|
| Addition | `+` | ✔ |
| Subtraction | `-` | ✔ |
| Multiplication | `x` | ✔ |
| Division | `/` | ✔ |

### Key Features

- Handles **very large numbers**
- Supports **positive & negative values**
- Removes **leading zeros automatically**
- Performs arithmetic like manual calculation
- Uses **dynamic memory allocation**
- Clean formatted output

---

## 🧠 Data Structure Used

Numbers are stored using a **doubly linked list**:

```c
typedef struct node
{
    struct node *prev;
    int data;
    struct node *next;
} Dlist;
