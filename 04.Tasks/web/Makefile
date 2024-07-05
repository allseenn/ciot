TARGET=web
ARGS=-pthread

all: $(TARGET)

$(TARGET): $(TARGET).c
	gcc $(ARGS) -o $@ $(TARGET).c

clean:
	rm -f $(TARGET)

install: 
	chmod 777 ${TARGET}
	sudo cp ${TARGET} /usr/local/sbin
