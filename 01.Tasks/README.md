# Урок 1. 

## Знакомство с AVR и платформой Arduino

### Задания

#### Задача 1. Светофор

Сделать “светофор” на трех светодиодах: красный, желтый, зеленый
Светофор работает в строгой последовательности цветов сигналов
1. Зеленый сигнал — разрешает движение в данном направлении.
2. Зеленый мигающий сигнал 3 раза — разрешает движение и предупреждает, что будет смена сигнала.
3. Желтый сигнал — запрещает движение и предупреждает, что будет красный сигнал.
4. Красный сигнал — запрещает движение в данном направлении

#### Задача 2. Кнопка перехода

Добавить кнопку перехода пешехода в светофор
Алгоритм работы:
1. Пешеход нажимает кнопку.
2. Через определенное программно время (например, 5 сек) светофор для машин переходит в режим
мигающий-желтый 3 раза.
3. Красный для перехода пешеходов горит строго определенное время, сколько бы раз кнопку не
нажимали
4. После "зеленого" с установленным временем задержки (5 сек) происходит разрешение нажатия
кнопки (до этого кнопка не реагирует)
Светофор готов к новому циклу.

#### Задача 3*. Включение светодиода

Включение светодиода по команде с консоли
Из заданий 2 и 4, рассмотренных на семинаре, синтезируем код,с помощью которого можно будет управлять
состоянием светодиода.
Необходимые компоненты: Arduino, резистор, светодиод, макетная плата.
Соберите цепи из указанных компонентов и напишите данный код. Запустите serial monitor. Введите с
клавиатуры «1», светодиод загорится зеленый. При вводе «0» зеленый светодиод потухнет. Можно сделать
для разных светодиодов.

### Решение

##### Задача 1. Светофор

- Код: [https://github.com/allseenn/ciot/blob/main/01.Tasks/01/01.ino](https://github.com/allseenn/ciot/blob/main/01.Tasks/01/01.ino)
- Фото: [https://github.com/allseenn/ciot/blob/main/01.Tasks/01/01.jpg](https://github.com/allseenn/ciot/blob/main/01.Tasks/01/01.jpg)
- Видео: [https://github.com/allseenn/ciot/raw/main/01.Tasks/01/01.mp4](https://github.com/allseenn/ciot/raw/main/01.Tasks/01/01.mp4)

##### Задача 2. Кнопка перехода

- Код: [https://github.com/allseenn/ciot/blob/main/01.Tasks/02/02.ino](https://github.com/allseenn/ciot/blob/main/01.Tasks/02/02.ino)
- Фото: [https://github.com/allseenn/ciot/blob/main/01.Tasks/02/02.jpg](https://github.com/allseenn/ciot/blob/main/01.Tasks/02/02.jpg)
- Видео: [https://github.com/allseenn/ciot/raw/main/01.Tasks/02/02.mp4](https://github.com/allseenn/ciot/raw/main/01.Tasks/02/02.mp4)

##### Задача 3*. Включение светодиода

- Код: [https://github.com/allseenn/ciot/blob/main/01.Tasks/03/03.ino](https://github.com/allseenn/ciot/blob/main/01.Tasks/03/03.ino)
- Фото: [https://github.com/allseenn/ciot/blob/main/01.Tasks/03/03.jpg](https://github.com/allseenn/ciot/blob/main/01.Tasks/03/03.jpg)
- Видео: [https://github.com/allseenn/ciot/raw/main/01.Tasks/03/03.mp4](https://github.com/allseenn/ciot/raw/main/01.Tasks/03/03.mp4)
