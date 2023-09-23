#include <iostream>

int main() {
    //if arrival time of process = time, push that process onto the waiting queue

            //need while loop while to run through processes

            bool complete = false;
            while (complete != true) {

                //if nothing in the waiting queue and nothing running add block duration to the total time
                /*
                if (running.empty() && waiting.empty()) {
                    std::cout << time << "\t" << "[IDLE]" << quantum << "I" << "\n";
                } else if (running.empty() && waiting.empty() && blocked.empty()) {
                    break;
                }
            }*/
                /*
                 * to start we need to sort process by arrival time
                 * sort the waiting queue
                 *
                 * if(running is empty){
                 *
                    pop off waiting queue into running queue
                    if (rem_cpu_time > quantum){
                        t+= quantum;
                        rem_cpu_time-=quantum;
                        push processes on to waiting queue
                        std::cout << time << "\t" << process.get.name << "\t" << quantum << "Q" << "\n";
                        subtract quantum time from total time
                }else{quantum > rem_cpu_time)
                        t+=rem_cpu_time;
                        push process on to blocked queue
                        std::cout << time << "\t" << process.get.name << "\t" << rem_cpu_time << "B" << "\n";
                        subtract remaining cpu bust time from total time
                    }
                if (current time >= block_duration + time of being blocked) then push on to waiting queue if not stay blocked
                if(get_total_running_time == 0){
                    std::cout << time << "\t" << get_name << get_cpu_burst << "T" << "\n";
                    }


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
