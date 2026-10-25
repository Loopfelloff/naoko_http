# naoko_http

A miniature HTTP/1.1 web server written in C.

**naoko_http** is a lightweight HTTP server maintained by [AbhiyanRegmi (Loopfelloff)](https://github.com/Loopfelloff). It is a learning-oriented project focused on understanding network programming, HTTP request handling, process-based concurrency, and static file serving in C.

> **Status:** Under maintenance and active development.

## Features

- **HTTP/1.1 request handling** — handles incoming HTTP requests.
- **Static file serving** — serves static files through `GET` requests.
- **Supported file types** — currently supports HTML, CSS, and JavaScript files.
- **Process-based concurrency** — creates a child process to handle each incoming client connection.
- **Automatic child process reaping** — the parent process reaps child processes after they finish handling requests.
- **Configurable server settings** — allows configuration of the TCP port, listening backlog, and receive buffer length.

## Concurrency Model

naoko_http uses a **process-per-connection** concurrency model.

When a client connects to the server, the parent process creates a child process to handle that connection. The child processes the request and sends the response to the client, while the parent continues listening for new connections.

After a child process terminates, the parent reaps it to prevent zombie processes.

This approach provides process-level isolation between client connections and serves as a practical introduction to concurrent network programming in C.

## Getting Started

### Prerequisites

- Git
- GCC or another compatible C compiler
- GNU Make
- A Unix-like operating system with POSIX socket and process APIs

### 1. Clone the repository

```bash
git clone git@github.com:Loopfelloff/naoko_http.git
cd naoko_http
```

Alternatively, clone using HTTPS:

```bash
git clone https://github.com/Loopfelloff/naoko_http.git
cd naoko_http
```

### 2. Add your static files

Navigate to the `assets` directory:

```bash
cd assets
```

Place your HTML files directly inside `assets/`. JavaScript files should go inside `javascript/`, and CSS files should go inside `css/`.

The directory structure should look like this:

```text
naoko_http/
├── assets/
│   ├── index.html
│   ├── about.html
│   ├── css/
│   │   └── style.css
│   └── javascript/
│       └── script.js
├── src/
├── include/
├── tests/
├── Makefile
└── README.md
```

Ensure that `index.html` exists inside `assets/` before requesting it from the browser.

### 3. Build the project

Return to the project root and compile the server:

```bash
cd ..
make
```

### 4. Start the server

Run the compiled executable:

```bash
./build/bin/webserver
```

The server listens on TCP port **3490** by default.

### 5. Access the server

Open the following URL in your browser:

```text
http://localhost:3490/index.html
```

If `assets/index.html` exists and the server starts successfully, the browser should display the page.

You can also request other static resources, such as:

```text
http://localhost:3490/about.html
http://localhost:3490/css/style.css
http://localhost:3490/javascript/script.js
```

## Configuration

To modify the server configuration, open `src/main.c` from the project root.

```bash
cd src
```

Open `main.c` in your preferred text editor and locate the server initialization/configuration code.

You can modify the following parameters:

| Parameter | Description |
|---|---|
| TCP port | The port on which the server listens for incoming connections. The default is `3490`. |
| `buf_len` | The buffer length used when receiving incoming request data. |
| `backlog` | The maximum number of pending connections permitted in the listening socket's queue. |

After changing the configuration, return to the project root and rebuild:

```bash
cd ..
make
```

Then restart the server for the changes to take effect.

## Current Limitations

naoko_http is currently a minimal HTTP server intended primarily for learning and experimentation.

- Only `GET` requests for static resources are supported.
- Supported resource types are currently limited to HTML, CSS, and JavaScript.
- JSON request-body parsing is not yet implemented.
- `POST` request handling is not yet implemented.
- Persistent connections and connection reuse are not yet supported as a complete HTTP/1.1 feature.
- The server is not intended for production use.

## Future Development

The following are planned areas for further development:

- [ ] Parse JSON request bodies.
- [ ] Implement `POST` request handling.
- [ ] Expand static file support to additional file formats.
- [ ] Improve connection handling and support persistent connections.
- [ ] Improve HTTP response generation and request processing.
- [ ] Extend protocol support and error handling.

These improvements will expand the server beyond basic static file serving and provide a foundation for handling more general HTTP communication.

## Development Background

Development of naoko_http was guided by **[Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)**, which provides a practical introduction to socket programming and network communication.

The project is an opportunity to explore the fundamentals of building a web server from the ground up, including TCP sockets, HTTP request parsing, process management, and response transmission.

## Contributing

Contributions, suggestions, and bug reports are welcome. If you find an issue or have an idea for improvement, feel free to open an issue or submit a pull request on GitHub.

## AI Usage

AI tools were used during the development and documentation of this project in the following ways:

- **README documentation:** The initial draft of this README was prepared using ChatGPT.
- **Memory leak prevention review:** Claude and ChatGPT were used for proofreading and reviewing the code for potential memory leaks.
- **Default static assets:** The default static files included in the `assets/` directory were prepared using Claude Sonnet 5.5 Low.

AI-assisted reviews and generated content do not guarantee the absence of memory leaks or other software defects. The code remains subject to further testing and verification.

## Maintainer

**Abhiyan Regmi (Loopfelloff)**

GitHub: [@Loopfelloff](https://github.com/Loopfelloff)

## License

A license has not been specified yet. Idgaf anyways so go bananas with this

