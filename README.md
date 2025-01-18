# Computer-Club (oop version)

## Структура проекта выглядит так

    Computer Club/
    ├── src/                - # Исходный код
    │    ├── main.cpp       - # Точка входа в программу
    |    ├── GameClub.cpp   - # Точка входа в программу
    │    └── timeUtils.cpp  - # Реализация модуля для работы с временем
    ├── include/            - # Заголовочные файлы
    │   ├── global.h        - # Файл, содержащий основные структуры, глобальные переменные и определения
    │   ├── GameClub.h      - # Файл, содержащий основные структуры, глобальные переменные и определения
    │   └── timeUtils.h     - # Интерфейс модуля для работы с временем
    └── data/               - # Каталог, в котором находиться тестовый файл для работы программы 

## Для скачивания программы

    git clone https://github.com/heiby-baby/Computer-club

## Cборка и запуск

### *Через g++*

#### *Для сборки основной программы*

    mkdir build
    g++ -o ".\build\CompClub.exe" .\src\GameClub.cpp .\src\main.cpp .\src\timeUtils.cpp -Iinclude

#### *Для запуска программы*

    .\build\ComputerClub.exe .\data\test_file.txt