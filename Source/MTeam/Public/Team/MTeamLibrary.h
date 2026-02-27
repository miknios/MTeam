// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "MTeamTypes.h"

#include "MTeamLibrary.generated.h"

class UMTeamComponent;
struct FMTeamAffiliationFilter;
struct FMTeamDefinition;

UCLASS()
class MTEAM_API UMTeamLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Must be called somewhere in your game module, so AI uses a custom attitude solver in its logic 
	static void RegisterAttitudeSolver();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MTeam|Team")
	static FGenericTeamId GetTeamIdForDefinition(const FMTeamDefinition& TeamDefinition);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MTeam|Team")
	static FGenericTeamId GetTeamIdForTeamName(const FName TeamName);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MTeam|Team")
	static TOptional<FMTeamDefinition> GetTeamDefinitionForTeamId(const FGenericTeamId TeamId);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MTeam|Team")
	static TArray<FName> GetTeamNamesAll();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MTeam|Team")
	static FGenericTeamId GetTeamIdForActor(const AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MTeam|Team")
	static UMTeamComponent* GetTeamComponentForActor(const AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MTeam|Team")
	static ETeamAttitude::Type GetAttitude(const FGenericTeamId A, const FGenericTeamId B);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MTeam|Team")
	static bool EvaluateAffiliationFilterForActors(const FMTeamAffiliationFilter& AffiliationFilter,
	                                               const AActor* ActorA, const AActor* ActorB);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MTeam|Team")
	static bool EvaluateAffiliationFilterForTeamComponents(const FMTeamAffiliationFilter& AffiliationFilter,
	                                                       const UMTeamComponent* TeamComponentA, const UMTeamComponent* TeamComponentB);

	static IGenericTeamAgentInterface* GetTeamAgentInterfaceForActor(const AActor* Actor);
};


