//#include "MyThirdPersonCharacter.h"
//#include "Camera/CameraComponent.h"
//#include "GameFramework/SpringArmComponent.h"
//#include "EnhancedInputComponent.h"
//#include "EnhancedInputSubsystems.h"
//
//AMyThirdPersonCharacter::AMyThirdPersonCharacter()
//{
//    PrimaryActorTick.bCanEverTick = true;
//
//    // Configura il braccio a molla e la camera
//    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
//    SpringArmComponent->SetupAttachment(RootComponent);
//    SpringArmComponent->TargetArmLength = 400.0f;
//
//    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
//    CameraComponent->SetupAttachment(SpringArmComponent);
//}
//
//void AMyThirdPersonCharacter::BeginPlay()
//{
//    Super::BeginPlay();
//
//    // Aggiungi il Mapping Context al giocatore
//    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
//    {
//        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
//        {
//            Subsystem->AddMappingContext(DefaultMappingContext, 0);
//        }
//    }
//}
//
//void AMyThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//    Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//  
//    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
//    {
//        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyThirdPersonCharacter::Move);
//        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyThirdPersonCharacter::Look);
//        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyThirdPersonCharacter::Jump);
//        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AMyThirdPersonCharacter::Interact);
//    }
//}
//
//void AMyThirdPersonCharacter::Move(const FInputActionValue& Value)
//{
//    FVector2D MovementVector = Value.Get<FVector2D>();
//
//    if (Controller)
//    {
//        const FRotator Rotation = Controller->GetControlRotation();
//        const FRotator YawRotation(0, Rotation.Yaw, 0);
//
//        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
//        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
//
//        AddMovementInput(ForwardDirection, MovementVector.Y);
//        AddMovementInput(RightDirection, MovementVector.X);
//    }
//}
//
//void AMyThirdPersonCharacter::Look(const FInputActionValue& Value)
//{
//    FVector2D LookAxisVector = Value.Get<FVector2D>();
//
//    if (Controller)
//    {
//        AddControllerYawInput(LookAxisVector.X);
//        AddControllerPitchInput(LookAxisVector.Y);
//    }
//}
//
//void AMyThirdPersonCharacter::Jump()
//{
//    ACharacter::Jump();
//}
//
//void AMyThirdPersonCharacter::Interact()
//{
//    if (InteractionComponent)
//    {
//        InteractionComponent->PerformInteraction();
//    }
//    UE_LOG(LogTemp, Warning, TEXT("Interact pressed!"));
//}