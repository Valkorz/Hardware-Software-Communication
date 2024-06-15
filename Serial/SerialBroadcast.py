import tkinter as tk
import customtkinter as ctk

#Define serial communication info
port = 'COM3'
baudRate = 9600

root_window = tk.Tk()
root_window.geometry("720x720")
root_window.title("Serial broadcaster")
