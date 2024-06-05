## Multithreaded Merge Sort with File I/O (main.cpp)

This repository contains a C++ program (`main.cpp`) that implements a multithreaded merge sort algorithm to sort a large list of integers stored in a file.

**Features:**

* Utilizes multiple threads for efficient sorting.
* Reads data from an input file and writes the sorted data to an output file.
* Offers options for sorting algorithms:
    * **Default:** Multithreaded Merge Sort
    * **Optional:** Standard library `sort` function for Quicksort (use `QuickSort` instead of `MergeSort` in thread function call)

**Requirements:**

* C++ compiler with C++11 support (for threads and chrono library)

**How to Use:**

1. **Clone the repository:**

   ```
   git clone https://github.com/M1na19/Multithreaded_mergesort.git
   ```

2. **Compile the program:**

   ```
   cd Multithreaded_mergesort
   g++ -o multithreaded_sort main.cpp -lpthread
   ```

3. **Run the program:**

   The program takes two arguments:

     * The first argument specifies the path to the input file containing the integers to sort.
     * The second argument specifies the path to the output file where the sorted data will be written.

   ```
   ./multithreaded_sort input.txt output.txt
   ```

**Example Usage:**

```
./multithreaded_sort large_numbers.txt sorted_numbers.txt
```

This command will sort the contents of `large_numbers.txt` and write the sorted data to `sorted_numbers.txt`.

**Performance:**

The program measures and prints the total sorting time in microseconds.\
The python script `tester.py` was used to test the average performance on diffrent data sets:\
| Test size  | Number of threads | Average completion time |
| ---------  | ----------------- | ----------------------- |
| 10         | 128               | 714μs/0.7ms             |
| 100        | 128               | 3798μs/3.7ms            |
| 1000       | 128               | 7070μs/7ms              |
| 10.000     | 128               | 7453μs/7.4ms            |
| 100.000    | 128               | 9933μs/9.9ms            |
| 1.000.000  | 128               | 39973μs/39.9ms          |
| 10.000.000 | 128               | 383916μs/383ms/0.38sec  |
| 100.000.000| 128               | 4036878μs/4036.8ms/4sec |

Tested on AMD Ryzen 7 4800H with Radeon Graphics

**Notes:**

* The `thread_num` variable within the code defines the number of threads used. It is automatically adjusted to a power of 2 based on the input size for efficient merging.
* The program dynamically allocates memory for the input array using `malloc`.

**Additional Information:**

* The program utilizes the `high_resolution_clock` from the `<chrono>` library for precise time measurement.
* The code includes comments to explain the functionality of different sections.

## Random Number Generator (generator.cpp)

This program generates a list of random integers and saves them to a file.

**How it Works:**

1. Takes three arguments:
   * Output filename
   * Number of integers to generate
   * Upper limit for the random numbers (inclusive)
2. Opens an output file for writing.
3. Generates random integers between 1 and the specified limit using the current time as a seed (ensures different sequences each run).
4. Writes the number of integers and then each random integer to the output file.
5. Optionally prints progress messages to the console during generation (every 1% by default).

**Example Usage:**

```
./generator random_numbers.txt 1000 100
```

This generates 1000 random integers between 1 and 100 and saves them to `random_numbers.txt`.
