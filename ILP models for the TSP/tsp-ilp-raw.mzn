int: n;
array[1..n, 1..n] of float: c;
array[1..n, 1..n] of var 0..1: x;

constraint forall(i, j in 1..n) (x[i, j] = x[j, i]);

constraint forall(i in 1..n) (
    sum(j in 1..n where j != i) (x[i, j]) = 2
);

var float: cost = sum(i, j in 1..n) (c[i, j] * x[i, j]) / 2;

solve minimize cost;

output ["\(n)\n"] ++ 
    [show(x[i, j]) ++
        if j = n then "\n" else " " endif
    | i, j in 1..n] 
    ++ ["cost: \(cost)"];
% output to be used in cycles.cpp