package com.github.pstephens.mal;

import com.github.pstephens.mal.collection.List;

public class Program {
    public static void main(String[] args) {
        /*if(Platform.isWindows()) {

            Pointer stdin = Kernel32.lib.GetStdHandle(Kernel32.STD_INPUT_HANDLE);
            System.out.println(String.format("GetStdHandle: %s", stdin.toString()));

            int[] mode = new int[1];
            boolean result = Kernel32.lib.GetConsoleMode(stdin, mode);
            System.out.println(String.format("GetConsoleMode: %b mode: 0x%08x", result, mode[0]));

            result = Kernel32.lib.SetConsoleMode(stdin, mode[0]
                    & ~(Kernel32.ENABLE_ECHO_INPUT | Kernel32.ENABLE_LINE_INPUT | Kernel32.ENABLE_PROCESSED_INPUT)
                    | (Kernel32.ENABLE_VIRTUAL_TERMINAL_INPUT));
            System.out.println(String.format("SetConsoleMode: %b", result));

            result = Kernel32.lib.GetConsoleMode(stdin, mode);
            System.out.println(String.format("GetConsoleMode: %b mode: 0x%08x", result, mode[0]));


            Pointer stdout = Kernel32.lib.GetStdHandle(Kernel32.STD_OUTPUT_HANDLE);
            System.out.println(String.format("GetStdHandle: %s", stdout.toString()));

            result = Kernel32.lib.GetConsoleMode(stdout, mode);
            System.out.println(String.format("GetConsoleMode: %b mode: 0x%08x", result, mode[0]));

            result = Kernel32.lib.SetConsoleMode(stdout, mode[0]
                    //& ~(Kernel32.ENABLE_PROCESSED_OUTPUT)
                    | (Kernel32.ENABLE_VIRTUAL_TERMINAL_PROCESSING));
            System.out.println(String.format("SetConsoleMode: %b", result));
        } else {
            execTtyCmd("/bin/stty", "-echo", "-icanon", "min", "1");
            //execTtyCmd("/bin/stty", "-icanon");
            //execTtyCmd("/bin/stty", "min", "1");
        }*/

        System.out.println(List.create(5, 6, 7));
        System.out.println(List.empty());
        System.out.println(List.create("45"));
        System.out.println(List.create(5, 6, 7).cons(4));
        System.out.println(List.<Object>create(5, 6, 7).cons("4"));

        System.out.println("Equals: " + (List.create(7, 8, 9, 10).equals(List.create(10, 9, 8, 7).reverse())));
        System.out.println("Equals: " + (List.empty().equals(List.empty().reverse())));
        System.out.println("Equals: " + (List.create(7, 8).equals(List.create(7, 8).reverse())));

        List<Integer> list = List.create(5, 6, 7).cons(4).reverse();

        System.out.println("List 1: " + List.create(7, 8, 9, 10));
        System.out.println("List 2: " + List.create(10, 9, 8, 7).reverse());


        System.out.println(list);

        /*

        while(true) {
            try {
                int ch = System.in.read();
                System.out.println(String.format("Key: %d %c", ch, ch > 32 ? (char)ch : ' '));
            } catch(Throwable e) {
                System.out.println(String.format("Error: %o", e));
            }
        }*/
    }

    public static void execTtyCmd(String... command) {
        try {
            Process p = new ProcessBuilder(command).inheritIO().start();
            p.waitFor();
            if(p.exitValue() != 0) {
                throw new Exception("Non zero exit code " + p.exitValue());
            }

        } catch(Throwable t) {
            System.out.println("Failed running " + String.join(" ", command) + "\n" + t.getMessage());
        }

    }
}
