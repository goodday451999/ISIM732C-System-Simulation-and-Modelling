#include<bits/stdc++.h>
#include <thread>
#include<unistd.h>

using namespace std;

queue <pair<int, int> > task_queue;
int task_id = 0;
float time_reduction_factor = 200000;
int flag = 0;
queue<int>servers; // Queue of servers for allocation of task
vector<mutex *>resources; 
int total_seconds = -1;
int departure_time = 0;
int length = 0;
int server_use_time[100000] = {0};
int waiting_time = 0;

//Global clock
void timer() {
    while(flag != 1) {
        total_seconds++;
        usleep(time_reduction_factor);
        //cout << total_seconds << endl;

        length += task_queue.size();
    }
}

// Method to lock resources for each server and perform the task
void perform_task(int server_id) {
    float sleep_time;
    int task_id;
    int before_start;
    int start;
    int end;

    before_start = total_seconds; // time at which request for lock is received
    resources[server_id]->lock(); // Lock resources for server with id received in parameter

    start = total_seconds; // time at which the task receives the lock
    waiting_time += (start - before_start); // time for which the task waited to acquire lock
    sleep_time = task_queue.front().second  * time_reduction_factor;
    task_id = task_queue.front().first;
    task_queue.pop(); // Remove task from task_queue
    usleep(sleep_time);
    departure_time += total_seconds;
    cout << "Server " << server_id << " Finished task with job id " << task_id << endl;
    end = total_seconds; // time at which task is finished
    server_use_time[server_id] += (end - start); // time for which the particular server is used is incremented

    resources[server_id]->unlock(); // Unlock resources for server with id received in parameter

    return;
}

void response_method(int number_of_servers, int arrival_time, int service_time) {
    cout << "Received request with job id " << task_id << " and inter arrival time of " << arrival_time << "s" << endl;
    // Received request is put in task queue
    task_queue.push({task_id, service_time});
    task_id++;

    int server_id = servers.front(); // Server in front of queue is assigned the received request

    servers.pop();
    servers.push(server_id); // Last assigned server is dequeued and pushed at the end of queue
    perform_task(server_id);

    return;
}

// Method to make request to server
void request_method(int number_of_servers, queue<pair<int, int>>input) {
    while(!input.empty()) {
        int seconds = -1;
        float sleep_time;
        vector<thread>v;

        while(1) {
            // Make request if the inter-arrival time is equal to timer
            if(input.front().first == seconds) {
                // Create separate thread for every request on server
                thread server(response_method, number_of_servers, input.front().first, input.front().second);
                v.push_back(move(server));
                // Remove input from the queue as the request has been made to the server
                input.pop();
                // Reset the timer
                seconds = 0;
            }

            sleep_time = 1 * time_reduction_factor; // Implementation of timer
            usleep(sleep_time); // Implementation of timer
            seconds++;

            if(input.empty()) {
                // Wait for all threads to complete their execution
                for(int i = 0; i < v.size(); i++) {
                    v[i].join();
                }
                break;
            }
        }

    }

    return;
}

int main() {    
    ifstream inputF; 
    inputF.open("input.txt");
    queue<pair<int, int> >input;
    int number_of_servers, number_of_customers;
    // cin >> number_of_servers;
    // cin >> number_of_customers;
    inputF>>number_of_servers>>number_of_customers;
    

    for(int count = 0; count < number_of_customers; count++) {
        int arrival_time, service_time;

        inputF >> arrival_time;
        inputF >> service_time;

        input.push({arrival_time, service_time});
    }
    inputF.close();
    for(int counter = 0; counter < number_of_servers; counter++ ) {
        int server_id = counter;

        servers.push(server_id); // Initially all servers are available for taking the job/task

        resources.push_back(new mutex()); // Push shared resource lock for each server in resource vector
    }

    thread time(timer); // Separate thread acting as global clock
    request_method(number_of_servers, input); // Passes input data to request method
    
    flag = 1;  // To stop the timer when all requests are served by the server
    time.join();

    cout << "All requests completed at " << total_seconds << endl;
    cout << "Cumulative departure time " << departure_time << endl;
    cout << "Avg. Queue Length " << (float)length / (float)total_seconds << endl;
    cout << "Avg. Waiting time " << (float)waiting_time / (float)input.size() << endl;

    for(int counter = 0; counter < number_of_servers; counter++) {
        // Idle time is use time of server less the total time taken for all requests to be completed  
        cout << "Idle time for server " << counter << " is " << (total_seconds - server_use_time[counter] - 2) << " s " << endl;
    }

    return 0;
}