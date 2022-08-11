// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStaticMesh_Copied.generated.h"

UCLASS()
class CPP_PLUGIN_API ACStaticMesh_Copied : public AActor
{
	GENERATED_BODY()
	

	private:
	UPROPERTY(VisibleDefaultsOnly)
	class UProceduralMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
	class UMaterialInstanceConstant* Material;

public:
	//외부에서 데이터 세팅해줄 함수들
	FORCEINLINE void SetPositions(TArray<FVector> InPositions) { Positions = InPositions; }
	FORCEINLINE void SetIndices(TArray<int32> InIndices) { Indices = InIndices; }
	FORCEINLINE void SetNormals(TArray<FVector> InNormals) { Normals = InNormals; }
	FORCEINLINE void SetUvs(TArray<FVector2D> InUvs) { Uvs = InUvs; }
	FORCEINLINE void SetColors(TArray<FColor> InColors) { Colors = InColors; }

public:
	ACStaticMesh_Copied();

	//OnConstruction 스크립트를 정의, BP에서 부모함수 콜을 걸어주면
	//여기 정의된 함수부터 실행하고 BP에서 실행한다
	virtual void OnConstruction(const FTransform& Transform) override;
	//SpawnActor와 SpawnActorDeffered 차이
	//SpawnActorDeffered는   FinishSpawningActor의 절차가 추가된다 이부분에서 
	//OnConstruction이전에 값 전달이 가능
	//액터의 수명주기 꼭꼭 확인할 것

protected:
	virtual void BeginPlay() override;

private:
	//렌더링 정보들
	TArray<FVector> Positions;
	TArray<int32> Indices;
	TArray<FVector> Normals;
	TArray<FVector2D> Uvs;
	TArray<FColor> Colors;

};
