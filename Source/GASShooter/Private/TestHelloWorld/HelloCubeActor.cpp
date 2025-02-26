#include "TestHelloWorld/HelloCubeActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// 定义日志分类（必须与声明一致）
DEFINE_LOG_CATEGORY(XHWLOG);

AHelloCubeActor::AHelloCubeActor()
{
    PrimaryActorTick.bCanEverTick = true;

    // 创建并设置静态网格体组件
    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
    RootComponent = CubeMesh;

    // 加载默认 Cube 模型
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(TEXT("/Engine/BasicShapes/Cube"));
    if (CubeAsset.Succeeded())
    {
        CubeMesh->SetStaticMesh(CubeAsset.Object);
    }

    // 设置碰撞和点击事件
    CubeMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CubeMesh->SetNotifyRigidBodyCollision(true);
    // 设置碰撞预设为 "BlockAllDynamic"（允许点击）
    CubeMesh->SetCollisionResponseToAllChannels(ECR_Block);
    CubeMesh->OnClicked.AddDynamic(this, &AHelloCubeActor::OnCubeClicked);
    CubeMesh->bVisualizeComponent = true; // 显示碰撞体积

    UE_LOG(XHWLOG, Warning, TEXT("AHelloCubeActor 构造函数执行 Hello World!666"));
}

void AHelloCubeActor::BeginPlay()
{
    Super::BeginPlay();
    // 获取玩家控制器
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        // 显示鼠标光标
        PC->bShowMouseCursor = true;
        
        // 设置输入模式：允许同时操作游戏和UI
        FInputModeGameAndUI InputMode;
        InputMode.SetHideCursorDuringCapture(false); // 点击时不隐藏光标
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // 不锁定鼠标
        PC->SetInputMode(InputMode);
        
        UE_LOG(XHWLOG, Warning, TEXT("鼠标已显示，输入模式已设置"));
    }

    // 记录初始位置作为绕圈中心
    InitialPosition = GetActorLocation();
    
    // 输出日志
    FString ActorName = GetName();
    UE_LOG(XHWLOG, Warning, TEXT("[%s] AHelloCubeActor BeginPlay Hello World 123!"), *ActorName);
}

void AHelloCubeActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 绕圈运动计算
    Angle += Speed * DeltaTime; // 角度累积（度）
    const float Radians = FMath::DegreesToRadians(Angle); // 转为弧度
    
    // 计算新位置
    const float X = Radius * FMath::Cos(Radians);
    const float Y = Radius * FMath::Sin(Radians);
    const FVector NewLocation = InitialPosition + FVector(X, Y, 0);
    
    // 更新位置
    SetActorLocation(NewLocation);

    // 每帧从鼠标位置发射射线
    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        FHitResult HitResult;
        PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
        
        if (HitResult.GetComponent() == CubeMesh)
        {
            // 鼠标悬停在Cube上时显示绿色边框
            CubeMesh->SetRenderCustomDepth(true);
            CubeMesh->SetCustomDepthStencilValue(0); // 绿色
            OnCubeClicked(CubeMesh, EKeys::LeftMouseButton);
        }
        else
        {
            CubeMesh->SetRenderCustomDepth(false);
        }
    }
    //UE_LOG(XHWLOG, Warning, TEXT("AHelloCubeActor Tick Hello World!"));
}

void AHelloCubeActor::OnCubeClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{

    UKismetSystemLibrary::PrintString(this, TEXT("OnCubeClicked Hello World!"), true, true, FLinearColor::Green, 2.0f);

    // 点击后重置绕圈中心到当前位置
    InitialPosition = GetActorLocation();

    // 打印当前位置
    FString CurrentPositionStr = FString::Printf(TEXT("当前位置: X=%f, Y=%f, Z=%f"), InitialPosition.X, InitialPosition.Y, InitialPosition.Z);
    UKismetSystemLibrary::PrintString(this, CurrentPositionStr, true, true, FLinearColor::Green, 2.0f);

    UE_LOG(XHWLOG, Warning, TEXT("点击事件已触发！刷新旋转中心到[%s]"), *CurrentPositionStr);
}