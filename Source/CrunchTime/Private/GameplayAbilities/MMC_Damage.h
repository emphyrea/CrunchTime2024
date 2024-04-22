// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_Damage.generated.h"

/**
 * 
 */
UCLASS()
class UMMC_Damage : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_Damage();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition AttackDamageCaptureDef;
	FGameplayEffectAttributeCaptureDefinition ArmorCaptureDef;
};
