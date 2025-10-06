
import random
import string
import argparse

def generate_password(length=12):
    chars = string.ascii_letters + string.digits + string.punctuation
    password = ''.join(random.choice(chars) for _ in range(length))
    return password

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Secure Password Generator")
    parser.add_argument("--length", type=int, default=12, help="Password length")
    args = parser.parse_args()

    pwd = generate_password(args.length)
    print(f"Senha gerada ({args.length} caracteres): {pwd}")
