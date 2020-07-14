#include "Parser.h"
#include "Parser.h"
#include <fstream>
#include <string>

Parser::Parser(string fileName)
{
    _fileName = fileName;

    // load the file 

}

vector<Context>& Parser::getContexts()
{
    return _contexts;
}

string Parser::readFile(string fileName)
{
    // read a file as string
    ifstream handle = ifstream(fileName);
    string data = "";

    if (handle.is_open()) {
        string line;
        while (getline(handle, line)) {
            data += line + '\n';
        }

        return data;
    }
    else {
        cout << "Could not open file " << fileName << endl;
        return string();
    }
}
