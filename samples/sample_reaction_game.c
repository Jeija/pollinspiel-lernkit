/*
	Der Spieler muss rechtzeitig den Taster bei der LED drücken, die aufleuchtet.
	Dabei erhöht sich die Spielgeschwindigkeit immer weiter. Am Ende wird das Ergebnis
	auf dem LCD-Display angezeigt.
*/

while(true)
{
	// Titel anzeigen
	ClearDisplay();
	char blockstring[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	WriteDisplayString("REACTION");
	SetDisplayCursor(0, 0);
	WriteDisplayString(blockstring);

	// Werte initialisieren
	int max_reaction_time = 1000;
	int reaction_time = 0;
	bool gameover = false;
	int score = 0;

	// Spiel starten, wenn Taster 5 gedrückt wird
	while(!getbutton(BUTTON5));
	ClearDisplay();
	WriteDisplayString("GO!");

	// Das Spiel selbst, solange nicht verloren:
	while(!gameover)
	{
		// Zeit zum reagieren als seed für die nächste LED verwenden
		uint8_t led = reaction_time % 4 + 1;

		// LED kurz aufblinken lassen mit sound
		setled(led, LED_ON);
		sound(440, 200);
		setled(led, LED_OFF);

		// Warten bis richtiger Knopf gedrückt wurde
		reaction_time = 0;
		while(!getbutton(led))
		{
			// Wenn nicht rechtzeitig gedrückt wird: Game Over
			reaction_time++;
			if (reaction_time > max_reaction_time)
				gameover = true;

			// Game Over, wenn falscher Knopf gedrückt wird
			for (uint8_t i = 1; i <= 4; i++)
				if (getbutton(i) && led != i)
					gameover = true;

			if (gameover) break;

			_delay_ms(1);
		}
		if (!gameover) score++;
		_delay_ms(300);

		// Spielgeschwindigkeit erhöhen
		max_reaction_time *= 0.97;
	}

	// "Game Over" anzeigen auf dem LCD
	ClearDisplay();
	WriteDisplayString("Game");
	SetDisplayCursor(0, 0);
	WriteDisplayString("Over");
	sound(440, 2000);

	// Score anzeigen
	char score_str[8];
	itoa(score, score_str, 10);
	ClearDisplay();
	WriteDisplayString("Score");
	SetDisplayCursor(0, 0);
	WriteDisplayString(score_str);
	_delay_ms(3000);
}
