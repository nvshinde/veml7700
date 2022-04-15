# output: main.o veml7700.o
# 	aarch64-linux-gnu-gcc -c main.o veml7700.o veml7700

# main.o: main.c
# 	aarch64-linux-gnu-gcc -c main.c

# veml7700.o: veml7700.c veml7700.h
# 	aarch64-linux-gnu-gcc -c veml7700.c

# clean:
# 	rm *.o veml7700

hts221_arm: main.c veml7700.c veml7700.h
	aarch64-linux-gnu-gcc main.c veml7700.c veml7700.h -o veml7700_aarch64

clean:
	rm *.o