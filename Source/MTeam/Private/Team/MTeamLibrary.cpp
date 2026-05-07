// Copyright (c) Miknios. All rights reserved.


#include "Team/MTeamLibrary.h"

#include "MDeveloperSettingsUtils.h"
#include "Team/MTeamComponent.h"
#include "Team/MTeamDefinition.h"
#include "Team/MTeamSettings.h"
#include "Team/MTeamTypes.h"

void UMTeamLibrary::RegisterAttitudeSolver()
{
	FGenericTeamId::SetAttitudeSolver(&GetAttitude);
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

	const UMTeamSettings* TeamSettings = M::DeveloperSettings::GetSettings<UMTeamSettings>();
	if (TeamSettings == nullptr)
	{
		return ETeamAttitude::Neutral;
	}

	const FMTeamAttitudeOverride* AttitudeOverrideFound = TeamSettings->AttitudeOverrides.FindByPredicate(
		[&A, &B](const FMTeamAttitudeOverride& AttitudeOverride)
		{
			if (AttitudeOverride.TeamADef == nullptr || AttitudeOverride.TeamBDef == nullptr)
			{
				return false;
			}

			return AttitudeOverride.TeamADef->TeamId == A && AttitudeOverride.TeamBDef->TeamId == B
				|| AttitudeOverride.TeamADef->TeamId == B && AttitudeOverride.TeamBDef->TeamId == A;
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
