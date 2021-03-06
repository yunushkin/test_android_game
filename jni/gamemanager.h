#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "note.h"
#include "score.h"
#include "texture.h"
#include "action.h"
#include "joystick.h"
#include <linux/stddef.h>
#include <list>
#include <pthread.h>

class Level;

class GameManager {
	enum {
		backgroundTex = 10, tubeTex, pushButtonUpTex, pushButtonUpOnPressTex, pushButtonDownTex, pushButtonDownOnPressTex, pushButtonLeftTex, pushButtonLeftOnPressTex,
		pushButtonRightTex, pushButtonRightOnPressTex, noteUpTex, noteDownTex, noteLeftTex, noteRightTex
	};
	GameManager();
	~GameManager();
	GameManager(const GameManager &) {}
	void operator=(const GameManager & ){}
	Level * lvl;
	std::list<Joystick::JoystickAction> userMove;
	Score score;
	Texture background;
	Joystick joystick;
	Texture leftTube;
	Texture rightTube;
	NoteList leftNoteList;
	NoteList rightNoteList;
	static pthread_mutex_t mutex;
	static const int updateTime = 1000; 
	static int texCounter;
public:
	static void lock();
	static void unlock();
	static GameManager& getInstance();
	void init();
	void loop();
	void draw();
	void onTouchEvent(const TouchAction& touchAct);
	void onResize(const int w, const int h);
	void setTexture(int texID);
};
#endif
