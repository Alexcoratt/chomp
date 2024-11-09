# Chomp
Данный репозиторий содержит очень простую реализацию не менее простой игры "Щелк" (или Chomp). Правила данной игры можно найти по [ссылке](https://ru.wikipedia.org/wiki/%D0%A9%D1%91%D0%BB%D0%BA).

## Сборка
Для сборки проекта необходим **Unix Makefiles**. Для запуска сборки достаточно написать в командной строке
```sh
make
```

Также при сборке можно задать дополнительные параметры, а именно:
1. `BUILD_DIR` - директория с результирующими файлами (по-умолчанию: `build`)
1. `SOURCE_DIR` - директория с исходными файлами (по-умолчанию: `src`)
1. `CC` - компилятор (по-умолчанию: `gcc`)
1. `CFLAGS` - флаги компилятора; флаги компилятора могут быть дополнены новыми (по-умолчанию: `-Wall -Iinclude -std=gnu11`)

## Запуск
После сборки программы в каталоге, имя которого было указано в качестве значения параметра `BUILD_DIR` (по-умолчанию `build`), появится исполняемый файл `chomp`. Для запуска данного файла необходимо написать в терминале
```sh
./chomp <высота поля> <ширина поля>
```

## Геймплей
В игре участвует два игрока (0-й и 1-й). Они ходят по очереди, начиная с 0-го.

### Игровое поле
Игровое поле отображается как матрица, заполненная одним из символов `@` или `.`. Символ `@` означает заполненную ячейку (неоткусанный кусочек шоколадки), тогда как `.` символизирует пустую ячейка (откусанный кусочек).

### Ввод
Для совершения хода игроку необходимо ввести координаты откусываемого кусочка. Первой координатой является номер строки, в которой находится кусочек, а второй - номер колонки.

Пример ввода
```
0 4
```

### Особенности реализации
**Важно: нумерация в игре идет с 0**. То есть первая строка обозначается числом 0 (как и первая колонка).

Также стоит отметить, что в данной реализации вертикальная ось инвертирована (первая строка является верхней на игровом поле).