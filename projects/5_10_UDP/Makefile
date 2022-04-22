all:server  client
server:server.c
	gcc  $^  -o  $@
client:client.c
	gcc  $^  -o  $@
clean:
	rm server  client -f
.PHONY:clean