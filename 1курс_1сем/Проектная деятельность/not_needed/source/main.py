import numpy as np
import matplotlib.pyplot as plt

# Определяем функцию и ее производную
def f(x):
    return x**3 - 2*x**2 - 4*x + 7

def df(x):
    return 3*x**2 - 4*x - 4

# Метод хорд (секущих)
def secant_method(f, x0, x1, tol, max_iter):
    iter_count = 0
    while abs(x1 - x0) >= tol and iter_count < max_iter:
        x_temp = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0))
        x0, x1 = x1, x_temp
        iter_count += 1
    return x1, iter_count

# Метод Ньютона (касательных)
def newton_method(f, df, x0, tol, max_iter):
    iter_count = 0
    while abs(f(x0)) >= tol and iter_count < max_iter:
        x0 = x0 - f(x0) / df(x0)
        iter_count += 1
    return x0, iter_count

# Параметры
tolerance = 1e-6
max_iterations = 100

# Поиск корней методами хорд и Ньютона
# Начальные приближения для метода хорд
x0_secant = -3
x1_secant = -2

# Начальное приближение для метода Ньютона
x0_newton = -3

root_secant, iter_secant = secant_method(f, x0_secant, x1_secant, tolerance, max_iterations)
root_newton, iter_newton = newton_method(f, df, x0_newton, tolerance, max_iterations)

print(f"Метод хорд: корень = {root_secant:.6f}, итераций = {iter_secant}")
print(f"Метод Ньютона: корень = {root_newton:.6f}, итераций = {iter_newton}")

# Построение графика функции
x_values = np.linspace(-4, 4, 400)
y_values = f(x_values)

plt.plot(x_values, y_values, label='f(x) = x^3 - 2x^2 - 4x + 7')
plt.axhline(0, color='black', linewidth=0.5)
plt.axvline(0, color='black', linewidth=0.5)
plt.scatter([root_secant, root_newton], [0, 0], color='red', zorder=5)
plt.legend()
plt.title('График функции и найденные корни')
plt.xlabel('x')
plt.ylabel('f(x)')
plt.grid(True)
plt.show()
