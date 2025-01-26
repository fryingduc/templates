#include <bits/stdc++.h>
using namespace std;

const string NAME = "";     // problem name
const string TestType = "Themis";  // "CMS", "Themis"

const int NTEST = 10;           // number of tests

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int rand(int l, int r) {
    assert(l <= r);
    return uniform_int_distribution<int> (l, r)(rng);
}

void makeTest(ofstream &input, int testId){

}

int main(){
    for(int _ = 1; _ <= NTEST; _++){
        string id;          // id of current test
        stringstream ss;
        ss << _;
        ss >> id;
       // cerr << _ << ' '  << endl;
        cout << "Making test: " << id << endl;
        string input, output, program = NAME;

        if (TestType == "CMS")
            input  = NAME + "_" + id + ".in",
            output = NAME + "_" + id + ".out";
        else
            system(("MKDIR " + NAME + "\\Test" + id).c_str()),
            input  = NAME+"\\Test" + id + '\\' + NAME + ".INP",
            output = NAME+"\\Test" + id + '\\' + NAME + ".OUT";


        ofstream inputFile(input.c_str());

        // create input
        makeTest(inputFile, _);
        inputFile.close();

        // create output
        system(("a.exe < " + input + " > " + output).c_str());
    }
}
