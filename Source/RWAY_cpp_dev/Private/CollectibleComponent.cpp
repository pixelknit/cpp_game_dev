// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectibleComponent.h"
#include "Components/ShapeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"

UCollectibleComponent::UCollectibleComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UCollectibleComponent::BeginPlay()
{
	Super::BeginPlay();
	TArray<UShapeComponent*> Shapes;
	GetOwner()->GetComponents<UShapeComponent>(Shapes);
	CollisionComponent = Shapes[0];

	if (CollisionComponent)
	{
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(
			this,
			&UCollectibleComponent::HandleOverlap
		);
	}
	
}

void UCollectibleComponent::HandleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor)
	{
		return;
	}

	if (OtherActor == UGameplayStatics::GetPlayerPawn(this, 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("THE PLAYER IS COLLIDING"));
		if (bIsKeyItem)
		{
			UMyGameInstance* GI = Cast<UMyGameInstance>(
				GetWorld()->GetGameInstance()
			);

			if (GI)
			{
				if (!KeyID.IsNone())
				{
					GI->Keys.Add(KeyID);
					GI->bHasKey = true;
				}
				else
				{
					GI->bHasKey = true;
				}
			}
		}

		GetOwner()->Destroy();
	}
}
