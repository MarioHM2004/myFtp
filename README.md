# MyFTP - FTP Protocol Implementation in C

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Supported Commands](#supported-commands)
- [Command-Reply Sequences](#command-reply-sequences)
- [Response Codes](#response-codes)
- [License](#license)
- [Contributing](#contributing)
- [References](#references)

## Introduction
MyFTP is a custom implementation of the File Transfer Protocol (FTP) based on RFC959, written in C. It supports a wide range of FTP commands, including user authentication, directory navigation, file transfer, and more. This project serves as both a practical example of network programming and a fully functional FTP server.

## Features
- **User Authentication**: Supports anonymous login with an empty password.
- **Directory Navigation**: Change directories, list contents, and print working directory.
- **File Transfer**: Upload and download files using both active and passive modes.
- **File Management**: Delete files on the server.
- **Informational Commands**: Get help and execute no-operation commands.
- **Compliant with RFC959**: Ensures compatibility with the official FTP specifications.

## Installation

1. **Clone the repository**:
    ```bash
    git clone https://github.com/MarioHM2004/myFtp.git
    cd myFtp
    ```

2. **Compile the source code**:
    ```bash
    make
    ```

## Usage

1. **Start the FTP server**:
    ```bash
    ./myftp port path
    ```

2. **Connect to the server** using an FTP client or command line:
    ```bash
    telnet localhost port
    ```

3. **Login as anonymous**:
    ```
    USER: Anonymous
    PASS: (press Enter)
    ```

## Supported Commands

Below are the mandatory FTP commands supported by MyFTP:

- **USER**: Specify user for authentication.
    ```
    USER <username>
    ```
- **PASS**: Specify password for authentication.
    ```
    PASS <password>
    ```
- **CWD**: Change working directory.
    ```
    CWD <pathname>
    ```
- **CDUP**: Change working directory to parent directory.
    ```
    CDUP
    ```
- **QUIT**: Disconnect from the server.
    ```
    QUIT
    ```
- **DELE**: Delete file on the server.
    ```
    DELE <pathname>
    ```
- **PWD**: Print working directory.
    ```
    PWD
    ```
- **PASV**: Enable "passive" mode for data transfer.
    ```
    PASV
    ```
- **PORT**: Enable "active" mode for data transfer.
    ```
    PORT <host-port>
    ```
- **HELP**: List available commands.
    ```
    HELP [<string>]
    ```
- **NOOP**: Do nothing.
    ```
    NOOP
    ```
- **RETR**: Download file from server to client.
    ```
    RETR <pathname>
    ```
- **STOR**: Upload file from client to server.
    ```
    STOR <pathname>
    ```
- **LIST**: List files in the current working directory.
    ```
    LIST [<pathname>]
    ```

## Command-Reply Sequences

MyFTP follows the command-reply sequences specified in RFC959. Below are examples of typical interactions:

- **Connection Establishment**:
    ```
    <- 220 Service ready for new user.
    ```

- **Login**:
    ```
    -> USER anonymous
    <- 331 User name okay, need password.
    -> PASS 
    <- 230 User logged in, proceed.
    ```

- **Directory Navigation**:
    ```
    -> CWD /directory
    <- 250 Requested file action okay, completed.
    ```

- **File Transfer**:
    ```
    -> RETR filename
    <- 150 File status okay; about to open data connection.
    <- 226 Closing data connection.
    ```

- **Logout**:
    ```
    -> QUIT
    <- 221 Service closing control connection.
    ```

## Response Codes

MyFTP supports the following response codes:

- **120**: Service ready in nnn minutes.
- **125**: Data connection already open; transfer starting.
- **150**: File status okay; about to open data connection.
- **200**: Command okay.
- **214**: Help message.
- **220**: Service ready for new user.
- **221**: Service closing control connection.
- **226**: Closing data connection.
- **227**: Entering Passive Mode.
- **230**: User logged in, proceed.
- **250**: Requested file action okay, completed.
- **257**: "PATHNAME" created.
- **331**: User name okay, need password.
- **332**: Need account for login.
- **xxx**: Error (RFC compliant)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request to discuss any changes or improvements.

## References

- [RFC959 - File Transfer Protocol](https://tools.ietf.org/html/rfc959)
