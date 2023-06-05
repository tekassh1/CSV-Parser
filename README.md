## Yadro Telecom test task for C++ intership

**For build**

1) Go to `/build` directory in terminal
2) Run ```cmake -G "MinGW Makefiles" ../CmakeLists.txt``` command
3) Run ```make``` command
4) Executable (.exe) file will appear in `/build` directory

This console app parses ```.csv``` file, and counting cells, if they contain an operation.
Example:

Input table
```
            A,          B,          C,          D,          E,          F,          G,
1,          5,          2,          3,          3,          =A1*G3,     1,          0,
2,          3,          5,          6,          6,          15,         4,          3,
3,          7,          8,          9,          9,          8,          7,          6,
4,          10, 

Result table
```
            A,          B,          C,          D,          E,          F,          G,
1,          5,          2,          3,          3,          30,         1,          0,
2,          3,          5,          6,          6,          15,         4,          3,
3,          7,          8,          9,          9,          8,          7,          6,
4,          10,         23,         12,         12,         11,         10,         9,
5,          13,         14,         15,         15,         14,         13,         9,
6,          16,         17,         18,         16,         17,         18,         0,
```


**Тестовое задание на стажировку С++ в Yadro Telecom**

 Для сборки

1) Перейдите в директорию `/build`
2) Выполните команду ```cmake -G "MinGW Makefiles" ../CmakeLists.txt```
3) Выполните команду ```make```
4) Исполняесый файл программы (.exe) появится в директории `/build`

by https://github.com/tekassh1