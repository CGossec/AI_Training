#include <bits/stdc++.h>
using namespace std;
#define ABS(A) (A) > 0 ? (A) : -(A)
#define POPULATION_SIZE 100
#define TARGET_SIZE 3
#define MUTATION_RATE 15 // 15 / 1000 => 1.5% chance of mutation
int target = 666;

double newGene()
{
    double Ox = rand() % 10;
    double OOx = rand() % 10;
    double OOOx = rand() % 1000;
    return ABS(OOOx);
}

int random_num(int start, int end)
{
    int random = rand() % end + start;
    return random;
}


class Individual
{
    public:
        int chromosome[TARGET_SIZE];
        int fitness;

        Individual()
        {
            int child_chrom[TARGET_SIZE] =
            {
                0
            };
            for (int i = 0; i < TARGET_SIZE; i++)
                child_chrom[i] = newGene();
            this->chromosome[0] = child_chrom[0];
            this->chromosome[1] = child_chrom[1];
            this->chromosome[2] = child_chrom[2];
            this->fitness = get_fitness();
        }

        Individual(int chro[TARGET_SIZE])
        {
            for (int i = 0; i < TARGET_SIZE; i++)
                this->chromosome[i] = chro[i];
            this->fitness = get_fitness();
        }

        Individual mate(Individual parent2)
        {
            int child_chrom[TARGET_SIZE] =
            {
                0
            };
            for (int i = 0; i < TARGET_SIZE; i++)
            {
                int tmp = rand() % 100;
                float choice = (float)tmp / 100;
                if (choice < 0.45)
                    child_chrom[i] = parent2.chromosome[i];
                else if (choice < 0.9)
                    child_chrom[i] = this->chromosome[i];
                else
                    mutate(i, child_chrom);
            }
            return Individual(child_chrom);
        }

    private:
        int get_fitness()
        {
            int res = 0;
            int good = 0;
            for (int i = 0; i < TARGET_SIZE; i++)
            {
                if (this->chromosome[i] <= 666)
                    good += 1;
                res += this->chromosome[i];
            }
            if (res > target || res < 0)
                return 999 - good;
            return 666 - res;
        }

        void mutate(int index, int *chrom)
        {
            /*int mutated = chrom[index];
            float choice = random_num(0, 100) / 100;
            if (choice)
                mutated += (chrom[index] * 15 / 100);
            else
                mutated -= (chrom[index] * 15 / 100);
            //if (rand() % 100 <= MUTATION_RATE)*/
                chrom[index] = rand() % 1000; //mutated;
        }
};

bool operator<(const Individual &ind1, const Individual &ind2)
{
    return ind1.fitness < ind2.fitness;
}

int main()
{
    srand(time(NULL));
    int generation = 0;
    vector<Individual> pop;
    bool found = false;
    for (int i = 0; i < POPULATION_SIZE; i++)
        pop.push_back(Individual());
    while (!found)
    {
        sort(pop.begin(), pop.end());
        if (pop[0].fitness <= 0)
        {
            found = true;
            break;
        }
        vector<Individual> new_gen;
        int tmp = 10 * POPULATION_SIZE / 100;
        /*for (int i = 0; i < tmp; i++)
        {
            new_gen.push_back(pop[i]);
        }*/
        for (int i = 0; i < POPULATION_SIZE/* - tmp*/; i++)
        {
            int r = random_num(0, 50);
            Individual parent1 = pop[r];
            r = random_num(0, 50);
            Individual parent2 = pop[r];
            Individual offspring = parent1.mate(parent2);
            new_gen.push_back(offspring);
        }
        cout << "Generation: " << generation << "\t";
        cout << "Chromosome: { " << pop[0].chromosome[0];
        cout << ", " << pop[0].chromosome[1];
        cout << ", " << pop[0].chromosome[2] << " }\t";
        cout << "Fitness: " << pop[0].fitness << endl;
        pop = new_gen;
        generation++;
    }
    cout << "Generation: " << generation << "\t";
    cout << "Chromosome: { " << pop[0].chromosome[0];
    cout << ", " << pop[0].chromosome[1];
    cout << ", " << pop[0].chromosome[2] << " }\t";
    cout << "Fitness: " << pop[0].fitness << endl;
}