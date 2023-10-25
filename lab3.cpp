#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>
#include <math.h>


#define SIZEPOP 2000
#define ITERATIONS 10000
#define PICKINGRATE 0.10f
#define MUTATIONRATE 0.25f
#define MUTATION RAND_MAX*MUTATIONRATE

#define GAGOAL   string("Мир")

using namespace std;

struct creature {
    string str;
    unsigned int fitness;
};
typedef vector<creature> crt_vector;

void initPopulation(crt_vector& population, crt_vector& buffer) {
    int sizeg = GAGOAL.size();
    for (int i = 0; i < SIZEPOP; i++)
    {
        creature crt;
        crt.fitness = 0;
        crt.str.erase();

        for (int j = 0; j < sizeg; j++)
        {
            crt.str+= (rand() % 255) + 33;
        }
        population.push_back(crt);

    }
    buffer.resize(SIZEPOP);
    
};

void InitFitness(crt_vector& population) {
    string goal = GAGOAL;
    int sizeg = goal.size();
    unsigned int fitness;
    for (int i = 0; i < SIZEPOP; i++)
    {
        fitness = 0;
        for (int j = 0; j < sizeg; j++)
        {
            fitness += abs(int(population[i].str[j] - goal[j]));

        }
        population[i].fitness = fitness;
    }
}

bool fitness_sort(creature& x, creature& y)
{
    return (x.fitness < y.fitness);
}

void sortbyFit(crt_vector& population) {
    sort(population.begin(), population.end(), fitness_sort);
}

void mutate(creature& crt) {
    int sizeg = GAGOAL.size();
    int pos = rand() % sizeg;
    char symbol= (rand() % 255) + 33;

    crt.str[pos] = symbol;
}
void picking(crt_vector& population, crt_vector& buffer, int psize) {
    for ( int i = 0;  i < psize; i++)
    {
        buffer[i].str = population[i].str;
        buffer[i].fitness = population[i].fitness;
    }
}

void crossing(crt_vector& population, crt_vector& buffer) {
    int psize = SIZEPOP * PICKINGRATE;
    int sizeg = GAGOAL.size(), pos, i1, i2;

    picking(population, buffer, psize);

    for (int i = psize; i < SIZEPOP; i++)
    {
        pos = rand() % sizeg;
        i1 = rand() % psize;
        i2 = rand() % psize;

        buffer[i].str = population[i1].str.substr(0, pos) + population[i2].str.substr(pos, sizeg - pos);

        if (rand() < MUTATION) mutate(buffer[i]);

    }

}
void printBest(crt_vector& population) {
    cout << "Best: " << population[0].str << " (" << population[0].fitness << ")" << endl;

}
void swap(crt_vector*& population, crt_vector*& buffer) {
    crt_vector* t = population; population = buffer; buffer = t;
}


int main()
{
    srand(unsigned(time(NULL)));
    setlocale(LC_ALL, "russian");
    crt_vector population, buffer;
    initPopulation(population, buffer);
    for (int i = 0; i < ITERATIONS; i++)
    {
        InitFitness(population);
        sortbyFit(population);
        printBest(population);

        if (population[0].fitness == 0)break;
        crossing(population, buffer);

        swap(population, buffer);

    }
    return 0;
}

