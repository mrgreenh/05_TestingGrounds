// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Classes/AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	AAIController* AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute) || PatrolRoute->GetPatrolPoints().Num() <= 0) { return EBTNodeResult::Failed; }
	auto NextPoint = PatrolRoute->GetPatrolPoints()[Index];

	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, NextPoint);

	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, (Index + 1) % PatrolRoute->GetPatrolPoints().Num());

	return EBTNodeResult::Succeeded;
}