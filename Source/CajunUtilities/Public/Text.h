// Copyright 2024 Cajun Pro LLC. All Rights Reserved.

#pragma once

#define LOCTEXT2(String) LOCTEXT(String, String)

#define LOCTEXT_NAMESPACE "CajunUtilities"

namespace TextUtils
{
	static const FText Unknown = LOCTEXT2("Unknown");
	static const FText None = LOCTEXT2("None");
	static const FText Invalid = LOCTEXT2("Invalid");

	static TArray<FString> ToStringArray(const TArray<FText>& Array)
	{
		TArray<FString> Out;
		for (int i = 0; i < Array.Num(); i++)
		{
			Out.Emplace(Array[i].ToString());
		}
		return Out;
	}
	
}

#undef LOCTEXT_NAMESPACE