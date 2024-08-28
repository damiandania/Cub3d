#! /usr/bin/bash

# valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-fds=yes  --track-origins=yes -s --trace-children=yes ./minishell
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes  --track-origins=yes -s ./cub3D map/map1.cub
