# Road Construction Scheduling System - Test Plan

## Test Case 1: Priority Scheduling Algorithm

### Input:
- Number of roads: 2
- Road 1:
  - Cities: 2 (numbered 0, 1)
  - Routes: 2
    - Route 1: 0 1 10 (city 0 to city 1, distance 10)
    - Route 2: 1 0 15 (city 1 to city 0, distance 15)
  - Start city: 0
  - End city: 1
  - Utility: 5 days
  - Traffic impact: 2 days
  - Estimated time: 10 days
  - Deadline: 15 days

- Road 2:
  - Cities: 2 (numbered 0, 1)
  - Routes: 2
    - Route 1: 0 1 20 (city 0 to city 1, distance 20)
    - Route 2: 1 0 25 (city 1 to city 0, distance 25)
  - Start city: 0
  - End city: 1
  - Utility: 3 days
  - Traffic impact: 1 day
  - Estimated time: 8 days
  - Deadline: 20 days

### Expected Output:
- Road 1: Shortest distance = 10 km
- Road 2: Shortest distance = 20 km
- Scheduling should prioritize based on utility, traffic impact, and deadlines

## Test Case 2: Banker's Algorithm

### Input:
- Number of roads: 3
- Number of resource types: 3
- Allocation Matrix:
  ```
  R0: 0 1 0
  R1: 2 0 0
  R2: 3 0 2
  ```
- Maximum Matrix:
  ```
  R0: 7 5 3
  R1: 3 2 2
  R2: 9 0 2
  ```
- Available Resources: 3 3 2

### Expected Output:
- Should find a safe sequence or determine if system is in unsafe state

## Manual Test Instructions:

1. Run the application: `bin\RoadConstruction.exe`
2. Choose option 1 for Priority Scheduling
3. Enter the test data as specified above
4. Verify the output matches expectations
5. Return to main menu and test Banker's Algorithm
6. Enter the test data for Banker's Algorithm
7. Verify the results 