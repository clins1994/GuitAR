#ifndef CHORD_HPP
#define CHORD_HPP

#include <string>
using namespace std;

class Chord
{
    public:
        Chord(string name);
        string name;
        int * frets;

        void setFrets(int e, int B, int G, int D, int A, int E);
};

#endif
