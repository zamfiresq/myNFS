# myNFS

## Project Overview

This project implements a **Network File System (NFS)** client and server, allowing remote access to a shared filesystem over a network. It involves building both the **NFS server** and **NFS client**, which communicate using the **Remote Procedure Call (RPC)** protocol. This setup allows the client to invoke procedures on the server without needing to know the underlying details of how those procedures are executed, ensuring seamless interaction between systems.

## Key Features

- **RPC Communication**: The NFS client and server communicate through RPC, using functions such as `opendir`, `readdir`, `mkdir` etc.
- **File Operations**: The NFS client can perform various file operations (e.g., listing directories, creating files, and directories) remotely on the NFS server.
- **Error Handling**: The project includes basic error handling for timeouts, connection errors, and memory allocation issues.
- **Memory Management**: Tools such as **Valgrind** and **AddressSanitizer** are used to detect and manage memory leaks, buffer overflows, and segmentation faults.

## Technical Details

### Dependencies

- **LibTIRPC**: The project uses `libtirpc` to implement the transport-independent RPC.
  - To install: `sudo apt-get install libtirpc-dev`
- **GCC**: The project is compiled using the GCC compiler with `-ltirpc` linked.
- **GDB & Valgrind**: For debugging and memory error detection.

### Compilation

To compile the NFS client:

```bash
gcc -g -o nfs_client nfs_client.c -ltirpc
```
To compile the NFS server:

```bash
gcc -g -o nfs_server nfs_server.c -ltirpc

```
Or:
```bash
make -f Makefile.nfs
```

### Running the Project

Start the NFS server:

```bash

./nfs_server
```

Run the NFS client to connect to the server:

```bash

./nfs_client
```
