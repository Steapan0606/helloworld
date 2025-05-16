
#include <windows.h>
#include <stdio.h>
#include <string.h> // обязательно для strlen и strcmp

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

extern "C" {

// Открытие COM-порта и установка скорости (baudrate)
EXPORT HANDLE open_com_port(const char* port_name, DWORD baud_rate) {
    HANDLE hCom = CreateFileA(
        port_name,                // Например, "COM3"
        GENERIC_READ | GENERIC_WRITE,
        0,                        // Без шаринга
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (hCom == INVALID_HANDLE_VALUE)
        return hCom;

    DCB dcb = {0};
    dcb.DCBlength = sizeof(dcb);

    if (!GetCommState(hCom, &dcb))
        return INVALID_HANDLE_VALUE;

    dcb.BaudRate = baud_rate; // Скорость (например, CBR_9600)
    dcb.ByteSize = 8;         // 8 бит данных
    dcb.Parity   = NOPARITY;  // Без контроля чётности
    dcb.StopBits = ONESTOPBIT;// 1 стоп-бит

    if (!SetCommState(hCom, &dcb))
        return INVALID_HANDLE_VALUE;

    return hCom;
}

// Закрытие порта
EXPORT void close_com_port(HANDLE hCom) {
    CloseHandle(hCom);
}

// Отправка команды устройству
EXPORT int send_command(HANDLE hCom, const char* cmd) {
    DWORD written;
    int len = strlen(cmd);
    WriteFile(hCom, cmd, len, &written, NULL);  // сама команда
    WriteFile(hCom, "\r\n", 2, &written, NULL); // символ конца строки
    return written;
}

// Чтение ответа устройства
EXPORT int read_response(HANDLE hCom, char* buf, int buf_size) {
    DWORD read_bytes;
    if (ReadFile(hCom, buf, buf_size-1, &read_bytes, NULL) && read_bytes > 0) {
        buf[read_bytes] = '\0'; // корректное завершение строки
        return read_bytes;
    }
    buf[0] = '\0';
    return 0;
}

} // extern "C"

