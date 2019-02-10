# ILP for the TSP

## 2. Did the running time increase significantly

Yes! It takes too long to finish for 51 and 100.

## 3. Adding subtour elimination constraints

At first our raw tsp model is outputting a graph with these cycles:

```c++
{1, 6, 3, 48, 27, 7, 37, 13, 31, 24, 35, 25, 42, 28, 4, 47, 9, 5, 36, 14, 8, 20, 41, 12, 43, 19, 17, 45, 15, 16, 39, 51, 40, 44, 30, 22, 38, 21, 26, 2, 32, 23, 34}
{10, 11, 29, 46}
{18, 33, 49, 50}
```

So we add these constraints to eliminate these sets and continue doing so, finally the set of constraints are only 15, and the final TSP is:

`1, 6, 3, 29, 11, 10, 46, 4, 28, 42, 25, 47, 9, 5, 35, 24, 36, 14, 8, 20, 41, 19, 17, 45, 15, 16, 39, 51, 40, 50, 18, 33, 49, 23, 32, 2, 26, 21, 38, 22, 44, 30, 43, 12, 31, 13, 37, 7, 27, 48, 34`
