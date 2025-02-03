// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StaticMeshDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_KGW_1_API UStaticMeshDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Mesh Asset Data")
	TArray<UStaticMesh*> StaticMeshAssetList;
};
