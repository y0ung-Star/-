# РЕШЕНИЕ ИНДИВИДУАЛЬНОГО ЗАДАНИЯ ПО ТЕОРИИ ПОЛЯ (ВАРИАНТ 5)

**Выполнил:** студент группы М3О-225БВ-24 Егоров А.В.  
**Кафедра:** №304  
**Преподаватель:** Машкин М.Н.  

---

## ИСХОДНЫЕ ДАННЫЕ

**Векторные поля:**
- $\vec{a} = y^2 \vec{i} + z^2 \vec{j} + x^2 \vec{k}$
- $\vec{b} = (2xy^3z + y) \vec{i} + (3x^2y^2z + x) \vec{j} + (x^2y^3 + 4z^3) \vec{k}$

**Поверхность $S$:**
Часть единичной сферы $x^2 + y^2 + z^2 = 1$, лежащая в первом октанте ($x \ge 0, y \ge 0, z \ge 0$). Направление нормали $\vec{n}$ — внешнее по отношению к сфере.

---

## ЧАСТЬ 1. ИССЛЕДОВАНИЕ ВЕКТОРНОГО ПОЛЯ $\vec{a}$

### Задача 1. Определение класса поля $\vec{a}$

Вычислим дивергенцию (divergence) поля $\vec{a}$:
$$\text{div }\vec{a} = \nabla \cdot \vec{a} = \frac{\partial a_x}{\partial x} + \frac{\partial a_y}{\partial y} + \frac{\partial a_z}{\partial z}$$
Так как:
- $a_x = y^2 \implies \frac{\partial a_x}{\partial x} = 0$
- $a_y = z^2 \implies \frac{\partial a_y}{\partial y} = 0$
- $a_z = x^2 \implies \frac{\partial a_z}{\partial z} = 0$

Получаем:
$$\text{div }\vec{a} = 0 + 0 + 0 = 0$$

Вычислим ротор (curl) поля $\vec{a}$:
$$\text{rot }\vec{a} = \nabla \times \vec{a} = \begin{vmatrix} \vec{i} & \vec{j} & \vec{k} \\ \frac{\partial}{\partial x} & \frac{\partial}{\partial y} & \frac{\partial}{\partial z} \\ y^2 & z^2 & x^2 \end{vmatrix}$$
$$\text{rot }\vec{a} = \left(\frac{\partial(x^2)}{\partial y} - \frac{\partial(z^2)}{\partial z}\right)\vec{i} + \left(\frac{\partial(y^2)}{\partial z} - \frac{\partial(x^2)}{\partial x}\right)\vec{j} + \left(\frac{\partial(z^2)}{\partial x} - \frac{\partial(y^2)}{\partial y}\right)\vec{k}$$
$$\text{rot }\vec{a} = -2z \vec{i} - 2x \vec{j} - 2y \vec{k}$$

**Вывод:** Так как $\text{div }\vec{a} = 0$, но $\text{rot }\vec{a} \ne \vec{0}$, векторное поле $\vec{a}$ является **соленоидальным** (трубчатым).

---

### Задача 2. Вычисление потока $P$ поля $\vec{a}$ через поверхность $S$

#### Метод 2.1. С помощью теоремы Гаусса-Остроградского (замыкание координатными плоскостями)
Чтобы применить теорему, замкнем поверхность $S$ частями координатных плоскостей, лежащими в первом октанте:
- $S_{xy}$: $z = 0, x^2 + y^2 \le 1, x, y \ge 0$ (внешняя нормаль $\vec{n}_{xy} = -\vec{k}$)
- $S_{yz}$: $x = 0, y^2 + z^2 \le 1, y, z \ge 0$ (внешняя нормаль $\vec{n}_{yz} = -\vec{i}$)
- $S_{xz}$: $y = 0, x^2 + z^2 \le 1, x, z \ge 0$ (внешняя нормаль $\vec{n}_{xz} = -\vec{j}$)

Тогда замкнутая поверхность $S_{cl} = S \cup S_{xy} \cup S_{yz} \cup S_{xz}$ ограничивает область $V$ — одну восьмую часть единичного шара.

По теореме Гаусса-Остроградского:
$$P_{cl} = \oiint_{S_{cl}} \vec{a} \cdot d\vec{S} = \iint_{V} \text{div }\vec{a} \, dV$$
Так как $\text{div }\vec{a} = 0$, получаем:
$$P_{cl} = \iiint_{V} 0 \, dV = 0 \implies P_S + P_{xy} + P_{yz} + P_{xz} = 0$$
Откуда:
$$P_S = -(P_{xy} + P_{yz} + P_{xz})$$

Вычислим потоки через замыкающие плоские грани:
1. **На грани $S_{xy}$** ($z = 0, \vec{n} = -\vec{k}$):
   $$\vec{a} \cdot \vec{n} = (y^2, z^2, x^2) \cdot (0, 0, -1) = -x^2$$
   $$P_{xy} = \iint_{S_{xy}} -x^2 \, dx dy$$
   Перейдем к полярным координатам ($x = r\cos\varphi, y = r\sin\varphi$, якобиан $J = r$, $r \in [0, 1], \varphi \in [0, \pi/2]$):
   $$P_{xy} = -\int_{0}^{\pi/2} \cos^2\varphi \, d\varphi \int_{0}^{1} r^3 \, dr = -\left[\frac{\varphi}{2} + \frac{\sin 2\varphi}{4}\right]_{0}^{\pi/2} \cdot \left[\frac{r^4}{4}\right]_{0}^{1} = -\frac{\pi}{4} \cdot \frac{1}{4} = -\frac{\pi}{16}$$

2. **На грани $S_{yz}$** ($x = 0, \vec{n} = -\vec{i}$):
   $$\vec{a} \cdot \vec{n} = (y^2, z^2, x^2) \cdot (-1, 0, 0) = -y^2$$
   $$P_{yz} = \iint_{S_{yz}} -y^2 \, dy dz = -\frac{\pi}{16} \quad \text{(в силу симметрии)}$$

3. **На грани $S_{xz}$** ($y = 0, \vec{n} = -\vec{j}$):
   $$\vec{a} \cdot \vec{n} = (y^2, z^2, x^2) \cdot (0, -1, 0) = -z^2$$
   $$P_{xz} = \iint_{S_{xz}} -z^2 \, dx dz = -\frac{\pi}{16} \quad \text{(в силу симметрии)}$$

Итоговый поток через сферу $S$:
$$P_S = -\left(-\frac{\pi}{16} - \frac{\pi}{16} - \frac{\pi}{16}\right) = \frac{3\pi}{16}$$

#### Метод 2.2. Непосредственное вычисление поверхностного интеграла
На сфере единичного радиуса внешняя единичная нормаль совпадает с радиус-вектором точки: $\vec{n} = (x, y, z)$.
Элемент площади сферы в сферических координатах ($r=1$): $dS = \sin\theta \, d\theta d\varphi$, где $\theta \in [0, \pi/2], \varphi \in [0, \pi/2]$.

Вычислим скалярное произведение $\vec{a} \cdot \vec{n}$:
$$\vec{a} \cdot \vec{n} = y^2 x + z^2 y + x^2 z$$
Поток:
$$P_S = \iint_{S} (y^2 x + z^2 y + x^2 z) \, dS$$
В силу полной симметрии подынтегрального выражения и области интегрирования относительно перестановки переменных $x, y, z$:
$$\iint_{S} y^2 x \, dS = \iint_{S} z^2 y \, dS = \iint_{S} x^2 z \, dS$$
Следовательно:
$$P_S = 3 \iint_{S} x^2 z \, dS$$

Вычислим один интеграл в сферических координатах ($x = \sin\theta\cos\varphi, z = \cos\theta$):
$$\iint_{S} x^2 z \, dS = \int_{0}^{\pi/2} d\varphi \int_{0}^{\pi/2} (\sin\theta\cos\varphi)^2 \cos\theta \cdot \sin\theta \, d\theta$$
$$\iint_{S} x^2 z \, dS = \left(\int_{0}^{\pi/2} \cos^2\varphi \, d\varphi\right) \cdot \left(\int_{0}^{\pi/2} \sin^3\theta \cos\theta \, d\theta\right)$$
Вычислим сомножители:
- $\int_{0}^{\pi/2} \cos^2\varphi \, d\varphi = \frac{\pi}{4}$
- $\int_{0}^{\pi/2} \sin^3\theta \cos\theta \, d\theta = \left[ \frac{\sin^4\theta}{4} \right]_{0}^{\pi/2} = \frac{1}{4}$

Получаем:
$$\iint_{S} x^2 z \, dS = \frac{\pi}{4} \cdot \frac{1}{4} = \frac{\pi}{16}$$
Следовательно:
$$P_S = 3 \cdot \frac{\pi}{16} = \frac{3\pi}{16}$$

**Результаты совпали.** $P_S = \frac{3\pi}{16}$.

---

### Задача 3. Вычисление циркуляции $C$ поля $\vec{a}$ по контуру $L$

Контур $L$ состоит из трех дуг окружностей единичного радиуса в координатных плоскостях, обходимых против часовой стрелки (если смотреть снаружи сферы):
- $L_1$: дуга в плоскости $xy$ ($z=0$) от $(1, 0, 0)$ до $(0, 1, 0)$
- $L_2$: дуга в плоскости $yz$ ($x=0$) от $(0, 1, 0)$ до $(0, 0, 1)$
- $L_3$: дуга в плоскости $zx$ ($y=0$) от $(0, 0, 1)$ до $(1, 0, 0)$

#### Метод 3.1. С помощью теоремы Стокса
По теореме Стокса:
$$C = \oint_{L} \vec{a} \cdot d\vec{r} = \iint_{S} \text{rot }\vec{a} \cdot \vec{n} \, dS$$
Мы ранее нашли: $\text{rot }\vec{a} = -2z \vec{i} - 2x \vec{j} - 2y \vec{k}$, а $\vec{n} = (x, y, z)$.
$$\text{rot }\vec{a} \cdot \vec{n} = -2zx - 2xy - 2yz = -2(xy + yz + zx)$$
Следовательно:
$$C = \iint_{S} -2(xy + yz + zx) \, dS = -2 \left( \iint_{S} xy \, dS + \iint_{S} yz \, dS + \iint_{S} zx \, dS \right)$$
В силу симметрии:
$$C = -6 \iint_{S} xy \, dS$$

Вычислим интеграл в сферических координатах ($x = \sin\theta\cos\varphi, y = \sin\theta\sin\varphi$):
$$\iint_{S} xy \, dS = \int_{0}^{\pi/2} d\varphi \int_{0}^{\pi/2} \sin^2\theta \sin\varphi\cos\varphi \cdot \sin\theta \, d\theta$$
$$\iint_{S} xy \, dS = \left(\int_{0}^{\pi/2} \sin\varphi\cos\varphi \, d\varphi\right) \cdot \left(\int_{0}^{\pi/2} \sin^3\theta \, d\theta\right)$$
- $\int_{0}^{\pi/2} \sin\varphi\cos\varphi \, d\varphi = \left[\frac{\sin^2\varphi}{2}\right]_{0}^{\pi/2} = \frac{1}{2}$
- $\int_{0}^{\pi/2} \sin^3\theta \, d\theta = \int_{0}^{\pi/2} (1 - \cos^2\theta) \sin\theta \, d\theta = \left[-\cos\theta + \frac{\cos^3\theta}{3}\right]_{0}^{\pi/2} = 0 - \left(-1 + \frac{1}{3}\right) = \frac{2}{3}$

Получаем:
$$\iint_{S} xy \, dS = \frac{1}{2} \cdot \frac{2}{3} = \frac{1}{3}$$
Следовательно, циркуляция:
$$C = -6 \cdot \frac{1}{3} = -2$$

#### Метод 3.2. Непосредственное интегрирование по контуру $L$
Циркуляция равна сумме криволинейных интегралов по трем дугам: $C = C_1 + C_2 + C_3$.

1. **Интеграл по дуге $L_1$** ($z = 0, dz = 0$):
   Поле на дуге: $a_x = y^2, a_y = 0$.
   $$C_1 = \int_{L_1} y^2 \, dx$$
   Параметризация: $x = \cos t, y = \sin t, t \in [0, \pi/2]$, $dx = -\sin t \, dt$.
   $$C_1 = \int_{0}^{\pi/2} \sin^2 t (-\sin t) \, dt = -\int_{0}^{\pi/2} \sin^3 t \, dt = -\frac{2}{3}$$

2. **Интеграл по дуге $L_2$** ($x = 0, dx = 0$):
   Поле на дуге: $a_y = z^2, a_z = 0$.
   $$C_2 = \int_{L_2} z^2 \, dy$$
   Параметризация: $y = \cos t, z = \sin t, t \in [0, \pi/2]$, $dy = -\sin t \, dt$.
   $$C_2 = \int_{0}^{\pi/2} \sin^2 t (-\sin t) \, dt = -\frac{2}{3}$$

3. **Интеграл по дуге $L_3$** ($y = 0, dy = 0$):
   Поле на дуге: $a_z = x^2, a_x = 0$.
   $$C_3 = \int_{L_3} x^2 \, dz$$
   Параметризация: $z = \cos t, x = \sin t, t \in [0, \pi/2]$, $dz = -\sin t \, dt$.
   $$C_3 = \int_{0}^{\pi/2} \sin^2 t (-\sin t) \, dt = -\frac{2}{3}$$

Итоговая циркуляция:
$$C = C_1 + C_2 + C_3 = -\frac{2}{3} - \frac{2}{3} - \frac{2}{3} = -2$$

**Результаты совпали.** $C = -2$.

---

## ЧАСТЬ 2. ИССЛЕДОВАНИЕ ВЕКТОРНОГО ПОЛЯ $\vec{b}$

### Задача 4. Анализ поля $\vec{b}$

#### 4.1. Проверка потенциальности поля $\vec{b}$
Вычислим ротор поля $\vec{b}$:
$$\text{rot }\vec{b} = \nabla \times \vec{b} = \begin{vmatrix} \vec{i} & \vec{j} & \vec{k} \\ \frac{\partial}{\partial x} & \frac{\partial}{\partial y} & \frac{\partial}{\partial z} \\ 2xy^3z + y & 3x^2y^2z + x & x^2y^3 + 4z^3 \end{vmatrix}$$

Вычислим компоненты ротора:
- Компонента $\vec{i}$:
  $$\frac{\partial b_z}{\partial y} - \frac{\partial b_y}{\partial z} = \frac{\partial(x^2y^3 + 4z^3)}{\partial y} - \frac{\partial(3x^2y^2z + x)}{\partial z} = 3x^2y^2 - 3x^2y^2 = 0$$
- Компонента $\vec{j}$:
  $$\frac{\partial b_x}{\partial z} - \frac{\partial b_z}{\partial x} = \frac{\partial(2xy^3z + y)}{\partial z} - \frac{\partial(x^2y^3 + 4z^3)}{\partial x} = 2xy^3 - 2xy^3 = 0$$
- Компонента $\vec{k}$:
  $$\frac{\partial b_y}{\partial x} - \frac{\partial b_x}{\partial y} = \frac{\partial(3x^2y^2z + x)}{\partial x} - \frac{\partial(2xy^3z + y)}{\partial y} = (6xy^2z + 1) - (6xy^2z + 1) = 0$$

Получаем:
$$\text{rot }\vec{b} = \vec{0}$$
**Вывод:** Так как ротор поля равен нулю во всем пространстве, векторное поле $\vec{b}$ является **потенциальным**.

#### 4.2. Нахождение потенциала $U(x, y, z)$ поля $\vec{b}$
Потенциал $U$ связан с полем соотношением $\vec{b} = \text{grad } U$. Найдем $U$ интегрированием по ломаной от точки $O(0,0,0)$ до $M(x,y,z)$:
$$U(x, y, z) = \int_{0}^{x} b_x(t, 0, 0) \, dt + \int_{0}^{y} b_y(x, t, 0) \, dt + \int_{0}^{z} b_z(x, y, t) \, dt$$

Вычислим интегралы поочередно:
1. **Первый интеграл** ($y=0, z=0$):
   $$b_x(t, 0, 0) = 2 \cdot t \cdot 0^3 \cdot 0 + 0 = 0$$
   $$\int_{0}^{x} 0 \, dt = 0$$

2. **Второй интеграл** ($z=0$, $x$ фиксирован):
   $$b_y(x, t, 0) = 3 \cdot x^2 \cdot t^2 \cdot 0 + x = x$$
   $$\int_{0}^{y} x \, dt = xy$$

3. **Третий интеграл** ($x, y$ фиксированы):
   $$b_z(x, y, t) = x^2y^3 + 4t^3$$
   $$\int_{0}^{z} (x^2y^3 + 4t^3) \, dt = \left[ x^2y^3t + t^4 \right]_{0}^{z} = x^2y^3z + z^4$$

Складывая результаты, получаем функцию потенциала:
$$U(x, y, z) = xy + x^2 y^3 z + z^4$$

#### 4.3. Проверка потенциала
Проверим правильность нахождения потенциала вычислением его градиента:
- $\frac{\partial U}{\partial x} = \frac{\partial(xy + x^2 y^3 z + z^4)}{\partial x} = y + 2xy^3z = b_x \quad \checkmark$
- $\frac{\partial U}{\partial y} = \frac{\partial(xy + x^2 y^3 z + z^4)}{\partial y} = x + 3x^2y^2z = b_y \quad \checkmark$
- $\frac{\partial U}{\partial z} = \frac{\partial(xy + x^2 y^3 z + z^4)}{\partial z} = x^2y^3 + 4z^3 = b_z \quad \checkmark$

Потенциал найден абсолютно верно.

#### 4.4. Вычисление работы $W$ поля $\vec{b}$ при перемещении из $O(0,0,0)$ в $M(1,1,1)$
Для потенциального поля работа равна разности значений потенциала в конечной и начальной точках траектории и не зависит от формы пути:
$$W = U(1, 1, 1) - U(0, 0, 0)$$
Вычислим значения потенциала в точках:
- $U(1, 1, 1) = 1 \cdot 1 + 1^2 \cdot 1^3 \cdot 1 + 1^4 = 1 + 1 + 1 = 3$
- $U(0, 0, 0) = 0 + 0 + 0 = 0$

Следовательно:
$$W = 3 - 0 = 3$$

**Контрольное число совпало.** $W = 3$.
