with open("lookupTable.txt", "w") as f:
    f.write("uint64_t lookupTable[0x400] = {\n\t")
    lookupTable = [0] * 0x400
    for grid in range(0x10000):
        if grid % 0x40 == 0:
            f.write("0b")
        if (grid & 0xF == 0xF) or (grid & 0xF0 == 0xF0) or \
           (grid & 0xF00 == 0xF00) or (grid & 0xF000 == 0xF000) or \
           (grid & 0x1111 == 0x1111) or (grid & 0x2222 == 0x2222) or \
           (grid & 0x4444 == 0x4444) or (grid & 0x8888 == 0x8888) or \
           (grid & 0x8421 == 0x8421) or (grid & 0x1248 == 0x1248):

            #firstIndex = grid >> 6
            #secondIndex = grid & 0x3F
            lookupTable[firstIndex] |= (1 << secondIndex)
            f.write("1")
        else:
            f.write("0")
        if grid % 0x40 == 0x3f:
            f.write(",  ")
        if grid % 0x100 == 0x0ff:
            f.write("\n\t")
    f.write("};\n")