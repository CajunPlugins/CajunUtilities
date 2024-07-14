// Copyright 2024 Cajun Pro LLC. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "DateTimeFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CAJUNUTILITIES_API UDateTimeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Utilities|Operators", meta=(CompactNodeTitle="+YRS", BlueprintThreadSafe))
	static FDateTime AddYears(const FDateTime& In, const int32 Years) { return In + FTimespan::FromDays(Years * 365); }

	UFUNCTION(BlueprintPure, Category="Utilities|Operators", meta=(CompactNodeTitle="+DAYS", BlueprintThreadSafe))
	static FDateTime AddDays(const FDateTime& In, const int32 Days) { return In + FTimespan::FromDays(Days); }

	UFUNCTION(BlueprintPure, Category="Utilities|Operators", meta=(CompactNodeTitle="+HRS", BlueprintThreadSafe))
	static FDateTime AddHours(const FDateTime& In, const int32 Hours) { return In + FTimespan::FromHours(Hours); }

	UFUNCTION(BlueprintPure, Category="Utilities|Operators", meta=(CompactNodeTitle="+MINS", BlueprintThreadSafe))
	static FDateTime AddMinutes(const FDateTime& In, const int32 Minutes) { return In + FTimespan::FromMinutes(Minutes); }

	UFUNCTION(BlueprintPure, Category="Utilities|Operators", meta=(CompactNodeTitle="+SECS", BlueprintThreadSafe))
	static FDateTime AddSeconds(const FDateTime& In, const int32 Seconds) { return In + FTimespan::FromSeconds(Seconds); }

	UFUNCTION(BlueprintPure, Category="Utilities|Operators", meta=(BlueprintThreadSafe))
	static FTimespan GetTimeLeftInDay(const FDateTime& In) { return FTimespan::FromDays(1) - In.GetTimeOfDay(); }

	UFUNCTION(BlueprintPure, Category="Utilities|Constants", meta=(BlueprintThreadSafe))
	static FTimespan GetTimeLeftToday(const bool bUtc = true) { return GetTimeLeftInDay(bUtc ? FDateTime::UtcNow() : FDateTime::Now()); }
};