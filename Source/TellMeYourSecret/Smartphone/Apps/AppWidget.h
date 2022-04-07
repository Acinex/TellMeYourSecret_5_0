// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AppWidget.generated.h"

class USmartphone;
class USmartphoneMesh;
/**
 * 
 */
UCLASS(BlueprintType)
class TELLMEYOURSECRET_API UAppWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void Close();
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool Back();
    UFUNCTION(BlueprintPure)
    UTexture* GetIcon() const { return Icon; }

    UFUNCTION(BlueprintPure)
    virtual int GetRow() const { return 0; }

    UFUNCTION(BlueprintPure)
    virtual int GetColumn() const { return 0; }

    virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    UTexture* Icon;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn="true"))
    USmartphone* Smartphone;
};
