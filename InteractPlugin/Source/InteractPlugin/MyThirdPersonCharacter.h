//#pragma once
//
//#include "CoreMinimal.h"
//#include "GameFramework/Character.h"
//#include "InteractionPlugin/Public/InteractionComponent.h"
//#include "MyThirdPersonCharacter.generated.h"
//
//class UInputMappingContext;
//class UInputAction;
//struct FInputActionValue;
//UCLASS()
//class INTERACTIONPLUGIN_API AMyThirdPersonCharacter : public ACharacter
//{
//    GENERATED_BODY()
//
//public:
//    AMyThirdPersonCharacter();
//
//protected:
//    virtual void BeginPlay() override;
//
//public:
//    virtual void Tick(float DeltaTime) override;
//    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
//
//    // Enhanced Input
//    UPROPERTY(EditDefaultsOnly, Category = "Input")
//    UInputMappingContext* DefaultMappingContext;
//
//    UPROPERTY(EditDefaultsOnly, Category = "Input")
//    UInputAction* MoveAction;
//
//    UPROPERTY(EditDefaultsOnly, Category = "Input")
//    UInputAction* LookAction;
//
//    UPROPERTY(EditDefaultsOnly, Category = "Input")
//    UInputAction* JumpAction;
//
//    UPROPERTY(EditDefaultsOnly, Category = "Input")
//    UInputAction* InteractAction;
//
//private:
//    void Move(const FInputActionValue& Value);
//    void Look(const FInputActionValue& Value);
//    void Interact();
//
//private:
//
//    UPROPERTY(VisibleAnywhere, Category = "Components")
//    UInteractionComponent* InteractionComponent;
//
//    UPROPERTY(VisibleAnywhere, Category = "Camera")
//    class USpringArmComponent* SpringArmComponent;
//
//    UPROPERTY(VisibleAnywhere, Category = "Camera")
//    class UCameraComponent* CameraComponent;
//};