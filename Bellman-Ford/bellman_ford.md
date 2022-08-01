# Solution task by Bellman-Ford's algorithm

Алгоритм решает задачу <strong>поиска кратчайшего пути</strong> от одной вершины до всех других во взвешенном графе
  
<strong>Постановка задачи</strong>: В ориентированном взвешенном графе вершины пронумерованы числами от `1` до `n`. Если `i < j`, то существует ребро из вершины `i` в вершину `j`, вес которого определяется по формуле `wt(i,j)=(179i+719j) mod 1000 - 500`. Определите вес кратчайшего пути, ведущего из вершины `1` в вершину `n`.

<strong>Тест</strong>

Input 1
```
1
```
Output 1
```
117
```
Input 2
```
3
```
Output 2
```
-164
```