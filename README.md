mag_dist
==========
Теория
------
### Определения 

#### Многогранник:
1. Вершины - грани нулевой размерности
2. Ребра - грани первой размерности
3. Ридж - грань на 1 меньше максимальной
4. Гиперграни(фасета) - гранни максимальной размерности

+ Двухсмежностный многоранник - любые две вершины смежные
+ Смежные вершины - соединены ребром 
+ У двухсмежностного многогранника, любая его грань двухсмежностна 

##### Возможные проверки:
0. Количество едениц в гиперграни не меньше размерности многогранника (для 2-симрлициарных равенство )
0. Свойства вершинной фигуры (2-смежностного многогранника)
0. Не пропадают столбцы (вершины)
0. Все 2-симплициарны


### Матрица инцидентности
Для сравнения матриц bliss graf

Определяющий критерий - принадлежность вершины гиперграни

+ f - гипергрань
+ v - вершина

Симплекс

  f  |  v  | 
:---:|:---:|
  1  |0111 |
  2  |1011 |
  3  |1101 |
  4  |1110 |
  
---
  
  f  |   v   | 
:---:|:-----:|
  1  |111000 |
  2  |110110 |
  3  |011011 |
  4  |000111 |
  5  |101101 |
  
  Матрица инцидентности для f2:
  1. Вычеркнуть f2 
  2. Выписать те столбцы в которых у f2 были единицы

  f  |  v  | 
:---:|:---:|
  1  |1100 |
  2  |0101 |
  3  |0011 |
  4  |1010 |

  Матрица инцидентности для v1(вершинная фигура (непонятно) ):
  1. Вычеркнуть v1 
  2. Выписать те строки в которых у v1 были единицы

  f  |   v  | 
:---:|:----:|
  1  | 1100 |
  2  | 1011 |
  3  | 0110 |
