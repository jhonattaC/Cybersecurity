
import socket
import argparse

def scan_port(host, port):
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.settimeout(1)
        result = sock.connect_ex((host, port))
        sock.close()
        return result == 0
    except Exception as e:
        return False

def scan_range(host, start, end):
    print(f"Scanning {host} from port {start} to {end}")
    for port in range(start, end + 1):
        if scan_port(host, port):
            print(f"[OPEN] Port {port}")
        else:
            print(f"[CLOSED] Port {port}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Simple Port Scanner")
    parser.add_argument("--host", required=True, help="Target host")
    parser.add_argument("--ports", default="1-1024", help="Port range, e.g., 20-100")
    args = parser.parse_args()

    start, end = map(int, args.ports.split("-"))
    scan_range(args.host, start, end)
