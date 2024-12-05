/* By: Ludvig Gunne Lindström */
#ifndef BUTTON_H
#define BUTTON_H

int	button_get(void);
void	button_set_event(void (*fn)(int));

#endif
