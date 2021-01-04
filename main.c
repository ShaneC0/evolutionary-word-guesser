
#include "Brain.h"

#define POPULATION 10
#define MUTATION_RATE 0.01F
#define TARGETSTRING "To be or not to be."

/*
    need to make mating pool memory allocation only as big as needed;
*/

int main(void)
{
    //TESTING
    Agent **agents = generateAgents(POPULATION, sizeof(TARGETSTRING));

    calcAllFitness(agents, TARGETSTRING, POPULATION);

    printAgents(agents, POPULATION);

    freeAgents(agents, POPULATION);
    return EXIT_SUCCESS;
}