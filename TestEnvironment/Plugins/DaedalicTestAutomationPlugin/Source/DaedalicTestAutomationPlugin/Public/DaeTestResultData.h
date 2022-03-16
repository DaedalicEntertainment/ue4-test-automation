#pragma once

#include <CoreMinimal.h>

/** Additional result data of a single test. */
class DAEDALICTESTAUTOMATIONPLUGIN_API FDaeTestResultData
{
public:
    virtual ~FDaeTestResultData();

    /** Gets the name of the type of this data. Used to ensure safe type-casting. */
    virtual FName GetDataType() const;
};
