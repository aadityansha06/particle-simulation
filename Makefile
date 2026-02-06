CC=gcc

CFLAGS = -Wall -std=c99
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
TARGET = particle


$(TARGET): particle.c
		$(CC) particle.c -o $(TARGET) $(LIBS) $(CFLAGS)

#Generatign run 
    
run: $(TARGET) 
		./$(TARGET)


clean: 
		rm -f $(TARGET)

