#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "UObject/ObjectSaveContext.h"
#include "Engine/Texture2D.h"
#include "Templates/SharedPointer.h"
#include "SvgTexture2D.generated.h"

namespace lunasvg
{
	class Bitmap;
}

UCLASS(BlueprintType)
class SVGBOOGA_API USvgTexture2D : public UTexture
{
	GENERATED_BODY()

public:
	USvgTexture2D(const FObjectInitializer& ObjectInitializer);

#if WITH_EDITOR
	bool UpdateTextureFromSvg(const FString& SvgFilePath, const int TextureWidth, const int TextureHeight,
	                          const FLinearColor InBackgroundColor);
#endif

	UFUNCTION(BlueprintCallable, Category = "SVG")
	UTexture2D* GetTexture();

	UFUNCTION(BlueprintCallable, Category = "SVG")
	int32 GetOriginalWidth() const;

	UFUNCTION(BlueprintCallable, Category = "SVG")
	int32 GetOriginalHeight() const;

	UFUNCTION(BlueprintCallable, Category = "SVG")
	FString GetImportPath() const;

	UFUNCTION(BlueprintCallable, Category = "SVG")
	void SetImportPath(FString& NewImportPath);

	UFUNCTION(BlueprintCallable, Category = "SVG")
	float GetAspectRatio();

protected:
	UPROPERTY(VisibleAnywhere, SkipSerialization, Category = "SVG")
	UTexture2D* Texture;

	FLinearColor BackgroundColor;

	UPROPERTY(VisibleAnywhere, Category = "Import Settings")
	FString ImportPath;

	UPROPERTY(VisibleAnywhere, Category = "Import Settings")
	int32 OriginalWidth;

	UPROPERTY(VisibleAnywhere, Category = "Import Settings")
	int32 OriginalHeight;

	UPROPERTY(VisibleAnywhere, Category = "SVG")
	float AspectRatio;

#if WITH_EDITOR
	TSharedPtr<FImage> ConvertBitmapToImage(const lunasvg::Bitmap& Bitmap);
	void UpdateTextureFromImage(const TSharedPtr<FImage>& SourceImage, const int TextureWidth, const int TextureHeight);
	void UpdateTextureFromBitmap(const lunasvg::Bitmap& Bitmap, const int TextureWidth, const int TextureHeight);
#endif

	virtual void Serialize(FArchive& Ar) override;

public:
	//#region For UTexture
	virtual FTextureResource* CreateResource() override;
	virtual int32 CalcCumulativeLODSize(int32 NumLODs) const final override;
	virtual float GetSurfaceWidth() const override;
	virtual float GetSurfaceHeight() const override;
	virtual float GetSurfaceDepth() const override;
	virtual uint32 GetSurfaceArraySize() const override;
	virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;
	virtual bool IsReadyForAsyncPostLoad() const override;
	virtual void PostLoad() override;
	virtual bool IsCompiling() const override;
	virtual bool IsDefaultTexture() const override;
	virtual bool IsCurrentlyVirtualTextured() const override;
	virtual void UpdateResource() override;
	virtual EMaterialValueType GetMaterialType() const override;
	//#region for UStreamableRenderAsset
	virtual bool StreamOut(int32 NewMipCount) override;
	virtual bool StreamIn(int32 NewMipCount, bool bHighPrio) override;
	//#endregion
	//#endregion
};
