#pragma once

#include "CoreMinimal.h"
#include "Settings_LTGenericGraphEditor.generated.h"

UENUM()
enum class ELTAutoLayoutStrategy : uint8
{
	Tree,
	ForceDirected,
};

UCLASS()
class LTGENERICGRAPHEDITOR_API ULTGenericGraphEditorSettings : public UObject
{
	GENERATED_BODY()

public:
	ULTGenericGraphEditorSettings();
	virtual ~ULTGenericGraphEditorSettings();

	UPROPERTY(EditDefaultsOnly, Category = "AutoArrange")
	float OptimalDistance;

	UPROPERTY(EditDefaultsOnly, AdvancedDisplay, Category = "AutoArrange")
	ELTAutoLayoutStrategy LTAutoLayoutStrategy;

	UPROPERTY(EditDefaultsOnly, AdvancedDisplay, Category = "AutoArrange")
	int32 MaxIteration;

	UPROPERTY(EditDefaultsOnly, AdvancedDisplay, Category = "AutoArrange")
	bool bFirstPassOnly;

	UPROPERTY(EditDefaultsOnly, AdvancedDisplay, Category = "AutoArrange")
	bool bRandomInit;

	UPROPERTY(EditDefaultsOnly, AdvancedDisplay, Category = "AutoArrange")
	float InitTemperature;

	UPROPERTY(EditDefaultsOnly, AdvancedDisplay, Category = "AutoArrange")
	float CoolDownRate;
};
