import matplotlib.pyplot as plt
import matplotlib.animation as animation
import serial
import json
from collections import deque

# Configurați portul serial
ser = serial.Serial('COM7', 115200)  # Folosim COM7 pentru conexiunea serială

# Inițializam deque-uri pentru ax și ay, limitate la 20 de puncte
ax_data = deque(maxlen=20)
ay_data = deque(maxlen=20)

# Setările grafice
fig, ax = plt.subplots()
ax.set_xlim(-1000, 1000)  # Ajustam limitele axei X
ax.set_ylim(-1000, 1000)  # Ajustam limitele axei Y
ax.set_xlabel('ax')
ax.set_ylabel('ay')
ax.axhline(0, color='black', linewidth=0.8)  # Linia orizontală la y=0
ax.axvline(0, color='black', linewidth=0.8)  # Linia verticală la x=0

# Inițializați linii goale pentru ax și ay
line, = ax.plot([], [], '-', label='ax vs ay')  # Linie continuă pentru conectarea punctelor
ax.legend()

def init():
    line.set_data([], [])
    return line,

def update(frame):
    try:
        line_data = ser.readline().decode('utf-8').strip()
        data = json.loads(line_data)
        ax_value = data['ax']
        ay_value = data['ay']
        
        # Adaugăm valorile la deque-uri (se păstrează doar ultimele 20 de puncte)
        ax_data.append(ax_value)
        ay_data.append(ay_value)
        
        # Datele pentru grafic
        line.set_data(ax_data, ay_data)
        
        # Ajustam limitele pentru axa X și Y pentru a include ultimele 20 de puncte
        if len(ax_data) > 0:
            ax.set_xlim(min(ax_data) - 10, max(ax_data) + 10)
            ax.set_ylim(min(ay_data) - 10, max(ay_data) + 10)
        
        # Afișează coordonatele în consolă
        print(f"ax: {ax_value}, ay: {ay_value}")
        
        return line,
    except json.JSONDecodeError:
        pass  # Ignoră datele care nu sunt în format JSON valid
    except Exception as e:
        print(f"An error occurred: {e}")  # Afișează orice altă eroare

# Animarea graficului
ani = animation.FuncAnimation(fig, update, init_func=init, blit=True, interval=100)

plt.show()
