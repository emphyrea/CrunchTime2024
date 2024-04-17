// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/CGameInstance.h"
#include "OnlineSubsystem.h"
#include "Online/OnlineSessionNames.h"
#include "OnlineSessionSettings.h"

void UCGameInstance::Login()
{
	UE_LOG(LogTemp, Warning, TEXT("Trying to Login"));
	if (IdentityPtr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Logining in"));
		FOnlineAccountCredentials Credientials;
		Credientials.Type = "accountportal";
		Credientials.Id = "";
		Credientials.Token = "";
		IdentityPtr->Login(0, Credientials);
	}
}

void UCGameInstance::CreateSession(const FName& SessionName)
{
	if (SessionPtr)
	{
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsDedicated = false;
		SessionSettings.bIsLANMatch = false;
		SessionSettings.bAllowInvites = true;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bAllowJoinInProgress = true;
		SessionSettings.bAllowJoinViaPresence = true;
		SessionSettings.bUseLobbiesIfAvailable = true;
		SessionSettings.bUsesPresence = true;
		SessionSettings.NumPublicConnections = 10;

		SessionSettings.Set(GetSessionNameKey(), SessionName.ToString(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		SessionPtr->CreateSession(0, SessionName, SessionSettings);
	}
}

void UCGameInstance::FindSessions()
{
	OnlineSessionSearch = TSharedPtr<FOnlineSessionSearch>(new FOnlineSessionSearch);
	OnlineSessionSearch->bIsLanQuery = false;
	OnlineSessionSearch->MaxSearchResults = 10;
	OnlineSessionSearch->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);
	SessionPtr->FindSessions(0, OnlineSessionSearch.ToSharedRef());
}

void UCGameInstance::Init()
{
	Super::Init();
	OnlineSubsystem = IOnlineSubsystem::Get();
	IdentityPtr = OnlineSubsystem->GetIdentityInterface();
	IdentityPtr->OnLoginCompleteDelegates->AddUObject(this, &UCGameInstance::LoginCompleted);
	
	SessionPtr = OnlineSubsystem->GetSessionInterface();
	SessionPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &UCGameInstance::CreateSessionCompleted);
	SessionPtr->OnFindSessionsCompleteDelegates.AddUObject(this, &UCGameInstance::FindSessionCompleted);
}

void UCGameInstance::LoginCompleted(int PlayerNumber, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Logged in"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Logged in failed"));
	}
}

void UCGameInstance::CreateSessionCompleted(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Session %s Created"), *SessionName.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to Create Session: %s"), *SessionName.ToString());
	}
}

void UCGameInstance::FindSessionCompleted(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		for (const FOnlineSessionSearchResult& SearchResult : OnlineSessionSearch->SearchResults)
		{
			FString SessionName = "";
			SearchResult.Session.SessionSettings.Get(GetSessionNameKey(), SessionName);
			UE_LOG(LogTemp, Warning, TEXT("Session: %s with id: %s found"), *SessionName, *SearchResult.GetSessionIdStr());
		}
	}
}
