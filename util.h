#ifndef _UTIL_H
#define _UTIL_H

void init(void);
void done(void);

void setled(uint8_t LED, uint8_t state);
char getbutton(char button);
void sound(int freq, int duration);
void waitms(int ms);
void setledByNum(uint8_t lednum, uint8_t state);

#endif
