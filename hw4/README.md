# Homework 4
- Generate random graphs and test $A^m$ counter of number of paths. Evaluate it within $log_2(m)$ matmuls.
- Generate small random (or select some graph and implement pagerank procedure). Compare with naive ranking.
- Tip: Moscow subway graph is nice example (but rather tiny).
- Try all tricks for evaluation of performance: optimization, blas, openmp, loop placing.
## Решение
- Генерация рандомных графов без петель написана (**generateRandomGraph**).
- По подсказке выбран граф московского метро (**moscow_metro_graph.txt**), под него написан алгоритм **PageRank**, сравнил с наивной реализацией важности (количество ребер, входящих в вершину). Проанализировал для простоты ТОП N вершин в каждом варианте:
    - PageRank:
        - 192 - 0.006615 - Vystavochny tsentr
        - 156 - 0.006148 - Sevastopolskaya
        - 143 - 0.006223 - Timiryazevskaya
        - 91 - 0.006305 - VDNH
        - 86 - 0.006142 - Kievskaya
        - 69 - 0.008216 - Kievskaya (Окружная)
        - 51 - 0.006097 - Kievskaya (очередная ветка)
        - 38 - 0.006654 - Krasnogvardeyskaya
        - 10 - 0.006924 - Biblioteka imeni Lenina
    - Naive:
        - 7 - 4 - Chistye prudy
        - 10 - 5 - Biblioteka imeni Lenina
        - 27 - 4 - Tverskaya
        - 28 - 4 - Teatralnaya
        - 29 - 4 - Novokuznetskaya
        - 49 - 5 - Arbatskaya
        - 51 - 4 - Kievskaya (очередная ветка)
        - 69 - 5 - Kievskaya (Окружная)
        - 79 - 4 - Taganskaya
        - 80 - 4 - Kurskaya
        - 86 - 4 - Kievskaya
        - 96 - 4 - Turgenevskaya
        - 120 - 4 - Pushkinskaya
        - 123 - 4 - Taganskaya (еще одна)
        - 136 - 4 - Marksistskaya
        - 148 - 4 - Chehovskaya
        - 149 - 4 - Borovitskaya
    - Итог: видно, что оба варианта находят все Киевские станции метро важными, но в целом наивный вариант больше тяготеет к центру, а вот PageRank выделяет некоторые другие особенности (например, есть ВДНХ и Выставочный центр). Важно учитывать, что версия метро достаточно старая, примерно 5-ти летняя или даже старше.
- Из оптимизации использовал openmp, где мог, переставлял loops.


