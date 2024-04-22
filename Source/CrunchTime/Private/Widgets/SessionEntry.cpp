// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SessionEntry.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
void USessionEntry::NativeConstruct()
{
	Super::NativeConstruct();
	SessionBtn->OnClicked.AddDynamic(this, &USessionEntry::SessionBtnClicked);
}

void USessionEntry::SetSessionInfo(const FString& SessionName, int index)
{
	SessionIndex = index;
	SessionNameText->SetText(FText::FromString(SessionName));
}

void USessionEntry::SessionBtnClicked()
{
	OnSessionBtnClicked.Broadcast(SessionIndex);
}
