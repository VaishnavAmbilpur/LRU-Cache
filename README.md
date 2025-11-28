# LRU Cache (C++ Implementation)

A high-performance Least Recently Used (LRU) Cache implementation in C++ using hash map and doubly linked list with **O(1)** time complexity for all operations.

## Features

- **O(1) average time** for `get(key)` and `put(key, value)`
- **Automatic eviction** of least recently used items
- **Manual memory management** with custom doubly linked list
- **Interactive menu-driven** testing interface
- **Single-file implementation** - easy to compile and run

## How It Works

- **Hash Map**: `unordered_map<int, Node*>` for O(1) lookups
- **Doubly Linked List**: Maintains usage order (MRU at head, LRU at tail)
- **Eviction**: When capacity exceeded, removes tail node

## Build & Run

```bash
g++ -std=c++17 -O2 lru_cache.cpp -o lru_cache
./lru_cache
