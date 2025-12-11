#pragma once

class ABitten;
DECLARE_MULTICAST_DELEGATE_OneParam(FCashChangedDelegate, int32 /*CashChangeValue */);
DECLARE_MULTICAST_DELEGATE_OneParam(FHealthChangedDelegate, int32 /*HealthChangeValue */);
DECLARE_MULTICAST_DELEGATE_OneParam(FAmmoChangedDelegate, int32 /*AmmoChangeValue */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnBittenConvertDelegate, ABitten* /*Bitten */);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGunPurchasedDelegate, AGun* /*Gun*/);





inline FCashChangedDelegate CashChanged;
inline FHealthChangedDelegate HealthChanged;
inline FAmmoChangedDelegate AmmoChanged;
inline FOnBittenConvertDelegate OnBittenConvert;

inline FOnGunPurchasedDelegate OnGunPurchased;


