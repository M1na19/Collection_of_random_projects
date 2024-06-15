## Plane Placement Optimization using Evolutionary Algorithm

This project tackles optimizing airplane seating arrangements to minimize passenger boarding time. It utilizes an evolutionary algorithm to discover the ideal seating configuration that achieves the fastest boarding process.

### Problem Statement

Airplane boarding can be a lengthy and inefficient ordeal, especially when passengers are randomly assigned seats. This project seeks an optimal seating arrangement that groups passengers together and assigns them to specific seats, ultimately minimizing boarding time.

### Approach

An evolutionary algorithm spearheads the quest for the best seating configuration. The algorithm begins with a population of randomly generated seating arrangements, each representing an "individual." Each individual is evaluated using a fitness function that simulates the boarding process and calculates the total boarding time.

The algorithm then progresses through multiple generations. In each generation, the fittest individuals (those with the lowest boarding time) are chosen and used to create new individuals through a combination of combining and mutating their characteristics. This process continues until a satisfactory solution is found or a predetermined number of generations is reached.

### Implementation

The project is built using C# and consists of these key components:

* **Environment:** This class retrieves configuration settings from a JSON file (env.json). These settings encompass the airplane's number of rows and seats, the maximum number of groups allowed, mutation rates, and simulation parameters.
* **Airplane:** This class embodies an individual seating arrangement. It stores the seating configuration as a dictionary, where keys represent seat positions (row and seat letter) and values represent group numbers.
* **Fitness:** This class calculates the fitness (boarding time) of an individual seating arrangement by simulating the boarding process. Factors like walking time, waiting time, and group seating preferences are incorporated into the simulation.
* **Mutations:** This class implements various mutation operations on individuals. Examples include adding or removing groups, swapping passengers between groups, and introducing random mutations.
* **Succesor:** This class handles the creation of new individuals (offspring) by combining and mutating selected individuals from the prior generation. 
* **EvolutionaryAlgorithm:** This class orchestrates the entire evolutionary algorithm. It initializes the population, evaluates individuals, selects the fittest ones, and generates new generations until a satisfactory solution is found.

### Usage

1. Clone the repository or download the source code.
2. Build the project using a C# compiler or an IDE like Visual Studio.
3. Execute the compiled program.
   - The program will read configuration settings from the env.json file and commence the evolutionary algorithm.
   - The algorithm will run for the specified number of generations, and the best seating arrangement discovered will be saved to the result.txt file.

### Configuration

The env.json file houses the configuration parameters for the algorithm. You can modify these parameters to align with your specific needs:

* **AirplaneConfig:** Defines the number of rows and seats within the airplane.
* **PassengerConfig:** Specifies the maximum number of groups.
* **MutationConfig:** Configures the mutation rates for adding/removing groups and swapping passengers.
* **MatingConfig:** Configures the threshold for mating individuals based on their similarity.
* **SimulationConfig:** Configures the simulation parameters, including the number of tests used for fitness evaluation, walking time ranges, waiting time ranges, and the number of generations and population sizes.

### Example Output

The result.txt file will contain the algorithm's best-found seating arrangement, along with its corresponding fitness value (boarding time). Here's an example of the output:

```
384.2489
7
  A B C     D E F  
| 5 3 4 | | 5 6 4 | 1
| 6 4 6 | | 4 5 3 | 2
...
```

The first line displays the fitness value (boarding time). The second line shows the number of groups used. The subsequent lines represent the seating arrangement, with each row depicting the group numbers assigned to the corresponding seats.

## Unveiling the Algorithm's Strategy in bestResult.txt

A closer look at the seating arrangement in `bestResult.txt` reveals a fascinating strategy employed by the algorithm. It seems the algorithm has strategically placed passengers with lower group numbers towards the back rows and sides of the aircraft.

Here's a breakdown of this strategy:

* **Group 1 Priority:** Passengers in Group 1 are primarily seated in the last few rows and side seats.
* **Similar Strategy for Group 2:** Group 2 follows a similar pattern, with most passengers positioned in the back and on the sides.
* **Front and Center for Higher Groups:** Groups with higher numbers, like 5 and 6, occupy the front rows and middle seats.

This seating arrangement hints at a strategy to expedite boarding. Passengers with lower group numbers (boarding later) are placed towards the back and sides, minimizing congestion in the aisles as they board. Conversely, passengers with higher group numbers (boarding earlier) are positioned near the front and middle, allowing them quicker access to their seats.

By strategically placing lower numbered groups towards the back and sides, the algorithm likely optimized the seating configuration to achieve two goals:

1. **Reduced Aisle Congestion:** As later-boarding passengers (lower groups) have more walking space, aisle congestion is minimized.
2. **Shorter Walking Distances:** Later-boarding passengers have shorter walking distances since their seats are located towards the periphery.
