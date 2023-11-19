// Author : Darshan Mahajan
#include <bits/stdc++.h>
using namespace std;

vector<string> getWords(string line)
{
    istringstream iss(line);
    vector<string> allWords;
    string word;
    while (iss >> word)
    {
        allWords.push_back(word);
    }
    return allWords;
}

void nestedCall(string line, string macroName, map<int, pair<string, string>> kpTabMap, map<string, bool> macroNameMap,fstream& mac)
{
    vector<string> allWords = getWords(line);
    
    fstream mnt("mnt.txt");
    fstream mdt("mdt.txt");
    
    string buffer;
    while (getline(mnt, buffer))
    {
        vector<string> mntLine = getWords(line);

        if (mntLine[0] == macroName)
        {
            vector<string> aptab;
            int tot_pp = stoi(mntLine[1]);
            int tot_kp = stoi(mntLine[2]);
            int mdtPtr = stoi(mntLine[3]);
            int kpdPtr = stoi(mntLine[4]);
            for (int i = 1; i < allWords.size(); i++)
            {
                pair<string, string> p;
                bool isKeywordPara = false;
                int j;
                string para = "";
                for (j = 0; j < allWords[i].size(); j++)
                {
                    if (allWords[i][j] == ',')
                    {
                        aptab.push_back(para);
                        break;
                    }
                    if (allWords[i][j] == '=')
                    {
                        reverse(para.begin(), para.end());
                        para.pop_back();
                        reverse(para.begin(), para.end());
                        p.first = para;
                        para.clear();
                        isKeywordPara = true;
                        break;
                    }
                    para += allWords[i][j];
                }
                if (isKeywordPara)
                {
                    j++;
                    for (; j < allWords[i].size(); j++)
                    {
                        para += allWords[i][j];
                    }
                    p.second = para;
                    aptab.push_back(para);
                }
            }

            for (int i = kpdPtr; i < kpdPtr + tot_kp; i++)
            {
                if (aptab.size() != tot_kp + tot_pp)
                {
                    aptab.push_back(kpTabMap[i].second);
                }
            }

            mdt.seekg(0, ios::beg);

            for (int i = 0; i < mdtPtr - 1; ++i)
            {
                if (!getline(mdt, buffer))
                {
                    cerr << "Error: mdtPtr exceeds the number of lines in the file." << endl;
                    return;
                }
            }

            while (getline(mdt, buffer))
            {
                istringstream bufStream(buffer);
                string bufWord;
                if (bufStream >> bufWord)
                {
                    if (bufWord != "MEND")
                        mac << bufWord << "\t";
                    if (bufWord == "MEND") break;
                }
                for (int i = 0; i < buffer.length(); i++)
                {
                    if (buffer[i] >= '0' and buffer[i] <= '9')
                    {
                        mac << aptab[(buffer[i] - '0') - 1] << "\t";
                    }
                }
                mac << endl;
            }
            cout << endl;
        }
    }
}

void processMacroPass2(const string &inputFile)
{
    fstream infile(inputFile);
    fstream mac("machine.txt", ios::out); // Open 'mac' file for writing
    fstream mnt("mnt.txt");
    fstream mdt("mdt.txt");
    fstream kpdt("kpdt.txt");

    string line;
    int startKpPtr = 0, endKpPtr = 0;
    map<int, pair<string, string>> kpTabMap;
    map<string, bool> macroNameMap;
    while (getline(mnt, line))
    {
        istringstream iss(line);
        string macro;
        if (iss >> macro)
        {
            macroNameMap[macro] = true;
        }
    }

    while (getline(kpdt, line))
    {
        vector<string> allWords = getWords(line);
        if (startKpPtr == 0)
            startKpPtr = stoi(allWords[0]);
        kpTabMap[stoi(allWords[0])] = {allWords[1], allWords[2]};
        endKpPtr = stoi(allWords[0]);
    }

    bool isMacro = false;
    while (getline(infile, line))
    {
        vector<string> allWords = getWords(line);
        if (allWords[0] == "MACRO")
        {
            // Dont Print the Macro in machine code
            isMacro = true;
            continue;
        }

        if (allWords[0] == "MEND")
        {
            isMacro = false;
            continue;
        }

        if (isMacro)
            continue;

        // Expand everything in between
        string macroName = allWords[0];
        bool isMacroCall = false;

        // Reset the file pointer to the beginning of MNT file
        mnt.clear(); // Clear any error flags
        mnt.seekg(0, ios::beg);

        string buffer;
        while (getline(mnt, buffer))
        {
            vector<string> mntLine = getWords(buffer);
            if (mntLine[0] == macroName)
            {
                vector<string> aptab;
                int tot_pp = stoi(mntLine[1]);
                int tot_kp = stoi(mntLine[2]);
                int mdtPtr = stoi(mntLine[3]);
                int kpdPtr = stoi(mntLine[4]);
                for (int i = 1; i < allWords.size(); i++)
                {
                    pair<string, string> p;
                    bool isKeywordPara = false;
                    int j;
                    string para = "";
                    for (j = 0; j < allWords[i].size(); j++)
                    {
                        if (allWords[i][j] == ',')
                        {
                            aptab.push_back(para);
                            break;
                        }
                        if (allWords[i][j] == '=')
                        {
                            reverse(para.begin(), para.end());
                            para.pop_back();
                            reverse(para.begin(), para.end());
                            p.first = para;
                            para.clear();
                            isKeywordPara = true;
                            break;
                        }
                        para += allWords[i][j];
                    }
                    if (isKeywordPara)
                    {
                        j++;
                        for (; j < allWords[i].size(); j++)
                        {
                            para += allWords[i][j];
                        }
                        p.second = para;
                        aptab.push_back(para);
                    }
                }

                for (int i = kpdPtr; i < kpdPtr + tot_kp; i++)
                {
                    if (aptab.size() != tot_kp + tot_pp)
                    {
                        aptab.push_back(kpTabMap[i].second);
                    }
                }

                mdt.seekg(0, ios::beg);

                for (int i = 0; i < mdtPtr - 1; ++i)
                {
                    if (!getline(mdt, buffer))
                    {
                        cerr << "Error: mdtPtr exceeds the number of lines in the file." << endl;
                        return;
                    }
                }

                while (getline(mdt, buffer))
                {
                    istringstream bufStream(buffer);
                    string bufWord;
                    if (bufStream >> bufWord)
                    {
                        if (macroNameMap[bufWord] == true)
                        {
                            nestedCall(buffer, bufWord, kpTabMap, macroNameMap, mac);
                            continue;
                        }

                        if (bufWord != "MEND")
                            mac << bufWord << "\t";
                        if (bufWord == "MEND") break;
                    }
                    for (int i = 0; i < buffer.length(); i++)
                    {
                        if (buffer[i] >= '0' and buffer[i] <= '9')
                        {
                            mac << aptab[(buffer[i] - '0') - 1] << "\t";
                        }
                    }
                    mac << endl;
                }
                cout << endl;
                isMacroCall = true;
            }
        }

        if (!isMacroCall)
        {
            mac << line << endl; // Write the line to 'mac' file
        }
    }

    // Close the 'mac' file
    mac.close();
}

int main()
{
    processMacroPass2("input.txt");
    return 0;
}