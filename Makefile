#-----------------------
# IMPORTANTE: Los valores de los parametros de los ejercicio?_test deben ajustarse.
# Se asume que los ficheros fuente se llaman ejercicio1.c, ejercicio2.c,...,ordenar.h
#-----------------------

CC = gcc -ansi -pedantic
CFLAGS = -Wall
EXE = ejercicio1 ejercicio2 ejercicio2blin ejercicio2bbin ejercicio2blin_auto


all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o busqueda.o permutaciones.o tiempos.o 
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o busqueda.o permutaciones.o tiempos.o

permutaciones.o : permutaciones.c permutaciones.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<
	
busqueda.o : busqueda.c busqueda.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

ordenacion.o : ordenacion.c ordenacion.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

tiempos.o : tiempos.c tiempos.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

#-------------------------------------------PRACTICA 3-------------------------------------------------------	
ejercicio1_test:
	@echo Ejecutando ejercicio1
	@./ejercicio1 -tamanio 100 -clave 20

ejercicio2_test:
	@echo Ejecutando ejercicio2
	@./ejercicio2 -num_min 100 -num_max 10000 -incr 100 -n_veces 5 -fichSalida ejercicio2.txt
	
ejercicio2_blin:
	@echo Ejecutando ejercicio2blin
	@./ejercicio2blin -num_min 1000 -num_max 10000 -incr 500 -n_veces 1 -fichSalida ejercicio2blin.txt

ejercicio2_bbin:
	@echo Ejecutando ejercicio2bbin
	@./ejercicio2bbin -num_min 1000 -num_max 10000 -incr 500 -n_veces 1 -fichSalida ejercicio2bbin.txt
	
ejercicio2_blin_auto1:
	@echo Ejecutando ejercicio2blin_auto1
	@./ejercicio2blin_auto -num_min 1000 -num_max 10000 -incr 500 -n_veces 1 -fichSalida ejercicio2blin_auto1.txt
	
ejercicio2_blin_auto2:
	@echo Ejecutando ejercicio2blin_auto2
	@./ejercicio2blin_auto -num_min 1000 -num_max 10000 -incr 500 -n_veces 100 -fichSalida ejercicio2blin_auto2.txt
	
ejercicio2_blin_auto3:
	@echo Ejecutando ejercicio2blin_auto3
	@./ejercicio2blin_auto -num_min 1000 -num_max 10000 -incr 500 -n_veces 10000 -fichSalida ejercicio2blin_auto3.txt
	
ejercicio1_v:
	@echo ">>>>>>Running ejercicio1 with valgrind"
	valgrind --leak-check=full ./ejercicio1 -tamanio 1000 -clave 50

ejercicio2_v:
	@echo ">>>>>>Running ejercicio2 with valgrind"
	valgrind --leak-check=full ./ejercicio2  -num_min 1000 -num_max 10000 -incr 100 -n_veces 5 -fichSalida ejercicio2.txt

ejercicio2_blin_v:
	@echo ">>>>>>Running ejercicio2blin with valgrind"
	valgrind --leak-check=full ./ejercicio2blin  -num_min 1000 -num_max 10000 -incr 500 -n_veces 1 -fichSalida ejercicio2blin.txt

ejercicio2_bbin_v:
	@echo ">>>>>>Running ejercicio2bbin with valgrind"
	valgrind --leak-check=full ./ejercicio2bbin  -num_min 1000 -num_max 10000 -incr 500 -n_veces 1 -fichSalida ejercicio2bbin.txt

ejercicio2_blin_auto1_v:
	@echo ">>>>>>Running ejercicio2blin_auto1 with valgrind"
	valgrind --leak-check=full ./ejercicio2blin_auto  -num_min 1000 -num_max 10000 -incr 500 -n_veces 1 -fichSalida ejercicio2blin_auto1.txt

ejercicio2_blin_auto2_v:
	@echo ">>>>>>Running ejercicio2blin_auto2 with valgrind"
	valgrind --leak-check=full ./ejercicio2blin_auto  -num_min 1000 -num_max 10000 -incr 500 -n_veces 100 -fichSalida ejercicio2blin_auto2.txt	
	
ejercicio2_blin_auto3_v:
	@echo ">>>>>>Running ejercicio2blin_auto3 with valgrind"
	valgrind --leak-check=full ./ejercicio2blin_auto  -num_min 1000 -num_max 100000 -incr 1000 -n_veces 10000 -fichSalida ejercicio2blin_auto3.txt