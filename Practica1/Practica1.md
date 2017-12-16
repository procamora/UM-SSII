---
title: Sistemas Inteligentes
subtitle: Practica 1
author:
    - Pablo José Rocamora Zamora G3.2
date: 9 de Diciembre de 2017
header: dsad
footer: So is this
geometry: margin=1in
toc: true
toc-depth: 1
fontsize: 11pt # puede ser 10, 11 o 12
fontfamily: lmodern
documentclass: scrartcl
header-includes:
    - \usepackage{xcolor}
    - \definecolor{miverde}{rgb}{0.31,0.60,0.02}
    - \definecolor{migris}{rgb}{0.56,0.35,0.01}
    - \definecolor{mimazul}{rgb}{0.13,0.29,0.53}
    - \lstset{basicstyle=\small\ttfamily} # Fija el tamaño del tipo de letra utilizado para el código
    - \lstset{breaklines=true} # Activa el salto de línea automático
    - \lstset{extendedchars=true} # Permite utilizar caracteres extendidos no-ASCII; solo funciona para codificaciones de 8-bits; para UTF-8 no funciona. En xelatex necesita estar a true para que funcione.
    - \lstset{tabsize=2} # Establece el salto de las tabulaciones a 2 espacios
    - \lstset{columns=fixed}
    - \lstset{showstringspaces=false} # subraya solamente los espacios que estén en una cadena de esto
    - \lstset{frame=trbl} # Añade un marco al código
    - \lstset{frameround=tttt}
    - \lstset{framesep=4pt}
    - \lstset{numbers=left} # Posición de los números de línea (none, left, right).
    - \lstset{numberstyle=\tiny\ttfamily} # Estilo para los números de línea
    - \lstset{postbreak=\raisebox{0ex}[0ex][0ex]{\ensuremath{\color{red}\hookrightarrow\space}}}
    - \lstset{keywordstyle=\color{mimazul}} # estilo de las palabras clave
    - \lstset{stringstyle=\color{miverde}} # Estilo de las cadenas de texto
    - \lstset{commentstyle=\color{migris}} # Estilo de los comentarios
    - \lstset{stepnumber=2} # Muestra solamente los números de línea que corresponden a cada salto. Va de 2 en 2. En este caso: 1,3,5,...
    - \lstset{numbersep=5pt} # Distancia de los números de línea al código
    - \lstset{backgroundcolor=\color[RGB]{248,248,248}} # Indica el color de fondo; necesita que se añada \usepackage{color} o \usepackage{xcolor}
    - \lstset{showspaces=false} # Si se activa, muestra los espacios con guiones bajos; sustituye a 'showstringspaces'
    - \lstset{showtabs=false} # muestra las tabulaciones que existan en cadenas de texto con guión bajo
    - \lstset{captionpos=b} # Establece la posición de la leyenda del cuadro de código
    - \lstset{breakatwhitespace=false} # esto hace que sea una linea son contar
    - \lstset{breakautoindent=true} # Activarlo para que los saltos automáticos solo se apliquen en los espacios en blanco
    - \lstset{escapeinside={\%*}{*)}} # Si quieres incorporar LaTeX dentro del propio código
    - \lstset{linewidth=\textwidth}
    - \lstset{basewidth=0.5em}
    - \lstset{language=C} # Establece el lenguaje por defecto. Se puede cambiar para cada bloque de código insertado
    - \lstset{otherkeywords={}} # Si se quieren añadir otras palabras clave al lenguaje
--- 



# Explicación breve y completa de la técnica Algoritmo Genético (AG). Debe quedarse muy claro cuáles son los elementos y el proceso que sigue dicha técnica.

Un algoritmo genético (AG) es una variante de la búsqueda de haz estocástica en el que los estados sucesores se generan combinando a dos estados padres, más que modificar un solo estado.

El algoritmo genético trata de encontrar la mejor solución por comparación de un conjunto de soluciones. 

Las soluciones se generan a través del cruzamiento de generaciones o soluciones anteriores, esta cruzando generaciones para obtener una nueva generación de manera que podamos compararla para ver si estamos acercándonos a la solución final [@1].


## Elementos

#### Tenemos diferentes formas de codificar una población:

- Codificación binaria
- Codificación entera
- Codificación real
- Codificación en orden

#### Tenemos distintos operadores genéticos:

- **Selección**: (escoge que individuos se reproducirán y cuales no)
    - **Ruleta**: Se eligen con probabilidad proporcional a su función de idoneidad.
    - **Torneo**: Se establecen k torneos aleatorios entre parejas de individuos y se eligen los que ganan en cada torneo (mejor función idoneidad).


- **Cruce**: (recombina individuos para producir descendencia)
    - **Cruce por un punto**: Dos padres ha partir de un gen, se intercambian el resto de genes, creando 2 hijos nuevos
    - **Cruce por dos puntos**:Dos padres ha partir de un rango de genes, se intercambian los genes de ese rango, creando 2 hijos nuevos

- **Mutación**: (provoca el cambio de valor de algunos genes del individuo)
    - **Cambio de un gen aleatorio**
    - **Intercambio entre dos genes**

#### Tenemos que definir la función objetivo

Es necesario crear la función fitness, es una función de adaptación que tiene que retornar: *>0*, es la forma de evaluar la población.

## Proceso

1. Codificamos el problema, en nuestro caso en forma de *Integer*
2. Generanos una población inicial aleatoriamente de k estados  
3. Seleccionamos k individuos a través del operador de selección para crear una nueva población.
4. Elegimos individuos con una probabilidad (p~c~) para ser cruzados y crear una nueva población.
5. Con una probabilidad (p~m~) mutamos los genes de los individuos de la población actual.
6. Esta nueva población sustituye a la original y forma la nueva población inicial que se usara en la siguiente generación, volvemos al paso 3


# Explicación detallada de todas las preguntas realizadas en la sección “Cuestiones para el diseño e implementación” de este guión.


## Explica de qué manera se están inicializando los individuos en el AG propuesto.


## Explica el funcionamiento de los operadores de selección indicados en la sección “Ajuste del Algoritmo Genético”.

Tenemos disponibles en este caso 2 operadores de Selección:

- GARouletteWheelSelector: Se asigna una probabilidad de selección proporcional al valor del fitness del cromosoma.
- GATournamentSelector: Escoge al individuo de mejor fitness de entre N~ts~ individuos seleccionados aleatoriamente con reemplazamiento (N~ts~=2,3,...).

[@2]

## Explica de qué manera se están cruzando los individuos.

Se hace un cruce por 2 puntos, el primer rango de genes corresponde a *p1* y el segundo rango a *p2*, el tamaño de los rangos es aleatorio por lo que a veces sera mas grande *p1* y otras mas pequeño.


## Explica de qué manera se están mutando los individuos.


## Define y explica la condición de parada que utilizarás.

Tenemos 2 condiciones de parada posibles: 

1. La optima es que el fitness sea 0, lo que significa que el problema ha encontrado la solución y termina correctamente.
2. Se ha llegado al numero máximo de generaciones, que en este caso son 12000, aquí llegaremos cuando no lleguemos a un fitness 0 y significara que la configuración que hayamos usado no es correcta.


## Diseña y explica la función fitness que utilizarás. Recuerda, como se indica al comienzo de este guión, que una solución del sudoku no puede repetir en una misma fila, columna o subcuadrícula ninguno de los números

La función fitness se compone de 3 partes, comprobar las filas, comprobar las columnas y comprobar las subcuadriculas


- **Comprobar Filas**: Recorre todas las filas, para cada fila crea un array en el que introduce el numero que lee, usando como indice el valor del numero, por lo que al acabar de leer la fila tendremos un array de números ordenados en el que si están todos los números la fila es correcta y si falta algún numero habrá un 0 en el array, la cantidad de 0 indican la cantidad de números que hay mal en la fila. Una vez rellenado el array, llama a la función `compruebaHuecosVacios()` para que calcule la cantidad de números que hay mal en la fila y aumentar nuestro contador global de fallos.


- **Comprobar columnas**: Recorre todas las columnas, para cada columna crea un array en el que introduce el numero que lee, usando como indice el valor del numero, por lo que al acabar de leer la columna tendremos un array de números ordenados en el que si están todos los números la columnas es correcta y si falta algún numero habrá un 0 en el array, la cantidad de 0 indican la cantidad de números que hay mal en la columna. Una vez rellenado el array, llama a la función `compruebaHuecosVacios()` para que calcule la cantidad de números que hay mal en la columna y aumentar nuestro contador global de fallos.


- **Comprobar subcuadriculas**: Recorre todas las subcuadriculas, para cada subcuadrícula crea un array en el que introduce el numero que lee, usando como indice el valor del numero, por lo que al acabar de leer la subcuadrícula tendremos un array de números ordenados en el que si están todos los números la subcuadrícula es correcta y si falta algún numero habrá un 0 en el array, la cantidad de 0 indican la cantidad de números que hay mal en la subcuadrícula. Una vez rellenado el array, llama a la función `compruebaHuecosVacios()` para que calcule la cantidad de números que hay mal en la subcuadrícula y aumentar nuestro contador global de fallos.


- **Función compruebaHuecosVacios**: Función que recibe un array con los valores de una fila, columna o subcuadrícula, lo recorre y por cada 0 que encuentre aumenta el contador, finalmente lo retorna para aumentar el contador general de la función fitness

Ejemplo 1: Tenemos una fila con los valores (7, 1, 3, 2, 5, 4, 6, 8, 9), al llamar a `calculaFilas()` obtenemos el array ordenado, posteriormente llamamos a `compruebaHuecosVacios()` y comprobamos el numero de 0 que hay, en este caso como no hay repeticiones, no hay y la fila es correcta

7 | 1 | 3 | 2 | 5 | 4 | 6 | 8 | 9
--|--|--|--|--|--|--|--|--
1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 


Ejemplo 2: Tenemos una columna con los valores (7, 1, 3, 3, 5, 5, 6, 8, 9), al llamar a `calculaColumnas()` obtenemos el array ordenado, posteriormente llamamos a `compruebaHuecosVacios()` y comprobamos el numero de 0 que hay, en este caso como esta repetido tanto el 3 como el 5, faltan 2 números que son el 2 y el 4, con lo que el numero de fallos son 2


7 | 1 | 3 | 3 | 5 | 5 | 6 | 8 | 9
--|--|--|--|--|--|--|--|--
1 | 0 | 3 | 0 | 5 | 6 | 7 | 8 | 9


\newpage



# La tabla completa que muestre los valores de la función fitness para todas las pruebas realizadas para el ajuste del software sobre los distintos valores para los parámetros ajustables y para los distintos “Casos para el Ajuste” propuestos. La tabla debe mostrarse de forma clara y que facilite su análisis. Ver sección “Ajuste del Algoritmo Genético” en este mismo documento.



![Tabla con selector GARouletteWheelSelector para casos de ajuste](images/CasosAjusteGARouletteWheelSelector.png)




![Tabla con selector GATournamentSelector para casos de ajuste](images/CasosAjusteGATournamentSelector.png)




![Gráfica comparando Probabilidades de Cruce](images/ProbCruce.png)


![Gráfica comparando Probabilidades de Mutación](images/ProbMutac.png)



# Análisis de las pruebas de ajuste (esto es, el análisis de la tabla de resultados del apartado c). El objetivo de este análisis es obtener el comportamiento del software diseñado.



a) se eligen los distintos métodos aplicables y un conjunto de posibles valores para los parámetros, 
b) se selecciona un conjunto significativo de casos del problema, 
c) se resuelven todos los casos utilizando todas las combinaciones de métodos-valores, 
d) se analizan las soluciones. 
A partir de esto, debemos obtener unos determinados métodos y valores que hacen al algoritmo robusto, eficiente y óptimo (o lo mejor posible).


# A partir de este análisis, indicar qué valores de los parámetros debemos utilizar, y el protocolo para asignarlos, para que el software tenga un comportamiento aceptable. Denominar a esta sección “manual-Asignación”.


# Para cada uno de los “Casos del Usuario” (ver sección correspondiente), indicar el protocolo seguido para resolverlo (siguiendo el “manual-Asignación”), el valor para cada parámetro, la solución obtenida y su fitness.








# Bibliografía 