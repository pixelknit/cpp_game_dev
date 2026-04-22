// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();
}

bool UInventoryComponent::AddItem(const FInventoryItem& NewItem)
{
    for (FInventoryItem& Existing : Items)
    {
        if (Existing.ItemID == NewItem.ItemID && Existing.Quantity < Existing.MaxStackSize)
        {
            int32 SpaceLeft = Existing.MaxStackSize - Existing.Quantity;
            Existing.Quantity += FMath::Min(NewItem.Quantity, SpaceLeft);
            OnInventoryChanged.Broadcast();
            OnItemAdded.Broadcast(NewItem);
            return true;
        }
    }

    if (Items.Num() < MaxSlots)
    {
        Items.Add(NewItem);
        OnInventoryChanged.Broadcast();
        OnItemAdded.Broadcast(NewItem);
        return true;
    }

    UE_LOG(LogTemp, Warning, TEXT("Inventory full! Could not add Item"));
    return false;
}

bool UInventoryComponent::RemoveItem(FName ItemID, int32 Amount)
{
    for (int32 i = 0; i < Items.Num(); i++)
    {
        if (Items[i].ItemID == ItemID)
        {
            Items[i].Quantity -= Amount;
            if (Items[i].Quantity <= 0)
                Items.RemoveAt(i);

            OnInventoryChanged.Broadcast();
            return true;
        }
    }
    return false;
}

bool UInventoryComponent::HasItem(FName ItemID, int32 Amount)
{
    return GetItemCount(ItemID) >= Amount;

}


int32 UInventoryComponent::GetItemCount(FName ItemID) const
{
    for (const FInventoryItem& Item : Items)
    {
        if (Item.ItemID == ItemID)
            return Item.Quantity;
    }
    return 0;
}

TArray<FInventoryItem> UInventoryComponent::GetItemsByType(EItemType Type) const
{
    TArray<FInventoryItem> Result;
    for (const FInventoryItem& Item : Items)
    {
        if (Item.ItemType == Type)
            Result.Add(Item);
    }
    return Result;
}

void UInventoryComponent::DebugPrintInventory() const
{
    for (const FInventoryItem& Item : Items)
    {
        UE_LOG(LogTemp, Log, TEXT("[Inventory] %s x%d"), *Item.ItemName.ToString(), Item.Quantity);
    }
}