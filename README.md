# Kursach
[![C/C++ CI](https://github.com/Nikatik/Kursach/actions/workflows/main.yml/badge.svg)](https://github.com/Nikatik/Kursach/actions/workflows/main.yml)
[![Lint](https://github.com/Nikatik/Kursach/actions/workflows/lint.yml/badge.svg)](https://github.com/Nikatik/Kursach/actions/workflows/lint.yml)
[![GitHub Classroom Workflow](https://github.com/Nikatik/Kursach/actions/workflows/classroom.yml/badge.svg)](https://github.com/Nikatik/Kursach/actions/workflows/classroom.yml)

**Программа по расчёту оптимального управления с мягкой посадкой для вертикального этапа снижения.**

В качестве подпрограммы реализован метод Виета-Кардано для нахождения решения кубического уравнения.

В программе присутствуют коэфициенты точности, с которыми КА должен быть посажен на поверхность тела. Также наличиствует "проверка на дурака", на израсходованное топливо и на столкновение с поверхностью с небезопасной скоростью.

# Сборка
 Зависимости:
  - g++
  - make
 
 Сборка:
```bash
make
```

# Использование
Базовый запуск программы:
```bash
./kursach
```
Запуск программы с вручную введёнными начальными массой, высотой и скоростью:
```bash
./kursach 1 100 1000 -30
```
Запуск программы с полностью вручную введёнными коэфициентами точности и начальными данными:

`(tol1, tol2, tol3, mass, height, velocity)`
```bash
./kursach 2 0.01 0.03 0.2 100 1000 -30
```
