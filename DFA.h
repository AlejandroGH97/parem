#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

class DFA {

    typedef vector<string> vs;
    typedef vector<int> vi;
    typedef unordered_map<string, int> umapsi;
    
public:

    vi Q;
    vs Alphabet;
    string q0;
    vi F;
    vector<umapsi> Tt;

    DFA(string file_name) {
        read(file_name);
    }

    bool belongs_to_Q(int qi, char s) {
        return find(Q.begin(), Q.end(), Tt[qi][string(1, s)]) != Q.end();
    }

    bool belongs_to_F(int qi) {
        return find(F.begin(), F.end(), qi) != F.end();
    }

    void print_all() {
        cout << "Q: " << endl;
        for (auto e : Q) cout << e << " ";
        cout << endl << endl;
        cout << "Alphabet: " << endl;
        for (auto e : Alphabet) cout << e << " ";
        cout << endl << endl;
        cout << "q0: " << endl << q0 << endl << endl;
        cout << "F: " << endl;
        for (auto e : F) cout << e << " ";
        cout << endl << endl;
        cout << "Tt: " << endl;
        int j = 0;
        for (auto m : Tt) {
            cout << j << " ";
            for (auto e : m) cout << e.first << " " << e.second << ", ";
            cout << endl;
            j++;
        }
    }

private:

    void read(string file_name) {
        ifstream file(file_name);

        if (file) {
            string file_Q;
            string file_Alphabet;
            string file_F;
            string transiciones;
            string basura;

            getline(file, file_Q);
            Q = split_int(file_Q, " ");
            getline(file, file_Alphabet);
            Alphabet = split(file_Alphabet, " ");
            getline(file, q0);
            getline(file, file_F);
            F = split_int(file_F, " ");
            getline(file, basura);

            while (getline(file, transiciones)) {
                vector<int> t = split_int(transiciones, " ");
                umapsi m;
                int i = 1;
                for (auto& c : Alphabet) {
                    m[c] = t[i];
                    i++;
                }
                Tt.push_back(m);
            }

            file.close();
        } else {
            cout << "couldnt open file\n";
        }
    }

    vector<string> split(string s, string delim) {
        vector<string> vec;
        size_t pos = 0;
        string token;
        while ((pos = s.find(delim)) != string::npos) {
            token = s.substr(0, pos);
            vec.push_back(token);
            s.erase(0, pos + delim.length());
        }
        vec.push_back(s);
        return vec;
    }

    vector<int> split_int(string s, string delim) {
        vector<int> vec;
        size_t pos = 0;
        string token;
        while ((pos = s.find(delim)) != string::npos) {
            token = s.substr(0, pos);
            vec.push_back(stoi(token));
            s.erase(0, pos + delim.length());
        }
        vec.push_back(stoi(s));
        return vec;
    }

};