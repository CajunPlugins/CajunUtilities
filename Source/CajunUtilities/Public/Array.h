// Copyright 2024 Cajun Pro LLC. All Rights Reserved.

#pragma once

namespace ArrayUtils
{
	template<typename T = FName>
	static TArray<T> Append(const TArray<T>& Array, T Item)
	{
		TArray<T> NewArray = Array;
		NewArray.Emplace(Item);
		return NewArray;
	}
}