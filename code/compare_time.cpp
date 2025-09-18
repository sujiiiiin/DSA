#include <cstdio>
#include <cstdlib>
int main()
{
    system("g++ rand_input.cpp -o rand_input");
    system("g++ check_input.cpp -o check_input");
    // system("g++ solution_1_cnttime.cpp -o solution_1_cnttime");
    system("g++ solution_2_cnttime.cpp -o solution_2_cnttime");
    system("g++ solution_3_cnttime.cpp -o solution_3_cnttime");
    while (1)
    {
        system("./rand_input > rand.in");
        // if (system("./check_input < rand.in") != 0)
        // {
        //     printf("invalid input!\n");
        //     break;
        // // }
        // system("./solution_1_cnttime < rand.in ");
        system("./solution_2_cnttime < rand.in ");
        system("./solution_3_cnttime < rand.in ");
    }
    return 0;
}