#include "stdafx.h"

class myinitquit : public initquit {
public:
	void on_init() {
	}
	void on_quit() {
	}
};
static initquit_factory_t<myinitquit> g_myinitquit_factory;