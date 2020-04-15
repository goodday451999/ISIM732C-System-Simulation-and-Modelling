### Single Worker Single Queue Problem. 

Input to the program will be ***input.txt*** file with the first line of the file specifying customers and subsequent lines giving the inter-arrival times and Service times of each customer.

### How to run?
* --> g++ -std=c++11 single.cpp -lpthread
* --> ./a.out


### Note:
1. You can simulate time delays using the sleep method provided in the programming language of your choice. It can be like 1s = sleep for 0.2s.
2. It's a multi-threaded program. Hence, the queue should be a shared variable between producer and consumer threads. All threads can be signalled to terminate on encountering end of file. Do not read all tasks at once and submit in the queue.
3. You can use any programming language of your choice.
