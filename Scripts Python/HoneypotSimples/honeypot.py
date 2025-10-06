
import socket
import threading

HOST = "0.0.0.0"
PORT = 2222

def handle_client(conn, addr):
    print(f"Acesso detectado: {addr}")
    conn.send(b"Bem-vindo ao serviço seguro\n")
    conn.close()

def start_honeypot():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((HOST, PORT))
    server.listen(5)
    print(f"Honeypot rodando em {HOST}:{PORT}")

    while True:
        conn, addr = server.accept()
        threading.Thread(target=handle_client, args=(conn, addr)).start()

if __name__ == "__main__":
    start_honeypot()
