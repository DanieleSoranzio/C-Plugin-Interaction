//#pragma once
//
//#include "CoreMinimal.h"
//#include "GameFramework/Character.h"
//#include "InteractionComponent.h"
//#include "MyThirdPersonCharacter.generated.h"
//
//class USpringArmComponent;
//class UCameraComponent;
//class UInputMappingContext;
//class UInputAction;
//struct FInputActionValue;
//
//UCLASS()
//class INTERACTIONPLUGIN_API AMyThirdPersonCharacter : public ACharacter
//{
//    GENERATED_BODY()
//
//	/** Camera boom positioning the camera behind the character */
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
//	USpringArmComponent* CameraBoom;
//
//	/** Follow camera */
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
//	UCameraComponent* FollowCamera;
//
//	/** MappingContext */
//	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
//	UInputMappingContext* DefaultMappingContext;
//
//	/* Interact Input Action*/
//	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
//	UInputAction* InteractAction;
//
//	/** Move Input Action */
//	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
//	UInputAction* MoveAction;
//
//	/** Look Input Action */
//	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
//	UInputAction* LookAction;
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
//private:
//	/** Called for movement input */
//	void Move(const FInputActionValue& Value);
//
//	/** Called for looking input */
//	void Look(const FInputActionValue& Value);
//
//    void Interact(); // Funzione per interagire
//
//    UPROPERTY(VisibleAnywhere, Category = "Components")
//    UInteractionComponent* InteractionComponent; // Componente di interazione
//
//	/** Returns CameraBoom subobject **/
//	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
//	/** Returns FollowCamera subobject **/
//	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
//};