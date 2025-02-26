# MultiLevelQueue
 Implementing Multi Level Queue Scheduling in OS using CPP/C++

+ I created to simulate a multilevel queue scheduling 
algorithm.  
+ Here I’ll discuss the program’s logic,  sample inputs and outputs, analyze the results, and the 
strengths and weaknesses of each scheduling algorithm used. 
------------------------

LOGIC :
 
The program simulates a CPU scheduler that manages processes using 4 queues, each with a 
different priority and scheduling algorithm:
 
	1. Queue 0 (q0): Highest priority, uses Round Robin (RR) with a time quantum of 20 seconds. 
	2. Queue 1 (q1): Medium-high priority, uses Shortest Job First (SJF). 
	3. Queue 2 (q2): Medium-low priority, uses Shortest Job First (SJF). 
	4. Queue 3 (q3): Lowest priority, uses First-In-First-Out (FIFO).
 
The CPU switches between queues every 20 seconds, ensuring higher-priority processes are 
executed first while still giving lower-priority processes a chance to run.
------------------------

Final Thoughts :
	
	This program demonstrates how multilevel queue scheduling can be used to manage processes 
with varying priorities. By combining different scheduling algorithms, it achieves a good balance 
between responsiveness and fairness. However, in real-world systems, dynamic adjustments (e.g., 
varying time quanta or priority boosting) may be needed to further improve performance.
