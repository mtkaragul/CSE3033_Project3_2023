# CSE3033 Operating Systems Project 3 - 2023

## Abstract
The provided code implements three different methods for calculating the square root
sum of a range of numbers concurrently using multiple threads. The methods differ in how
they handle synchronization:

● Method 1: Each thread independently updates the global sum without
synchronization.
   ○ Expected Behavior: For the same input, we expect the results (sum) to be
different when the number of threads changes. This is because, without mutex
synchronization, threads do not work concurrently. Consequently, Method 1 is
prone to race conditions, and the absence of synchronization may lead to
incorrect results.

● Method 2: Each thread acquires a mutex before updating the global sum to ensure
mutual exclusion.

● Method 3: Each thread calculates a local sum, and after the local sum is computed, it
acquires the mutex to update the global sum.

## Questions:
1. Which method(s) provide the correct result and why?
   
Method 2 and Method 3 are likely to provide correct results because they use a mutex
to synchronize access to the global sum. This ensures that multiple threads do not
concurrently update the global variable, avoiding race conditions.
Method 1 is prone to race conditions, and it may produce incorrect results. Multiple
threads updating the global variable simultaneously can lead to data corruption.

2. Among the method(s) providing the correct result, which method is
the fastest?

Method 3 is by far the fastest method. Method 2 is quite slow. Although method 2 and
method 3 give the same result, there is a speed difference between them. Method 1 is faster
than method 2 but gives wrong results.

3. Does increasing the number of threads always result in a smaller
total time?

Not necessarily. The speedup achieved by increasing the number of threads depends
on the nature of the workload and the available CPU cores.
If the workload is not parallelizable or if the number of threads exceeds the number of
available CPU cores, increasing the number of threads may not result in a smaller total time.

5. Are there any differences in user time/system time ratio of the
processes as the number of threads increases? What could be the
cause of these differences?

As the number of threads increases, there is an increase in both user time, indicating
more time spent in user-level code, and system time, signifying an escalation in kernel-level
operations.
Increasing the number of threads may lead to more CPU contention, affecting the
ratio. Mutex operations and synchronization mechanisms can contribute to kernel-level
activities, impacting the ratio.

## Outputs
We ran the program on 3 different computers. One of them has Linux and the other
has a Mac operating system. On the 3rd computer, we installed Linux with a virtual machine
and tried it. We got the results the fastest on Mac, so we filled the tables with the data we got
from Mac. On the other two computers we had to wait very long times for methods 1 and 2,
so we put some of the data we ran on Linux at the bottom of the report.

##### To Compile Code:

> gcc project3.c -o project3.out -lm -pthread

##### To Run Code:

> time ./project3.out `<startOfTheRange>` `<endOfTheRange>` `<threadNumber>` `<methodNumber>`

##### Contributors
> Muhammed Talha Karagül
> 
> Kadir Bat
> 
> Feyzullah Asıllıoğlu 
