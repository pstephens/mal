package com.github.pstephens.readline;

public class KeyEvent {
    private KeyEvent() { }

    public static boolean isControlEvent(int id) {
        return id < 0x00000020 || id > 0x01000000;
    }

    public static boolean isCodePoint(int id) {
        return !isControlEvent(id);
    }

    public static boolean modShift(int id) { return false; }
    public static boolean modCtrl(int id) { return false; }
    public static boolean modAlt(int id) { return false; }

    public static final int BACKSPACE         = 0x00000008;
    public static final int HORIZONTAL_TAB    = 0x00000009;
    public static final int ENTER             = 0x0000000a;
    public static final int ESCAPE            = 0x0000001b;

    public static final int UP_ARROW          = 0x01000001;
    public static final int DOWN_ARROW        = 0x01000002;
    public static final int LEFT_ARROW        = 0x01000003;
    public static final int RIGHT_ARROW       = 0x01000004;
    public static final int PAGE_UP           = 0x01000005;
    public static final int PAGE_DOWN         = 0x01000006;
    public static final int HOME              = 0x01000007;
    public static final int END               = 0x01000008;

    public static final int INSERT            = 0x01000011;
    public static final int DEL               = 0x01000012;

    public static final int F1                = 0x01000021;
    public static final int F2                = 0x01000022;
    public static final int F3                = 0x01000023;
    public static final int F4                = 0x01000024;
    public static final int F5                = 0x01000025;
    public static final int F6                = 0x01000026;
    public static final int F7                = 0x01000027;
    public static final int F8                = 0x01000028;
    public static final int F9                = 0x01000029;
    public static final int F10               = 0x0100002a;
    public static final int F11               = 0x0100002b;
    public static final int F12               = 0x0100002c;

    public static final int MOD_SHIFT         = 0x10000000;
    public static final int MOD_CTRL          = 0x20000000;
    public static final int MOD_ALT           = 0x40000000;
}
