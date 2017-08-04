#include <chrono>

#include "christofides.h"

int main(int argc, char *argv[])
{
    Christofides tsp;
    tsp.load();
  	//std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
    tsp.run();
    //std::cout << "elapsed_time " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-t).count() << std::endl;
    return 0;
}
