#ifndef _UTIL_H
#define _UTIL_H

/***** LED enums *****/
enum LED_state
{
	LED_ON = 1,
	LED_OFF = 0
};
typedef enum LED_state LED_state;

enum LED_id
{
	LED1 = 1,
	LED2 = 2,
	LED3 = 3,
	LED4 = 4
};
typedef enum LED_id LED_id;

/***** Button enums *****/
enum Button_state
{
	BUTTON_PRESSED = 1,
	BUTTON_RELEASED = 0
};
typedef enum Button_state Button_state;

enum Button_id
{
	BUTTON1 = 1,
	BUTTON2 = 2,
	BUTTON3 = 3,
	BUTTON4 = 4,
	BUTTON5 = 5
};
typedef enum Button_id Button_id;

// Für den Programmierer relevante Funktionen
void setled(LED_id led, LED_state state);
Button_state getbutton(Button_id button);
void sound(int freq, int duration);
void waitms(int ms);

// Interne Funktionen zur Initialisierung etc.
void init(void);
void done(void);

#endif
