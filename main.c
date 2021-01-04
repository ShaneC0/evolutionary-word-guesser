
#include "Brain.h"

#define POPULATION 1000
#define MUTATION_RATE 0.02
#define TARGETSTRING "abcdefghijklmnopqrstuvwxyz"

int main(void)
{
    Agent **agents = generateAgents(POPULATION, strlen(TARGETSTRING));

    calcAllFitness(agents, TARGETSTRING, POPULATION);

    int generation = 0;

    while (!checkFinished(agents, POPULATION))
    {
        agents = evolve(agents, POPULATION, strlen(TARGETSTRING), MUTATION_RATE);
        calcAllFitness(agents, TARGETSTRING, POPULATION);
        printBestAgent(agents, POPULATION, generation++);
    }

    printf("Target String: %s\nMutation Rate: %.2f\nPopulation: %d\nTotal Generations: %d\n", TARGETSTRING, MUTATION_RATE, POPULATION, generation);

    freeAgents(agents, POPULATION);
    return EXIT_SUCCESS;
}
