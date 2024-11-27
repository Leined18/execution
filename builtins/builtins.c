/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:39:30 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/11/27 11:40:25 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// Declaración del array (sin inicializar)
t_builtin builtins[4];

void init_builtins(void)
{
    builtins[0].name = "cd";
    builtins[0].func = cd_builtin;

    builtins[1].name = "env";
    builtins[1].func = env_builtin;

    builtins[2].name = "pwd";
    builtins[2].func = pwd_builtin;

    builtins[3].name = NULL;
    builtins[3].func = NULL;
}

int execute_builtin(char **args, t_env *envp)
{
    for (int i = 0; builtins[i].name; i++)
    {
        if (strcmp(args[0], builtins[i].name) == 0)
            return builtins[i].func(args, envp);
    }
    return -1; // No es un builtin
}