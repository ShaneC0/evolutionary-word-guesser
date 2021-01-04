
#include "Brain.h"

#define POPULATION 10
#define MUTATION_RATE 0.1
#define TARGETSTRING "Simple"

//implement loop to make array of agents until at least 1 has fitness > 0

int main(void)
{
    //TESTING
    Agent **agents = generateAgents(POPULATION, strlen(TARGETSTRING));

    calcAllFitness(agents, TARGETSTRING, POPULATION);

    printAgents(agents, POPULATION);

    for (int i = 0; i < 100; i++)
    {
        agents = evolve(agents, POPULATION, strlen(TARGETSTRING), MUTATION_RATE);
        calcAllFitness(agents, TARGETSTRING, POPULATION);
    }

    printf("100 Evolutions\n");

    printAgents(agents, POPULATION);

    freeAgents(agents, POPULATION);
    return EXIT_SUCCESS;
}
