// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/GameplayUI.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

#include "GameplayAbilities/CAttributeSet.h"
#include "Widgets/StatusGuage.h"

void UGameplayUI::NativeConstruct()
{
	Super::NativeConstruct();

	UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningPlayerPawn());
	if (OwnerASC)
	{
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UCAttributeSet::GetHealthAttribute()).AddUObject(this, &UGameplayUI::HealthUpdated);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UCAttributeSet::GetMaxHealthAttribute()).AddUObject(this, &UGameplayUI::MaxHealthUpdated);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UCAttributeSet::GetManaAttribute()).AddUObject(this, &UGameplayUI::ManaUpdated);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UCAttributeSet::GetMaxManaAttribute()).AddUObject(this, &UGameplayUI::MaxManaUpdated);
	}

	OwnerAbilitySystemComponent = OwnerASC;
}

void UGameplayUI::HealthUpdated(const FOnAttributeChangeData& ChangeData)
{
	StatusGuage->SetHealth(ChangeData.NewValue, GetAttributeValue(UCAttributeSet::GetMaxHealthAttribute()));
}

void UGameplayUI::MaxHealthUpdated(const FOnAttributeChangeData& ChangeData)
{
	StatusGuage->SetHealth(GetAttributeValue(UCAttributeSet::GetHealthAttribute()), ChangeData.NewValue);
}

void UGameplayUI::ManaUpdated(const FOnAttributeChangeData& ChangeData)
{
	StatusGuage->SetMana(ChangeData.NewValue, GetAttributeValue(UCAttributeSet::GetMaxManaAttribute()));
}

void UGameplayUI::MaxManaUpdated(const FOnAttributeChangeData& ChangeData)
{
	StatusGuage->SetMana(GetAttributeValue(UCAttributeSet::GetManaAttribute()), ChangeData.NewValue);
}


float UGameplayUI::GetAttributeValue(const FGameplayAttribute& Attribute) const
{
	if (OwnerAbilitySystemComponent)
	{
		bool Found = false;
		float value = OwnerAbilitySystemComponent->GetGameplayAttributeValue(Attribute, Found);
		if (Found)
		{
			return value;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("%s Can't find attribute: %s "), *GetName(), *Attribute.AttributeName);

	return -1;
}
