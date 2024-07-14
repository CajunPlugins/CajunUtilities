// Copyright 2024 Cajun Pro LLC. All Rights Reserved.

using UnrealBuildTool;

public class CajunUtilities : ModuleRules
{
	public CajunUtilities(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new [] { 
			"Core",
			"Json",
			"JsonUtilities",
			"HTTP"
		});
		PrivateDependencyModuleNames.AddRange(new []
		{
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore"
		});
	}
}
