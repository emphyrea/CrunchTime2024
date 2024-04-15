// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/CGameInstance.h"
#include "OnlineSubsystem.h"

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

void UCGameInstance::Init()
{
	Super::Init();
	OnlineSubsystem = IOnlineSubsystem::Get();
	IdentityPtr = OnlineSubsystem->GetIdentityInterface();
	IdentityPtr->OnLoginCompleteDelegates->AddUObject(this, &UCGameInstance::LoginCompleted);
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
