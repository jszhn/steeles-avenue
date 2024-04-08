def val2bin(write: int) -> int:
    bin = 1
    for i in range(write):
        bin = bin << 1
        bin += 1
    return bin

print(bin(val2bin(9)))