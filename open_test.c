#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int	main(void)
{
	int	fd;

	unlink("fichier_test");
	fd = open("fichier_test", O_CREAT, 00777);
	return (0);
}
