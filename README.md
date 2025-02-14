# Computer-Club

## Требует дороботки

## Структура проекта выглядит так

```
    Computer Club/
    ├── src/                         - # Исходный код
    │    ├── main.cpp                - # Точка входа в программу
    |    ├── GameClub.cpp            - # Содержит реализацию методов для работы компьютерного клуба
    │    ├── timeUtils.cpp           - # Реализация модуля для работы с временем
    │    └── tests                   - # Папка с тестами
    │        ├── test_gameClub.cpp   - # Тесты для классы GameClub
    │        └── test_timeUtils.cpp  - # Тесты для утилит для работы со временем
    ├── include/                     - # Заголовочные файлы
    │   ├── global.h                 - # Файл, содержащий основные структуры, глобальные переменные и определения
    │   ├── GameClub.h               - # Файл, содержащий определение основного класса для работы с компьютерным клубом
    │   └── timeUtils.h              - # Интерфейс модуля для работы с временем
    └── data/                        - # Каталог, в котором находиться тестовый файл для работы программы 
        └── test_file.txt            - # Файл в котором записаны события
```

## Для скачивания программы

```powershell
git clone https://github.com/heiby-baby/Computer-club
```

## Cборка и запуск

### *Сборка через cmake*

```powershell
mkdir build
cd build
cmake ..
cmake --build .
```

#### *Для запуска программы*

#####Windows

```powershell
cd debug
.\CompCLub.exe .\<имя вашего файла>.txt
```
пример 
```powershell
cd debug
.\CompClub.exe .\data\test_file.txt
```
#####Linux
```bash
./CompClub <имя вашего файла>.txt
```
пример
```bash
./CompClub data/test_file.txt
```

#### *Для запуска тестов*

```
ctest
```


