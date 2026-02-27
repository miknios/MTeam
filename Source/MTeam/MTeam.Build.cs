// Copyright (c) Miknios. All rights reserved.

using UnrealBuildTool;

public class MTeam : ModuleRules
{
	public MTeam(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", 
				"AIModule",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"DeveloperSettings"
			}
		);
	}
}

