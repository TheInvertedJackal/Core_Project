#include <iostream>
#include <filesystem>
#include <fstream>
#include <conio.h>
#include <windows.h>

using namespace std;
using namespace std::filesystem;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER '\r'

void set_cursor(int,int);
void print_selection(int, string*, int);
int make_a_selection(string*, int, int);
COORD get_current_cursor(HANDLE hConsoleOutput);

const int SELECTION_COUNT = 4;

/*
    Structure:
    Jump into cmd
    Loadable .bat files from folder
    Add new .bat files via file loader
    Jump into coding projects [All coding projects => files]                    
*/

int main(){

    path saved_dirs = "dirs.txt";

    path fast_launch_dir;

    path programming_projects_dir;

    if(exists(saved_dirs)){
        ifstream dirs_file(saved_dirs);
        string temp;
        dirs_file >> temp;
        if(dirs_file){
            fast_launch_dir = temp;
            cout << fast_launch_dir.parent_path() << endl;
        }
        dirs_file >> temp;
        if(dirs_file){
            programming_projects_dir = temp;
            cout << programming_projects_dir.parent_path() << endl;
        }
        dirs_file.close();
    }

    string * selections = new string[SELECTION_COUNT]{
        "CMD",
        "Fast Launch",
        "Programming Projects",
        "Exit"
    };
    int selected = make_a_selection(selections, SELECTION_COUNT, -1);
    switch (selected)
    {
    case 0:
        system("start cmd");
        break;
    case 1:
        break;
    case 2:
        break;
    default:
        cout << "Bye." << endl;
        break;
    }
    delete[] selections;
    return 0;
}

int make_a_selection(string* selections, int count, int back_out){
    HANDLE handle;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD og_pos = get_current_cursor(handle);

    int selected = 0;
    bool selecting = true;
    char c;

    print_selection(0, selections, count);
    set_cursor(2, og_pos.Y);
    while (selecting){
        switch ((c = _getch())){
            case KEY_UP:
                if(selected > 0){
                    --selected;
                    set_cursor(2, og_pos.Y + selected);
                }
                break;
            case KEY_DOWN:
                if(selected < SELECTION_COUNT - 1){
                    ++selected;
                    set_cursor(2, og_pos.Y + selected);
                }
                break;
            case KEY_ENTER:
                selecting = false;
                break;
        }
    }
    set_cursor(0, og_pos.Y + count);
    if(selected == back_out){

    }
    return selected;
}

COORD get_current_cursor(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
    else
    {
        // The function failed. Call GetLastError() for details.
        COORD invalid = { 0, 0 };
        return invalid;
    }
}

void print_selection(int selected_value, string* selections, int count){
    for (size_t i = 0; i < count; i++)
    {
        cout << " [" << i + 1 << "] > " << selections[i] << endl;
    }
}

void set_cursor(int x = 0 , int y = 0)
{
    HANDLE handle;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordinates = get_current_cursor(handle);
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition ( handle , coordinates );
}