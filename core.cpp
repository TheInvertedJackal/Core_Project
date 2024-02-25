#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER '\r'

void offset_cursor(int,int);

void print_selection(int, string*, int);

const int SELECTION_COUNT = 3;

int main(){
    string * selections = new string[SELECTION_COUNT]{
        "Value",
        "12",
        "Select ME!"
    };
    print_selection(-1, selections, SELECTION_COUNT);
    offset_cursor(0, 0);
    int selected = 0;
    bool selecting = true;
    char c;
    while (selecting){
        switch ((c = _getch())){
            case KEY_UP:
                if(selected > 0){
                    --selected;
                    offset_cursor(0,-1);
                }
                break;
            case KEY_DOWN:
                if(selected < SELECTION_COUNT - 1){
                    ++selected;
                    offset_cursor(0,1);
                }
                break;
            case KEY_ENTER:
                selecting = false;
                break;
        }
    }
    cout << "You are " << selected + 1 << " spaces from your stating point." << endl;
    delete[] selections;
    return 0;
}

void print_selection(int selected_value, string *selections, int count){
    for (size_t i = 0; i < count; i++)
    {
        cout << "(" << i << ")> " << selections[i] << endl;
    }
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

void offset_cursor(int x = 0 , int y = 0)
{
    HANDLE handle;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordinates = get_current_cursor(handle);
    coordinates.X += x;
    coordinates.Y += y;
    SetConsoleCursorPosition ( handle , coordinates );
}