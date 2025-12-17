# Лабораторная работа №1 - Go версия

## Описание
Go реализация DBMS с JSON сериализацией для управления абстрактными структурами данных.

## Сборка и запуск

```bash
# Сборка
go build -o dbms dbms.go

# Запуск
./dbms --file main.json --query 'COMMAND name [args...]'
```

## Поддерживаемые команды

Все команды аналогичны C++ версии:

### Массив (M)
- `MPUSHEND <name> <value>` - добавить в конец
- `MPUSHI <name> <value> <index>` - вставить по индексу
- `MREAD <name>` - вывести все элементы
- `MLEN <name>` - получить длину
- `MGET <name> <index>` - получить элемент

### Стек (ST)
- `STPUSH <name> <value>` - добавить элемент
- `STPOP <name>` - извлечь элемент (LIFO)
- `STREAD <name>` - вывести все элементы

### Очередь (Q)
- `QPUSH <name> <value>` - добавить элемент
- `QPOP <name>` - извлечь элемент (FIFO)
- `QREAD <name>` - вывести все элементы

### Односвязный список (SLL)
- `SLLADDH <name> <value>` - добавить в голову
- `SLLADDT <name> <value>` - добавить в хвост
- `SLLREAD <name>` - вывести все элементы
- `SLLFINDV <name> <value>` - найти элемент

### Двусвязный список (DLL)
- `DLLADDH <name> <value>` - добавить в голову
- `DLLADDT <name> <value>` - добавить в хвост
- `DLLREADF <name>` - вывести прямо
- `DLLREADB <name>` - вывести обратно

### Двоичное дерево (BRT)
- `BRTINSERT <name> <value>` - вставить число
- `BRTDEL <name> <value>` - удалить число
- `BRTREAD <name>` - вывести отсортированно

## Примеры

```bash
# Работа с массивом
./dbms --file main.json --query 'MPUSHEND myarray newval'
./dbms --file main.json --query 'MREAD myarray'

# Работа со стеком
./dbms --file main.json --query 'STPUSH mystack item'
./dbms --file main.json --query 'STPOP mystack'

# Работа с деревом
./dbms --file main.json --query 'BRTINSERT mytree 4'
./dbms --file main.json --query 'BRTREAD mytree'
```

## JSON формат
Аналогичен C++ версии с поддержкой всех 6 структур данных.
