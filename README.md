# Minishell

Minishell es una implementación simplificada de un shell en C, desarrollada como parte del currículo de la escuela 42. Su objetivo es profundizar en el funcionamiento de los intérpretes de comandos, la gestión de procesos y señales, así como mejorar la comprensión del sistema operativo Unix/Linux.

## Características

- Soporte para múltiples comandos encadenados con pipes (`|`).
- Gestión de redirecciones de entrada y salida (`>`, `>>`, `<`, `<<`).
- Implementación de built-ins (`cd`, `export`, `unset`, `env`, etc.).
- Manejo de variables de entorno sin el uso de `setenv`, `unsetenv` ni `environ`.
- Expansión de variables (`$VAR`).
- Manejo de señales (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`).
- Soporte para comillas simples y dobles.
- Gestión de errores de sintaxis y ejecución.

## Instalación y Uso

```sh
# Clonar el repositorio
git clone https://github.com/grabier/minishell.git
cd minishell

# Compilar el proyecto
make

# Ejecutar Minishell
./minishell
```

## Ejemplos de Uso

```sh
# Ejecutar un comando simple
echo "Hola, mundo"

# Redirecciones
ls > output.txt

# Uso de pipes
ls -l | grep minishell

# Manejo de variables de entorno
export PATH="/usr/bin:$PATH"
echo $PATH
```

## Dependencias

- `gcc` (o cualquier compilador compatible con C)
- `make`
- Entorno Linux o MacOS
