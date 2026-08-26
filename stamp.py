#!/usr/bin/env python3
import sys

XOR_KEY = 0x5A

def main():
    f = open(sys.argv[1], "rb")
    d = f.read()
    f.close()

    out = open("generated_data.c", "w")
    out.write('#include "load.h"\n\n')
    out.write('bin_data_t data = {\n')
    out.write(f'    .len = {len(d)}ULL,\n')
    out.write('    .payload = {')
    
    out.write(", ".join(f"0x{b ^ XOR_KEY:02X}" for b in d))
    
    out.write('}\n')
    out.write('};\n')
    out.close()
    
    print(f"wrote generated_data.c {len(d)} bytes")

if __name__ == "__main__":
    main()