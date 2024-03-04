// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_GetNextPatrolPoint.h"
#include "AIController.h"
#include "AI/PatrollingComponent.h"
#include "GameFramework/Character.h"
#include "Engine/TargetPoint.h""

EBTNodeResult::Type UBTTask_GetNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIC = OwnerComp.GetAIOwner();
	ACharacter* Pawn = AIC->GetCharacter();
	UPatrollingComponent* PatrollingComp = Pawn->GetComponentByClass<UPatrollingComponent>();
	if (PatrollingComp)
	{
		const ATargetPoint* NextPatrolPoint = PatrollingComp->GetNextPatrolPoint();
		if (NextPatrolPoint)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, NextPatrolPoint->GetActorComponent());
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
