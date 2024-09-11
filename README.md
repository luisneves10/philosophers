# 🍝 Philosophers

The "philosophers" project at 42 simulates the classic dining philosophers problem, focusing on process synchronization and concurrency.

## 🚀 Features

- Simulates multiple philosophers sitting at a table, alternating between eating, sleeping and thinking.
- Implements a solution to the dining philosophers problem while avoiding deadlocks and race conditions.

## 🛠️ Technologies Used

- **C Programming Language**
- **POSIX Threads (pthreads)**

## 📥 Installation

To run the Philosophers simulation on your local machine, follow these steps:

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/luisneves10/philosophers.git
    ```
2. **Navigate to the Project Directory**:
    ```bash
    cd philosophers
    ```
3. **Compile the Code**:
    ```bash
    make
    ```
4. **Run the Program**:
    You can run the simulation with the following parameters:
    ```bash
    ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
    ```

    Example:
    ```bash
    ./philo 5 800 200 200
    ```

## 📚 Learning Experience

- **Concurrency and Synchronization:** This project taught me how to manage multiple threads running concurrently and how to use synchronization mechanisms like mutexes.
- **Deadlock Avoidance:** I learned how to implement strategies to prevent deadlock and starvation in concurrent systems.
- **Multithreading:** The use of POSIX threads improved my understanding of multithreaded programming and managing shared resources efficiently.
