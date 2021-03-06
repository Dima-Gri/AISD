# Find bridges using dfs (Поиск мостов c помощью DFS) 

<strong>Постановка задачи</strong>: Найти вершины графа, которые являются мостами. Сначала выводится кол-во мостов, а затем сами мосты.

<strong>Идея:</strong> Во-первых нам понадобятся марки времени, то есть мы будем запоминаться время, в которое попали в вершину. Во-вторых, во время обхода dfs дополнительно будем хранить для каждой вершины
минимальную метку времени среди всех вершин, которые в нее обращаются, а при обратном ходе dfs будем утаскивать эти минимумы из текущих вершин к их родителям, тем самым мы узнаем для каждой вершины в какую минимальную метку
обращались ее дети. Вот тут стоит осознать, что, если искомая метка времени какой то вершины меньше ее дополнительной метки, то эта вершина будет мостом

<strong>Тест</strong>

Input
```
6 7
1 2
2 3
3 4
1 3
4 5
4 6
5 6
```
Output
```
1
3
```
