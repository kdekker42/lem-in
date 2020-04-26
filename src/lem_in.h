/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lem_in.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: twoerdem <twoerdem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/20 11:33:18 by twoerdem       #+#    #+#                */
/*   Updated: 2019/11/26 15:34:04 by twoerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# define L_ROOM 1
# define L_LINK 2
# define L_COMM 3
# define L_ANTS 4
# define L_IGNO 5

typedef struct		s_read
{
	char			*line;
	char			*original_line;
	int				type;
	struct s_read	*next;
}					t_read;

typedef struct		s_edge
{
	struct s_vertex	*vertex;
	struct s_edge	*next;
	struct s_edge	*prev;
	int				direction;
	int				visited;
	int				visible;
}					t_edge;

typedef struct		s_paths
{
	struct s_edge	*path;
	struct s_paths	*next;
	int				ants;
	int				path_length;
}					t_paths;

typedef struct		s_vertex
{
	char			visited;
	int				ant;
	int				new_ant;
	char			*name;
	t_edge			*edges;
	struct s_vertex	*prev_in_bfs;
	struct s_vertex	*next;
}					t_vertex;

typedef	struct		s_rooms
{
	char			*name;
	t_vertex		*in;
	t_vertex		*out;
	struct s_rooms	*next;
}					t_rooms;

typedef struct		s_lem_in
{
	int				n_ants;
	int				n_rooms;
	int				shortest_path;
	t_vertex		*begin;
	t_vertex		*end;
	t_paths			*found_paths;
	t_paths			*new_found_paths;
	t_rooms			**hash_table;
	char			*error;
	struct s_read	*lines;
}					t_lem_in;

int					is_coord(char *str);
void				get_line_type(t_lem_in *lem_in, t_read *new_line,\
						char *line);
void				read_to_list(t_lem_in *lem_in, char *line);
void				read_file(t_lem_in *lem_in);

char				*extract_room_name(char *line);
int					get_hash_key(char *name, int size);
t_vertex			*create_vertex(char *name);
void				add_room_to_table(t_read *list, t_read *prev,\
						t_lem_in *lem_in);
void				index_rooms(t_lem_in *lem_in);

t_rooms				*get_room_from_table(char *name, t_lem_in *lem_in);
void				insert_link(t_vertex *room_a, t_vertex *room_b,\
						int direction);
void				create_link(t_read *list, t_lem_in *lem_in);
void				make_links(t_read *list, t_lem_in *lem_in);
t_rooms				*init_table(char *name);

int					edge_direction_breath_first_search(t_lem_in *lem_in);
t_edge				*ed_bfs_loop_edges(t_edge *queue);
void				place_edge_directions(t_lem_in *lem_in);
int					get_edge_direction(t_vertex *room_a, t_vertex *room_b);
void				edit_edge_direction(t_vertex *room_a, t_vertex *room_b);

int					path_finding_breath_first_search(t_lem_in *lem_in);
t_edge				*pf_bfs_loop_edges(t_edge *queue);
void				track_path(t_lem_in *lem_in);
void				add_to_path_list(t_lem_in *lem_in, t_edge *path,\
						int path_length);
t_edge				*add_to_path(t_edge *path, t_vertex *room);

void				push_to_queue(t_edge *queue, t_vertex *room);
void				do_stuff(t_lem_in *lem_in, t_rooms *new_table);
void				clean_queue(t_edge *queue);
void				unvisit_edges(t_rooms *table);
void				visit_edge(t_vertex *room_a, t_vertex *room_b);

void				spread_ants(t_lem_in *lem_in, t_paths *path_list);
int					calculate_longest_path(t_paths *path_list);
void				unvisit(t_lem_in *lem_in);
void				clean_paths(t_paths *paths, t_lem_in *lem_in);
void				pathfinding(t_lem_in *lem_in);

void				print_list(t_read *list);
int					pull_ants_and_print(t_edge *path, int ant, int printed);
void				print_solution(t_paths *path_list, t_lem_in *lem_in,\
						int ant);
void				execute_functions(t_lem_in *lem_in);

void				paths_found(t_lem_in *lem_in);
void				bonus_flag(t_lem_in *lem_in, char *flag);

#endif
