---
timelimit: 1
...

# 3D Geometry

An axis-aligned tetrahedron (also known as triangular pyramid) $DABC$ is a convex polyhedron in three dimension with vertices

* $D: (x_1, y_1, z_1)$
* $A: (x_2, y_1, z_1)$
* $B: (x_1, y_2, z_1)$
* $C: (x_1, y_1, z_2)$.

Also, an axis-aligned cube $PQRSDEFG$ is a convex polyhedron with vertices

* $P: (x_3, y_3, z_3)$
* $Q: (x_3, y_3, z_4)$
* $R: (x_3, y_4, z_3)$
* $S: (x_3, y_4, z_4)$
* $D: (x_4, y_3, z_3)$
* $E: (x_4, y_3, z_4)$
* $F: (x_4, y_4, z_3)$
* $G: (x_4, y_4, z_4)$.

Given an axis-aligned tetrahedron $DABC$ and an axis-aligned cube $PQRSDEFG$, find the volume of their intersection.

## Input

The input consists of several test cases terminated by end-of-file. For each test case,

There are $4$ lines, and the $i$-th line contains three integers $x_i$, $y_i$, and $z_i$.

* $-500 \leq x_i, y_i, z_i \leq 500$ for each $1 \leq i \leq 4$
* $x_1 \neq x_2$, $y_1 \neq y_2$, $z_1 \neq z_2$
* $x_3 \neq x_4$, $y_3 \neq y_4$, $z_3 \neq z_4$
* In each input, the number of test cases does not exceed $10^5$.

## Output

For each test case, output a float which denotes the volume.

Your answer is considered correct if its *absolute* or *relative error* doesn't exceed $10^{-6}$.

<!--SAMPLES-->
