import hashlib

input_file = "rockyou.txt"

with open(input_file, "rb") as f_in:
    for line in f_in:
        password_bytes = line.rstrip(b"\r\n")

        # Compute SHA-256 hex digest
        sha256_hash = hashlib.sha256(password_bytes).hexdigest()
        if sha256_hash == "8ec47631827329eb114714a20d9b3eeb8a9a4293bd5d6823af0632e8d4f30dfa" :
            print(password_bytes.decode("utf-8"))

