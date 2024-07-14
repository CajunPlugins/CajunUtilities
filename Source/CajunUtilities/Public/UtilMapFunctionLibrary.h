// Copyright 2023 Rise Of A Legend.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "UtilMapFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CAJUNUTILITIES_API UUtilMapFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** 
	 * Finds the key associated with the provided Value
	 *
	 * @param	Map		The map to perform the lookup on
	 * @param	Key		The key associated with the value, default constructed if value was not found
	 * @param	Value	The value that will be used to look the key up, 
	 * @return	True if a key was found (False indicates nothing in the map has the provided value)
	 */
	UFUNCTION(BlueprintPure, CustomThunk, Category="Utilities|Map", meta=(DisplayName="Find Key", CompactNodeTitle="FIND KEY", MapParam="Map", MapKeyParam="Key", MapValueParam="Value", AutoCreateRefTerm = "Key, Value", BlueprintThreadSafe))
	static bool Map_FindKey(const TMap<int32, int32>& Map, const int32& Value, int32& Key) ;

	DECLARE_FUNCTION(execMap_FindKey)
	{
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FMapProperty>(nullptr);
		void*         MapAddr = Stack.MostRecentPropertyAddress;
		FMapProperty* MapProperty = CastField<FMapProperty>(Stack.MostRecentProperty);
		if (!MapProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		// Since Key and Value aren't really an int, step the stack manually
		const FProperty* CurrKeyProp = MapProperty->KeyProp;
		const int32      KeyPropertySize = CurrKeyProp->ElementSize * CurrKeyProp->ArrayDim;
		void*            KeyStorageSpace = FMemory_Alloca(KeyPropertySize);
		CurrKeyProp->InitializeValue(KeyStorageSpace);

		Stack.MostRecentPropertyAddress = nullptr;
		Stack.MostRecentPropertyContainer = nullptr;
		Stack.StepCompiledIn<FProperty>(KeyStorageSpace);

		const FProperty* CurrValueProp = MapProperty->ValueProp;
		const int32      ValuePropertySize = CurrValueProp->ElementSize * CurrValueProp->ArrayDim;
		void*            ValueStorageSpace = FMemory_Alloca(ValuePropertySize);
		CurrValueProp->InitializeValue(ValueStorageSpace);

		Stack.MostRecentPropertyAddress = nullptr;
		Stack.MostRecentPropertyContainer = nullptr;
		Stack.StepCompiledIn<FProperty>(ValueStorageSpace);
		const FFieldClass* CurrValuePropClass = CurrValueProp->GetClass();
		const FFieldClass* MostRecentPropClass = Stack.MostRecentProperty->GetClass();
		void*              ItemPtr;
		// If the destination and the inner type are identical in size and their field classes derive from one another, then permit the writing out of the array element to the destination memory
		if (Stack.MostRecentPropertyAddress != nullptr && (ValuePropertySize == Stack.MostRecentProperty->ElementSize * Stack.MostRecentProperty->ArrayDim) &&
			(MostRecentPropClass->IsChildOf(CurrValuePropClass) || CurrValuePropClass->IsChildOf(MostRecentPropClass)))
		{
			ItemPtr = Stack.MostRecentPropertyAddress;
		}
		else
		{
			ItemPtr = ValueStorageSpace;
		}

		P_FINISH;
		P_NATIVE_BEGIN;
			*static_cast<bool*>(RESULT_PARAM) = GenericMap_FindKey(MapAddr, MapProperty, KeyStorageSpace, ItemPtr);
		P_NATIVE_END;

		CurrValueProp->DestroyValue(ValueStorageSpace);
		CurrKeyProp->DestroyValue(KeyStorageSpace);
	}
	
	static bool GenericMap_FindKey(const void* Map, const FMapProperty* Property, void* Key, const void* Value) {
		if (Map)
		{
			FScriptMapHelper Helper(Property, Map);
			int32            Size = Helper.Num();
			uint8*           FoundKey = nullptr;
			for (int32 i = 0; Size; ++i)
			{
				if (Helper.IsValidIndex(i))
				{
					if (Value == Helper.GetValuePtr(i))
					{
						FoundKey = Helper.GetKeyPtr(i);
						break;
					}
				}
			}
			if (FoundKey)
			{
				Property->KeyProp->CopyCompleteValueFromScriptVM(Key, FoundKey);
			}
			else
			{
				Property->KeyProp->InitializeValue(Key);
			}
			return FoundKey != nullptr;
		}
		return false;
	}
};
