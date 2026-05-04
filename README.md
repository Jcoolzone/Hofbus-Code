hofbus-tester.c CREDITS GO TO PROFESSOR JIANCHEN SHAN

Hofbus is a small program written for my Operating Systems class at Hofstra University. It provides functions for a bus which
handles different processes concurrently. It implements locks correctly in xv6 and is tested using the hofbustester.c test
code. 

THE CHALELNGE: write a concurrent program so that no process is boarded out of order, no seats are out of order. 

station_init: initializes station struct variables as well as necessary mutexes. 

station_load_bus: broadcasts to student processes that the bus is available then runs until all students are boarded or 
all seats are filled. 

station_wait_for_bus: suspend activity until an open bus is at the station and it's this process' turn. 
