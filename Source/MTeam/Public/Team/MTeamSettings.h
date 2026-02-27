// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MTeamDefinition.h"
#include "Engine/DeveloperSettings.h"
#include "MTeamSettings.generated.h"

UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="MTeam Settings"))
class MTEAM_API UMTeamSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	static UMTeamSettings* Get() { return CastChecked<UMTeamSettings>(StaticClass()->GetDefaultObject()); }

	UPROPERTY(EditAnywhere, Config)
	TArray<FMTeamDefinition> Teams;

	UPROPERTY(EditAnywhere, Config)
	TArray<FMTeamAttitudeOverride> AttitudeOverrides;
};


