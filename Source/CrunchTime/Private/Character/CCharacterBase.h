// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AbilitySystemInterface.h"

#include "GameFramework/Character.h"
#include "GameplayEffectTypes.h"
#include "GameplayAbilities/CGameplayCueInterface.h"
#include "GenericTeamAgentInterface.h"

#include "CCharacterBase.generated.h"

class UCAbilitySystemComponent;
class UCAttributeSet;
class UGameplayEffect;

UCLASS()
class ACCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICGameplayCueInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACCharacterBase();
	void SetupAbilitySystemComponent();
	void InitAttributes();
	void InitAbilities();
	virtual FGenericTeamId GetGenericTeamId() const override { return TeamId;  }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//called on the server only, when posses by a controller.
	virtual void PossessedBy(AController* NewController) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	class UTargetingBoxComponent* TargetingBoxComponent;

	void PlayMontage(UAnimMontage* MontageToPlay);

	/*************************************************************/
	/*                              Gameplay Ability                                  */
	/*************************************************************/
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	void InitStatusHUD();
private:
	UPROPERTY(VisibleAnywhere, Category = "Gameplay Ability")
	UCAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UCAttributeSet* AttributeSet;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	class UWidgetComponent* StatusWidgetComp;

	UPROPERTY()
	class UStatusGuage* StatusGuage;

	void HealthUpdated(const FOnAttributeChangeData& ChangeData);
	void MaxHealthUpdated(const FOnAttributeChangeData& ChangeData);

	/*************************************************************/
	/*                              Gameplay Cue                                   */
	/*************************************************************/
public:
	virtual void PlayHitReaction() override;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Cue")
	UAnimMontage* HitReactionMontage;

	/*************************************************************/
	/*                                      Death                                      */
	/*************************************************************/
private:
	void StartDeath();
	
	void DeathTagChanged(const FGameplayTag TagChanged, int32 NewStackCount);

	UPROPERTY(EditDefaultsOnly, Category = "Death")
	UAnimMontage* DeathMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	TSubclassOf<UGameplayEffect> DeathEffect;
	
	/*************************************************************/
	/*                                          AI                                           */
	/*************************************************************/
	UPROPERTY(Replicated)
	FGenericTeamId TeamId;

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;

	UPROPERTY(VisibleDefaultsOnly, Category = "AI")
	class UAIPerceptionStimuliSourceComponent* AIPerceptionSourceComp;
};
