#include "TestHelloWorld/HelloCubeActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// 定义日志分类（必须与声明一致）
DEFINE_LOG_CATEGORY(XHWLOG);

AHelloCubeActor::AHelloCubeActor()
{
	//设置tick可执行
	PrimaryActorTick.bCanEverTick = false;
	
	// 创建并设置静态网格体组件
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	RootComponent = CubeMesh; // 设为根组件

	// 加载默认 Cube 模型
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(TEXT("/Engine/BasicShapes/Cube"));
	if (CubeAsset.Succeeded()) 
	{
		CubeMesh->SetStaticMesh(CubeAsset.Object);
	}

	// 启用点击事件
	CubeMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CubeMesh->SetNotifyRigidBodyCollision(true);
	CubeMesh->OnClicked.AddDynamic(this, &AHelloCubeActor::OnCubeClicked);

	UE_LOG(XHWLOG, Warning, TEXT("AHelloCubeActor 构造函数执行 Hello World!"));
}

void AHelloCubeActor::OnCubeClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	// 输出到控制台
	UE_LOG(XHWLOG, Warning, TEXT("OnCubeClicked Hello World!"));

	// 输出到屏幕（调试用）
	UKismetSystemLibrary::PrintString(this, TEXT("Hello World!"), true, true, FLinearColor::Green, 2.0f);

	// 向前移动 100 单位
	FVector CurrentLocation = GetActorLocation();
	SetActorLocation(CurrentLocation + GetActorForwardVector() * 100.0f);
}

void AHelloCubeActor::BeginPlay()
{
	Super::BeginPlay();
	// 获取当前 Actor 的名称（内部唯一标识，如 "HelloCubeActor_5"）
	FString ActorName = GetName();
	// 输出到控制台
	UE_LOG(XHWLOG, Warning, TEXT( "[%s] AHelloCubeActor BeginPlay Hello World 333!"),*ActorName);
}

void AHelloCubeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(XHWLOG, Warning, TEXT("AHelloCubeActor Tick Hello World!"));
}