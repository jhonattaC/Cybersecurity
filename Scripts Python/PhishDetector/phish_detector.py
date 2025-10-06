
import argparse
import email
from urllib.parse import urlparse

def analyze_email(file_path):
    with open(file_path, "r") as f:
        msg = email.message_from_file(f)
    print("Remetente:", msg.get("From"))
    print("Assunto:", msg.get("Subject"))

    links = []
    if msg.is_multipart():
        for part in msg.walk():
            if part.get_content_type() == "text/plain":
                body = part.get_payload(decode=True).decode(errors="ignore")
                links += [word for word in body.split() if "http" in word]
    else:
        body = msg.get_payload(decode=True).decode(errors="ignore")
        links += [word for word in body.split() if "http" in word]

    print("\nLinks suspeitos:")
    for link in links:
        domain = urlparse(link).netloc
        print(f"{link} -> {domain}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Phishing Email Detector")
    parser.add_argument("--email", required=True, help="Email file (.eml)")
    args = parser.parse_args()
    analyze_email(args.email)
