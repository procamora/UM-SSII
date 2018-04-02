---
title: Sistemas Inteligentes
subtitle: Practica 2
author:
    - Pablo José Rocamora Zamora G3.2
date: Convocatoria de Junio
header: dsad
footer: So is this
geometry:
    - top=1in
    - margin=1in
    - bottom=1in
    - right=1in
    - left=1in
toc: true
toc-depth: 1
fontsize: 11pt # puede ser 10, 11 o 12
fontfamily: lmodern
documentclass: scrartcl
lang: es
bibliography: bibliografia.bib
csl: estilo.csl
link-citations: true
lof: false # Añadir lista de figuras
lot: false # Añadir lista de tablas 
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


acercándonos a la solución final [@split].

acercándonos a la solución final [@regex].

acercándonos a la solución final [@sort].


# Explicación breve y completa de la técnica Sistema Basado en Reglas (SBR).

## Introducción

Los sistemas basados en reglas (SBR) se inspiran en los sistemas de deducción en lógica proposicional o de primer orden. Se les suele llamar Sistemas Expertos (SE) porque el conocimiento suele proceder de expertos humanos y los SBR permiten capturarlo bien.

- Utilizan la estructura de inferencia _modus ponens_ para obtener conclusiones lógicas.
- Interpretan la primera premisa de un _modus ponens_ como una regla de la forma **IF condición THEN acción**.

## Componentes Básicos

- Base de conocimiento (BC): Contiene las reglas que codifican todo el conocimiento. Una regla se consta de 2 partes: izquierda o antecedente y derecha o consecuente. Ejemplo: *IF antecedente THEN consecuente*.

- Base de Hechos (BH): Son los hechos establecidos como verdaderos, pueden ser tanto datos de entrada como conclusiones inferidas.

- Motor de Inferencias (MI): Selecciona las reglas que se pueden ejecutar y las ejecuta con el objetivo de obtener alguna conclusión.

Una diferencia importante entre la BC y la BH es que la BH almacena información puntual sobre un problema concreto mientras  que la BC almacena porciones de cocimiento sobre como resolver el problema genérico.

## Inferencia en un SBR

Hay dos formas de razonar un MI: 

- Encadenamiento hacia delante o dirigido por datos, se seleccionan las reglas cuyos antecedentes se verifican, dado el contenido de la BH. La particularidad de esta etapa es la equiparación, donde se seleccionan las reglas cuyos antecedentes se verifican, dado el contenido de la BH.
- Encadenamiento hacia atrás o dirigido por metas, se especifica una meta objetivo y se trata de determinar su la meta se verifica o no, teniendo en cuenta el contenido de la BH.

## Técnicas de Equiparación

La equiparación del antecedente de las reglas con el estado de la BH no siempre es trivial, puede no describir situaciones particulares sino generales.
Otro problema es la necesidad de examinar todas las reglas en cada ciclo de inferencias, ya que puede ser poco eficiente si la BC es extensa, puede mejorar con indexado de reglas o el algoritmo *RETE*


## Técnicas de resolución de conflictos

Un método de resolución de conflictos selecciona, a partir del conjunto conflicto, la regla a aplicar. Las principales técnicas de resolución son las siguientes:

- Según la BC (Criterios estáticos): Seleccionan las reglas ordenados por un criterio, como puede ser prioridad de reglas.
- Según la BH (Criterios dinámicos): Reglas que usan elementos mas recientes de la BH.
- Según la ejecución (Criterios dinámicos): Usar reglas no utilizadas previamente.



# Explicación clara de los elementos siguientes del motor de inferencia diseñado (dado que el diseño es anterior a la implementación, no se debe hacer mención a aspectos de código):

## Equiparación-Conjunto conflicto

La equiparación: El objetivo de la equiparación es seleccionar reglas validas para la BH, se realizara recorriendo regla a regla la BC y comprobando para cada condición de la regla si esta esa misma condición en la BH, si esta y se cumplen todas las condiciones de la regla entonces podremos obtener esa regla para ser usada posteriormente

Conjunto conflicto: La equiparación nos retorna una lista de reglas validas para usarse, para resolver que regla tenemos que usar en cada caso cogeremos siempre la primera, ya que la BC esta ordenada primero por prioridad y en caso de empate de prioridad por numero de regla, gracias a eso la equiparación nos retorna la lista ordenada y resolver el conjunto conflicto es una tarea sencilla.


## Condición de parada

Tenemos 2 condiciones de parada:

 - Cuando en la BH aparezca el objetivo que buscamos, lo que significara que hemos resuelto el problema.
 - Cuando equiparar no retorna ninguna regla o todas las reglas que retornan ya han sido usadas, lo que significara que no podemos continuar y por tanto resolver el problema por falta de información.




# Aplicación del SBR construido a las siguientes situaciones. Incluir y explicar el razonamiento seguido en la resolución de cada base de hechos (fichero Salida1.txt que se indica en el apartado e)) y la solución obtenida y que proporcionaremos al usuario del SBR (fichero Salida2.txt que se indica en el apartado e)). Además, para la Situación 2, explicar claramente todas las decisiones tomadas para la definición del fichero de configuración.

Situación 1: Identificación de Frutas – Se proporcionan (recursos del Aula Virtual) la BC-F, Config-F, y cuatro bases de hechos (BH-F1, BH-F2, BH-F3 y BH-F4).

Situación 2: Detección de Inundaciones – Se proporciona BC-I (recursos del Aula Virtual). Para la aplicación, deben definirse el fichero de configuración y cuatro bases de hechos.

Tanto las BH como las BC proporcionadas no podrán ser modificadas.



# Bibliografía 

La referencia:

- 1: Usado para convertir un string en un int, ya que la funcion stoi de c++ parece que no esta implementada correctamente en MinGW

- : Usado para ver como partir un string a partir de un delimitador especifico

- : Usado para convertir un string en un operador y realizar su respectiva operacion

- : Usado para ver la forma mas correcta de hacer un return null de un struct cuando nunca deberia de ejecutarse, en c++ lo correcto seria enviar una excepcion