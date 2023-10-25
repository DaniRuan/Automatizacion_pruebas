'''
Save terminal output logs in a folder
By Daniel Ruán
Email: A01731921@tec.mx
EDAG - ITESM Intership

'''
import subprocess
import os
from datetime import datetime

folder = "logs"

# If the folder exists or not
if not os.path.exists(folder):
    os.makedirs(folder)

# Number of file
log_number = 1
while True:
    file_name = f"log{log_number}.txt"
    log_file_path = os.path.join(folder, file_name)

    if not os.path.exists(log_file_path):
        break

    log_number += 1

# Command with details
command = f"pio test -v"

# Create a subprocess and redirect info
with open(log_file_path, 'w') as log_file:
    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, universal_newlines=True)  # , stderr=subprocess.STDOUT
    for line in process.stdout:
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")  # Get current timestamp
        log_line = f"[{timestamp}] {line}"  # Add timestamp to each line
        print(log_line, end='')  # Print to the terminal
        log_file.write(log_line)  # Write to the log file

print(f"\nTest output saved in {log_file_path}\n")
