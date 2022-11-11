How to Run the code:
                    1) g++ push_relabel.cpp
                    2) ./a.out <test.txt file>
                        e.g. ./a.out test01.txt

How to run on different inputs: The input file for the test should contain the first line as number of total vertices in the graph. And from the second line onwards,
                                there should be the values for the single edge on a single line with attributes in the order: (starting_location, end_location, capacity). 
                                For example: 4              -> total number of vertices
                                             0 1 10         ->edge 1 with start_location, end_location, capacity attributes
                                             1 3 10         ->edge 2 with start_location, end_location, capacity attributes
                                             0 2 5          ->edge 3 with start_location, end_location, capacity attributes
                                             2 3 5          ->edge 4 with start_location, end_location, capacity attributes

The expected outputs for each test cases are in the folder 'expected_outputs'. In this folder every txt file will have the expected output of the corresponding test case.