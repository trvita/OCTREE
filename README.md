**OCTREE**  
 Реализация типа данных октодерево (октарное дерево, дерево октантов) на языке Си для работы с графическими примитивами - точками, в каждом октанте хранится заданное константой NUM_NODES в octree.h количество точек.
Сборка приложения:

    $ make bin/main && bin/test && result
Запуск приложения:
    $ make run/main
    
Генерация изображения октодерева в result.png:

    $ make run/result
Запуск тестов:

    $ make run/test


Октодеревья (октарные деревья, восьмеричные деревья, octree) представляют собой рекурсивное разбиение трёхмерного пространства на восемь октант, которое представляется деревом. Являются трёхмерным аналогом квадродеревьев.
Октодеревья применяются для пространственной индексации, обнаружения столкновений в трехмерном пространстве,
определения скрытых поверхностей, в трассировке лучей и методе конечных элементов.
Каждый узел в этой реализации октодерева состоит из восьми указателей на потомков, пронумерованных от 0 до
7, логической переменной-индикатором-листа, координат центра октанта, размера октанта и массива примитивов в
октанте. 
Основные операции с октодеревом
•	octree_create: создание октодерева заданной размерности с заданными координатами центра, относительно
которого в дальнейшем будет происходить разбиение;
•	octree_insert: вставка элемента в октодерево - лист проверяется на переполнение, при переполнении происходит
разбиение и старые примитивы узла распределяются по новым октантам;
•	octree_delete: удаление элемента из октодерева – при наличии более, чем 1 примитива в узле, координаты
последнего занесённого примитива меняются местами с координатами удаляемого и число примитив уменьшается, иначе
узел становится пустым листом;
•	octree_divide: разбиение пространства на октанты – рассчитываются координаты центра и размеры будущих
октантов, затем октанты создаются;
•	child_index: получение номера октанта по координатам
•	octree_lookup: поиск элемента по координатам с помощью проверки на то, является узел листом или нет, и номера
октанта по координатам.

Определение номера октанта в child_index:
i = [ 0 - 7 ]
coord_x = 1     1 << coord_x = 00000001		x pos = {1, 3, 5, 7}	x neg = {0, 2, 4, 6}
coord_y = 2	    1 << coord_y = 00000010		y pos = {2, 3, 6, 7}	y neg = {0, 1, 4, 5}
coord_z = 3	    1 << coord_z = 00000100		z pos = {4, 5, 6, 7}	z neg = {0, 1, 2, 3}

00000000 0
00000001 1
00000010 2 
00000011 3

00000100 4
00000101 5
00000110 6
00000111 7
                                                                        
                                                                                                              
                     0             &@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                 
                      \          2@@&                        @M@                        X@@@@                 
                       \       2@@@                        @H@                        2@@@ @@                 
                        \    X@@@            2           @#@           3            X@@@   @@                 
                            @@@                        @B@                         @@@     @@                 
                          @@@                        &@@2                        @@@       @@                 
                        @@@                        2@@@                        @@@@        @@                 
                      X@@BBBBBBBBBBBBBBBBBBBBBBBBBH#BBBBBBBBBBBBBBBBBBBBBBBBBB@@@          @@                 
                    2@@&                        @M@                        2@@@@           @@                 
                  @@@@                        @@@                        &@@@ @@           @@                 
                 @@@         6              @M@             7           @@@   @@           @@                 
               @@@                        @@@2                        @@@     @@           @@                 
             @@@                        X@@@                        @@@X      @@     3     @@                 
           @@@2                        @@@                        &@@@        @@           @@                 
         A#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@          @@           @@                 
         AMH                         @#                          @@           @@           @@                 
         AMH                         @#                          @@           @@           @@                 
         AMH                         @#                          @@           @@         @@@@                 
         AMH                         @#                          @@     7     @@        @@@@@                 
         AMH                         @#                          @@           @@      @#@  @@                 
         AMH                         @#                          @@           @@    @@@    @@                 
         AMH                         @#               7          @@           @@  @#@      @@                 
         AMH            6            @#                          @@           @@@@@        @@                 
         AMH                         @#                          @@           @&@          @@                 
         AMH                         @#                          @@         X@@@           @@                 
         AMH                         @#                          @@       2@@&@@           @@                 
         AMH                         @#                          @@      @M@  @@           @@                 
         AMH                         @#                          @@    @@@    @@           @@                 
         AMH                         @#                          @@  @@@      @@     1     @@                 
         AMH                         @#                          @@@#@        @@           @@                 
         AM@@@@@@@@@@@@@@@@@@@@@@@@@@@#@@@@@@@@@@@@@@@@@@@@@@@@@@@H@          @@           @@                 
         AMH                         @#                          @@           @@           @@                 
         AMH                         @#                          @@           @@           @@                 
         AMH                         @#                          @@           @@          @@@                 
         AMH                         @#                          @@           @@        @@@X                  
         AMH                         @#                          @@      5    @@      @@@2                    
         AMH                         @#                          @@           @@    @@@@                      
         AMH                         @#              5           @@           @@   @@@                        
         AMH               4         @#                          @@           @@ @@@                          
         AMH                         @#                          @@           @@@@                            
         AMH                         @#                          @@          @@@                              
         AMH                         @#                          @@        @@@2                               
         AMH                         @#                          @@      @@@2                                 
         AMH                         @#                          @@    &@@X                                   
         AMH                         @#                          @@  &@@3                                     
         AMH                         @#                          @@ @@@                                       
         AMH                         @#                          @@@@                                         
         &@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
