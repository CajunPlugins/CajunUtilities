// Copyright 2024 Cajun Pro LLC. All Rights Reserved.

#pragma once

#include "Dom/JsonObject.h"
#include "JsonObjectWrapper.h"

#define NEW_JSON_OBJECT(Name) const TSharedPtr<FJsonObject> Name = MakeShareable(new FJsonObject);

namespace JsonUtils
{
	static FString JsonObjectToString(const TSharedPtr<FJsonObject>& JsonObject)
	{
		FString                                                                Out;
		const TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Out);
		FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
		return Out;
	}

	static TSharedPtr<FJsonObject> StringToJsonObject(const FString& JsonString)
	{
		TSharedPtr<FJsonObject>         JsonObject = MakeShareable(new FJsonObject);
		const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
		if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
			return JsonObject;
		return TSharedPtr<FJsonObject>();
	}

	static FJsonObjectWrapper JsonObjectToWrapper(const TSharedPtr<FJsonObject>& JsonObject)
	{
		FJsonObjectWrapper Wrapper;
		Wrapper.JsonObject = JsonObject;
		Wrapper.JsonString = JsonObjectToString(Wrapper.JsonObject);
		return Wrapper;
	}

	static float GetSafeValue(const TSharedPtr<FJsonObject>& JsonObject, const FString& Key, const float Default)
	{
		return JsonObject->HasTypedField<EJson::Number>(Key) ? JsonObject->GetNumberField(Key) : Default;
	}

	static FString GetSafeValue(const TSharedPtr<FJsonObject>& JsonObject, const FString& Key, const FString& Default)
	{
		return JsonObject->HasTypedField<EJson::String>(Key) ? JsonObject->GetStringField(Key) : Default;
	}

	//static const TCHAR* GetJsonValueString(const TSharedPtr<FJsonValue>& JsonValue)
	//{
	//	if (JsonValue.IsValid())
	//	{
	//		if (JsonValue->Type == EJson::Object)
	//		{
	//			return *JsonObjectToString(JsonValue->AsObject());
	//		}
	//		// TODO::Implement other types
	//		return TEXT("Unimplemented type in jsonutils");
	//	}
	//	return TEXT("");
	//}
}

