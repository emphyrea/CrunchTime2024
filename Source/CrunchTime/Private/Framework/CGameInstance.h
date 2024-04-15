// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "CGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UCGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	void Login();
protected:
	virtual void Init() override;

    class	IOnlineSubsystem* OnlineSubsystem;
	IOnlineIdentityPtr IdentityPtr;
	void LoginCompleted(int  PlayerNumber, bool bWasSuccessful, const FUniqueNetId& UserId, const FString&  Error);
};
