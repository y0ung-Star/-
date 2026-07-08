import sys

class Graph:
    def __init__(self, file_path, is_directed):
        """
        1) Конструктор.
        Принимает путь к файлу (или None/пустую строку для пустого графа)
        и флаг ориентированности (True/False).
        1A: Файл со списком рёбер.
        2B: Хранение в виде матрицы смежности.
        """
        self.is_directed = is_directed
        self.nodes = []  # Список имен вершин (чтобы мапить индексы матрицы на реальные имена)
        self.matrix = [] # Матрица смежности (список списков)

        if file_path:
            try:
                with open(file_path, 'r') as f:
                    lines = f.readlines()
                    # собираем все уникальные вершины
                    unique_nodes = set()
                    parsed_edges = []
                    
                    for line in lines:
                        parts = line.strip().split()
                        if len(parts) < 3: continue
                        u, v, w = parts[0], parts[1], float(parts[2])
                        unique_nodes.add(u)
                        unique_nodes.add(v)
                        parsed_edges.append((u, v, w))
                    
                    # Инициализируем вершины и пустую матрицу
                    for node in sorted(list(unique_nodes)):
                        self.add_vertex(node)
                    
                    # Добавляем ребра
                    for u, v, w in parsed_edges:
                        self.add_edge(u, v, w)
                        
                print(f"Граф успешно загружен из {file_path}")
            except FileNotFoundError:
                print("Файл не найден, создан пустой граф.")

    def _get_idx(self, v_name):
        """Вспомогательный метод: найти индекс вершины в матрице по имени."""
        try:
            return self.nodes.index(str(v_name))
        except ValueError:
            return -1

    # 2) size
    def size(self):
        return len(self.nodes)

    # 3) weight
    def weight(self, v1, v2):
        idx1 = self._get_idx(v1)
        idx2 = self._get_idx(v2)
        if idx1 == -1 or idx2 == -1: return None
        return self.matrix[idx1][idx2]

    # 4) is_edge
    def is_edge(self, v1, v2):
        w = self.weight(v1, v2)
        return w is not None and w != float('inf')

    # 5) add_vertex
    def add_vertex(self, v_name):
        v_str = str(v_name)
        if v_str in self.nodes:
            print("Вершина уже существует")
            return
        
        self.nodes.append(v_str)
        # Расширяем матрицу: добавляем новую строку и колонку
        # Сначала удлиняем существующие строки
        for row in self.matrix:
            row.append(float('inf'))
        
        # Добавляем новую строку (заполненную inf)
        new_row = [float('inf')] * len(self.nodes)
        # Расстояние до самой себя = 0 (обычно), но в матрице смежности для ребер 
        # часто ставят inf, если нет петли. Оставим inf, если нет явного ребра.
        self.matrix.append(new_row)

    # 6) add_edge
    def add_edge(self, v1, v2, weight):
        idx1 = self._get_idx(v1)
        idx2 = self._get_idx(v2)
        
        if idx1 == -1 or idx2 == -1:
            print("Ошибка: одна из вершин не существует.")
            return

        self.matrix[idx1][idx2] = float(weight)
        if not self.is_directed:
            self.matrix[idx2][idx1] = float(weight)

    # 7) list_of_edges
    def list_of_edges(self, v=None):
        edges = []
        n = len(self.nodes)
        
        if v is None:
            # Все ребра
            for i in range(n):
                # Для неориентированного графа, чтобы не дублировать, берем j >= i
                start_j = 0 if self.is_directed else i
                for j in range(start_j, n):
                    if self.matrix[i][j] != float('inf'):
                        edges.append((self.nodes[i], self.nodes[j], self.matrix[i][j]))
        else:
            # Инцидентные вершине v
            idx = self._get_idx(v)
            if idx != -1:
                # Исходящие (или инцидентные для неориентированного)
                for j in range(n):
                    if self.matrix[idx][j] != float('inf'):
                        edges.append((self.nodes[idx], self.nodes[j], self.matrix[idx][j]))
                # Если граф ориентированный, нужно ли искать входящие?
                # В задании сказано "дуг, исходящих из данной вершины".
        return edges

    def remove_vertex(self, v_name):
        idx = self._get_idx(v_name)
        if idx == -1: return
        
        # Удаляем из списка имен
        self.nodes.pop(idx)
        # Удаляем строку матрицы
        self.matrix.pop(idx)
        # Удаляем колонку матрицы (элемент idx в каждой строке)
        for row in self.matrix:
            row.pop(idx)

    def remove_edge(self, v1, v2):
        idx1 = self._get_idx(v1)
        idx2 = self._get_idx(v2)
        if idx1 != -1 and idx2 != -1:
            self.matrix[idx1][idx2] = float('inf')
            if not self.is_directed:
                self.matrix[idx2][idx1] = float('inf')

    # --- АЛГОРИТМЫ ---

    def get_connectivity_components(self):
        """
        Проверка связности (BFS). 
        Для орграфа ищем компоненты слабой связности.
        """
        visited = set()
        components = []
        n = len(self.nodes)

        for i in range(n):
            if i not in visited:
                component = []
                queue = [i]
                visited.add(i)
                while queue:
                    curr = queue.pop(0)
                    component.append(self.nodes[curr])
                    # Ищем соседей
                    for neighbor in range(n):
                        # Проверяем связь в обе стороны (для слабой связности орграфа)
                        connected = (self.matrix[curr][neighbor] != float('inf')) or \
                                    (self.matrix[neighbor][curr] != float('inf'))
                        
                        if connected and neighbor not in visited:
                            visited.add(neighbor)
                            queue.append(neighbor)
                components.append(component)
        return components

    # ВАРИАНТ 3B: Беллмана-Форда
    def bellman_ford(self, start_node, end_node=None):
        start_idx = self._get_idx(start_node)
        if start_idx == -1:
            return None, "Вершина не найдена"

        n = len(self.nodes)
        dist = [float('inf')] * n
        predecessors = [None] * n
        dist[start_idx] = 0

        # Релаксация ребер N-1 раз
        all_edges = []
        for u in range(n):
            for v in range(n):
                if self.matrix[u][v] != float('inf'):
                    all_edges.append((u, v, self.matrix[u][v]))

        for _ in range(n - 1):
            changed = False
            for u, v, w in all_edges:
                if dist[u] != float('inf') and dist[u] + w < dist[v]:
                    dist[v] = dist[u] + w
                    predecessors[v] = u
                    changed = True
            if not changed: break

        # Проверка на отрицательные циклы (не обязательно по заданию, но полезно)
        for u, v, w in all_edges:
            if dist[u] != float('inf') and dist[u] + w < dist[v]:
                return None, "Найден цикл отрицательного веса"

        # Формирование результата
        if end_node:
            end_idx = self._get_idx(end_node)
            if end_idx == -1: return None, "Конечная вершина не найдена"
            if dist[end_idx] == float('inf'): return float('inf'), []
            
            path = []
            curr = end_idx
            while curr is not None:
                path.append(self.nodes[curr])
                curr = predecessors[curr]
            return dist[end_idx], path[::-1]
        else:
            # Вернуть расстояния до всех
            res = {}
            for i in range(n):
                res[self.nodes[i]] = dist[i]
            return res

    # ВАРИАНТ 4B: Алгоритм Прима
    def prim_mst(self):
        if not self.nodes: return 0, []
        
        n = len(self.nodes)
        selected = [False] * n
        # Начинаем с вершины 0
        selected[0] = True
        edge_count = 0
        mst_edges = []
        mst_weight = 0

        while edge_count < n - 1:
            min_w = float('inf')
            x = -1
            y = -1

            # Ищем минимальное ребро из посещенных (selected) в непосещенные
            for i in range(n):
                if selected[i]:
                    for j in range(n):
                        if not selected[j]:
                            # Для орграфа игнорируем направление (берем min(i->j, j->i))
                            w_forward = self.matrix[i][j]
                            w_backward = self.matrix[j][i]
                            
                            # Эффективный вес (если ребро есть хотя бы в одну сторону)
                            w = float('inf')
                            if w_forward != float('inf'): w = w_forward
                            if w_backward != float('inf'): w = min(w, w_backward) # если есть оба, берем min
                            
                            if w < min_w:
                                min_w = w
                                x = i
                                y = j
            
            if min_w == float('inf'):
                break # Граф несвязный

            selected[y] = True
            mst_edges.append((self.nodes[x], self.nodes[y], min_w))
            mst_weight += min_w
            edge_count += 1
            
        return mst_weight, mst_edges

# --- ИНТЕРФЕЙС КОМАНДНОЙ СТРОКИ ---

def main():
    g = None
    print("=== Программа работы с графом (Вариант: Матрица, Беллман-Форд, Прима) ===")
    print("Команды:")
    print(" create <dir/undir>      - создать пустой граф (dir=ориент, undir=неориент)")
    print(" load <file> <dir/undir> - считать граф из файла")
    print(" add_v <name>            - добавить вершину")
    print(" add_e <u v w>           - добавить ребро")
    print(" del_v <name>            - удалить вершину")
    print(" del_e <u v>             - удалить ребро")
    print(" print                   - вывести список вершин и ребер")
    print(" conn                    - компоненты связности")
    print(" path <u v>              - кратчайший путь (Беллман-Форд)")
    print(" dist <u>                - расстояния от вершины до всех (Беллман-Форд)")
    print(" mst                     - минимальное остовное дерево (Прима)")
    print(" exit                    - выход")

    while True:
        try:
            cmd = input("\nВвод> ").strip().split()
        except EOFError:
            break
            
        if not cmd: continue
        action = cmd[0].lower()

        if action == 'exit':
            break

        elif action == 'create':
            if len(cmd) < 2:
                print("Укажите тип: dir или undir")
                continue
            is_directed = (cmd[1] == 'dir')
            g = Graph(None, is_directed)
            print("Пустой граф создан.")

        elif action == 'load':
            if len(cmd) < 3:
                print("Формат: load <filename> <dir/undir>")
                continue
            is_directed = (cmd[2] == 'dir')
            g = Graph(cmd[1], is_directed)

        elif action == 'add_v':
            if not g: print("Граф не создан"); continue
            if len(cmd) < 2: print("Нужно имя вершины"); continue
            g.add_vertex(cmd[1])
            print("Вершина добавлена.")

        elif action == 'add_e':
            if not g: print("Граф не создан"); continue
            if len(cmd) < 4: print("Формат: add_e u v weight"); continue
            g.add_vertex(cmd[1]) # На случай если не были созданы
            g.add_vertex(cmd[2])
            g.add_edge(cmd[1], cmd[2], cmd[3])
            print("Ребро добавлено.")

        elif action == 'del_v':
            if not g: print("Граф не создан"); continue
            g.remove_vertex(cmd[1])
            print("Выполнено.")

        elif action == 'del_e':
            if not g: print("Граф не создан"); continue
            g.remove_edge(cmd[1], cmd[2])
            print("Выполнено.")

        elif action == 'print':
            if not g: print("Граф не создан"); continue
            print(f"Вершины ({g.size()}): {g.nodes}")
            print("Ребра:")
            for u, v, w in g.list_of_edges():
                print(f"  {u} -> {v} : {w}")

        elif action == 'conn':
            if not g: print("Граф не создан"); continue
            comps = g.get_connectivity_components()
            print(f"Компоненты связности ({len(comps)}):")
            for i, c in enumerate(comps):
                print(f"  {i+1}: {c}")

        elif action == 'path':
            if not g: print("Граф не создан"); continue
            if len(cmd) < 3: print("Формат: path start end"); continue
            dist, path = g.bellman_ford(cmd[1], cmd[2])
            if path is None:
                print(f"Ошибка: {dist}") # dist тут содержит текст ошибки
            elif dist == float('inf'):
                print("Пути не существует.")
            else:
                print(f"Длина пути: {dist}")
                print(f"Путь: {' -> '.join(path)}")

        elif action == 'dist':
            if not g: print("Граф не создан"); continue
            res = g.bellman_ford(cmd[1])
            if isinstance(res, tuple): # Если вернулась ошибка
                print(res[1])
            else:
                print("Расстояния от", cmd[1])
                for node, d in res.items():
                    print(f" -> {node}: {d}")

        elif action == 'mst':
            if not g: print("Граф не создан"); continue
            w, edges = g.prim_mst()
            print(f"Вес MST: {w}")
            print("Ребра MST:")
            for u, v, wei in edges:
                print(f"  {u} - {v} : {wei}")
        
        else:
            print("Неизвестная команда")

if __name__ == "__main__":
    main()
