import http.server
import socketserver
import threading
import os
import subprocess
import urllib.parse
import webview

PORT = 8080

# Dynamische Pfad-Ermittlung (Funktioniert auf jedem PC und mit jedem Benutzernamen!)
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
DRIVER_PATH = os.path.join(BASE_DIR, "notmyfault_driver.ko")
INDEX_PATH = os.path.join(BASE_DIR, "index.html")

def auto_load_driver():
    if not os.path.exists("/proc/notmyfault") and os.path.exists(DRIVER_PATH):
        try:
            subprocess.run(["sudo", "insmod", DRIVER_PATH], check=True)
        except Exception:
            pass

def send_kernel_cmd(command):
    if not os.path.exists("/proc/notmyfault"):
        return False
    try:
        with open("/proc/notmyfault", "w") as f:
            f.write(command)
        return True
    except Exception:
        return False

class AttackAPIHandler(http.server.SimpleHTTPRequestHandler):
    def do_POST(self):
        if self.path == "/api/trigger":
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length).decode('utf-8')
            params = urllib.parse.parse_qs(post_data)
            cmd = params.get('cmd', [''])
            
            success = send_kernel_cmd(cmd)
            
            self.send_response(200 if success else 500)
            self.send_header("Content-Type", "application/json")
            self.end_headers()
            response = '{"status": "success"}' if success else '{"status": "error"}'
            self.wfile.write(response.encode('utf-8'))

    def do_GET(self):
        if self.path == "/" or self.path == "/index.html":
            self.send_response(200)
            self.send_header("Content-Type", "text/html")
            self.end_headers()
            with open(INDEX_PATH, "rb") as f:
                self.wfile.write(f.read())
        else:
            os.chdir(BASE_DIR)
            super().do_GET()

def start_server():
    socketserver.TCPServer.allow_reuse_address = True
    with socketserver.TCPServer(("", PORT), AttackAPIHandler) as httpd:
        httpd.serve_forever()

if __name__ == "__main__":
    auto_load_driver()
    threading.Thread(target=start_server, daemon=True).start()
    
    # Startet das App-Fenster universell mit relativem HTML-Inhalt
    webview.create_window("CortexCrash Engine", f"http://localhost:{PORT}/", width=1020, height=680, resizable=False)
    webview.start()
