#  Emergency Travel Planning System using Adjacency Lists and BFS/DFS Algorithms
The Emergency Travel Plan project simulates a scenario where a traveler needs to navigate through cities using both road and aerial routes. The system optimizes routes based on either speed or cost, providing insights into the minimum days required for travel.

# Features
- Graph Representation: Shows cities and routes in an adjacency list format.
- Optimization Strategies: Allows users to choose between optimizing for speed (shortest path) or cost (least cost).
* Path Visualization: Displays the path taken by the traveler through various cities.
- Interactive Menu: Provides a user-friendly interface to select optimization strategies and view results.

# Dependencies
C++ standard libraries 
- iostream
- iomanip
- cmath

# Algorithm
#### - Graph Representation:
Cities and routes are represented using adjacency lists.
#### - Breadth-First Search (BFS): 
Used to find the shortest path in terms of days, either optimizing for speed (shortest path) or cost (least cost).
#### - Dynamic Memory Management: 
Handles memory allocation and deallocation for nodes and arrays.
#### - User Interaction: 
Offers an interactive menu for users to choose between speed or cost optimization.

# Implementation
- City_Node: Represents each city with road routes and an optional aerial route.
- Travel_Node: Represents individual routes with destination city, cost, and linkage to next routes.
- Traveler_Controller: Manages the overall travel logic, including initialization, pathfinding, and optimization strategies.
- Main Program: Drives the program flow, taking input for multiple test cases, initializing routes, and displaying results.

# How to Use
- Input: Enter the number of cities and aerial routes for each test case.
- Aerial Routes: Specify source and destination pairs for aerial connections.
- Optimization: Choose between speed or cost optimization.
- Output: View the minimum days required for travel based on the chosen strategy and the path taken.#
