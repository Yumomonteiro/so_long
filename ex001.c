#include <stdio.h>
#include <stdlib.h>
#include "minilibx-linux/mlx.h"
#include  "minilibx-linux/mlx_int.h"
int main()
{
    void *mlx_ptr;
    mlx_ptr = mlx_init();
    if (NULL == mlx_ptr)
        return (1);
    mlx_destroy_display(mlx_ptr);
    free(mlx_ptr);
}
