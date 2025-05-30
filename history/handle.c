#include "../data.h"

void	add_mhistory_file(t_lines *history_lines)
{
	int		fd;
	char	*index;
	t_lines	*tmp;

	fd = open(".history", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Error opening history file");
		return ;
	}
	tmp = history_lines;
	if (!tmp)
	{
		close(fd);
		return ;
	}
	while (tmp)
	{
		index = ft_itoa(tmp->index);
		write(fd, index, ft_strlen(index));
		write(fd, ' ', 1);
		write(fd, tmp->line, ft_strlen(tmp->line));
		write(fd, '\n', 1);
	}
	close(fd);
}

void	clear_history(void)
{
	int	fd;

	fd = open(".history", O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		perror("Error al limpiar el historial");
		return ;
	}
	close(fd);
}

int	main(void)
{
	t_data	*data_program;
	t_lines	*history_lines;

	data_program = (t_data *)malloc(sizeof(t_data));
	history_lines = (t_lines *)malloc(sizeof(t_lines));
	add_mhistory(data_program, "cmd01 test");
	add_mhistory(data_program, "cmd02 test");
	printf("cmdt tester added\n");
	show_history(data_program);
	printf("history_lines created\n");
	add_mhistory_file(history_lines);
	printf("lines added to .history\n");
	// clear_history();
	return (0);
}

// COMPILAR PARA PROBAR
// cc libft/libft.a history/handle.c


// PENDIENTE:

// ¿Cómo maneja la shell original la búsqueda inversa (Ctrl + R)?
// Las shells como bash implementan esta funcionalidad de forma interactiva usando una búsqueda incremental inversa sobre el historial en memoria, no sobre el fichero .bash_history.
// 	•	Cuando pulsas Ctrl + R, entras en un modo interactivo donde puedes escribir una parte del comando y se va buscando hacia atrás en el historial.
// 	•	Esto se gestiona con librerías como readline, que internamente mantienen una lista en memoria (usualmente una lista enlazada o un array dinámico).
// 	•	La búsqueda es en tiempo real, mostrando coincidencias conforme escribes.

// ¿El shell original guarda duplicados en el historial?
// Sí, bash guarda duplicados, pero con excepciones o configuraciones:
// 	•	Por defecto, sí los guarda, incluso comandos idénticos seguidos.
// 	•	Sin embargo, puedes evitar duplicados usando la variable de entorno HISTCONTROL.
// Por ejemplo:
// export HISTCONTROL=ignoredups
// O:
// export HISTCONTROL=erasedups
// En resumen: guardar duplicados es lo normal, pero permitir opciones de configuración mejora la experiencia. Puedes empezar guardándolos y más adelante agregar opciones.
// ¿Qué utilidad tiene limitar el tamaño del historial?
// Limitar el tamaño del historial tiene tres utilidades principales:
// 	1.	Evitar crecimiento excesivo del archivo .history
// 	•	Si el usuario deja abierta la shell por días, puede acumular miles de líneas.
// 	2.	Reducir uso de memoria
// 	•	Si cargas toda la historia en memoria (lista), no quieres que eso se vuelva costoso.
// 	3.	Simular comportamiento estándar
// 	•	Bash, por ejemplo, usa variables como HISTSIZE y HISTFILESIZE:

// export HISTSIZE=1000       # en memoria > ~ 1MB
// export HISTFILESIZE=2000   # en disco	> ~ 2MB
// 	•	Esto significa que el historial en memoria puede ser más grande que el del archivo, pero no al revés.
// 	•	Si el archivo es más grande, se trunca al tamaño de HISTFILESIZE.
// 	•	Si la memoria es más grande, se trunca al tamaño de HISTSIZE.

// ➡️ Si quieres imitar bash, puedes poner un límite razonable (ej: 500 o 1000) y recortar la lista/fichero cuando se supere.
