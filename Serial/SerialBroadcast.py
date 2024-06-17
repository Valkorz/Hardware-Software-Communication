import tkinter as tk
import customtkinter as ctk
from serial import Serial
import struct

#Define serial communication info
port = 'COM3'
baudRate = 9600
ser = Serial(port=port, baudrate=baudRate)

root_window = tk.Tk()
root_window.geometry("720x720")
root_window.title("Serial broadcaster")

label = ctk.CTkLabel(root_window, text="Serial broadcaster: Servo movement", font=("arial bold", 42))
label.place(relx=0.5, rely=0.1, anchor=tk.CENTER)

label_num = ctk.CTkLabel(root_window, text="Fingers (check to open/close):", font=("arial", 16))
label_num.place(relx=0.5, rely=0.2, anchor=tk.CENTER)

#Add checkboxes for each finger
thumb = tk.IntVar()
index = tk.IntVar()
middle = tk.IntVar()
ring = tk.IntVar()
pinky = tk.IntVar()

thumbch = tk.Checkbutton(root_window, text="", variable=thumb)
indexch = tk.Checkbutton(root_window, text="", variable=index)
middlech = tk.Checkbutton(root_window, text="", variable=middle)
ringch = tk.Checkbutton(root_window, text="", variable=ring)
pinkych = tk.Checkbutton(root_window, text="", variable=pinky)

thumbch.place(relx=0.5, rely=0.3, anchor=tk.CENTER)
indexch.place(relx=0.5, rely=0.35, anchor=tk.CENTER)
middlech.place(relx=0.5, rely=0.4, anchor=tk.CENTER)
ringch.place(relx=0.5, rely=0.45, anchor=tk.CENTER)
pinkych.place(relx=0.5, rely=0.5, anchor=tk.CENTER)

#Send to Arduino
def send():
    reset()
    data = [thumb.get(), index.get(), middle.get(), ring.get(), pinky.get()]
    bytes_data = struct.pack('>' + 'B' * len(data), *data)

    print(f"sending: {bytes_data}")
    ser.write(bytes_data)
    
def reset():
    clear = '#'
    ser.write(clear.encode())
    

button_send = ctk.CTkButton(master=root_window, corner_radius=10, 
                                  command=send, 
                                  text="Send to serial")
button_send.place(relx=0.5, rely=0.9, anchor=tk.CENTER)

root_window.mainloop()


