// ₢ Copright Fuly Software Since 2025


#include "PlayerController/RPGPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interfaces/EnemyInterface.h"
#include "Kismet/KismetSystemLibrary.h"

ARPGPlayerController::ARPGPlayerController()
{
	bReplicates = true;
}

void ARPGPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	EyesTrace();
}

void ARPGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!InputMappingContext)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("InputMappingContext is null"));
		}
	}
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!Subsystem)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Subsystem is null"));
		}
	}
	Subsystem->AddMappingContext(InputMappingContext, 0);
}

void ARPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(Move, ETriggerEvent::Triggered, this, &ARPGPlayerController::OnMove);
	EnhancedInputComponent->BindAction(Look, ETriggerEvent::Triggered, this, &ARPGPlayerController::OnLook);
	EnhancedInputComponent->BindAction(Jump, ETriggerEvent::Triggered, this, &ARPGPlayerController::OnJump);
}

void ARPGPlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator InputRotation = GetControlRotation();
	const FRotator YawRotation = FRotator(0, InputRotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn =  GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ARPGPlayerController::OnLook(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerYawInput(InputAxisVector.X);
		ControlledPawn->AddControllerPitchInput(InputAxisVector.Y);
	}
}

void ARPGPlayerController::OnJump()
{
	
}

void ARPGPlayerController::EyesTrace()
{
	FHitResult TraceResult;
	FVector StartLocation = GetPawn()->GetActorLocation();
	StartLocation.Z += 50.0f;
	const FVector EndLocation = GetPawn()->GetActorForwardVector() * 500.0f + StartLocation;
	const TArray<AActor*> ActorsToIgnore;
	
	UKismetSystemLibrary::SphereTraceSingle(this, StartLocation, EndLocation, 20.0f, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, ActorsToIgnore, EDrawDebugTrace::None, TraceResult, true, FLinearColor::Red, FLinearColor::Green, 0.0f);

	if (!TraceResult.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = TraceResult.GetActor();

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			ThisActor->HighlightActor();
		}
		
	}
	else
	{
		if (ThisActor == nullptr)
		{
			LastActor->UnHighlightActor();
		}
		else
		{
			if (LastActor != ThisActor)
			{
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
		}
	}
}
