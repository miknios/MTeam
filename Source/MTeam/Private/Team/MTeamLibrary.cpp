// Copyright (c) Miknios. All rights reserved.


#include "Team/MTeamLibrary.h"

#include "Team/MTeamComponent.h"
#include "Team/MTeamDefinition.h"
#include "Team/MTeamSettings.h"
#include "Team/MTeamTypes.h"

void UMTeamLibrary::RegisterAttitudeSolver()
{
	FGenericTeamId::SetAttitudeSolver(&GetAttitude);
}

FGenericTeamId UMTeamLibrary::GetTeamIdForDefinition(const FMTeamDefinition& TeamDefinition)
{
	return GetTeamIdForTeamName(TeamDefinition.TeamName);
}

FGenericTeamId UMTeamLibrary::GetTeamIdForTeamName(const FName TeamName)
{
	UMTeamSettings* TeamSettings = UMTeamSettings::Get();
	if (TeamSettings == nullptr)
	{
		return FGenericTeamId::NoTeam;
	}

	for (int i = 0; i < TeamSettings->Teams.Num(); ++i)
	{
		if (TeamSettings->Teams[i].TeamName == TeamName)
		{
			return i;
		}
	}

	return FGenericTeamId::NoTeam;
}

TOptional<FMTeamDefinition> UMTeamLibrary::GetTeamDefinitionForTeamId(const FGenericTeamId TeamId)
{
	UMTeamSettings* TeamSettings = UMTeamSettings::Get();
	if (TeamSettings == nullptr)
	{
		return NullOpt;
	}

	const bool bValidId = TeamSettings->Teams.IsValidIndex(TeamId.GetId());
	if (!bValidId)
	{
		return NullOpt;
	}

	return TeamSettings->Teams[TeamId.GetId()];
}

TArray<FName> UMTeamLibrary::GetTeamNamesAll()
{
	TArray<FName> Result;

	UMTeamSettings* TeamSettings = UMTeamSettings::Get();
	if (TeamSettings != nullptr)
	{
		for (const FMTeamDefinition& Team : TeamSettings->Teams)
		{
			Result.Emplace(Team.TeamName);
		}
	}

	return Result;
}

FGenericTeamId UMTeamLibrary::GetTeamIdForActor(const AActor* Actor)
{
	const IGenericTeamAgentInterface* TeamAgent = GetTeamAgentInterfaceForActor(Actor);
	if (TeamAgent == nullptr)
	{
		return FGenericTeamId::NoTeam;
	}

	return TeamAgent->GetGenericTeamId();
}

UMTeamComponent* UMTeamLibrary::GetTeamComponentForActor(const AActor* Actor)
{
	if (!IsValid(Actor))
	{
		return nullptr;
	}

	if (const APawn* Pawn = Cast<APawn>(Actor))
	{
		if (IsValid(Pawn->Controller))
		{
			const AController* Controller = Pawn->Controller;
			UMTeamComponent* TeamComponent = Controller->FindComponentByClass<UMTeamComponent>();
			if (IsValid(TeamComponent))
			{
				return TeamComponent;
			}
		}
	}

	UMTeamComponent* TeamComponent = Actor->FindComponentByClass<UMTeamComponent>();
	return TeamComponent;
}

ETeamAttitude::Type UMTeamLibrary::GetAttitude(const FGenericTeamId A, const FGenericTeamId B)
{
	if (A.GetId() == B.GetId())
	{
		return ETeamAttitude::Friendly;
	}

	UMTeamSettings* TeamSettings = UMTeamSettings::Get();

	const TOptional<FMTeamDefinition> TeamA = GetTeamDefinitionForTeamId(A);
	if (!TeamA.IsSet())
	{
		return ETeamAttitude::Neutral;
	}

	const TOptional<FMTeamDefinition> TeamB = GetTeamDefinitionForTeamId(B);
	if (!TeamB.IsSet())
	{
		return ETeamAttitude::Neutral;
	}

	const FMTeamAttitudeOverride* AttitudeOverrideFound = TeamSettings->AttitudeOverrides.FindByPredicate(
		[&TeamA, &TeamB](const FMTeamAttitudeOverride& AttitudeOverride)
		{
			return AttitudeOverride.TeamA == TeamA->TeamName && AttitudeOverride.TeamB == TeamB->TeamName
				|| AttitudeOverride.TeamA == TeamB->TeamName && AttitudeOverride.TeamB == TeamA->TeamName;
		});

	if (AttitudeOverrideFound == nullptr)
	{
		return ETeamAttitude::Neutral;
	}

	return AttitudeOverrideFound->Attitude;
}

bool UMTeamLibrary::EvaluateAffiliationFilterForActors(const FMTeamAffiliationFilter& AffiliationFilter, const AActor* ActorA,
                                                       const AActor* ActorB)
{
	const FGenericTeamId TeamA = GetTeamIdForActor(ActorA);
	const FGenericTeamId TeamB = GetTeamIdForActor(ActorB);

	return AffiliationFilter.Evaluate(TeamA, TeamB);
}

bool UMTeamLibrary::EvaluateAffiliationFilterForTeamComponents(const FMTeamAffiliationFilter& AffiliationFilter,
                                                               const UMTeamComponent* TeamComponentA, const UMTeamComponent* TeamComponentB)
{
	const FGenericTeamId TeamA = IsValid(TeamComponentA) ? TeamComponentA->GetGenericTeamId() : FGenericTeamId::NoTeam;
	const FGenericTeamId TeamB = IsValid(TeamComponentB) ? TeamComponentB->GetGenericTeamId() : FGenericTeamId::NoTeam;

	return AffiliationFilter.Evaluate(TeamA, TeamB);
}

IGenericTeamAgentInterface* UMTeamLibrary::GetTeamAgentInterfaceForActor(const AActor* Actor)
{
	return GetTeamComponentForActor(Actor);
}


