// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "MTeamDefinition.generated.h"

UCLASS()
class UMTeamDefinitionAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FGenericTeamId TeamId;
};

USTRUCT(BlueprintType)
struct MTEAM_API FMTeamAttitudeOverride
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMTeamDefinitionAsset> TeamADef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMTeamDefinitionAsset> TeamBDef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETeamAttitude::Type> Attitude = ETeamAttitude::Neutral;
};
