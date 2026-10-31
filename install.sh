#!/bin/bash
if [ "$EUID" -ne 0 ]; then echo "Please run as root (sudo bash)!"; exit 1; fi
if [ -f /etc/os-release ]; then . /etc/os-release; DISTRO=$ID; fi
case "$DISTRO" in
    ubuntu|debian|zorin|pop|mint) apt-get update && apt-get install -y build-essential linux-headers-$(uname -r) python3-tk python3 git ;;
    fedora|rhel|centos) dnf groupinstall -y "Development Tools" && dnf install -y kernel-devel-$(uname -r) python3-tkinter git ;;
    arch|manjaro) pacman -Sy --noconfirm base-devel linux-headers tk python git ;;
    *) echo "Unknown distribution. Trying to install generic dependencies..." ;;
esac
cd /tmp && rm -rf linux-notmyfault && git clone https://githubusercontent.com && cd linux-notmyfault && make && insmod notmyfault_driver.ko && python3 notmyfault_gui.py
