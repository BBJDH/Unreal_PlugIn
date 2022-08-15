// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CViewportObject.generated.h"

/**
 * 
 */
UCLASS()
class CPP_PLUGIN_API UCViewportObject : public UObject
{
	GENERATED_BODY()
	private:
	UPROPERTY(EditAnywhere, Category = "Example")
	FString Name;

	UPROPERTY(EditAnywhere, Category = "Example")
	FDateTime StartDate;

	UPROPERTY(EditAnywhere, Category = "Example")
	float Duration;
	
};
