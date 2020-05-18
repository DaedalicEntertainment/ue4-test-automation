# Assertions

Daedalic Test Automation Plugin comes with the following assertion nodes for use in your automated tests:

## Basic Assertions

| Node | Description |
| --- | --- |
| ![Assert Fail](AssertFail.png) | Finishes the current test as failure. |
| ![Assert True](AssertTrue.png) | Expects the specified value to be true. |
| ![Assert False](AssertFalse.png) | Expects the specified value to be false. |
| ![Assert Valid](AssertValid.png) | Expects the specified object to be valid. |
| ![Assert Invalid](AssertInvalid.png) | Expects the specified object not to be valid. |
| ![Assert Was Triggered](AssertWasTriggered.png) | Expects the specified trigger box to be triggered. |
| ![Assert Was Not Triggered](AssertWasNotTriggered.png) | Expects the specified trigger box not to be triggered. |

## Equality

| Node | Description |
| --- | --- |
| ![Assert Equal (Byte)](AssertEqualByte.png) | Expects the specified bytes to be equal. |
| ![Assert Equal (Integer)](AssertEqualInteger.png) | Expects the specified 32-bit integers to be equal. |
| ![Assert Equal (Integer64)](AssertEqualInteger64.png) | Expects the specified 64-bit integers to be equal. |
| ![Assert Equal (Float)](AssertEqualFloat.png) | Expects the specified floats to be (nearly) equal. |
| ![Assert Equal (Name)](AssertEqualName.png) | Expects the specified names to be equal. |
| ![Assert Equal (String)](AssertEqualString.png) | Expects the specified strings to be equal. |
| ![Assert Equal (Text)](AssertEqualText.png) | Expects the specified texts to be equal. |
| ![Assert Equal (Vector)](AssertEqualVector.png) | Expects the specified vectors to be (nearly) equal. |
| ![Assert Equal (Rotator)](AssertEqualRotator.png) | Expects the specified rotators to be (nearly) equal. |
| ![Assert Equal (Transform)](AssertEqualTransform.png) | Expects the specified transforms to be (nearly) equal. |

## Inequality

| Node | Description |
| --- | --- |
| ![Assert Not Equal (Byte)](AssertNotEqualByte.png) | Expects the specified bytes not to be equal. |
| ![Assert Compare (Byte)](AssertCompareByte.png) | Compares the specified bytes for order. |
| ![Assert Not Equal (Integer)](AssertNotEqualInteger.png) | Expects the specified 32-bit integers not to be equal. |
| ![Assert Compare (Integer)](AssertCompareInteger.png) | Compares the specified 32-bit integers for order. |
| ![Assert Not Equal (Integer64)](AssertNotEqualInteger64.png) | Expects the specified 64-bit integers not to be equal. |
| ![Assert Compare (Integer64)](AssertCompareInteger64.png) | Compares the specified 64-bit integers for order. |
| ![Assert Not Equal (Float)](AssertNotEqualFloat.png) | Expects the specified floats not to be equal. |
| ![Assert Compare (Float)](AssertCompareFloat.png) | Compares the specified floats for order. |
| ![Assert Not Equal (Name)](AssertNotEqualName.png) | Expects the specified names not to be equal. |
| ![Assert Not Equal (String)](AssertNotEqualString.png) | Expects the specified strings not to be equal. |
| ![Assert Not Equal (Text)](AssertNotEqualText.png) | Expects the specified texts not to be equal. |
| ![Assert Not Equal (Vector)](AssertNotEqualVector.png) | Expects the specified vectors not to be equal. |
| ![Assert Not Equal (Rotator)](AssertNotEqualRotator.png) | Expects the specified rotators not to be equal. |
| ![Assert Not Equal (Transform)](AssertNotEqualTransform.png) | Expects the specified transforms not to be equal. |

## Range Checks

| Node | Description |
| --- | --- |
| ![Assert In Range (Byte)](AssertInRangeByte.png) | Expects Value to be between MinInclusive and MaxInclusive. |
| ![Assert In Range (Integer)](AssertInRangeInteger.png) | Expects Value to be between MinInclusive and MaxInclusive. |
| ![Assert In Range (Integer64)](AssertInRangeInteger64.png) | Expects Value to be between MinInclusive and MaxInclusive. |
| ![Assert In Range (Float)](AssertInRangeFloat.png) | Expects Value to be between MinInclusive and MaxInclusive. |
| ![Assert Not In Range (Byte)](AssertNotInRangeByte.png) | Expects Value not to be between MinInclusive and MaxInclusive. |
| ![Assert Not In Range (Integer)](AssertNotInRangeInteger.png) | Expects Value not to be between MinInclusive and MaxInclusive. |
| ![Assert Not In Range (Integer64)](AssertNotInRangeInteger64.png) | Expects Value not to be between MinInclusive and MaxInclusive. |
| ![Assert Not In Range (Float)](AssertNotInRangeFloat.png) | Expects Value not to be between MinInclusive and MaxInclusive. |

## UMG Widgets

| Node | Description |
| --- | --- |
| ![Assert Widget Is Visible](AssertWidgetIsVisible.png) | Expects the specified widget to be valid and visible (e.g. added to viewport, not hidden or collapsed). |
| ![Assert Text Is Set](AssertTextIsSet.png) | Expects the specified text not to be empty. |
| ![Assert Rich Text Is Set](AssertRichTextIsSet.png) | Expects the specified rich text not to be empty. |
| ![Assert Image Is Set](AssertImageIsSet.png) | Expects the specified image to be set up to use a texture or material. |
