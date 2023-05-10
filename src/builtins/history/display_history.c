/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** display_history
*/

#include <string.h>
#include <stdlib.h>
#include "mysh.h"
#include "str_func.h"
#include "macro_errors.h"

static void print_history_line(history_t *history, int fd)
{
    char *time = create_time_line();
    char *num = num_to_str(history->num_cmd);

    if (!time || !num)
        return;
    if (history->flags == NO_FLAG)
        dprintf(fd, "%s  %s   %s\n", num, time, "history");
    free(num);
    free(time);
}

static void print_tab_elt(tab_hist_t *elt, int fd, int flags)
{
    if (!elt)
        return;
    if (IS_FLAG(flags, FLAG_H))
        dprintf(fd, "%s", elt->command);
    else
        dprintf(fd, "%s  %s   %s", elt->num, elt->time, elt->command);
}

int display_history(tab_hist_t **tab, int fd, history_t *history)
{
    int i = 0;
    int step = 1;
    int end = 0;

    if (!tab || !history)
        return ERROR;
    end = my_strstrlen((char **)tab);
    if (IS_FLAG(history->flags, FLAG_R)) {
        i = end - 1;
        step = -1;
        end = -1;
    }
    for (; i != end; i += step) {
        print_tab_elt(tab[i], fd, history->flags);
    }
    print_history_line(history, fd);
    return SUCCESS;
}
