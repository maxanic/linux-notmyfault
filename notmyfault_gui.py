import tkinter as tk
from tkinter import messagebox
import os
def send_cmd(command):
	if not os.path.exists("/proc/notmyfault"):
		messagebox.showerror("Error", "Kernel module driver is not loaded!")
		return
	try:
		with open("/proc/notmyfault", "w") as f: f.write(command)
	except Exception as e: messagebox.showerror("Error", f"Execution failed: {e}")
root = tk.Tk()
root.title("Linux NotMyFault v2.0")
root.geometry("460x420")
root.configure(bg="#121212")
root.resizable(False, False)
tk.Label(root, text="LINUX NOTMYFAULT", font=("Courier", 18, "bold"), fg="#00FF00", bg="#121212").pack(pady=15)
s = {"font": ("Courier", 10, "bold"), "width": 38, "bd": 0, "pady": 8, "cursor": "hand2"}
tk.Button(root, text="[+] KERNEL MEMORY LEAK (256MB)", bg="#FF9F00", fg="#000000", command=lambda: [send_cmd("leak"), lbl_status.config(text="STATUS: 256MB allocated in kernel space!", fg="#FF9F00")], **s).pack(pady=8)
tk.Button(root, text="[*] SIMULATE HARD SYSTEM HANG", bg="#D35400", fg="#FFFFFF", command=lambda: send_cmd("hang") if messagebox.askyesno("WARNING", "This will freeze all CPU cores. Continue?") else None, **s).pack(pady=8)
tk.Button(root, text="[!] MEMORY PAGE FAULT (BAD POINTER)", bg="#E74C3C", fg="#FFFFFF", command=lambda: send_cmd("pagefault") if messagebox.askyesno("WARNING", "Trigger bad pointer dereference in kernel?") else None, **s).pack(pady=8)
tk.Button(root, text="[!!] HARD KERNEL PANIC (BSOD)", bg="#FF0000", fg="#FFFFFF", command=lambda: send_cmd("panic") if messagebox.askyesno("CRITICAL WARNING", "Trigger immediate unrecoverable kernel panic?") else None, **s).pack(pady=8)
lbl_status = tk.Label(root, text="STATUS: System stable. Ready to deploy.", fg="#00FF00", bg="#121212", font=("Courier", 9, "italic"))
lbl_status.pack(pady=25)
root.mainloop()
