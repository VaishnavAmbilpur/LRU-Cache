LRU Cache (C++ Implementation)

This project is a clean and minimal implementation of an LRU (Least Recently Used) Cache in C++.
It uses a hash map + doubly linked list to achieve:

O(1) average time for get(key)

O(1) average time for put(key, value)

Automatic eviction of the least recently used item when capacity is full

This version includes:

A simple menu-driven console interface

A fully self-contained single-file implementation (easy to run on any compiler)

A clear, readable C++ design with manual memory management

Features

Efficient LRU Cache using:

unordered_map for fast lookups

custom doubly-linked list for fast updates

Handles all integer keys and values

Works without any STL containers like std::list

Detects invalid cache sizes

Supports unlimited interactive operations through a menu

How It Works

The cache maintains:

A hash map

Maps key → Node*

Allows fast O(1) lookup

A doubly linked list

Most recently used node at the head

Least recently used node at the tail

Whenever a key is accessed:

It moves to the head of the list

When the cache exceeds capacity, the tail node is removed

Time Complexity
Operation	Complexity
get(key)	O(1)
put(key, value)	O(1)
Eviction	O(1)
Usage (Menu Program)

After compiling, run the program and choose:

1) Insert key/value
2) Get a key
3) Print full cache
4) Exit


Example session:

Enter cache capacity: 2

1) Put key/value
2) Get key
3) Print cache
4) Exit
Choose: 1
Key: 1
Value: 100

Choose: 3
Cache (most recent -> least recent): [1:100]

Building and Running
Compile using g++
g++ -std=c++17 lru.cpp -o lru

Run
./lru


Works on:

Linux

macOS

Windows (MinGW / WSL)

No external dependencies.
