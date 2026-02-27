// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"

#include "MTeamTypes.generated.h"

USTRUCT(BlueprintType)
struct MTEAM_API FMTeamAffiliationFilter
{
	GENERATED_BODY()

	FMTeamAffiliationFilter() = default;

	FMTeamAffiliationFilter(const bool bInDetectEnemies, const bool bInDetectNeutrals, const bool bInDetectFriendlies)
		: bFriendly(bInDetectFriendlies),
		  bHostile(bInDetectEnemies),
		  bNeutral(bInDetectNeutrals)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense")
	uint32 bFriendly : 1 = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense")
	uint32 bHostile : 1 = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense")
	uint32 bNeutral : 1 = true;

	uint8 GetAsFlags() const;
	bool Evaluate(FGenericTeamId A, FGenericTeamId B) const;
};


