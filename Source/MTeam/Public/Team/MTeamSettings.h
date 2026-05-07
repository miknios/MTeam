// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MDeveloperSettingsAsset.h"
#include "MTeamDefinition.h"
#include "MTeamSettings.generated.h"

UCLASS()
class MTEAM_API UMTeamSettings : public UMDeveloperSettingsAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FMTeamAttitudeOverride> AttitudeOverrides;
};
