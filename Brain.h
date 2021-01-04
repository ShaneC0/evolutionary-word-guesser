#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct
{
    double fitness;
    size_t dnaLen;
    char dna[];
} Agent;

//Iterates through each agent and prints its fitness and dna
void printAllAgents(Agent **agents, int population)
{
    for (int i = 0; i < population; i++)
    {
        printf("Fitness: %f\tDNA: %s\n", agents[i]->fitness, agents[i]->dna);
    }
}

void printBestAgent(Agent **agents, int population, int generation)
{
    Agent *bestFit = agents[0];
    for(int i = 0; i < population; i++)
    {
        if(agents[i]->fitness > bestFit->fitness)
        {
            bestFit = agents[i];
        }
    }
    printf("%d\t%s\t%f\n", generation, bestFit->dna, bestFit->fitness);
}

//Returns char from 65-122 on ascii table incl. space period and comma
char generateChar(void)
{
    int charCode = rand() % (122 - 65 + 1) + 65;
    if (charCode == 91)
        charCode = 32;
    if (charCode == 92)
        charCode = 46;
    if (charCode == 93)
        charCode = 44;
    return (char)charCode;
}

//Frees each agent then the array itself
void freeAgents(Agent **agents, int population)
{
    for (int i = 0; i < population; i++)
    {
        free(agents[i]);
    }

    free(agents);
}

//Generates a single pointer to agent with 0 fitness and random DNA
Agent *generateAgent(size_t targetLen)
{
    Agent *agent = malloc(sizeof(Agent) + (sizeof(char) * targetLen));
    agent->dnaLen = targetLen;
    agent->fitness = 0.0;

    for (int i = 0; i < agent->dnaLen; i++)
    {
        agent->dna[i] = generateChar();
    }

    return agent;
}

//Calls `generateAgent` `population` times. Returns array of pointer to Agent
Agent **generateAgents(int population, size_t targetLen)
{
    Agent **agents = malloc((sizeof(Agent) + (sizeof(char) * targetLen)) * population);

    //makes initial DNA different every time
    srand(time(0));
    for (int i = 0; i < population; i++)
    {
        agents[i] = generateAgent(targetLen);
    }

    return agents;
}

//Sets `fitness` value on `agent` to percentage of characters identical to `target`
void calcOneFitness(Agent *agent, char *target)
{
    unsigned int matchCount = 0;

    for (size_t i = 0; i < strlen(target); i++)
    {
        if (target[i] == agent->dna[i])
            matchCount++;
    }

    double calculatedFitness = (double)matchCount / strlen(target) * 100;
    agent->fitness = calculatedFitness;
}

//Loops through all `agents` in `population` and sets their `fitness` based on `target`
void calcAllFitness(Agent **agents, char *target, int population)
{
    for (unsigned int i = 0; i < population; i++)
    {
        calcOneFitness(agents[i], target);
    }
}

//Returns an agent from `agents` based on fitness
Agent *weightedSelect(Agent **agents, int population)
{
    while (1)
    {
        Agent *agent = agents[rand() % population];
        int r = rand() % 100;

        if (r < agent->fitness)
        {
            return agent;
        }
    }
}

//Sets `child` dna to be half of `parent1`'s and half `parent2`s
void crossover(Agent *child, Agent *parent1, Agent *parent2, size_t targetLen)
{
    int splitIndex = targetLen / 2;
    for (int i = 0; i < targetLen; i++)
    {
        if (i < splitIndex)
        {
            child->dna[i] = parent1->dna[i];
        }
        else
        {
            child->dna[i] = parent2->dna[i];
        }
    }
}

//Mutates characters in `child` dna based on `mutationRate`
void mutate(Agent *child, size_t targetLen, double mutationRate)
{
    for (size_t i = 0; i < targetLen; i++)
    {
        if (((double) rand() / RAND_MAX) < mutationRate)
        {
            child->dna[i] = generateChar();
        }
    }
}

//Takes two parents and returns a child with crossed and mutated dna
Agent *reproduce(Agent *parent1, Agent *parent2, size_t targetLen, double mutationRate)
{
    Agent *child = malloc(sizeof(Agent) + (sizeof(char) * targetLen));

    crossover(child, parent1, parent2, targetLen);
    mutate(child, targetLen, mutationRate);

    return child;
}

//Returns an array of agents that are children of the array passed in
Agent **evolve(Agent **agents, int population, size_t targetLen, double mutationRate)
{
    Agent **evolvedAgents = malloc((sizeof(Agent) + (sizeof(char) * targetLen)) * population);

    for (int i = 0; i < population; i++)
    {
        Agent *parent1 = weightedSelect(agents, population);
        Agent *parent2 = weightedSelect(agents, population);
        while(parent1 == parent2) {
            parent1 = weightedSelect(agents, population);
            parent2 = weightedSelect(agents, population);
        }
        evolvedAgents[i] = reproduce(parent1, parent2, targetLen, mutationRate);
    }

    free(agents);
    return evolvedAgents;
}

//Loops through `agents` and checks if any has a fitness of 100
int checkFinished(Agent **agents, int population)
{
    for(int i = 0; i < population; i++)
    {
        if(agents[i]->fitness == 100.0)
        {
            return 1;
        }
    }
    return 0;
}