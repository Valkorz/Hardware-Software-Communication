import tkinter as tk
import customtkinter as ctk
from serial import Serial

#Define serial communication info
port = 'COM3'
baudRate = 9600
ser = Serial(port=port, baudrate=baudRate)

root_window = tk.Tk()
root_window.geometry("720x720")
root_window.title("Serial broadcaster")

label = ctk.CTkLabel(root_window, text="Serial broadcaster: Servo movement", font=("arial bold", 42))
label.place(relx=0.5, rely=0.1, anchor=tk.CENTER)

label_num = ctk.CTkLabel(root_window, text="Servo ID:", font=("arial", 16))
label_num.place(relx=0.5, rely=0.2, anchor=tk.CENTER)

label_rot = ctk.CTkLabel(root_window, text="Servo rotation:", font=("arial", 16))
label_rot.place(relx=0.5, rely=0.4, anchor=tk.CENTER)

#Servo ID entry
textbox_num = tk.Entry(root_window, font=("arial", 16))
textbox_num.place(relx=0.5, rely=0.3, anchor=tk.CENTER)

#Servo angle entry
textbox_rot = tk.Entry(root_window, font=("arial", 16))
textbox_rot.place(relx=0.5, rely=0.5, anchor=tk.CENTER)

#Send to Arduino
def send():
    print(f"sending: {textbox_rot.get()}")
    bytes = textbox_rot.get().encode()
    ser.write(bytes)
    

button_send = ctk.CTkButton(master=root_window, corner_radius=10, 
                                  command=send, 
                                  text="Send to serial")
button_send.place(relx=0.5, rely=0.9, anchor=tk.CENTER)

root_window.mainloop()


