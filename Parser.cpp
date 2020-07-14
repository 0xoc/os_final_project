#include "Parser.h"
#include "Parser.h"
#include <fstream>
#include <string>
#include "Logger.h"

void Parser::parseLine(string& line)
{
    line = clearLine(line);

    log(line);
}

string Parser::clearLine(string& line)
{
    char clearChars[3] = { '\n','\t' , ' ' };
    
    bool isSafe;

    string _cleardLine = "";

    for (int i = 0; i < line.size(); i++) {
        isSafe = true;

        for (int j = 0; j < sizeof(clearChars) / sizeof(char); j++) {
            if (line[i] == clearChars[j]) {
                isSafe = false;
                break;
            }
        }

        if (isSafe)
            _cleardLine += line[i];
    }

    return _cleardLine;

}

Parser::Parser(string fileName)
{
    _fileName = fileName;

    // load the file 
    string _fileData = readFile(_fileName);

    if (_fileData != string()) {
        // file read successfuly
        log("Parsing Context File");

        // split by line
        string _line = "";
        int _lineStart = 0;
        int _lineEnd = 0;

        for (int i = 0; i < _fileData.size() ; i++) {
            if (_fileData[i] == '\n') {
                _lineEnd = i;
                _line = _fileData.substr(_lineStart, _lineEnd - _lineStart + 1);

                parseLine(_line);

                _lineStart = i + 1;
                _lineEnd = i + 1;

                continue;
            }
        }
    }
    else {
        // faild to read file
    }

}

vector<Context>& Parser::getContexts()
{
    return _contexts;
}

string Parser::readFile(string& fileName)
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