int: n;
array[1..n, 1..n] of float: c;
array[1..n, 1..n] of var 0..1: x;
array[1..n] of var 1..n: u;

constraint forall(i in 1..n) (
    sum(j in 1..n where j != i) (x[i, j]) = 1
);

constraint forall(i in 1..n) (
    sum(j in 1..n where j != i) (x[j, i]) = 1
);

constraint u[1] = 1;
constraint forall(i in 2..n) (1 < u[i]);
constraint forall(i, j in 2..n where i != j) (
    u[i] - u[j] + (n * x[i, j]) <= n - 1
);

var float: cost = sum(i, j in 1..n) (c[i, j] * x[i, j]);

solve minimize cost;

output ["\(n)\n"] ++ 
    [show(x[i, j]) ++
        if j = n then "\n" else " " endif
    | i, j in 1..n] 
    ++ ["cost: \(cost)"];
% output to be used in cycles.cpp