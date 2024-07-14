// Copyright 2024 Cajun Pro LLC. All Rights Reserved.

#pragma once

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"



#define HTTP_RESPONSE_PARAMS const FHttpRequestPtr& Request, const FHttpResponsePtr& Response, const bool bWasSuccessful

#define HTTP_REQUEST(VarName) const TSharedRef<IHttpRequest> VarName = FHttpModule::Get().CreateRequest();
