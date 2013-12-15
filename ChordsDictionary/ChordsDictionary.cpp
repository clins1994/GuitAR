#include <iostream>
#include <cstring>
#include <string>
#include "Chord.hpp"
#include "pugixml.hpp"

using namespace std;

int main()
{
    string chord_str;
    cout << ("Qual o acorde? ");
    getline(cin, chord_str);

    // Check if chord is valid
    if (chord_str[0] < 'A' || chord_str[0] > 'G')
    {
        cout << "Chord entered is invalid!" << endl;
        return -1;
    }

    // Load file
    string path = "db/";
    path.append(chord_str, 0, 1);
    path.append(".xml");
    pugi::xml_document doc;
    if (!doc.load_file(path.c_str(), ~pugi::parse_minimal))
    {
        cout << "Can't open file!" << endl;
        return -1;
    }

    pugi::xml_node chords = doc.child("Chords");
    pugi::xml_node chord;
    for (chord = chords.child("Chord"); chord; chord = chord.next_sibling("Chord"))
    {
        string aux = chord.text().get();
        unsigned found = aux.find(" or ");
        unsigned size = strlen(chord.text().get());
        if (aux.compare(chord_str) == 0)
        {
            break;
        }
        else if (found != string::npos)
        {
            if (chord_str.compare(aux.substr(found + 4, size - found - 4)) == 0)
                break;

            if (chord_str.compare(aux.substr(0, found)) == 0)
                break;
        }
    }

    if (chord != NULL)
    {
        cout << chord.text().get() << endl;
        for (pugi::xml_attribute attr = chord.child("Strings").first_attribute(); attr; attr = attr.next_attribute())
        {
            cout << attr.name() << " |---";
            if (strcmp(attr.value(), "-1") == 0)
                cout << "-";
            else
                cout << attr.value();
            cout << "---|" << endl;
        }
    }
}
