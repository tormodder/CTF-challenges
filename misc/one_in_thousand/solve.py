from pwn import *

counter = 1

while True:
    r = remote("127.0.0.1", 6789)
    content = r.recvall()
    counter += 1 
    if (b"CTF" in content):
        print(content)
        print(f"took {counter} attempts")
        break
