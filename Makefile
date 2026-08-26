all:
	gcc load.c generated_data.c -o kfinitmod.bin

clean:
	rm -f stamp.bin generated_data.c

.PHONY: all clean