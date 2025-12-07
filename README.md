# 🐚 Minishell - As beautiful as a shell can be

> "Writing your own shell is the best way to understand how your OS really talks to you."

[![C](https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Bash](https://img.shields.io/badge/Shell-Bash_Compatible-4EAA25?style=for-the-badge&logo=gnu-bash)](https://www.gnu.org/software/bash/)
[![42](https://img.shields.io/badge/School-42-000000?style=for-the-badge&logo=42)](https://42.fr/)

## 🚀 Introducción

Minishell es una recreación simplificada (pero robusta) de la shell Bash. Este proyecto no trata solo de parsear comandos, sino de entender y manipular los procesos del sistema, la gestión de memoria y los descriptores de archivos a bajo nivel utilizando la API de C de Unix.

El objetivo: crear una shell funcional capaz de ejecutar comandos, manejar tuberías (pipes), redirecciones y señales, **sin fugas de memoria (memory leaks)**.

---

## 📸 Demo en Acción

![Pipes Demo](assets/minishell.png)

---

## ✨ Características Implementadas

| Categoría | Funcionalidades |
| :--- | :--- |
| **Command Execution** | Ejecución de binarios (ej. `/bin/ls`) y comandos del `PATH`. |
| **Built-ins** | Implementación propia de `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`. |
| **Redirections** | Input (`<`), Output (`>`), Append (`>>`) y Here-Doc (`<<`). |
| **Pipes** | Tuberías infinitas (`cmd1 | cmd2 | cmd3 ...`). |
| **Signals** | Manejo correcto de `Ctrl-C` (SIGINT), `Ctrl-\` (SIGQUIT) y `Ctrl-D` (EOF). |
| **Parsing** | Manejo de comillas simples (`' '`) y dobles (`" "`) y expansión de variables (`$VAR`). |
| **Memory** | Gestión rigurosa. Cero leaks comprobados con Valgrind. |

---

## 🧠 Desafíos Técnicos

Lo más complejo de este proyecto no fue lo que se ve, sino lo que ocurre detrás:

* **Arquitectura Padre/Hijo:** Uso intensivo de `fork()` para crear subprocesos y `execve()` para convertirlos en nuevos programas.
* **Gestión de File Descriptors:** Uso de `dup2()` y `pipe()` para redirigir `STDIN` y `STDOUT` entre procesos sin perder el control de la terminal.
* **Signal Handling:** Evitar que la shell se cierre cuando un proceso hijo recibe una señal de interrupción, diferenciando entre el modo interactivo y el de ejecución.

---

## 🛠️ Instalación y Uso

```bash
# 1. Clona el repositorio
git clone [https://github.com/grabier/minishell.git](https://github.com/grabier/minishell.git)

# 2. Entra al directorio
cd minishell

# 3. Compila (asegúrate de tener readline instalado)
make

# 4. Ejecuta
./minishell
