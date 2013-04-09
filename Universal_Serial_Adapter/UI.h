/*
  Serial Adapter Project: Dynamic serial TTY passthroughs
 by: Mike Crosson
 Nusku Networks
 date: 2013/03/09
 license: CC-BY SA 3.0 - Creative commons share-alike 3.0
 use this code however you'd like, just keep this license and
 attribute.
 */

#include <Metro.h>

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

	Metro* uiTimeout;

public:
	UI(Config* aConfig);
	void startUI();

	void processInputEvents();
	void processTimeoutEvents();

	void disableUI();
	void enableUI();
};
