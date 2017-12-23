---
title: Sistemas Inteligentes
subtitle: Practica 2
author:
    - Pablo José Rocamora Zamora G3.2
date: 9 de Diciembre de 2017
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


acercándonos a la solución final [@youtube].


a)b)c)

# Explicación breve y completa de la técnica Sistema Basado en Reglas (SBR).



# Explicación clara de los elementos siguientes del motor de inferencia diseñado (dado que el diseño es anterior a la implementación, no se debe hacer mención a aspectos de código):

- Equiparación-Conjunto conflicto
- Condición de parada





# Aplicación del SBR construido a las siguientes situaciones. Incluir y explicar el razonamiento seguido en la resolución de cada base de hechos (fichero Salida1.txt que se indica en el apartado e)) y la solución obtenida y que proporcionaremos al usuario del SBR (fichero Salida2.txt que se indica en el apartado e)). Además, para la Situación 2, explicar claramente todas las decisiones tomadas para la definición del fichero de configuración.

Situación 1: Identificación de Frutas – Se proporcionan (recursos del Aula Virtual) la BC-F, Config-F, y cuatro bases de hechos (BH-F1, BH-F2, BH-F3 y BH-F4).

Situación 2: Detección de Inundaciones – Se proporciona BC-I (recursos del Aula Virtual). Para la aplicación, deben definirse el fichero de configuración y cuatro bases de hechos.

Tanto las BH como las BC proporcionadas no podrán ser modificadas.



# Bibliografía 

La referencia:

- 1: Es 