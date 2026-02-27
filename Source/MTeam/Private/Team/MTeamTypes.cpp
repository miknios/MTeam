// Copyright (c) Miknios. All rights reserved.


#include "Team/MTeamTypes.h"

#include "GenericTeamAgentInterface.h"
#include "Team/MTeamLibrary.h"

uint8 FMTeamAffiliationFilter::GetAsFlags() const
{
	return IntCastChecked<uint8>(
		(bHostile << ETeamAttitude::Hostile)
		| (bNeutral << ETeamAttitude::Neutral)
		| (bFriendly << ETeamAttitude::Friendly));
}

bool FMTeamAffiliationFilter::Evaluate(const FGenericTeamId A, const FGenericTeamId B) const
{
	static constexpr uint8 AllFlags =
		(1 << ETeamAttitude::Hostile)
		| (1 << ETeamAttitude::Neutral)
		| (1 << ETeamAttitude::Friendly);

	const uint8 AffiliationFlags = GetAsFlags();

	return (AffiliationFlags == AllFlags) || ((1 << UMTeamLibrary::GetAttitude(A, B)) & AffiliationFlags) != 0;
}


