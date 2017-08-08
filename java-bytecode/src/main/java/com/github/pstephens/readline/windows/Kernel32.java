package com.github.pstephens.readline.windows;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;

public interface Kernel32 extends Library {
    Kernel32 lib =
            (Kernel32) Native.loadLibrary("kernel32", Kernel32.class);

    int STD_INPUT_HANDLE =  -10;
    int STD_OUTPUT_HANDLE = -11;
    int STD_ERROR_HANDLE =  -12;

    int ENABLE_PROCESSED_INPUT =             0x0001;
    int ENABLE_LINE_INPUT =                  0x0002;
    int ENABLE_ECHO_INPUT =                  0x0004;
    int ENABLE_WINDOW_INPUT =                0x0008;
    int ENABLE_MOUSE_INPUT =                 0x0010;
    int ENABLE_INSERT_MODE =                 0x0020;
    int ENABLE_QUICK_EDIT_MODE =             0x0040;
    int ENABLE_VIRTUAL_TERMINAL_INPUT =      0x0200;
    int ENABLE_WRAP_AT_EOL_OUTPUT =          0x0002;
    int ENABLE_PROCESSED_OUTPUT =            0x0001;
    int ENABLE_VIRTUAL_TERMINAL_PROCESSING = 0x0004;
    int DISABLE_NEWLINE_AUTO_RETURN =        0x0008;
    int ENABLE_LVB_GRID_WORLDWIDE =          0x0010;

    Pointer GetStdHandle(int nStdHandle);

    boolean GetConsoleMode(Pointer hConsoleHandle, int[] lpMode);
    boolean SetConsoleMode(Pointer hConsoleHandle, int dwMode);

    int GetLastError();
}
