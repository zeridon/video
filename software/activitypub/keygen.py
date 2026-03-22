"""
keygen.py — Genereer een RSA-keypair voor HTTP Signatures.

Gebruik:
    python keygen.py
    python keygen.py --privkey mijn_privkey.pem --pubkey mijn_pubkey.pem

Bewaar privkey.pem veilig en buiten version control.
"""

import argparse
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives import serialization


def generate(privkey_path: str, pubkey_path: str) -> None:
    key = rsa.generate_private_key(public_exponent=65537, key_size=2048)

    with open(privkey_path, "wb") as f:
        f.write(key.private_bytes(
            encoding=serialization.Encoding.PEM,
            format=serialization.PrivateFormat.PKCS8,
            encryption_algorithm=serialization.NoEncryption(),
        ))

    with open(pubkey_path, "wb") as f:
        f.write(key.public_key().public_bytes(
            encoding=serialization.Encoding.PEM,
            format=serialization.PublicFormat.SubjectPublicKeyInfo,
        ))

    print(f"Geschreven: {privkey_path}")
    print(f"Geschreven: {pubkey_path}")
    print("Voeg privkey.pem toe aan .gitignore!")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--privkey", default="privkey.pem")
    parser.add_argument("--pubkey",  default="pubkey.pem")
    args = parser.parse_args()
    generate(args.privkey, args.pubkey)
