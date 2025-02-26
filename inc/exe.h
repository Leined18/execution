/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:20:16 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/02/26 13:20:17 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H

# include "builtin.h"
# include "types.h"
# include "cmd.h"
# include "env.h"
# include "exe_utils.h"
# include "libft.h"
# include "mt.h"
# include "parse.h"
# include <readline/history.h>
# include <readline/readline.h>

// Verde
# define SUCCESS "\033[1;32m✅ Success: Function finished well!\n\033[0m"
// Rojo
# define ERROR "\033[1;31m❌ Error: Error in function!\n\033[0m"
// Amarillo
# define WARNING "\033[1;33m⚠️ Warning: Warning in function!\n\033[0m"

#endif