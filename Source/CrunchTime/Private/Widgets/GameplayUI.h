// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayEffectTypes.h"
#include "GameplayUI.generated.h"

/**
 * 
 */
UCLASS()
class UGameplayUI : public UUserWidget
{
	GENERATED_BODY()
public:
	//this is the begin play or start
	virtual void NativeConstruct() override;
private:
	UPROPERTY(meta=(BindWidget))
	class UStatusGuage* StatusGuage;
	
	UPROPERTY(meta=(BindWidget))
	class UHorizontalBox* AbilityHBox;
	
	UPROPERTY(meta=(BindWidget))
	class UAttributeGuage* StrengthGuage;

	UPROPERTY(meta=(BindWidget))
	class UAttributeGuage* IntellegenceGuage;

	UPROPERTY(meta=(BindWidget))
	class UAttributeGuage* AttackDamageGuage;

	UPROPERTY(meta=(BindWidget))
	class UAttributeGuage* ArmorGuage;

	class UGameplayUI* GameplayUI;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TSubclassOf<class UAbilityGuage> AbilityGuageClass;

	void HealthUpdated(const FOnAttributeChangeData& ChangeData);
	void MaxHealthUpdated(const FOnAttributeChangeData& ChangeData);

	void ManaUpdated(const FOnAttributeChangeData& ChangeData);
	void MaxManaUpdated(const FOnAttributeChangeData& ChangeData);

	float GetAttributeValue(const FGameplayAttribute& Attribute) const;

	UPROPERTY()
	const class UAbilitySystemComponent* OwnerAbilitySystemComponent;
};
