# VLSI-Testing
Algorithm that extracts a circuit from a netlist and performs fault collapsing
## Background
In large scale integration, logic circuits can suffer from single stuck at faults that are 
responsible for incorrect outputs. To help deal with these errors, we implement something called
fault modelling where the single-stuck-at faults are organized into data structures so that we can perform
testing, and detect whether a logical circuit is indeed experiencing such a fault.

## Examples of single stuck at faults
![fault model](https://i.imgur.com/0bCbODb.png)

As you can see from this example, if there were no faults present on the circuit, then the output would be 1 given this test vector. Since there is a stuck at 0 fault on the first AND gate, the output of the circuit is 0 since the final AND gate is fed a controlling value, leading to incorrect logic.

## Approach
This is an interactive program where the user is given 6 options:
- Option 0 is responsible for reading a circuit netlist file and parse it into separate data structures.
- Option 1 is responsible for fault collapsing, meaning that all the redundant faults are removed.
- Option 2 is responsible for listing the fault classes.
- Option 3 is responsible for generating all the test vectors that are able to detect the fault universe.
- Option 4 is responsible for boolean satisfiability.
- Option 5 is responsible for exiting the program.
