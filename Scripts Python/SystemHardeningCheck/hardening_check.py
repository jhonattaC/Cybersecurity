
import os
import platform

def check_linux():
    print("== Checando Linux ==")
    print("Usuários com UID 0:")
    os.system("awk -F: '($3 == 0) {print $1}' /etc/passwd")
    print("\nServiços ativos:")
    os.system("systemctl list-units --type=service --state=running")

def check_windows():
    print("== Checando Windows ==")
    os.system("net user")

if platform.system() == "Linux":
    check_linux()
elif platform.system() == "Windows":
    check_windows()
else:
    print("Sistema não suportado")
