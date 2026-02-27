// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FMTeamModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
