# проект "Угадай число" Вариант 1
import random  # этот модуль выбирает случайные числа или переставляет элементы списка в обратном порядке

current_attempt = 0
attempt_number = 0
max_count_attempts = 8  # макс. число попыток
hidden_number = random.randint(0, 50)  # загаданное число [1; 50]
print('Загадано число от 0 до 50')

while attempt_number < max_count_attempts:  # пока попытки не исчерпаны, даём возможность угадать
    print('Ваше число: ', end='')
    attempt_number += 1
    current_attempt = int(input())
    if current_attempt < hidden_number:
        print('Введённое число меньше загаданного')
    elif current_attempt > hidden_number:
        print('Введённое число больше загаданного')
    else:
        break  # угадали


if current_attempt == hidden_number:
    print('Угадано число {}, количество попыток: {}'.format(hidden_number, attempt_number))
else:
    print('Не угадано число {}, количество попыток: {}'.format(hidden_number, max_count_attempts))
