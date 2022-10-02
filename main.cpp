#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
using std::cout; using std::cin; using std::string;

// written by chapel1337
// made from 9/31/2022 to 10/1/2022
// started on 9/31/2022 late at night with little to no motivation, didn't get much done
// finished today with (again) little to no motivation, took much longer than it should've to make
// my largest and most ambitious project yet™
// attempted to make this spread out into multiple files, but the linker was being very funny
// 557 lines
// run this as adminstrator for all features to work

std::ofstream output{};
std::ifstream input{};

string response{}; // string type to prevent invalid input spam

string fileDirectory{ "" };
string fileName{ "" };
string fileExtension{ "" };
string fileText{ "" };
string file{ "" };

bool correctionsEnabled{ false };

void mainMenu();
void invalidInput(string returnFunction);
void returnTo(string returnFunction);
void openTextFile();

void clear()
{
    system("cls");
}

void title(string title)
{
    std::system(("title " + title).c_str());
}

template <typename T>
void sleep(T time)
{
    Sleep(time * 1000);
}

void displayCredits()
{
    std::system("title c++ notepad");

    cout << "c++ notepad\n";
    cout << "written by chapel1337\n";
}

int wordCount()
{
    std::ifstream input{ file };
    int wordCount{};

    string fileLine{};

    while (getline(input, fileLine))
    {
        for (int i{ 0 }; i < fileLine.length(); i++)
        {
            if (fileLine[i] == ' ' && i != 1)
            {
                wordCount++;
            }
            if (fileLine[i] == 1 && i == ' ')
            {
                continue;
            }
        }
    }
    input.close();

    return wordCount;
}

int letterCount()
{
    std::ifstream input{ file };
    int letterCount{};

    string fileLine{};

    while (getline(input, fileLine))
    {
        for (int i{ 0 }; i < fileLine.length(); i++)
        {
            letterCount++;
        }
    }
    input.close();

    return letterCount;
}

int punctuationCount()
{
    std::ifstream input{ file };
    int punctuationCount{};

    string fileLine{};

    while (getline(input, fileLine))
    {
        for (int i{ 0 }; i < fileLine.length(); i++)
        {
            switch (fileLine[i])
            {
            case '?':
            case '.':
            case ',':
            case ';':
            case ':':
            case '"':
            case '\'':
            case '-':
            case '_':
            case '[':
            case ']':
            case '{':
            case '}':
            case '...':
            case '!':
                punctuationCount++;
            break;
            }
        }
    }
    input.close();

    return punctuationCount;
}

int vowelCount()
{
    std::ifstream input{ file };
    int vowelCount{};

    string fileLine{};

    while (getline(input, fileLine))
    {
        for (int i{ 0 }; i < fileLine.length(); i++)
        {
            switch (fileLine[i])
            {
                case 'A':
                case 'a':
                case 'E':
                case 'e':
                case 'I':
                case 'i':
                case 'O':
                case 'o':
                case 'U':
                case 'u':
                case 'y':
                case 'Y':
                    vowelCount++;
                break;
            }
        }
    }
    input.close();

    return vowelCount;
}

void textViewer();

void displayStatistics()
{
    clear();

    cout << "word count: " << wordCount() << '\n';
    cout << "letter count: " << letterCount() << '\n';
    cout << "punctuation count: " << punctuationCount() << '\n';
    cout << "vowel count: " << vowelCount() << '\n';

    // scary one line if statement
    if (correctionsEnabled) cout << "corrections: enabled\n\n";
    else cout << "corrections: disabled\n\n";

    textViewer();
}

void textViewer()
{
    std::ifstream input{ file };
    string fileLine = "";

    if (correctionsEnabled)
    {
        while (getline(input, fileLine))
        {
            for (int i{ 0 }; i < fileLine.length(); i++)
            {
                /*
                if (fileLine[i] == '.' && fileLine[i + 1] != ' ')
                {
                    cout << fileLine << '\n';

                    char fileLineArray[100] {};
                    for (int i{ 0 }; i < fileLine.length(); i++)
                    {
                        if (fileLine[i] == '.' && fileLine[i + 1] != ' ')
                        {
                            fileLineArray[i + 1] = ' ';
                            fileLine[i + 1] += fileLineArray[i];
                        }
                        else
                        {
                            fileLine[i] += fileLineArray[i];
                        }
                    }

                    for (int i{ 0 }; i < sizeof(fileLineArray) / sizeof(fileLineArray[0]); i++)
                    {
                        fileLine[i] = fileLineArray[i];
                    }

                    string firstHalf{ fileLine.substr(0, fileLine[i]) };
                    string secondHalf{ fileLine.substr(fileLine[i], fileLine.length() + 1) };
                    fileLine = firstHalf + ' ' + secondHalf;
                    */

                // switch statements do not support &&, so i have to resort to if statement spam
                if (fileLine[i] == '.' && fileLine[i + 1] == ' ')
                {
                    fileLine[i + 2] = toupper(fileLine[i + 2]);
                }
                if (fileLine[i] == '!' && fileLine[i + 1] == ' ')
                {
                    fileLine[i + 2] = toupper(fileLine[i + 2]);
                }
                if (fileLine[i] == '?' && fileLine[i + 1] == ' ')
                {
                    fileLine[i + 2] = toupper(fileLine[i + 2]);
                }
                if (fileLine[i] == '.' && fileLine[i + 1] == ' ')
                {
                    fileLine[i + 2] = toupper(fileLine[i + 2]);
                }
                if (fileLine[i] == fileLine[0] && fileLine != " ")
                {
                    fileLine[i] = toupper(fileLine[i]);
                }
            }

            cout << fileLine << '\n';
        }
    }
    else
    {
        while (getline(input, fileLine))
        {
            cout << fileLine << '\n';
        }
    }

    input.close();

    getline(cin, response);

    if (response == "exit" || response == "back")
    {
        file = "";
        fileDirectory = "";
        fileName = "";
        fileText = "";
        fileExtension = "";

        returnTo("managerMenu");
    }
    else if (response == "corrections" || response == "correct")
    {
        if (correctionsEnabled) correctionsEnabled = false;
        else correctionsEnabled = true;

        displayStatistics();
    }
    else
    {
        displayStatistics();
    }

    response = "";
}

void openTextHandler()
{
    clear();

    if (file == "")
    {
        openTextFile();
    }
    else
    {
        clear();
        title("text analyzer");

        clear();
        
        cout << "press enter to update statistics\n";
        cout << "input exit/back to go back\n";
        cout << "input correct/corrections to toggle corrections\n";

        sleep(2);
        clear();
        
        textViewer();
    }
}

void createTextFile()
{
    clear();
    title("create text file");

    cout << "remember to include the drive name (C:\\)\n";
    cout << "where should your text file be located?\n";
    getline(cin, fileDirectory);

    fileDirectory += '\\';

    clear();

    cout << "name your text file: \n";
    getline(cin, fileName);

    clear();

    cout << "name your file extension: \n";
    getline(cin, fileExtension);

    clear();

    cout << "input text: \n";
    getline(cin, fileText);

    clear();

    file = fileName + '.' + fileExtension;

    output.open(fileDirectory + file);
    output << fileText;
    output.close();

    cout << "created text file " << file << ", contents are: " << fileText << '\n';

    fileName = "";
    fileDirectory = "";
    fileText = "";
    file = "";

    sleep(2);
    returnTo("managerMenu");
}

void openTextFile()
{
    clear();
    title("open text file");

    cout << "remember to include the drive name (C:\\)\n";
    cout << "input directory where the text file is located: \n";
    getline(cin, fileDirectory);

    clear();

    cout << "input text file name: \n";
    getline(cin, fileName);

    clear();

    cout << "input text file extension: \n";
    getline(cin, fileExtension);

    clear();

    for (int i{ 0 }; i < fileDirectory.length(); i++)
    {
        if (fileDirectory[i] == '/') // to combat the user's ignorance
        {
            fileDirectory[i] = '\\';
        }
    }

    fileDirectory += "\\";
    file = fileDirectory + fileName + '.' + fileExtension;

    openTextHandler();
}

void deleteTextFile()
{
    clear();
    title("delete text file");

    cout << "remember to include the drive name (C:\\)\n";
    cout << "input directory where the text file is located: \n";
    getline(cin, fileDirectory);

    clear();

    cout << "input text file name: \n";
    getline(cin, fileName);

    clear();

    cout << "input text file extension: \n";
    getline(cin, fileExtension);

    clear();

    for (int i{ 0 }; i < fileDirectory.length(); i++)
    {
        if (fileDirectory[i] == '/') // to combat the user's ignorance (x2)
        {
            fileDirectory[i] = '\\';
        }  
    }

    fileDirectory += "\\";
    file = fileDirectory + fileName + '.' + fileExtension;

    std::system(("del " + file).c_str());

    clear();
    cout << fileName << " deleted in " << fileDirectory;

    fileName = "";
    fileDirectory = "";
    fileExtension = "";
    file = "";

    sleep(2);
    returnTo("managerMenu");
}

void managerMenuHandler()
{
    if (response == "1")
    {
        createTextFile();
    }
    else if (response == "2")
    {
        openTextFile();
    }
    else if (response == "3")
    {
        deleteTextFile();
    }
    else if (response == "4")
    {
        mainMenu();
    }
    else
    {
        invalidInput("managerMenu");
    }
    response = "";
}

void managerMenu()
{
    clear();
    title("text file manager menu");

    cout << "1. create text file\n";
    cout << "2. open text file\n";
    cout << "3. delete text file\n";
    cout << "4. back\n";
    getline(cin, response);

    managerMenuHandler();
}

void exit()
{
    clear();

    for (int i{ 3 }; i >= 1; i--)
    {
        sleep(1);
        clear();

        cout << "okay, exiting in " << i;
    }

    sleep(1);
    _exit(1);
}

void menuResponseHandler()
{
    if (response == "1")
    {
        openTextHandler();
    }
    else if (response == "2")
    {
        managerMenu();
    }
    else if (response == "3")
    {
        exit();
    }
    else
    {
        invalidInput("mainMenu");
    }
    response = "";
}

void mainMenu()
{
    clear();
    title("main menu");

    cout << "1. text file analyzer \n";
    cout << "2. text file manager \n";
    cout << "3. exit\n";
    getline(cin, response);

    menuResponseHandler();
}

void invalidInput(string returnFunction)
{
    clear();
    cout << "invalid input\n";

    sleep(2);
    returnTo(returnFunction);
}

void returnTo(string returnFunction)
{
    if (returnFunction == "mainMenu")
    {
        mainMenu();
    }
    else if (returnFunction == "managerMenu")
    {
        managerMenu();
    }
}

int main()
{
    displayCredits();

    sleep(2);
    clear();

    mainMenu();
}