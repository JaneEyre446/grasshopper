gcc -c ${1} ../lib/console.c -o console.o
gcc -c ${1} ../lib/file.c -o file.o
gcc -c ${1} ../lib/socket.c -o socket.o
gcc -c ${1} ftpClient.c -o ftpClient.o
gcc -c ${1} ftpServer.c -o ftpServer.o
gcc ${1} console.o file.o socket.o ftpServer.o -o ftpServer
gcc ${1} console.o file.o socket.o ftpClient.o -o ftpClient

