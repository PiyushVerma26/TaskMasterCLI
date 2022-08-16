#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
using namespace std;

//   ****************************** Function Calling **************************

// Help Function Which Show Usage Of The Task

void help()
{
    string a = "Usage :-\n$ ./task add 2 hello world    # Add a new item with priority 2 and text \"hello world\" to the list\n$ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order\n$ ./task del INDEX            # Delete the incomplete item with the given index\n$ ./task done INDEX           # Mark the incomplete item with the given index as complete\n$ ./task help                 # Show usage\n$ ./task report               # Statistics";
    cout << a << endl;
}
// ---------------------------------Adding And Sorting Function------------------

// Sorting And Adding Tasking In File Through Multimap

void strtime(multimap<string, int> &M)
{

    multimap<int, string> MM;

    for (auto &it : M)
    {
        // MM.insert({it.second,it.first});
        MM.insert(pair<int, string>(it.second, it.first));
    }

    // printing elements in file using file handling
    string filename("task.txt");
    ofstream file_out;
    file_out.open(filename);
    for (auto &it : MM)
    {

        file_out << to_string(it.first) << " " << it.second << endl;
    }
}

// Taking Input From Command And BreakIng Arguments Into Integer And String
void add(int argc, char *argv[])
{
    // Creating Multimap Object
    multimap<string, int> MulM;


    // Breaking Arguments
    string priority = "";

    string text = "";
    int i;
    for (i = 2; i < argc; i++)
    {
        if (i == 2)
        {
            priority.append(argv[i]);
        }
        if (i > 2)
        {
            text.append(argv[i]);
        }

        if (i != 2 && i < argc - 1)
        {
            text.append(" ");
        }
    }
    string str = "Added task: \"" + text + "\" with priority " + priority;
    cout << str << endl;
    // Converting String Into Integer Through Stringstream
    stringstream SS;
    int a;
    SS << priority;
    SS >> a;
    // Inserting Arguments Into Multimap 
    MulM.insert(pair<string, int>(text, a));

    // Reading Data Fron File 

    ifstream infile;
    infile.open("task.txt");
    if (!infile)
    {
    }
    else
    {

        int x;
        for (string line; infile >> x;)
        {

            infile.get(); // ignore space

            getline(infile, line);

            MulM.insert(pair<string, int>(line, x));
        }
    }
// After Reading Data From File Calling Sort Function For Sorting
    strtime(MulM);
}

// -----------------Function(ls) For Showing Data As Index ,Task And [Priority]----------------------------
void listprio()
{
    multimap<int, string> MulMp;
    ifstream infile;
    infile.open("task.txt");
    // Checking File If It Exist Or Not
    if (!infile)
    {
        cout << "There are no pending tasks!";
    }
    else
    {
        int y;
        for (string linepara; infile >> y;)
        {

            infile.get(); // ignore space

            getline(infile, linepara);

            MulMp.insert(pair<int, string>(y, linepara));
        }
    }
    // Printing Sorted Data With Index ,Task And Priority
    int index = 1;
    for (auto &it : MulMp)
    {

        cout << index << ". " << it.second << " "
             << "[" << it.first << "]" << endl;
        index++;
    }
}

// -------------------------------Function For Deleting Task From File----------------------------------------
int delete_task(int argc, char *argv[])
{
    // Showing Error Message
    if (argv[2] == NULL)
    {
        cout << "Error: Missing NUMBER for deleting tasks.";
    }

    multimap<int, string> MullMp;
    ofstream ofs;
    // Creating Temporary file
    ofs.open("temp.txt", ios::app);
    ifstream infile;
    infile.open("task.txt");
    if (!infile)
    {
    }
    else
    {
        int y;
        for (string linepara; infile >> y;)
        {
            infile.get(); // ignore space
            getline(infile, linepara);
            MullMp.insert(pair<int, string>(y, linepara));
        }

        int index = 1;
        int p;
        stringstream NN;
        NN << argv[2];
        NN >> p;
        // Showing Error Message
        if (p > MullMp.size() || p == 0)
        {
            cout << "Error: task with index #" << argv[2] << " does not exist. Nothing deleted." << endl;
            return 0;
        }

        for (auto &it : MullMp)
        {
            if (index == p)
            {
            }
            // Copying Data From "task.txt" To "Temp.txt" (except which index no is match)
            else
            {
                ofs << to_string(it.first) << " " << it.second << endl;
            }
            index++;
        }
        // Showing Deleted Task Index
        cout << "Deleted task #" << argv[2]<<endl;
        infile.close();
        ofs.close();
        // Removing task.txt and renaming temp.txt as task.txt
        remove("task.txt");
        rename("temp.txt", "task.txt");
    }
    return 0;
}
// ------------------------------Function For Done Command-----------------------------------
int done(int argc, char *argv[])
{
    // Showing Error Message
    if (argv[2] == NULL)
    {
        cout << "Error: Missing NUMBER for marking tasks as done.";
        return 0;
    }

    multimap<int, string> MullMp;
    ofstream ofs;
    ofs.open("completed.txt", ios::app);
    ofstream outfile;
    outfile.open("temp.txt", ios::app);
    ifstream infile;
    infile.open("task.txt");
    if (!infile)
    {
    }
    else
    {
        int y;
        for (string linepara; infile >> y;)
        {

            infile.get(); // ignore space

            getline(infile, linepara);
            MullMp.insert(pair<int, string>(y, linepara));
        }

        int index = 1;
        int p;
        stringstream NN;
        NN << argv[2];
        NN >> p;
        // Showing Error Message When Given Index Is Not Available
        if (p > MullMp.size() || p == 0)
        {
            cout << "Error: no incomplete item with index #" << argv[2] << " exists." << endl;
            return 0;
        }

        for (auto &it : MullMp)
        {
// Printing Done Data In Completed And Pending In Temp.txt
            if (index == p)
            {
                ofs << to_string(it.first) << " " << it.second << endl;
            }
            else
            {
                outfile << to_string(it.first) << " " << it.second << endl;
            }
            index++;
        }
        cout << "Marked item as done.";
        infile.close();
        ofs.close();
        outfile.close();
        // Removing task.txt and renaming temp.txt as task.txt
        remove("task.txt");
        rename("temp.txt", "task.txt");
    }
    return 0;
}
// ------------------------Functions(Report) For Showing Pending And Done Task---------------------------
// Function To Read Data From File "task.txt" To Show Pending Task 
void pendingTasksReport()
{
    multimap<int, string> MulMp;
    ifstream infile;
    infile.open("task.txt");
    if (!infile)
    {
        cout << "There are no pending tasks!";
    }
    else
    {
        int y;
        for (string linepara; infile >> y;)
        {

            infile.get(); // ignore space

            getline(infile, linepara);

            MulMp.insert(pair<int, string>(y, linepara));
        }
    }
    //Showing Pending Items
    cout << "Pending : " << MulMp.size() << "\n";
    int index = 1;
    for (auto &it : MulMp)
    {

        cout << index << ". " << it.second << " "
             << "[" << it.first << "]"
             << "\n"
             << endl;
        index++;
    }
}
// Function To Read Data From File "completed.txt" To Show Completed task
void taskcomplete()
{
    multimap<int, string> MulMp;
    ifstream infile;
    infile.open("completed.txt");
    if (!infile)
    {
        cout << "There are no pending tasks!";
    }
    else
    {
        int y;
        for (string linepara; infile >> y;)
        {

            infile.get(); // ignore space

            getline(infile, linepara);

            MulMp.insert(pair<int, string>(y, linepara));
        }
    }

    // Printing Completd Task On Terminal
    cout << "Completed : " << MulMp.size() << endl;
    int index = 1;
    for (auto &it : MulMp)
    {

        cout << index << ". " << it.second << endl;
        index++;
    }
}
// Report Function Calling Pending Function And Completed Function
void report()
{
    pendingTasksReport();
    taskcomplete();
}


int main(int argc, char *argv[])
{
    // Initial Check
    if (argc == 1)
    {
        help();
        return 0;
    }
// Taking Argv[1] VAlue In Para
    string para = argv[1];

    // Calling Help Function To  Show Usage
    if (para == "help")
    {
        help();
    }

    //  Calling Multiple Task AddIng Function

    if (para == "add")
    {
        if (argv[2] == NULL)
        {
            cout << "Error: Missing tasks string. Nothing added!";
            return 0;
        }
        add(argc, argv);
    }

    //  Calling Priority Based List Function

    if (para == "ls")
    {
        listprio();
    }

    // Calling Delete Function Through Index

    if (para == "del")
    {
        delete_task(argc, argv);
    }

    // Calling Done function

    if (para == "done")
    {
        done(argc, argv);
    }

    // Calling Report Function Which Show Pending Item And Done Item List
    if (para == "report")
    {
        report();
    }

    return 0;
}
