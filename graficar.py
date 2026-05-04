import matplotlib.pyplot as plt
import numpy as np

x_pts = [2.74, 3.25, 3.95, 5.23, 5.98, 7.02, 7.93]
y_pts = [2.46, 3.72, 4.46, 4.96, 5.64, 6.03, 5.81]

plt.scatter(x_pts, y_pts, color='black', zorder=5, label='Nodos (datos)')

x_val = np.linspace(2.74, 3.25, 100)
y_val = -1.06789*(x_val - 2.74)**3 + 0*(x_val - 2.74)**2 + 2.74835*(x_val - 2.74) + 2.46
plt.plot(x_val, y_val, label='Tramo 0')
x_val = np.linspace(3.25, 3.95, 100)
y_val = 0.583242*(x_val - 3.25)**3 + -1.63388*(x_val - 3.25)**2 + 1.91507*(x_val - 3.25) + 3.72
plt.plot(x_val, y_val, label='Tramo 1')
x_val = np.linspace(3.95, 5.23, 100)
y_val = 0.261981*(x_val - 3.95)**3 + -0.40907*(x_val - 3.95)**2 + 0.485005*(x_val - 3.95) + 4.46
plt.plot(x_val, y_val, label='Tramo 2')
x_val = np.linspace(5.23, 5.98, 100)
y_val = -0.473796*(x_val - 5.23)**3 + 0.596937*(x_val - 5.23)**2 + 0.725474*(x_val - 5.23) + 4.96
plt.plot(x_val, y_val, label='Tramo 3')
x_val = np.linspace(5.98, 7.02, 100)
y_val = 0.0383877*(x_val - 5.98)**3 + -0.469105*(x_val - 5.98)**2 + 0.821349*(x_val - 5.98) + 5.64
plt.plot(x_val, y_val, label='Tramo 4')
x_val = np.linspace(7.02, 7.93, 100)
y_val = 0.127961*(x_val - 7.02)**3 + -0.349335*(x_val - 7.02)**2 + -0.0298284*(x_val - 7.02) + 6.03
plt.plot(x_val, y_val, label='Tramo 5')

plt.title('Interpolacion por Trazadores Cubicos Naturales')
plt.xlabel('X')
plt.ylabel('Y')
plt.legend()
plt.grid(True)
plt.show()
