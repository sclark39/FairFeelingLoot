#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class LTGENERICGRAPHEDITOR_API FAssetTypeActions_LTGenericGraph : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_LTGenericGraph(EAssetTypeCategories::Type InAssetCategory);

	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual uint32 GetCategories() override;

private:
	EAssetTypeCategories::Type MyAssetCategory;
};