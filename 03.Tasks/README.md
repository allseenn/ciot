# Урок 3 

## Знакомство с платформой Raspberry Pi

### Задания

#### Задача 1. Локальный чат

Работа с TCP-сокетами и WEB-сервером
Написать приложение «Локальный чат» на архитектуре «клиент-сервер»,
Сообщение должно заканчиваться символом точка «.».

#### Задача 2*. Байт-стаффинг

Семинар 3. Работа с TCP-сокетами и WEB-сервером
Написать приложение «Локальный чат» на архитектуре «клиент-сервер» с использованием
байт-стаффинга (byte stuffing).

<table>
<tr><th>МНП</th><th>Сегмент данных</th><th>МКП</th></tr>
<tr><td>1 байт</td><td>Сообщения чата</td><td>1 байт</td></tr>
<tr><td>SOP = 0x7E</td><td></td><td>EOP = 0x7E</td></tr>
</table>

Где:

- МНП (SOP) – маркер начала пакета;
- МКП (EOP)– маркер конца пакета;

Сегмент данных не содержит кодов МНП и МКП (достигается применением вставки байт). Если в
передаваемых данных встречается код 0x7E, то он заменяется последовательностью 0x7D, 0x5E.
Если в передаваемых данных встречается код 0x7D, то он заменяется последовательностью 0x7D, 0x5D.
То есть:
0x7E = вставить 0x7D, заменить 0x7E на ( 0x7E xor 0x20) = 0x7D, 0x5E
0x7D = вставить 0x7D, заменить 0x7D на ( 0x7D xor 0x20) = 0x7D, 0x5D
При приеме данных происходит обратная замена
0x7D, 0x5E = отбросить 0x7D, заменить 0x5E на ( 0x5E xor 0x20) = 0x7E.
0x7D, 0x5D = отбросить 0x7D, заменить 0x5D на ( 0x5D xor 0x20) = 0x7D.

#### Задача 3. Кнопка

Используя практическое задание №2, необходимо «разобрать» кнопку, т.е. отправлять в консоль данные ее нажатия.

### Решение

#### Задача 1. Локальный чат