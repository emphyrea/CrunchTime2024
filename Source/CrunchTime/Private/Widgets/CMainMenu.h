// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSessionSettings.h"
#include "CMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class UCMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
private:
	UPROPERTY(meta = (BindWidget))
	class UButton* LoginBtn;

	UPROPERTY(meta = (BindWidget))
	class UEditableText* SessionNameText;

	UPROPERTY(meta = (BindWidget))
	class UButton* CreateSessionBtn;
	
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* SessionEntryList;

	UPROPERTY(meta = (BindWidget))
	class UButton* FindSessionBtn;

	UFUNCTION()
	void SessionNameTextChanged(const FText& NewText);
	UFUNCTION()
	void LoginBtnClicked();

	UFUNCTION()
	void CreateSessionBtnClicked();

	UFUNCTION()
	void FindSessionBtnClicked();

	UPROPERTY(EditDefaultsOnly, Category = "Session")
	TSubclassOf<class USessionEntry> SessionEntryClass;
	
	void LoadSessionWithIndex(int Index);

	void SessionSearchCompleted(const TArray<FOnlineSessionSearchResult>& SearchResults);

	class UCGameInstance* CGameInst;
};
