/*
  Serial Adapter Project: Dynamic serial TTY passthroughs
 by: Mike Crosson
 Nusku Networks
 date: 2013/03/09
 license: CC-BY SA 3.0 - Creative commons share-alike 3.0
 use this code however you'd like, just keep this license and
 attribute.
 */

// UI State machine (current element = config / stats / inline display of data)
// Configuration state machine (speed, pinout, logic level, sd card on/off, boot logo on/off)
// Message to config (element + new value)
// Message to UI (element + success/fail)

// Button's controlling UI
// UIButton* okButton = new UIButton(22, 23);
// UIButton* cancelButton = new UIButton(24, 25);

#include "Project.h"
#include "UIButton.h"
#include "UIJoystickPSP.h"
#include "UILCD.h"
#include "Config.h"

class UI {
private:
	UIButton* okButton;
	UIButton* cancelButton;
	UIJoystickPSP* pspJoystick;

	joyDirection joyStickEvent;

	UILCD* lcd;

	Config* config;

public:
	UI(Config* aConfig);
	void startUI();

	void processInputEvents();

	void disableUI();
	void enableUI();
};
