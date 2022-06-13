# после запуска данного скрипта программа будет автоматически запускаться при запуске компьютера
import os
import getpass

USER_NAME = getpass.getuser()  # сохраним в эту переменную логин пользователя


def add_to_startup(file_path="D:\\work\\DZ_var_1.py"):
    bat_patch = r'C:\Users\%s\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup' % USER_NAME
    with open(bat_patch + '\\' + "open.bat", "w+") as bat_file:
        bat_file.write(r'D:\work\venv\Scripts\python.exe %s' % file_path)


add_to_startup()
