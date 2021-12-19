#pragma once

#include "p2List.h"
#include "Globals.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleSceneIntro.h"

#include "PerfTimer.h"
#include "Timer.h"

#include <sstream>
#include <string.h>
using namespace std;

class Application
{
public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModulePlayer* player;
	ModuleSceneIntro* scene_intro;
	ModulePhysics* physics;

private:

	p2List<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	// Config
	void setDeltaTime(float dt) { this->dt = dt; };

	void setWindowTitle(const char* title) { window->SetTitle(title); };

	void setDebugMode() { debug = !debug; };
	bool getDebugMode() { return debug; };

private:

	void AddModule(Module* mod);

private:
	// Debug by default is off (Debug key = F1)
	bool debug = false;

	// Time control --------
	PerfTimer* ptimer;
	PerfTimer* frameDuration;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;

	int frameCount = 0;
	int framesPerSecond = 0;
	int lastSecFrameCount = 0;

	float dt = 1000.0f / 60;
};