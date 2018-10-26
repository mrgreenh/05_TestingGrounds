// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Classes/AIController.h"
#include "PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	AAIController* AIController = OwnerComp.GetAIOwner();
	auto Pawn = AIController->GetPawn();
	auto PatrolRoute = Cast<APatrollingGuard>(Pawn)->PatrolRoute;
	auto NextPoint = PatrolRoute[Index];

	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, NextPoint);

	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, (Index + 1) % PatrolRoute.Num());

	return EBTNodeResult::Succeeded;
}