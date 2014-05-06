shogun-linalg
=============

Prototype for Shogun's linear algebra library that supports different linalg library backends like Eigen3, ViennaCL etc.

Structure
============
linalg is divided in modules, for example
```
linalg
 |--- Redux (reduction module)
 |  |--- norm (matrix and vector)
 |  |--- dot 
 |  '--- sum (various sum methods on matrix and vector)
 |--- LinSolver
 |  |--- Cholesky
 |  |--- QR
 |  '--- SVD
 |--- EigSolver
 |  |--- Blah
 |  '--- Blah
 '---Misc (IDK :D)
 ```
Facilities
============
Now, we can set backends in compile time via compiler options. It can be used to
 - Set a particular backend (say, Eigen3) for all the linalg modules via `-DUSE_EIGEN3` compiler option
 - Set module specific backends (say, LinSolver) via `-DUSE_EIGEN3_LINSLV` options and so
 - Some default backends are always set. Which backend should be used as default that is left up to API designers
 - For users, they can always use any particular backend they want via especially mentioning the backend, no matther what global backend was set initially.
 - All of these are done in compile time for faster execution
 
What's inside
==============
A test demo showing working example of dot and sum operation from the redux module (3 tests, two of them are using global settings, another is using explicitly set backend).
To compile, inside src run
```
g++ test.cpp -I. -std=c++0x -lshogun -I/usr/include/eigen3
```
Use additional `-DUSE_EIGEN3` to set Eigen3 as global backend. Use `-DUSE_EIGEN3_REDUX` to set Eigen3 as default for reduction module linalg operations.
