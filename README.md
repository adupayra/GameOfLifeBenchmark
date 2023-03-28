# GameOfLifeOpenGL (March 2023)

While the aim of this project was to provide an implementation of the Game Of Life with a GUI developped with OpenGL, the main focus is to compare different
approaches to speed up the evaluation of the grid of cells. <br>
Many different approaches relying on parallelization were studied and a benchmarking tool was implemented to efficiently compare them.

## Game of life implementation

The grid of cells is represented using a one dimensionnal array of bytes. The one array implementation allows a faster access compared to a multi dimensionnal array implementation.

## OpenGL implementation

This project being pretty simple overall, there is not really any technical details to be given. This implementation was made following MVC pattern to dissociate the UI from 
the model. While the render part simply consists of a rectangle on which we apply a texture. This texture is generated thanks to the grid of cells provided by the model. <br>
Here is a screenshot of one generation in a world composed of 1 048 576 cells:
![image](https://user-images.githubusercontent.com/55114282/228110492-ce99012a-4f82-448b-8816-4ca1b3205545.png)

## Comparison of different methods in the computation of the new generation

As stated before, the main focus of this project is the comparison of different methods to speed up the computation of the next generation of cells. As these methods were only applied on
this specific step on the model side, it is required to precise that they could be applied in other parts of the application as well (such as grid initialization
or texture generation for instance, which are made using a single thread for now). <br> <br>
An obvious way to speed up the computation of new generations is to use CPU multi threading instead of a single thread, or to use GPU multi threading. However there are multiple ways
to implement such a CPU multi threading approach. Here are all the approaches that were covered: <br>

### Simple CPU mono thread implementation

Here, the computation of the new generation is simply made by evaluating each cells of the world one by one and deciding if it should be alive or dead.

### Simple CPU mono thread implementation with a different algorithm to update the cells 

The idea of this other method is to reduce the number of cells that are required to be evaluated in order to generate the new generation. In the rules of the game of life, 
only living cells have an influence on the next generation. Therefore, this algorithm skips dead cells to only focus on living cells, reducing the amount of cells to be 
treated in a lot of cases.

### Multi threading using The Parallel Patterns Library (PPL) from the windows API

This method relies on a high level method to handle multi threaded for loops to manage concurrent work. It is a simple and easy to use method but has the drawback of being
platform dependant, and as we will see with the benchmark, not the most performant in our case.

### Multi threading with C++ standard library's threads

This approach is also quite easy to implement in this case. The principle is to divide the array of cells into as much threads as the OS and hardware can offer. Each thread will then process the new state of the cells that is attributed to it.

### Multi threading with C++ standard library's threads and threadpool

Here, a threadpool is implemented to avoid destroying and creating threads at every new generations.

### GPU acceleration using CUDA

With this method, it is required to decide the number of threads to use per block. To do so, the benchmark tool is also used.

## Benchmark tool

This tool is quite simple, it allows to compare the performance of different methods (or in the case of GPU acceleration, different numbers of threads per block) as well as 
profiling different information (for now, the only information available is the average percentage of CPU used during the computation on top of the average execution time).<br> <br>
It will start an instance of a game of life and compute iterations for a fixed number of generations for the methods that we want to compare, and store the results in a CSV file. The world size gets increased and the process is repeated until the world size threshold is reached. <br>

Here is an example of benchmark to compare the different methods:

![image](https://user-images.githubusercontent.com/55114282/228109786-81969afd-76bb-4b01-a239-b13f8d9b37d9.png)

We can see expected results:
Mono thread CPU is the slowest, followed by the method using Parallel Patterns Library, then CPU multithreading without threadpool, followed by the version using a threadpool, with finally the GPU accelerated version.<br>
We can also notice that the alternative algorithm is giving very poor results. <br> <br>

Regarding the GPU acceleration threads per blocks comparison, here is a benchmark example:
![image](https://user-images.githubusercontent.com/55114282/228110085-9d325bed-773d-4e9e-a27a-af27a37a9f00.png)

We can see here that the number of threads per block doesn't change much the results unless it is 32.

## Going further

To enhance this project features, I thought of multiple options:
- Adding a side menu to the GUI with different functionnalities such as:
  - Displaying real time profiling information on top of the benchmarking feature (such as CPU usage, time of execution to provide current generation, memory usage...). 
  - Offering the possibility to interact with the GUI by zooming or affecting the speed of generations update
- Adding further profiling information to the benchmark
- Adding a 3D version, which would be an improved version of my previous project made in 2019 that was thought as an introduction to both C++ and OpenGL.
- For now, each cell is represented by one byte, while we only store either 0 or 1 in this integer. Finding a way to store one bit for each cell (or 8 cells for one byte), 
would reduce the amount of Ram used by 8 and maybe allow faster computation depending on the implementation.
- Improving the mono threading CPU algorithm based on the evaluation of the neighbourhood of living cells only.

These improvements might be added in the future if I ever get back on this project.
