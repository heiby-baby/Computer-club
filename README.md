# Computer-Club

## Структура проекта выглядит так

```
Computer Club/
├── CMakeLists.txt - # Файл конфигурации для сборки проекта
├── src/ - # Исходный код
│    ├── main.cpp - # Точка входа в программу
│   └── timeUtils.cpp - # Реализация модуля для работы с временем
├── include/ - # Заголовочные файлы
│   ├── global.h - # Файл, содержащий основные структуры, глобальные переменные и определения
│   └── timeUtils.h - # Интерфейс модуля для работы с временем
├── tests/ - # Тесты
│   └── test_timeUtils.cpp - # Тесты для второго модуля
└── data/ - # Каталог, в котором находиться тестовый файл для работы программы 
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

```powershell
cd debug
.\main.exe .\test_file.txt
```

#### *Для запуска тестов*

```powerchell
cd debug
.\test_timeUtils.exe
```

#### 

### *Через g++*

#### *Для сборки основной программы*

```powershell
mkdir build
g++ -o ".\build\ComputerClub.exe" .\src\main.cpp .\src\timeUtils.cpp -Iinclude
```

#### *Для сборки тестов*

```powershell
mkdir build
g++ -o ".\build\test_timeUtils.exe" .\tests\test_timeUtils.cpp .\src\timeUtils.cpp -Iinclude
```

#### *Для запуска программы*

```powershell
.\build\main.exe .\data\test_file.txt
```

#### *Для запуска тестов*

```powershell
.\build\test_timeUtils.exe
```


