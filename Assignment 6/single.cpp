#include<bits/stdc++.h>
#include <thread>
#include<unistd.h>

using namespace std;

queue <pair<int, int>> task_queue;
int task_id = 0;
int time_reduction_factor = 200000;
int flag = 0;
mutex access_resources; // Critical Section, shared resource
int total_seconds = -1;
int length = 0;
int departure_time = 0;
int idle_time = -1;
int server_use_time = -1;

// Global clock
void timer() {
    while(flag != 1) {
        total_seconds++;
        usleep(time_reduction_factor);

        //cout << total_seconds << endl;
        length += (task_queue.size() > 0) ? (task_queue.size() - 1) : 0;
    }

    return;
}

// Method to lock resources and perform the task
void perform_task() {
    int sleep_time;
    int task_id;
    int start;
    int end;

    access_resources.lock(); // Lock the resources

    start = total_seconds;
    sleep_time = task_queue.front().second * time_reduction_factor; // Perform task for service time of request
    task_id = task_queue.front().first;
    usleep(sleep_time);
    cout << "Finished task with task id " << task_id << endl;
    task_queue.pop(); // Remove task from task_queue
    departure_time += total_seconds;
    end = total_seconds;
    server_use_time += (end - start);

    access_resources.unlock(); // Unlock the resources

    return;
}

// Method to serve client request
void response_method(int arrival_time, int service_time) {
    cout << "Received request with task id " << task_id << " and inter arrival time of " << arrival_time << "s" << endl;
    // Received request is put in task queue
    task_queue.push({task_id, service_time});
    task_id++;
    perform_task();

    return;
}

// Method to make request to server
void request_method(queue<pair<int, int>>input) {
    while(!input.empty()) {
        int seconds = -1;
        int sleep_time;
        vector<thread>v;

        while(1) {
            // Make request if the inter-arrival time is equal to timer
            if(input.front().first == seconds) {
                // Create separate thread for every request on server
                thread server(response_method, input.front().first, input.front().second);
                v.push_back(move(server));
                // Remove input from the queue as the request has been made to the server
                input.pop();
                // Reset the timer
                seconds = 0;
            }

            sleep_time = 1 * time_reduction_factor;
            usleep(sleep_time); // Implementation of timer
            seconds++; // Implementation of timer

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
    int number_of_customers;
    // cin >> number_of_servers;
    // cin >> number_of_customers;
    inputF>>number_of_customers;
    

    for(int count = 0; count < number_of_customers; count++) {
        int arrival_time, service_time;

        inputF >> arrival_time;
        inputF >> service_time;

        input.push({arrival_time, service_time});
    }

    thread time(timer); // Separate thread acting as global clock
    request_method(input); // Passes input data to request method
    
    flag = 1; // To stop the timer when all requests are served by the server
    time.join();

    idle_time = total_seconds - server_use_time;
    cout << "All requests completed at " << total_seconds << endl;
    cout << "Cumulative departure time " << departure_time << endl;
    cout << "Avg. Queue Length " << (float)length / (float)total_seconds << endl;
    cout << "Total Idle time of the server " << idle_time << endl;

    return 0;
}