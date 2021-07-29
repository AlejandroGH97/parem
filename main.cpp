#include <iostream>
#include <vector>
#include <fstream>
#include <omp.h>
#include <math.h>

#include "PaREM.h"

using namespace std;

int main(int argc, char** argv) {

    if (argc != 2) {
        cout << "{NTHR} argument missing.\n";
        return 0;
    }

    int nthr = atoi(argv[1]);

    omp_set_num_threads(nthr);

    DFA dfa("Automata.txt");

    //cout << PaREM(dfa, "pareparaplaparepaparallelraplaraplapapareparaplpplaraparraraparallelapareparaplapareparaplaraplapapareparapa", nthr, RegexMatch) << "\n";
    //return 0;

    cout << "finished dfa.\n";

    // dfa.print_all();
    
    string T;
    //cout << "finished parem.\n";

    ifstream file("inputs.txt");
    ofstream results("results.txt");
    int thread_num_tests[] = {2,4,8,16};
    double start, end, total = 0.0;

    for(int i = 0; i < 4; i++) {

        cout<<"INPUT "<<i<<endl;
        getline(file,T);
        results<<100*pow(10,i)<<'\n';

        for(int j = 0; j < 4; j++) {

            cout<<thread_num_tests[j]<<" THREADS"<<endl;
            results<<thread_num_tests[j]<<" threads: ";
            omp_set_num_threads(thread_num_tests[j]);

            for(int k = 0; k < 10; k++){
                start = omp_get_wtime();
                // RegexMatch o AutomatonMatch
                PaREM(dfa, T, thread_num_tests[j], RegexMatch);
                end = omp_get_wtime();
                total += (end - start)*1000000;
            }
            
            total /= 10;
            
            results<<total<<" µs\n";
            total = 0.0;
        }
    }

    // if (PaREM(dfa, T, thread_num_tests[j])) cout << "posible";
    // else cout << "imposible";
    
    
    return 0;
}
