# создать программу напоминания о предстоящих событиях (автозагрузка)

# это независимый от платформы API для использования функций
import datetime
from tkinter import *  # эта библиотека позволяет использовать графический интерфейс на Python
from tkinter import messagebox
from plyer import notification
from tkcalendar import DateEntry
import pickle  # позволяет сохранять объекты в файл


# cчитывание сигналов из хранилища
def read_file(filename='D:\\work\\alarms.pkl'):
    with open(filename, 'rb') as f:
        try:
            res = pickle.load(f)
            f.close()
            return res
        except pickle.UnpicklingError:
            print('Error while reading from object.')
            return []


# запись списка сигналов в хранилище
def write_file(filename='D:\\work\\alarms.pkl'):
    global alarms
    with open(filename, 'wb') as f:
        try:
            pickle.dump(alarms, f)
            f.close()
        except pickle.PicklingError:
            print('Error while writing an object.')


def check_date(alarm):  # получение данных о сигнале
    current_date = datetime.datetime.now().replace(microsecond=0)
    delta = alarm - current_date
    wait = int(delta.total_seconds()) * 1000
    if wait <= 0:
        return False
    else:
        return wait  # в случае успеха возврат  числового значения ожидания


# добавление сигнала
def get_details():
    global alarms  # определяем переменную alarms как глобальную переменную внутри get_details при помощи global
    get_title = title.get()
    get_message = message.get()
    get_date = app_calendar.get_date()
    get_hours = time_hours.get()
    get_minutes = time_minutes.get()
    if get_title == "" or \
            get_message == "" or \
            get_date == "" or \
            get_hours == "" or \
            get_minutes == "":
        messagebox.showerror("Alert", "Необходимо заполнить все поля")
        return
    elif (not get_hours.isdigit()) or \
            (not get_minutes.isdigit()) or \
            (int(get_hours) not in [i for i in range(0, 24)]) or \
            (int(get_minutes) not in [i for i in range(0, 60)]):
        messagebox.showerror("Alert", "Некорректные значения времени")
        return
    else:
        alarm = datetime.datetime(day=get_date.day,
                                  month=get_date.month,
                                  year=get_date.year,
                                  hour=int(get_hours),
                                  minute=int(get_minutes),
                                  second=0)
        wait = check_date(alarm)
        if wait:
            collision_flag = False
            for i in range(len(alarms)):
                if (alarms[i][2].day == alarm.day) and \
                        (alarms[i][2].month == alarm.month) and \
                        (alarms[i][2].month == alarm.month) and \
                        (alarms[i][2].year == alarm.year) and \
                        (alarms[i][2].hour == alarm.hour) and \
                        (alarms[i][2].minute == alarm.minute):
                    collision_flag = True
                    break
            if not collision_flag:
                alarms.append([get_title, get_message, alarm])

                if len(alarms) == 1:
                    set_notifications()
            else:
                messagebox.showerror("Alert", "Такая дата/время уже занята")
        else:
            messagebox.showerror("Alert", "Указана прошедшая дата/время")
        alarms.sort(key=lambda x: x[2])  # сортировка по возрастанию
        print(alarms)
        return


def exec_notification(alarm_index):
    global alarms
    if len(alarms) > 0:
        notification.notify(title=alarms[alarm_index][0], message=alarms[alarm_index][1])
        del alarms[alarm_index]
        set_notifications()


# обход уже существующего хранилища и установка в работу уведомлений
def set_notifications():
    global alarms
    if len(alarms) > 0:
        wait = check_date(alarms[0][2])
        print(alarms[0][0], wait, sep=" ")
        if wait > 0:
            root.after(wait, exec_notification, 0)
        else:
            del alarms[0]
            set_notifications()  # пока список сигналов непуст, set_notifications() будет рекурсивно вызываться


def entry_point():
    activateButton.config(state=DISABLED)
    addButton.config(state="normal")
    set_notifications()


root = Tk()
root.title("Notifier-app")
root.geometry("500x500")

# описание интерфейса (формы для ввода, кнопка, календарь)
title_label = Label(root, text="Название уведомления", font=("arial", 10))
title_label.place(x=12, y=70)
title = Entry(root, width="40", font=("arial", 10))
title.place(x=160, y=70)

message_label = Label(root, text="Отображать сообщение", font=("arial", 10))
message_label.place(x=12, y=120)
message = Entry(root, width="40", font=("arial", 10))
message.place(x=160, y=120)

date_label = Label(root, text="Установить дату", font=("arial", 10))
date_label.place(x=12, y=170)
app_calendar = DateEntry(root, selectmode='day')
app_calendar.place(x=160, y=170)

time_label = Label(root, text="Установить время", font=("arial", 10))
time_label.place(x=12, y=380)
time_hours = Entry(root, width=5)
time_hours.place(x=160, y=380)
time_minutes = Entry(root, width=5)
time_minutes.place(x=195, y=380)


activateButton = Button(root,
                        text="Запуск",
                        font=("arial", 10), width=20,
                        fg="#FFFFFF", bg="#00008B",
                        command=entry_point)
activateButton.place(x=150, y=450)

addButton = Button(root,
                   text="Установить уведомление",
                   font=("arial", 10), width=20,
                   fg="#FFFFFF", bg="#00008B",
                   command=get_details,
                   state=DISABLED)
addButton.place(x=150, y=410)

alarms = read_file()
root.resizable(0, 0)
root.mainloop()
write_file()  # обновление хранилища
