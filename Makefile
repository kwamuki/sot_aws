CC = gcc
CFLAGS	=	-W -Wall
TARGET	=	sot_client_example

all	:	$(TARGET)

$(TARGET) : sot_client_example.o sot_key_gen_256.o sot_aes_enc.o
		$(CC) $(CFLASGS) -o $@ $^ `libgcrypt-config --libs`

sot_client_example.o : sot_client_example.c
		$(CC) $(CFLASGS) -c -o $@ $^
		
sot_key_gen_256.o : sot_key_gen_256.c
		$(CC) $(CFLASGS) -c -o $@ $^

sot_aes_enc.o : sot_aes_enc.c
		$(CC) $(CFLASGS) -c -o $@ $^

clean :
		rm -rf *.o sot_client_example
