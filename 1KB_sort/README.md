**External Merge Sort for Low RAM Usage**

This C++ program implements an external merge sort algorithm designed to sort large datasets using minimal RAM. It achieves this by dividing the input file into smaller chunks, sorting them in memory, and then merging the sorted chunks in a series of passes using external storage.

**Key Features:**

- **Low RAM Footprint (1 MegaBit/125KB):** The algorithm sorts data in manageable chunks, significantly reducing RAM requirements compared to traditional in-memory sorting methods. This makes it suitable for resource-constrained devices or situations where RAM is limited.
- **Efficient External Merging:** The merge process efficiently combines sorted sub-files into larger sorted files, minimizing disk I/O operations.
- **Clear File Management:** The code handles file opening, closing, and removal effectively, ensuring proper cleanup and avoiding potential file system errors.

**Potential Applications:**

- Sorting very large datasets on devices with limited RAM (e.g., embedded systems, older computers).
- Sorting log files or other continuously generated data streams where memory is a concern.
- Implementing external sorting as a component of a larger data processing pipeline.

**Historical Context of RAM**

Random-access memory (RAM) has undergone significant evolution since its inception in the early days of computing. Here's a brief overview:

- **Early RAM (1940s-1950s):** Magnetic drum and core memory were the first forms of RAM, offering limited capacity and slow access times.
- **Transistorized RAM (1960s-1970s):** The invention of transistors led to the development of semiconductor RAM (SRAM), providing faster access speeds and higher densities.
- **Dynamic RAM (DRAM) (1970s-Present):** DRAM became dominant due to its ability to store more data in less space and at a lower cost than SRAM. DRAM advancements have driven continuous increases in RAM capacity and affordability over the decades.
- **Modern RAM (2000s-Present):** Double data rate (DDR) memory introduced faster data transfers, with DDR4 being a common standard today. Specialized RAM types like GDDR are used for graphics processing.

The ability to sort large datasets with minimal RAM has become increasingly important as data volumes continue to grow. This external merge sort implementation offers a valuable solution for such scenarios.

**Considerations**
- **Ram Usage** could not be further reduces due to `fopen()` requirements
- **Massif file** included showing heap activity