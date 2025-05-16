
#include <stdio.h>
#include <windows.h>

// Макрос для импорта функций из другого файла (как пример с DLL)
#ifdef _WIN32
#define IMPORT __declspec(dllimport)
#else
#define IMPORT
#endif

// Объявления внешних функций для работы с COM-портом
extern "C" {
    IMPORT HANDLE open_com_port(const char* port_name, DWORD baud_rate);
    IMPORT void close_com_port(HANDLE hCom);
    IMPORT int send_command(HANDLE hCom, const char* cmd);
    IMPORT int read_response(HANDLE hCom, char* buf, int buf_size);
}

int main() {
    char port[20];
    printf("Введите имя COM-порта (например, COM3): ");
    scanf("%19s", port);

    // Открываем COM-порт с заданным названием и скоростью (9600 бод — стандарт)
    HANDLE hCom = open_com_port(port, CBR_9600);
    if (hCom == INVALID_HANDLE_VALUE) {
        printf("Ошибка открытия порта!\n");
        return 1;
    }

    printf("Порт открыт. Введите команду ('exit' для выхода):\n");
    char cmd[100];
    char resp[100] = "";

    // Основной цикл — пользователь набирает команды, они отправляются устройству
    while (1) {
        printf("> ");
        scanf("%99s", cmd);

        if (strcmp(cmd, "exit") == 0) 
            break;

        // Отправляем команду на прибор
        send_command(hCom, cmd);
        // Читаем (ожидаем) ответ от прибора
        int len = read_response(hCom, resp, sizeof(resp));

        if (len > 0)
            printf("Ответ прибора: %s\n", resp);
        else
            printf("Нет ответа от прибора.\n");
    }

    close_com_port(hCom); // После работы закрываем порт
    printf("Порт закрыт.\n");
    return 0;
}
