// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityGuage.generated.h"

struct FGameplayAbilitySpec;
class UGA_AbilityBase;
/**
 * 
 */
UCLASS()
class UAbilityGuage : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetupOwingAbilityCDO(const UGA_AbilityBase* OwningAbilityCDO);
private:
	UPROPERTY(meta = (BindWidget))
	class UImage* IconImage;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CooldownDurationText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ManaCostText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CooldownCounterText;

	UPROPERTY(EditDefaultsOnly, Category = "Cooldown")
	FName CooldownPercentMaterialParamName = "Percent";
	
	UPROPERTY(EditDefaultsOnly, Category = "Icon")
	FName IconTextureMaterialParamName = "Icon";

	const class UGA_AbilityBase* AbilityCDO;
};