#include "Interaction/PickupActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Interaction/InteractionManagerComponent.h"
#include "Interaction/InventoryComponent.h"

APickupActor::APickupActor()
{
    PrimaryActorTick.bCanEverTick = false;

    InteractSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractSphere"));
    RootComponent = InteractSphere;
    InteractSphere->SetSphereRadius(InteractRadius);
    InteractSphere->SetCollisionProfileName(TEXT("Trigger"));

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APickupActor::BeginPlay()
{
    Super::BeginPlay();
    InteractSphere->SetSphereRadius(InteractRadius);
    InteractSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupActor::OnSphereBeginOverlap);
    InteractSphere->OnComponentEndOverlap.AddDynamic(this, &APickupActor::OnSphereEndOverlap);
}

void APickupActor::OnSphereBeginOverlap(UPrimitiveComponent*, AActor* OtherActor,
    UPrimitiveComponent*, int32, bool, const FHitResult&)
{
    APawn* Pawn = Cast<APawn>(OtherActor);
    if (Pawn && Pawn->IsPlayerControlled())
    {
        auto* Manager = Pawn->FindComponentByClass<UInteractionManagerComponent>();
        if (Manager) Manager->SetCurrentInteractable(this);
    }
}

void APickupActor::OnSphereEndOverlap(UPrimitiveComponent*, AActor* OtherActor,
    UPrimitiveComponent*, int32)
{
    APawn* Pawn = Cast<APawn>(OtherActor);
    if (Pawn && Pawn->IsPlayerControlled())
    {
        auto* Manager = Pawn->FindComponentByClass<UInteractionManagerComponent>();
        if (Manager) Manager->ClearCurrentInteractable(this);
    }
}

void APickupActor::Interact_Implementation(AActor* Interactor)
{
    UInventoryComponent* Inventory = Interactor->FindComponentByClass<UInventoryComponent>();
    if (Inventory && Inventory->AddItem(ItemData))
    {
        Inventory->DebugPrintInventory();
        OnPickedUp(Interactor);
    }
}

FText APickupActor::GetInteractPrompt_Implementation()
{
    return FText::Format(
        NSLOCTEXT("Pickup", "PromptFmt", "Press [E] to pick up {0}"),
        ItemData.ItemName
    );
}

void APickupActor::OnPickedUp_Implementation(AActor* Interactor)
{
    Destroy();
}