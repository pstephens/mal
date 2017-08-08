package com.github.pstephens;

import com.github.pstephens.readline.windows.Kernel32;
import com.sun.jna.Pointer;

public class Program {
    public static void main(String[] args) {
        Pointer stdin = Kernel32.lib.GetStdHandle(Kernel32.STD_INPUT_HANDLE);
        System.out.println(String.format("GetStdHandle: %s", stdin.toString()));

        int[] mode = new int[1];
        boolean result = Kernel32.lib.GetConsoleMode(stdin, mode);
        System.out.println(String.format("GetConsoleMode: %b mode: 0x%08x", result, mode[0]));


        result = Kernel32.lib.SetConsoleMode(stdin, mode[0] & ~(Kernel32.ENABLE_ECHO_INPUT | Kernel32.ENABLE_LINE_INPUT));
        System.out.println(String.format("SetConsoleMode: %b", result));

        result = Kernel32.lib.GetConsoleMode(stdin, mode);
        System.out.println(String.format("GetConsoleMode: %b mode: 0x%08x", result, mode[0]));
    }

}
