![Minitalk logo](.media/minitalk_logo.png)

![Grade badge](https://img.shields.io/badge/125_%2F_100-004d40?label=final%20grade&labelColor=151515&logo=data:image/svg%2bxml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIGhlaWdodD0iMjRweCIgdmlld0JveD0iMCAwIDI0IDI0IiB3aWR0aD0iMjRweCIgZmlsbD0iI0ZGRkZGRiI+PHBhdGggZD0iTTAgMGgyNHYyNEgweiIgZmlsbD0ibm9uZSIvPjxwYXRoIGQ9Ik0xMiAxNy4yN0wxOC4xOCAyMWwtMS42NC03LjAzTDIyIDkuMjRsLTcuMTktLjYxTDEyIDIgOS4xOSA4LjYzIDIgOS4yNGw1LjQ2IDQuNzNMNS44MiAyMXoiLz48L3N2Zz4=) ![Language Badge](https://img.shields.io/badge/C-fe428e?logo=C&label=language&labelColor=151515) ![Norminette Badge](https://img.shields.io/badge/passing-brightgreen?logo=42&label=norminette&labelColor=151515) ![Library Badge](https://img.shields.io/badge/my_own_libft-004d40?logo=GitHub&label=library%20used&labelColor=151515)

# Minitalk

This project is about creating a simple client/server program. Both programs can only communicate through `SIGUSR1` and `SIGUSR2` POSIX signals.
The client encodes each bit of the message and uses `SIGUSR1` to send 0s to the server, and `SIGUSR2` to send 1s. The server accumulates the received bits and stores each byte received into a temporary buffer.
Once a null-terminator `\0` has been received by the server, it prints the message and sends `SIGUSR2` back to the client to close communication. Unicode characters are supported by both client and server.

The full subject can be found [here](.media/en.subject.pdf).

# Downloading and compiling the project

Clone the library and use `make` to compile
```
git clone https://github.com/theozanchi/42_Berlin_minitalk/tree/main
cd 42_Berlin_minitalk
make
```

![Compilation screenshot](.media/compilation_complete_screenshot.png)

# Running the program

Launch the server first
```
./server
```
It displays its process ID:
![Server PID screenshot](.media/server_pid_screenshot.png)

Then messages can be sent from the client:
![Client screenshot](.media/client_screenshot.png)

Unicode characters are supported on both sides:
![Unicode characters screenshot](.media/unicode_characters_screenshot.png)

A message of any size can be passed (examples of 1000 words of Lorem Ipsum):
![Big lorem ipsum example](.media/lorem_ipsum_screenshot.png)
