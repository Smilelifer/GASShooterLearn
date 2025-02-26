// Copyright 2024 Dan Kestranek.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HelloCubeActor.generated.h"

// 声明日志分类（模块名_API 确保跨模块可见）
DECLARE_LOG_CATEGORY_EXTERN(XHWLOG, Log, All);

UCLASS()
class GASSHOOTER_API AHelloCubeActor : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AHelloCubeActor();

	UFUNCTION()
	void OnCubeClicked(UPrimitiveComponent* ClickedComponent, FKey ButtonPressed);
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* CubeMesh;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
