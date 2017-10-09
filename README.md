# Multithreading
Multithreading tests/examples

1) Data Race and Mutex.cpp:

Multithreading using a shared resource (a cout object) and overcoming two threads competing for use of it using Mutex and locks



2) one_time.cpp

Multithreading with a statement that is supposed to execute exactly once while running on several threads (Practically, this could be opening a file, or prompting a user for info). 

3) conditional_variable.cpp

Uses wait/sleep/notify to have threads work together
