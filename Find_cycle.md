# Find Cycle using dfs (Поиск цикла с помощью dfs)

Постановка: на входе матрица смежности, нужно определить есть ли цикл и вывести его

Идея: вершины, которые находятся в обходе, красим в одинц цвет(красный), а обойденные окончательно вершины красим в другой цвет(черный).

Если в какой-то момент очередная вершина обращается в вершину, которая покрашена в красный цвет, то значит, существует цикл и нужно запомнить вершину, которая на нем лежит