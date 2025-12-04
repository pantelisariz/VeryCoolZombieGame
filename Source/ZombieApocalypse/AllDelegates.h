#pragma once

DECLARE_MULTICAST_DELEGATE_OneParam(FCashChangedDelegate, int32 /*CashChangeValue */);
DECLARE_MULTICAST_DELEGATE_OneParam(FHealthChangedDelegate, int32 /*HealthChangeValue */);
DECLARE_MULTICAST_DELEGATE_OneParam(FAmmoChangedDelegate, int32 /*AmmoChangeValue */);


inline FCashChangedDelegate CashChanged;
inline FHealthChangedDelegate HealthChanged;
inline FAmmoChangedDelegate AmmoChanged;
