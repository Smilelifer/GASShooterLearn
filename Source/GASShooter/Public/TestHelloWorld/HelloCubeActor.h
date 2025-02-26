#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HelloCubeActor.generated.h"

// 定义日志分类（必须与声明一致）
DECLARE_LOG_CATEGORY_EXTERN(XHWLOG, Log, All);

UCLASS()
class GASSHOOTER_API AHelloCubeActor : public AActor
{
	GENERATED_BODY()
    
public:
	AHelloCubeActor();
	// 绕圈运动参数（暴露给细节面板）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Circular Movement")
	float Speed = 100.0f; // 角速度（度/秒）

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Circular Movement")
	float Radius = 200.0f; // 圆半径
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	// 点击事件处理函数
	UFUNCTION()
	void OnCubeClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CubeMesh;

	float Angle = 0.0f;      // 当前角度（度）
	FVector InitialPosition; // 初始位置（绕圈中心）
};