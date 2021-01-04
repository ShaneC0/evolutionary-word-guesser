#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    double fitness;
    size_t dnaLen;
    char dna[];
} Agent;

void printAgents(Agent **agents, int population)
{
    for (int i = 0; i < population; i++)
    {
        printf("Fitness: %f\tDNA: %s\n", agents[i]->fitness, agents[i]->dna);
    }
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

    for (int i = 0; i < population; i++)
    {
        agents[i] = generateAgent(targetLen);
    }

    return agents;
}

void sortAgentsByFitness(Agent **agents, int population);

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
