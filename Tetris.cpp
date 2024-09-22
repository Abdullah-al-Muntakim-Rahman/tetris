#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <array>
#include <vector>
#include <random>
#include <windows.h>
#include <locale>
#include <codecvt>
using namespace std;
#pragma comment(lib, "winmm.lib")

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> uniformIntDistrib(0, 6);
string brick, space;
const int row = 28, column = 50;
int interval, frame;
int x_position, y_position;
int block_number;
array<array<int, 2>, 4> calculate_position(int x, int y);
array<array<int, 2>, 4> positions = calculate_position(x_position, y_position);
vector<vector<string>> grid(row, vector<string>(column, space));

wstring s2ws(const string& str) {
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}

void show() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD bufferSize = { (SHORT)((column * 4) + 1), (SHORT)(row + 2) };
    COORD bufferCoord = { 0, 0 };
    SMALL_RECT writeRegion = { 0, 0, bufferSize.X - 1, bufferSize.Y - 1 };

    CHAR_INFO* buffer = new CHAR_INFO[bufferSize.X * bufferSize.Y];
    for (int i = 0; i < bufferSize.X * bufferSize.Y; ++i) {
        buffer[i].Char.UnicodeChar = L' ';
        buffer[i].Attributes = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
    }

    int index = 0;
    buffer[index++] = { L'+', FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED };
    for (int p = 0; p < column * 2; ++p) {
        buffer[index++] = { L'-', FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED };
    }
    buffer[index++] = { L'+', FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED };
    index += bufferSize.X - index % bufferSize.X;

    for (int i = 0; i < row; ++i) {
        buffer[index++] = { L'|', FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED };
        for (int j = 0; j < column; ++j) {
            const string& str = grid[i][j];
            wstring wstr = s2ws(str);
            int k = 0;
            while (k < 2 && k < wstr.size()) {
                buffer[index++] = { wstr[k], FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED };
                ++k;
            }

            while (k < 2) {
                buffer[index++] = { L' ', FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED };
                ++k;
            }
        }
        buffer[index++] = { L'|', FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED };
        index += bufferSize.X - index % bufferSize.X;
    }

    buffer[index++] = { L'+', FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED };
    for (int p = 0; p < column * 2; ++p) {
        buffer[index++] = { L'-', FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED };
    }
    buffer[index++] = { L'+', FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED };

    WriteConsoleOutput(hConsole, buffer, bufferSize, bufferCoord, &writeRegion);

    delete[] buffer;

}

void clean() {
    fill(grid.begin(), grid.end(), vector<string>(column, space));
}

void new_block() {
    x_position = (int)((column / 2) - 2);
    y_position = 0;
    block_number = uniformIntDistrib(gen);
    positions = calculate_position(x_position, y_position);
}

void detectCollision(array<array<int, 2>, 4> positions) {
    switch (block_number)
    {
        case 0:
            if (x_position < 0) {
                x_position = column - 2;
            }
            else if (x_position > (column - 2)) {
                x_position = 0;
            }
            else if (y_position > (row - 2)) {
                new_block();
            }
            break;
        case 1:
            if (x_position < 0) {
                x_position = column - 1;
            }
            else if (x_position > (column - 1)) {
                x_position = 0;
            }
            else if (y_position > (row - 4)) {
                new_block();
            }
            break;
        case 2:
            if (x_position < 1) {
                x_position = column - 2;
            }
            else if (x_position > (column - 2)) {
                x_position = 1;
            }
            else if (y_position > (row - 2)) {
                new_block();
            }
            break;
        case 3:
            if (x_position < 0) {
                x_position = column - 3;
            }
            else if (x_position > (column - 3)) {
                x_position = 0;
            }
            else if (y_position > (row - 2)) {
                new_block();
            }
            break;
        case 4:
            if (x_position < 0) {
                x_position = column - 2;
            }
            else if (x_position > (column - 2)) {
                x_position = 0;
            }
            else if (y_position > (row - 3)) {
                new_block();
            }
            break;
        case 5:
            if (x_position < 1) {
                x_position = column - 1;
            }
            else if (x_position > (column - 1)) {
                x_position = 1;
            }
            else if (y_position > (row - 3)) {
                new_block();
            }
            break;
        case 6:
            if (x_position < 0) {
                x_position = column - 3;
            }
            else if (x_position > (column - 3)) {
                x_position = 0;
            }
            else if (y_position > (row - 2)) {
                new_block();
            }
            break;
        case 7:
            if (x_position < 0) {
                x_position = column - 4;
            }
            else if (x_position > (column - 4)) {
                x_position = 0;
            }
            else if (y_position > (row -1)) {
                new_block();
            }
            break;
        case 8:
            if (x_position < 0) {
                x_position = column - 2;
            }
            else if (x_position > (column - 2)) {
                x_position = 0;
            }
            else if (y_position > (row - 3)) {
                new_block();
            }
            break;
        case 9:
            if (x_position < 1) {
                x_position = column - 1;
            }
            else if (x_position > (column - 1)) {
                x_position = 1;
            }
            else if (y_position > (row - 3)) {
                new_block();
            }
            break;
        case 10:
            if (x_position < 0) {
                x_position = column - 3;
            }
            else if (x_position > (column - 3)) {
                x_position = 0;
            }
            else if (y_position > (row - 2)) {
                new_block();
            }
            break;
        case 11:
            if (x_position < 0) {
                x_position = column - 2;
            }
            else if (x_position > (column - 2)) {
                x_position = 0;
            }
            else if (y_position > (row - 3)) {
                new_block();
            }
            break;
        case 12:
            if (x_position < 2) {
                x_position = column - 1;
            }
            else if (x_position > (column - 1)) {
                x_position = 2;
            }
            else if (y_position > (row - 2)) {
                new_block();
            }
            break;
        case 13:
            if (x_position < 0) {
                x_position = column - 3;
            }
            else if (x_position > (column - 3)) {
                x_position = 0;
            }
            else if (y_position > (row - 2)) {
                new_block();
            }
            break;
        case 14:
            if (x_position < 0) {
                x_position = column - 2;
            }
            else if (x_position > (column - 2)) {
                x_position = 0;
            }
            else if (y_position > (row - 3)) {
                new_block();
            }
            break;
        case 15:
            if (x_position < 0) {
                x_position = column - 3;
            }
            else if (x_position > (column - 3)) {
                x_position = 0;
            }
            else if (y_position > (row - 2)) {
                new_block();
            }
            break;
        case 16:
            if (x_position < 1) {
                x_position = column - 1;
            }
            else if (x_position > (column - 1)) {
                x_position = 1;
            }
            else if (y_position > (row - 3)) {
                new_block();
            }
            break;
        case 17:
            if (x_position < 1) {
                x_position = column - 2;
            }
            else if (x_position > (column - 2)) {
                x_position = 1;
            }
            else if (y_position > (row - 2)) {
                new_block();
            }
            break;
        case 18:
            if (x_position < 0) {
                x_position = column - 2;
            }
            else if (x_position > (column - 2)) {
                x_position = 0;
            }
            else if (y_position > (row - 3)) {
                new_block();
            }
            break;
        default:
            break;
    }
}

array<array<int, 2>, 4> OPositions(int x, int y) {
    return { {
        {x, y},
        {x + 1, y},
        {x + 1, y + 1},
        {x, y + 1}
    } };
}

array<array<int, 2>, 4> IPositions(int x, int y) {
    return { {
        {x, y},
        {x, y + 1},
        {x, y + 2},
        {x, y + 3}
    } };
}

array<array<int, 2>, 4> IPositionsR1(int x, int y) {
    return { {
        {x, y},
        {x + 1, y},
        {x + 2, y},
        {x + 3, y}
    } };
}

array<array<int, 2>, 4> SPositions(int x, int y) {
    return { {
        {x, y},
        {x + 1, y},
        {x, y + 1},
        {x - 1, y + 1}
    } };
}

array<array<int, 2>, 4> SPositionsR1(int x, int y) {
    return { {
        {x, y},
        {x, y + 1},
        {x + 1, y + 1},
        {x + 1, y + 2}
    } };
}

array<array<int, 2>, 4> ZPositions(int x, int y) {
    return { {
        {x, y},
        {x + 1, y},
        {x + 1, y + 1},
        {x + 2, y + 1}
    } };
}

array<array<int, 2>, 4> ZPositionsR1(int x, int y) {
    return { {
        {x, y},
        {x, y + 1},
        {x - 1, y + 1},
        {x - 1, y + 2}
    } };
}

array<array<int, 2>, 4> LPositions(int x, int y) {
    return { {
        {x, y},
        {x + 1, y + 2},
        {x, y + 1},
        {x, y + 2}
    } };
}

array<array<int, 2>, 4> LPositionsR1(int x, int y) {
    return { {
        {x, y},
        {x + 1, y},
        {x + 2, y},
        {x, y + 1}
    } };
}

array<array<int, 2>, 4> LPositionsR2(int x, int y) {
    return { {
        {x, y},
        {x + 1, y},
        {x + 1, y + 1},
        {x + 1, y + 2}
    } };
}

array<array<int, 2>, 4> LPositionsR3(int x, int y) {
    return { {
        {x, y},
        {x, y + 1},
        {x - 1, y + 1},
        {x - 2, y + 1}
    } };
}

array<array<int, 2>, 4> JPositions(int x, int y) {
    return { {
        {x, y},
        {x, y + 1},
        {x, y + 2},
        {x - 1, y + 2}
    } };
}

array<array<int, 2>, 4> JPositionsR1(int x, int y) {
    return { {
        {x, y},
        {x, y + 1},
        {x + 1, y + 1},
        {x + 2, y + 1}
    } };
}

array<array<int, 2>, 4> JPositionsR2(int x, int y) {
    return { {
        {x, y},
        {x + 1, y},
        {x + 1, y + 1},
        {x + 1, y + 2}
    } };
}

array<array<int, 2>, 4> JPositionsR3(int x, int y) {
    return { {
        {x, y},
        {x + 1, y},
        {x + 2, y},
        {x + 2, y + 1}
    } };
}

array<array<int, 2>, 4> TPositions(int x, int y) {
    return {{
        {x, y},
        {(x + 1), (y)},
        {(x + 2), (y)},
        {x + 1, (y + 1)}
    }};
}

array<array<int, 2>, 4> TPositionsR1(int x, int y) {
    return { {
        {x, y},
        {x - 1, (y + 1)},
        {(x), (y + 1)},
        {(x), (y + 2)}
    } };
}

array<array<int, 2>, 4> TPositionsR2(int x, int y) {
    return { {
        {x, y},
        {(x), (y + 1)},
        {(x + 1), (y + 1)},
        {x - 1, (y + 1)}
    } };
}

array<array<int, 2>, 4> TPositionsR3(int x, int y) {
    return { {
        {x, y},
        {(x ), (y + 1)},
        {(x + 1), (y + 1)},
        {x, (y + 2)}
    } };
}
array<array<int, 2>, 4>(*funcArray[])(int x,int y) = { OPositions, IPositions, SPositions, ZPositions,LPositions, JPositions, TPositions, IPositionsR1, SPositionsR1, ZPositionsR1, LPositionsR1, LPositionsR2, LPositionsR3, JPositionsR1, JPositionsR2, JPositionsR3, TPositionsR1, TPositionsR2, TPositionsR3 };

void rotate() {
    switch (block_number) {
    case 0:
        break;
    case 1:
        block_number = 7;
        break;
    case 2:
        block_number = 8;
        break;
    case 3:
        block_number = 9;
        break;
    case 4:
        block_number = 10;
        break;
    case 5:
        block_number = 13;
        break;
    case 6:
        block_number = 16;
        break;
    case 7:
        block_number = 1;
        break;
    case 8:
        block_number = 2;
        break;
    case 9:
        block_number = 3;
        break;
    case 10:
        block_number = 11;
        break;
    case 11:
        block_number = 12;
        break;
    case 12:
        block_number = 4;
        break;
    case 13:
        block_number = 14;
        break;
    case 14:
        block_number = 15;
        break;
    case 15:
        block_number = 5;
        break;
    case 16:
        block_number = 17;
        break;
    case 17:
        block_number = 18;
        break;
    case 18:
        block_number = 6;
        break;
    default:
        break;
    }
}

void paint(int x, int y, int block_number, array<array<int, 2>, 4> positions) {
    try{
        grid[positions[0][1]][positions[0][0]] = brick;
        grid[positions[1][1]][positions[1][0]] = brick;
        grid[positions[2][1]][positions[2][0]] = brick;
        grid[positions[3][1]][positions[3][0]] = brick;
    }
    catch(...){}
}
array<array<int, 2>, 4> calculate_position(int x, int y) {
    positions = funcArray[block_number](x, y);
    return positions;
}

void processInput() {
    // Get the standard input handle
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE) {
        std::cerr << "GetStdHandle error\n";
        return;
    }

    const int maxEvents = 128;
    INPUT_RECORD irInBuf[maxEvents];
    DWORD cNumRead;

    // Event loop
    while (true) {
        // Read console input
        if (!ReadConsoleInput(hStdin, irInBuf, maxEvents, &cNumRead)) {
            std::cerr << "ReadConsoleInput error\n";
            return;
        }

        // Process the events
        for (DWORD i = 0; i < cNumRead; ++i) {
            if (irInBuf[i].EventType == KEY_EVENT) {
                KEY_EVENT_RECORD& ker = irInBuf[i].Event.KeyEvent;

                // Check if key is pressed down
                if (ker.bKeyDown) {
                    switch (ker.wVirtualKeyCode) {
                    case VK_LEFT:
                        x_position--;
                        detectCollision(positions);
                        break;
                    case VK_RIGHT:
                        x_position++;
                        detectCollision(positions);
                        break;
                    case VK_SPACE:
                        rotate();
                        detectCollision(positions);
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
}

void update() {
    clean();
    positions = calculate_position(x_position, y_position);
    detectCollision(positions);
    paint(x_position, y_position, block_number, positions);
    show();
}

void setInterval(int interval) {
    while (true) {
        update();
        this_thread::sleep_for(chrono::milliseconds(interval));
    }
}
void setIntervalY(int interval) {
    while (true) {
        y_position++;
        this_thread::sleep_for(chrono::milliseconds(interval));
    }
}

int main()
{
    timeBeginPeriod(1);
    brick = "[]";
    space = "  ";
    frame = 0;
    new_block();
    thread periodicThread(setInterval, 1);
    thread periodicThread2(setIntervalY, 500);
    thread inputCheck(processInput);
    periodicThread.join();
    periodicThread2.join();
    inputCheck.join();
    timeEndPeriod(1);
}
