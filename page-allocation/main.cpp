#include <iostream>
#include <random>

#include "page_allocation.hpp"

constexpr uint16_t GRAPH_SIZE = 64;

int main(int argc, char* argv[]) {
    if(argc != 5) {
        std::cerr << "Usage: " << argv[0] << "<requests_number> <d_value> <p_value> <repetitions>" << std::endl;
        return -1;
    }

    size_t requestsNumber = std::stoul(argv[1]);
    size_t dValue = std::stoul(argv[2]);
    float pValue = std::stof(argv[3]);
    size_t repetitions = std::stoul(argv[4]);

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<uint16_t> nodesDistribution(0, GRAPH_SIZE - 1);
    std::uniform_real_distribution<float> operationDistribution(0.0, 1.0);

    size_t cost = 0;
    size_t maxCopies = 0;
    for(size_t rep = 0; rep < repetitions; rep++) {
        size_t maxCopiesLocal = 0;
        std::vector<uint16_t> resourceNodes(1, nodesDistribution(gen));
        PageAllocation pageAllocation(GRAPH_SIZE, resourceNodes, dValue);
        for(size_t reqNum = 0; reqNum < requestsNumber; reqNum++) {
            if(operationDistribution(gen) <= pValue) {
                cost += pageAllocation.write(nodesDistribution(gen));
            }
            else {
                cost += pageAllocation.read(nodesDistribution(gen));
            }
            if(pageAllocation.getCopiesNumber() > maxCopiesLocal) {
                maxCopiesLocal = pageAllocation.getCopiesNumber();
            }
        }

        maxCopies += maxCopiesLocal;
    }
    
    if(repetitions * requestsNumber == 0) {
        std::cout << 0 << " " << 0 << std::endl;
    }
    else {
        std::cout << static_cast<double>(cost) / static_cast<double>(repetitions * requestsNumber) << " " 
                  << static_cast<double>(maxCopies) / static_cast<double>(repetitions) << std::endl;
    }

    return 0;
}