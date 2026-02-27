// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Components/ActorComponent.h"
#include "MTeamComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MTEAM_API UMTeamComponent : public UActorComponent, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// IGenericTeamAgentInterface
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	// ~ IGenericTeamAgentInterface
	
	UFUNCTION(BlueprintCallable, Category = "Team")
	void SetTeam(const FName InTeamName);
	
	UFUNCTION(BlueprintCallable, Category = "Team")
	FName GetAssignedTeam() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team", meta = (GetOptions = "MTeam.MTeamLibrary.GetTeamNamesAll"))
	FName AssignedTeamName;
};


