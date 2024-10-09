key = "der stend dei kongjen til domar."

flag  = []

with open("text.txt") as f:
    found = False
    skip = False
    non_empty = False

    for line in f:
        clean = line.strip()

        if non_empty and clean:
            for c in clean:
                if c.strip():
                    flag.append(c)
            non_empty = False

        if skip:
            skip = False
            non_empty = True
            continue

        if clean == key:
            found = True
            skip = True
            continue

if flag:
    for i in flag:
        print(i, end="")


