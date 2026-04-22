// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "InventoryTypes.h"
#include "PickupActor.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UWidgetComonent;

UCLASS(Abstract)
class RWAY_CPP_DEV_API APickupActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	FInventoryItem ItemData;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	float InteractRadius = 150.0f;

	virtual void Interact_Implementation(AActor* Interactor) override;
	virtual FText GetInteractPrompt_Implementation() override;

protected:

	UPROPERTY(VisibleAnywhere)
	USphereComponent* InteractSphere;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintNativeEvent, Category = "Pickup")
	void OnPickedUp(AActor* Interactor);
	virtual void OnPickedUp_Implementation(AActor* Interactor);

};
