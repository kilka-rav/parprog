Численное решение уравнения переноса. Распаралеилование алгоритма.
Для решения этой задачи я выбрал разностную схему прямоугольник, так как в ней не нужно после решать уравнение методом прогонки.
Описание алгоритма можно найти в lab1.pdf. Для ускорения алгоритма я использовал идею pipelin'а. Первый поток считает крайние точки и сразу
же передает их следующему потоку. https://levelup.gitconnected.com/five-stages-of-risc-pipeline-aad0c3eb1233
