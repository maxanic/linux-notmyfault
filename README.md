# Linux NotMyFault

A native equivalent to the Windows Sysinternals **NotMyFault** tool, rewritten for Linux. It provides a graphical user interface (GUI) to intentionally trigger kernel memory leaks, system hangs, memory page faults, and hard kernel panics (BSOD) for debugging and testing purposes.

## Universal 1-Line Installation
Run this command on any major distribution to install dependencies, build the driver, and launch the UI:
```bash
curl -sSL https://githubusercontent.com | sudo bash
```

## Manual Build
```bash
make
sudo insmod notmyfault_driver.ko
sudo python3 notmyfault_gui.py
```
