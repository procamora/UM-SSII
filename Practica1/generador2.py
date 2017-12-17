#!/bin/env python3

############################################################################
# Copyright 2017 Pablo Rocamora <pablojoserocamora@gmail.com>              #
#                                                                          #
# Permission to use, copy, modify, and distribute this software for any    #
# purpose with or without fee is hereby granted, provided that the above   #
# copyright notice and this permission notice appear in all copies.        #
#                                                                          #
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES #
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF         #
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR  #
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES   #
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN    #
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF  #
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.           #
############################################################################


import argparse #https://docs.python.org/3/library/argparse.html
import subprocess
import re


poblacion = [100, 150]
operadorSeleccion = ["GARouletteWheelSelector", "GATournamentSelector"]
cruce = [0.8, 0.85, 0.9, 0.95]
mutacion = [0.01,0.05, 0.1, 0.125, 0.15]
casosAjuste = ["Casos/Caso-A1.txt", "Casos/Caso-A2.txt", "Casos/Caso-A3.txt", "Casos/Caso-A4.txt", "Casos/Caso-A5.txt", "Casos/Sudoku-1.txt", "Casos/Sudoku-2.txt", "Casos/Sudoku-3.txt", "Casos/MIO.txt", ]

salidaTemp = "tempp.txt"


def CrearArgParseo():
    parser = argparse.ArgumentParser(description='%(prog)s es un script para ejecutar los programas de AOC.')

    requiredNamed = parser.add_argument_group('required named arguments')
    requiredNamed.add_argument('-o', '--output', required=True, help='Resultado de la ejecucion.')
    parser.add_argument('-p', '--program', help='Programa a ejecutar.')

    parser.add_argument('-v', '--verbose', action='store_true', help='Verbose flag (boolean).', default=False)

    # tambien lo puedo poner en la misma linea
    parser.set_defaults(program='../Debug/UM-SSII')
    #parser.print_help()
    return parser.parse_args()



def imprimeArgumentos(argumentos):
    print("output: " + argumentos.output)
    print("program: " + argumentos.program)
    print("verbose: " + str(argumentos.verbose))


def write(arg, texto, tipo):
     with open(arg.output, tipo) as f:
        f.write(texto.replace(".", ","))


def ejecutaBinario(arg, argumentosBinario):
    '''
    Metodo encargado de ejecutar el binario
    '''

    comando = '/usr/bin/time -f "%e" ./{binario} {argumentos} > {salida}'.format(binario=arg.program, salida=salidaTemp, argumentos=argumentosBinario)
    if arg.verbose:
        print("comando time: " + comando)

    ejecucion = subprocess.Popen(comando, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = ejecucion.communicate()

    return stderr.decode("utf-8").replace("\n", "")


def leerResultado():
    with open('{salida}'.format(salida=salidaTemp), 'r') as f:
        content = f.read()
        print(content)
        retorno = re.findall('fitness: \d', content)
        print(retorno)
        return retorno[0].replace("fitness: ", "")


def main():
    arg = CrearArgParseo()

    if arg.verbose:
        imprimeArgumentos(arg)


    write(arg, "SELECTOR;POBLACION;PROB CRUCE;PROB MUTAC;C1;C2;C3;C4;C5;S1;S2;S3;MIO;;Tiempo C1;Tiempo C2;Tiempo C3;Tiempo C4;Tiempo C5;Tiempo S1;Tiempo S2;Tiempo S3;Tiempo mio\n", "w")
    cont = 1
    for iSeleccion in operadorSeleccion:
        for iPoblacion in poblacion:
            for iCruce in cruce:
                for iMutacion in mutacion:
                    resultados = str()
                    tiempos = str()
                    for iCasoAjuste in casosAjuste:
                        argumentos = "{} {} {} {} {}".format(iCasoAjuste, iPoblacion, iSeleccion, iCruce, iMutacion)
                        tiempos += "{};".format(ejecutaBinario(arg, argumentos))
                        resultados += "{};".format(leerResultado())
                    write(arg, "{};{};{};{};{};{}\n".format(iSeleccion, iPoblacion, iCruce, iMutacion, resultados, tiempos), "a")
                    print("Terminado interacion: {} de {}".format(cont, "80"))
                    cont += 1


#=SI(SUMA(E2:I2)=0; PROMEDIO(K2:O2);)
main()