Solving the traveling salesman problem with simulated annealing.
Pseudocode from Skiena's "The Algorithm Design Manual":

<code>
Create initial solution S<br/>
Initialize temperature t<br/>
repeat<br/>
    for i = 1 to iteration-length do<br/>
        Generate a random transition from S to Si<br/>
        If (C(S) ≥ C(Si)) then S = Si<br/>
        else if (e^((C(S)−C(Si))/(k·t)) > random[0, 1)) then S = Si<br/>
    Reduce temperature t<br/>
until (no change in C(S))<br/>
Return S
</code>