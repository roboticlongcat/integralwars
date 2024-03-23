###Цель проекта
Разработать образовательную игру, предназначенную для помощи студентам в изучении интегралов и их свойств.

##Основные требования

Разработка ведется на языке C++ с использованием ООП подхода.

Соблюдены требования к программам дисциплины.

Код логически разбит по модулям .cpp и .h/.hpp.

Обязательно использование внешней библиотеки (необязательно интерфейсной), например: QT (данный фреймворк используется на собственный страх и риск), SFML, GTK и другие библиотеки;

Разработка полностью ведется через Git и удаленный репозиторий. Каждый участник команды должен сам коммитить свои правки, чтобы можно было оценить личный вклад участника группы.

Разработан графический интерфейс (обсуждается с учетом темы).

Обязательно использование структур данных из библиотеки STL.

Обязательно сборка проекта с использованием CMake или альтернативного сборщика.

Обязательное использование паттернов объектно-ориентированного программирования (простые паттерны типа "Фасад" и "Одиночка" в этот зачет не идут).
Функциональные требования

## 3.1. Главное меню
+Начать игру.
+Просмотр списка интегралов для запоминания.
+Упражнения для запоминания интегралов .
+Настройки.
+Выход из игры.

## 3.2. Игровой процесс
+Режим запоминания
+Карточки:
Выводить интеграл на экран . Пользователь нажимает на галочку или крестик и даётся правильный ответ.При нажатии на галочку добавляется в изученные.   
+Список интеграл-ответ:
3 колонки : интеграл , ответ и состояние(изучен или нет) . 

## Режим тренировки
+1)Несколько вариантов ответа
Пользователь должен выбрать правильный вариант ответа. В случае успеха начисляются очки. 
+2)Подборка
Слева будет список из нескольких интегралов, справа вперемешку ответы. Пользователь должен сопоставить .За каждую верную пару начисляются очки.
+3)Верно/неверно
Пользователю будет выводится интеграл с предполагаемым ответом . Пользователь должен верный ли ответ. В случае успеха даются очки. 

Будет присутствовать возможность подсказки для 1 и 2 , при использовании которой будут вычитаться количество очков, которое может получить пользователь . Подсказка будет представлять из себя вывод нужной таблицы на 5 секунд. 

##Отображение результатов
+Отображение текущего счета игрока.
+После тренировки отображение количества правильных и неправильных ответов.
+Отображение количества изученных интегралов 

##Графический интерфейс
+Главное меню с кнопками для выбора действий.
+Интерфейс для отображения интегралов.
+Отображение текущего счета и статистики игрока.
+Интерфейс карточек

#Дополнительные требования
+Интеграция с системой учета времени для отсчета времени на решение каждого интеграла.
+Возможность выбора уровня сложности (количество интегралов, сложность интегралов и т.д.).
+Фабричный метод (для создания различных типов игровых объектов).

#Дополнительные материалы
+Список интегралов для запоминания.
+Список упражнений 
+Список замен дифференциалов 
+Правила игры и инструкции для пользователя.


