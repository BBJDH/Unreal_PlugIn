// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

struct FExampleDebuggerCategoryData
{
	FVector Location;
	FRotator Rotation;
	FVector Forward;
};


/**
 * 
 */
class EXAMPLE_API FExampleDebuggerCategory : public FGameplayDebuggerCategory
{
public:
	FExampleDebuggerCategory();
	~FExampleDebuggerCategory();

public:
	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();

	virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;
	virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;

};
