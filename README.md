# Philosophers

_Philosophers_ is a 42 School project based on Edsger Dijkstra's famous Dining Philosophers problem. The goal of this project is to explore concurrent programming by managing threads and mutexes.

## Overview

This project simulates a group of philosophers sitting at a round table, each alternating between eating, sleeping, and thinking. The twist is that the philosophers must share limited resources (forks) to eat spaghetti. The simulation must ensure that the philosophers live as long as possible under the constraints of the problem.

## Problem Description

- **Setup:**
  - One or more philosophers sit at a round table.
  - A large bowl of spaghetti is placed at the center.
  - There is exactly one fork between each pair of philosophers (i.e., as many forks as philosophers).

- **Rules:**
  - A philosopher needs to pick up both the fork on their immediate left and the fork on their immediate right to eat.
  - After eating, a philosopher sleeps and then thinks.
  - If a philosopher does not start eating within a specified time frame (denoted as `time_to_die`), they die of starvation.
  - Philosophers cannot communicate with each other.

## Project Parameters

The program accepts the following command-line arguments:

1. **number_of_philosophers**:  
   The total number of philosophers sitting around the table.

2. **time_to_die (in milliseconds)**:  
   The maximum time a philosopher can go without eating. If a philosopher does not start eating within this time (since their last meal or the beginning of the simulation), they die.

3. **time_to_eat (in milliseconds)**:  
   The time it takes for a philosopher to finish eating. During this period, the philosopher holds both forks.

4. **time_to_sleep (in milliseconds)**:  
   The duration a philosopher spends sleeping after eating.

5. **number_of_times_each_philosopher_must_eat (optional)**:  
   If provided, the simulation ends when each philosopher has eaten at least this many times. If omitted, the simulation only ends when a philosopher dies.

## Mandatory Part: Threads and Mutexes

- Each philosopher is implemented as a separate thread.
- Forks are represented as mutexes to prevent concurrent access.
- A philosopher must acquire the mutexes for both the fork on their immediate left and the fork on their immediate right to begin eating.

### Usage

Clone the repository:
```sh
git clone git@github.com:cde-paiv/Philosophers.git
```


Run the program with the following arguments:

```shell
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat]
```

The arguments must be integers between 0 and INT_MAX representing a time in milliseconds. For example:

```shell
/philo 4 800 200 200 5
```

If the arguments are valid, the program will output the actions of each philosopher until one of them dies or until all of them have eaten number_of_times_each_philo_must_eat, if specified.
