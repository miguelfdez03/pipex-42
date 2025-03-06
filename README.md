<h1 align="center">🚀 pipex</h1>
<h3 align="center">Una implementación de pipes en C</h3>

# 📝 Descripción
Pipex es un proyecto que recrea el comportamiento de los pipes en shell. Simula el funcionamiento del operador `|` y los redireccionamientos `<` y `>`, permitiendo la ejecución de comandos en cadena.

## 🔍 Funcionamiento Detallado

### Prototipo del programa
```bash
./pipex archivo1 comando1 comando2 archivo2
```
Equivale a:
```bash
< archivo1 comando1 | comando2 > archivo2
```

### Estructura del Proyecto
```
.
├── pipex.c          # Función main y lógica principal
├── pipex.h          # Header con prototipos y definiciones
└── pipex_utils.c    # Funciones auxiliares
```

### Funciones Principales

1. `main()`: 
   - Valida argumentos
   - Crea el pipe
   - Gestiona los procesos padre e hijo

2. `child_process()`: 
   - Maneja el primer comando
   - Redirecciona entrada desde archivo1
   - Conecta su salida al pipe

3. `parent_process()`:
   - Maneja el segundo comando
   - Lee desde el pipe
   - Redirecciona salida a archivo2

### Gestión de Procesos
- Utiliza `fork()` para crear procesos
- Usa `pipe()` para comunicación entre procesos
- Maneja descriptores de archivo correctamente
- Implementa `waitpid()` para sincronización

## 🚀 Uso

### Compilación
```bash
make
```

### Ejemplos de Uso
```bash
# Contar líneas de un archivo
./pipex input.txt "cat" "wc -l" output.txt

# Buscar una palabra y ordenar resultados
./pipex archivo.txt "grep palabra" "sort" resultados.txt

# Comprimir un archivo
./pipex original.txt "cat" "gzip" comprimido.gz
```

## ⚠️ Manejo de Errores
- Verifica permisos de archivos
- Valida existencia de comandos
- Controla errores de pipe y fork
- Gestiona memoria dinámicamente

## 🔧 Funciones Permitidas
- pipe()
- fork()
- dup2()
- execve()
- wait()
- access()
- unlink()
- malloc()
- free()
- perror()
- strerror()
- exit()

## 📚 Funciones Auxiliares

### find_command_path()
- Busca la ruta completa del comando
- Utiliza la variable PATH
- Verifica permisos de ejecución

### open_file_handler()
- Gestiona apertura de archivos
- Maneja permisos y errores
- Crea archivos si es necesario

### get_env_value()
- Busca variables de entorno
- Extrae valores específicos
- Útil para PATH y otras variables

## 🧪 Testing
```bash
# Test básico
./pipex infile.txt "ls -l" "wc -l" outfile.txt

# Test con comando inexistente
./pipex infile.txt "comando_falso" "wc -l" outfile.txt

# Test con archivo sin permisos
./pipex /etc/shadow "cat" "wc -l" outfile.txt
```

## 💡 Consejos
- Cierra siempre los descriptores de archivo
- Libera la memoria correctamente
- Maneja todos los casos de error posibles
- Comprueba los valores de retorno

---


- LinkedIn: https://www.linkedin.com/in/miguelfdezmunoz

---

Nota: Este repositorio se sube con el propósito de compartir mi progreso y ofrecer un recurso orientativo para aquellos que necesiten ayuda en su aprendizaje. Espero que se utilice como base de estudio y no solo para copiar y pegar soluciones.
<p align="center">🚀 Never stop learning!</p>