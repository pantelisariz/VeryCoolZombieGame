#pragma once

DECLARE_MULTICAST_DELEGATE_OneParam(FCashChangedDelegate, int32 /*CashChangeValue */);


inline FCashChangedDelegate CashChanged;
