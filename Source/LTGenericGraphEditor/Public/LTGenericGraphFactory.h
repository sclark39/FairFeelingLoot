#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "LTGenericGraph.h"
#include "LTGenericGraphFactory.generated.h"

UCLASS()
class LTGENERICGRAPHEDITOR_API ULTGenericGraphFactory : public UFactory
{
	GENERATED_BODY()

public:
	ULTGenericGraphFactory();
	virtual ~ULTGenericGraphFactory();

	UPROPERTY(EditAnywhere, Category=DataAsset)
	TSubclassOf<ULTGenericGraph> LTGenericGraphClass;

	virtual bool ConfigureProperties() override;
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
