/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
int loop_separator(char c, char *separator);

int find_index_separator(char *str, int idx_pcd, char *separator)
{
    for (; str[idx_pcd] != '\0'; idx_pcd += 1) {
        if (loop_separator(str[idx_pcd], separator) == 0 &&
            loop_separator(str[idx_pcd + 1], separator) == 1) {
            return idx_pcd + 1;
        }
    }
    return -1;
}
