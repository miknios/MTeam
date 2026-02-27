// Copyright (c) Miknios. All rights reserved.


#include "Team/MTeamComponent.h"

#include "Team/MTeamDefinition.h"
#include "Team/MTeamLibrary.h"

FGenericTeamId UMTeamComponent::GetGenericTeamId() const
{
	return UMTeamLibrary::GetTeamIdForTeamName(AssignedTeamName);
}

void UMTeamComponent::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	TOptional<FMTeamDefinition> TeamDefinition = UMTeamLibrary::GetTeamDefinitionForTeamId(TeamID);
	if (!TeamDefinition.IsSet())
	{
		return;
	}

	AssignedTeamName = TeamDefinition->TeamName;
}

ETeamAttitude::Type UMTeamComponent::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* OtherAgent = UMTeamLibrary::GetTeamAgentInterfaceForActor(&Other);
	if (OtherAgent == nullptr)
	{
		return ETeamAttitude::Neutral;
	}
	
	return UMTeamLibrary::GetAttitude(GetGenericTeamId(), OtherAgent->GetGenericTeamId());
}

void UMTeamComponent::SetTeam(const FName InTeamName)
{
	AssignedTeamName = InTeamName;
}

FName UMTeamComponent::GetAssignedTeam() const
{
	return AssignedTeamName;
}


