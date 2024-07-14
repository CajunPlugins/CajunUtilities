// Copyright 2024 TyGames, Inc. All Rights Reserved.

#pragma once

namespace MapUtils {
	template<typename K,typename V = FString>
	static TMap<V, K> ReverseMap(TMap<K, V> Map)
	{
		TMap<V, K> NewMap = {};
		TArray<K> Keys;
		TArray<V> Values;
		Map.GenerateKeyArray(Keys);
		Map.GenerateValueArray(Values);
		for (int32 i = 0; i < Values.Num(); i++)
		{
			NewMap.Add(Values[i], Keys[i]);
		}
		return NewMap;
	}
	
	template<typename K, typename V = FName>
	static K FindKey(TMap<K, V> Map, V Value, K Default = K())
	{
		TArray<K> Keys;
		TArray<V> Values;
		Map.GenerateKeyArray(Keys);
		Map.GenerateValueArray(Values);
		int32 Index = 0;
		return Values.Find(Value, Index) ? Keys[Index] : Default; 
	}

	template<typename K>
	static K FindKey(TMap<K, FText> Map, const FText Value, K Default = K())
	{
		TArray<K> Keys;
		TArray<FText> Values;
		Map.GenerateKeyArray(Keys);
		Map.GenerateValueArray(Values);
		int32 Index = 0;
		for (int i = 0; i < Values.Num(); i++)
		{
			if (Values[i].EqualTo(Value))
			{
				return Keys[i];
			}
		}
		return Default;
	}
	
	template<typename K, typename V = FName>
	static V GetValue(TMap<K, V> Map, K Key, V Default = V())
	{
		return Map.Contains(Key) ? Map[Key] : Default;
	}

	template<typename K, typename V = FName>
	static TArray<V> GetValueArray(const TMap<K, V>& Map)
	{
		TArray<V> Result;
		Map.GenerateValueArray(Result);
		return Result;
	}

	template<typename K, typename V = FName>
	static TArray<K> GetKeyArray(const TMap<K, V>& Map)
	{
		TArray<V> Result;
		Map.GenerateKeyArray(Result);
		return Result;
	}

	template<typename K, typename V = FName>
	static TArray<TTuple<K, V>> GetTupleArray(const TMap<K, V>& Map)
	{
		TArray<K> Keys;
		Map.GenerateKeyArray(Keys);
		TArray<V> Values;
		Map.GenerateValueArray(Values);
		TArray<TTuple<K, V>> Result;
		for (int32 i = 0; i < Map.Num(); i++)
		{
			Result.Emplace(TTuple<K, V>(Keys[i], Values[i]));
		}
		return Result;
	}
};
