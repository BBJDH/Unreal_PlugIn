
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDrawVertex.generated.h"

UCLASS()
class CPP_PLUGIN_API ACDrawVertex : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleDefaultsOnly)
	class UProceduralMeshComponent* Mesh;
	
public:	
	ACDrawVertex();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void AddTriangles(int32 InStart);

private:
	TArray<FVector> Positions;
	TArray<int32> Indices;
	TArray<FVector> Normals;
	TArray<FColor> Colors;
	TArray<FVector2D> Uvs;



};
