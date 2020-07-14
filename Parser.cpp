#include "Parser.h"
#include "Parser.h"
#include <fstream>
#include <string>
#include "Logger.h"

void Parser::parseLine(string& line, int lineNumber)
{
    line = clearLine(line);

    if (line.size() > 0) {

        // this line is a comment
        if (line[0] == '|')
            return;
        // number of tokens read from source file
        int _token = 0;
        
        // beggining and end of a token
        int _tokenStart = 0;
        int _tokenEnd = 0;

        string _pid;
        string _arrivalTime;
        string _burstTime;

        // this could be _pid, _arrivalTime or _burstTime depending on how many tokens have been found
        string* _dest = &_pid;

        // split by ; and extact pid, arrivalTile and burst time 
        for (int i = 0; i < line.size(); i++) {

            // only 3 tokens are allowed
            if (_token > 2) {
                log(string("Error on line ") + to_string(lineNumber), 2);
                log("Invalid Line", 2);
                return;
            }

            // the end of a token is detected
            if (line[i] == ';') {
                string token = line.substr(_tokenStart, _tokenEnd - _tokenStart);
                *_dest = token;
                _tokenStart = i + 1;
                _tokenEnd = i + 1;
                _token++;

                // select destination
                switch (_token)
                {
                case 0:
                    _dest = &_pid;
                    break;
                case 1:
                    _dest = &_arrivalTime;
                    break;
                case 2:
                    _dest = &_burstTime;
                    break;
                default:
                    log(string("Error on line ") + to_string(lineNumber), 2);
                    log("Invalid Token", 2);
                    return;
                }

            }
            else {
                _tokenEnd++;
            }
        }

        if (_token != 2) {
            log(string("Error on line ") + to_string(lineNumber), 2);
            log("Invalid line, exactly 3 tokens expected", 2);
            return;
        }

        // tokenize the last part
        *_dest = line.substr(_tokenStart, _tokenEnd - _tokenStart);

        _contexts.emplace_back(_pid, _arrivalTime, _burstTime);

    } else {
        log("emtpy line", 1);
    }
}

string Parser::clearLine(string& line)
{
    char clearChars[] = { '\n','\t' , ' ' };
    
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
        int lineNumber = 0;
        int _lineStart = 0;
        int _lineEnd = 0;

        for (int i = 0; i < _fileData.size() ; i++) {
            if (_fileData[i] == '\n') {
                lineNumber++;
                _lineEnd = i;
                _line = _fileData.substr(_lineStart, _lineEnd - _lineStart + 1);

                parseLine(_line, lineNumber);

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
