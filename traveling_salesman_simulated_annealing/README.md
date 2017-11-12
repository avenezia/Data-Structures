Solving the traveling salesman problem with simulated annealing.<br/>
Pseudocode from Skiena's "The Algorithm Design Manual":

```
Create initial solution S
Initialize temperature t
repeat
    for i = 1 to iteration-length do
        Generate a random transition from S to Si
        If (C(S) ≥ C(Si)) then S = Si
        else if (e^((C(S)−C(Si))/(k·t)) > random[0, 1)) then S = Si
    Reduce temperature t
until (no change in C(S))
Return S
```