#pragma once

#include "DaeTestPerformanceBudgetViolation.h"
#include "DaeTestResultData.h"
#include <CoreMinimal.h>

/** Result data for performance tests. */
class DAEDALICTESTAUTOMATIONPLUGIN_API FDaeTestPerformanceBudgetResultData
    : public FDaeTestResultData
{
public:
    virtual FName GetDataType() const override;

    /** Performance budget violations that occurred during the test. */
    TArray<FDaeTestPerformanceBudgetViolation> BudgetViolations;
};
