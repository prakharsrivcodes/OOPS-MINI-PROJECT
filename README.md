# E-Waste Management & Recycling System

A C++ console application to register, categorize, track and manage electronic waste, and to maintain recycling records so that e-waste is disposed of responsibly.

**SDG Mapped:** SDG 12 – Responsible Consumption and Production

## Problem Statement

Improper disposal of electronic waste (old mobile phones, laptops, batteries and other devices) causes environmental pollution and health hazards. This project provides a systematic way to manage, categorize and track e-waste for safe disposal, reuse and recycling.

## Features

- Register e-waste items (Mobile, Laptop, Battery, Appliance/Other) with name and weight
- Auto-generated unique ID for every item
- Category-specific disposal advice shown on registration and search
- View all records in a formatted table
- Search an item by ID
- Update recycling status: Registered → Collected → Processing → Recycled / Reused / Disposed
- Delete a record
- Statistics: total items, total weight, and number of items recycled/reused
- Persistent storage: records are saved to and loaded from a file automatically

## Concepts Used

| Concept | Where it is used |
|---|---|
| Abstraction | `EWaste` abstract base class with pure virtual functions |
| Inheritance | `Mobile`, `Laptop`, `Battery`, `Appliance` derive from `EWaste` |
| Polymorphism | `getCategory()`, `getDisposalAdvice()`, `display()` called via base-class pointers |
| Encapsulation | Protected data members with getters/setters |
| STL | `vector<EWaste*>` to store records, `<algorithm>`, `<iomanip>`, `<sstream>` |
| File Handling | `ifstream` / `ofstream` for saving and loading records (`ewaste_records.txt`) |
| Memory Management | Virtual destructor and manual cleanup of dynamically allocated objects |

## Project Structure

```
EWasteManagementSystem/
├── main.cpp
├── README.md
└── ewaste_records.txt   (auto-generated on first save)
```

## How to Run

Requirements: a C++ compiler such as g++ (C++11 or later).

```bash
g++ main.cpp -o ewaste
./ewaste          # Windows: ewaste.exe
```

## Menu

```
1. Add New E-Waste Item
2. View All Records
3. Search Item by ID
4. Update Recycling Status
5. Show Statistics & Summary
6. Delete Record
0. Save & Exit
```

## Data File Format

Each record is stored as one line, delimited by `|`:

```
Category|ID|Name|Weight|Status
Mobile|1|Samsung S10|0.17|Registered
```

## Learning Outcomes

- Practical use of C++ OOP concepts, STL and file handling
- Understanding the importance of systematic e-waste management and recycling

## Future Scope

- Input validation for all user entries
- Hazard-based priority queue for batteries and other hazardous items
- Date tracking and recycling reports
- GUI or web front-end

## Author

Prakhar Srivastava
Namit Lakhchowra
Md Imran