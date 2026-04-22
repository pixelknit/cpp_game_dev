// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableInterface.h"
#include "InteractionManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractableFound, const FText&, PromptText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractableLost);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RWAY_CPP_DEV_API UInteractionManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionManagerComponent();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void TryInteract();

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractableFound OnInteractableFound;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractableLost OnInteractableLost;

	void SetCurrentInteractable(AActor* Actor);
	void ClearCurrentInteractable(AActor* Actor);

private:
	UPROPERTY()
	AActor* CurrentInteractable = nullptr;
		
};
