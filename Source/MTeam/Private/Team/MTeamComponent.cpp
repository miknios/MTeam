// Copyright (c) Miknios. All rights reserved.


#include "Team/MTeamComponent.h"

#include "Team/MTeamDefinition.h"
#include "Team/MTeamLibrary.h"

FGenericTeamId UMTeamComponent::GetGenericTeamId() const
{
	if (TeamDefinitionAsset == nullptr)
	{
		return FGenericTeamId::NoTeam;
	}

	return TeamDefinitionAsset->TeamId;
}

// TODO: find FMTeamDefinitionAsset matching the TeamID
void UMTeamComponent::SetGenericTeamId(const FGenericTeamId& TeamID)
{
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

void UMTeamComponent::SetTeam(const UMTeamDefinitionAsset* InTeamDefinitionAsset)
{
	TeamDefinitionAsset = const_cast<UMTeamDefinitionAsset*>(InTeamDefinitionAsset);
}

UMTeamDefinitionAsset* UMTeamComponent::GetAssignedTeam() const
{
	return TeamDefinitionAsset;
}
