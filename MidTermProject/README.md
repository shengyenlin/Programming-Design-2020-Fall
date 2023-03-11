# Midterm project - operation research 

## Project description
In this project, you'll be given m machines and n orders, and your task is to schedule a production and maintenance plan that minimizes delivery delays. You have the freedom to assign orders to machines as you see fit, and to determine the processing order for each machine. Additionally, you can strategically insert maintenance on each machine to improve machine yield and increase production efficiency. Your ultimate goal is to minimize the total delay time. This midterm project is designed to encourage you to explore and experiment with different algorithms to see if you can come up with the best possible plan.

For detailed constraints of machines and orders, please refer to `project_description.pdf`.

## Methodologies

1. Sort orders using the bubble sorting method, with orders that expire sooner placed at the front, and if they have the same expiration date, orders with larger quantities are placed at the front.

2. Allocate appropriate machines according to the order sequence, assigning each order to a different machine. When assigning orders, choose the machine that minimizes the delay time for that order. If there are multiple machines with the same delay time, choose the one with the lowest production capacity. 

    Each order is processed in the orderDistribute function, which calculates the delay time and machine production efficiency for each machine, storing them in the machineMightDelay and machineFinalPR arrays. Then, the delay time and efficiency (machineFinalPR * ideal production rate) are compared, and the machine's production efficiency, production time, accumulated delay time, number of orders, and order numbers are updated.

3. Arrange the order of machine maintenance using the bubble sorting method, with machines that need the most maintenance at the front and those that need the least at the end. Machines are first sorted by total delay time (machineDelayTotal), then by order quantity (sum), and finally by maximum hourly production rate (a).

4. Declare workerFree as a matrix of h * maxProductionTime + 10001, representing each worker's availability during a certain time period. The added 10001 is to avoid memory allocation issues caused by an increase in maxProductionTime under optimal conditions.

5. Declare repairList as a matrix of m * number of orders for each machine. Each machine can be repaired for a maximum number of times, and repairs are not included in the orders. Therefore, this matrix represents whether each machine needs maintenance before the start of each order (1 means maintenance is needed).

6. For each machine, start with the one that needs the most maintenance and work down to the one that needs the least. Run determineRepair_1 until the number of repairs is less than or equal to the number of maintenance personnel h. After that point, run determineRepair_2.

For detailed algorithm, please refer to the `midterm_project.docx` (In chinese).

## How to reproduce out result

Please upload `project_code.cpp` to PDOGS