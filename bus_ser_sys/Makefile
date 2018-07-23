BIN=bus_ser_sys
OBJECTS=main.o bus_ser_sys.o c_socket.o
LINK=-lpthread -lmxml

$(BIN):$(OBJECTS)
	g++ -o $(BIN) $(OBJECTS) $(LINK)

%.o:%.cpp
	g++ -c $< -o $@

.PHONY:clean
clean:
	rm -rf $(BIN) $(OBJECTS)
