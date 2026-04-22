// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractionManagerComponent.h"

// Sets default values for this component's properties
UInteractionManagerComponent::UInteractionManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UInteractionManagerComponent::TryInteract()
{
	if (CurrentInteractable &&
		CurrentInteractable->Implements<UInteractableInterface>())
	{
		IInteractableInterface::Execute_Interact(CurrentInteractable, GetOwner());
	}
}

void UInteractionManagerComponent::SetCurrentInteractable(AActor* Actor)
{
	CurrentInteractable = Actor;
	if (Actor && Actor->Implements<UInteractableInterface>())
	{
		FText Prompt = IInteractableInterface::Execute_GetInteractPrompt(Actor);
		OnInteractableFound.Broadcast(Prompt);
	}
}

void UInteractionManagerComponent::ClearCurrentInteractable(AActor* Actor)
{
	if (CurrentInteractable == Actor)
	{
		CurrentInteractable = nullptr;
		OnInteractableLost.Broadcast();
	}
}


// Called when the game starts
