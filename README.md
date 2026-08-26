# kfinitmod

single bin kernel module loader

## Usage

```bash
[nichole@pop-os:~/Dev/kfinitmod] python3 stamp.py ~/module.ko
wrote generated_data.c 7490840 bytes
[nichole@pop-os:~/Dev/kfinitmod] make
[nichole@pop-os:~/Dev/kfinitmod] ls | grep bin
kfinitmod.bin


....


user@brick5:~$ sudo ./kfinitmod.bin
[sudo] password for user:
loaded
```