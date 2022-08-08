// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

struct FExampleDebuggerCategoryData
{
	FString Name;
	FVector Location;
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
	//데이터를 모아주는 역할 정의
	virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;
	//데이터를 그리는 역할 정의

private:
	FExampleDebuggerCategoryData PlayerPawnData;
	FExampleDebuggerCategoryData ForwardActorData;
	FExampleDebuggerCategoryData SelectedActorData;
};
