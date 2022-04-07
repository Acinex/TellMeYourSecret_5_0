#pragma once
#include "Blueprint/UserWidget.h"

#include "MainMenuContainer.generated.h"

class UTextBlock;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCloseRequest);

UCLASS(BlueprintType, Blueprintable)
class TELLMEYOURSECRET_API UMainMenuContainer : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Hide();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Show();

	virtual void NativeOnInitialized() override;

	UPROPERTY()
	FCloseRequest CloseRequest;

protected:
	UPROPERTY(meta=(BindWidget))
	UButton* BackButton;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* NameTextBlock;

	UPROPERTY(EditAnywhere)
	FText Name;

private:
	UFUNCTION()
	void Close();
};
