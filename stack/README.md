# Intel4004 Stack Management

The actual implementation can be found in `stack.cpp`.

Due to some ambiguities regarding the task definition, some assumptions were made:

- The `getCurrentStackPoition` method returns the position which was last filled. After the initalisation it retruns `-1`, after the first push `0` (because 0 is filled and in my eyes the current position), after the second push `1` and so on.

- `isOverflow` and `isUnderflow` returns `true` if the next push/pop operation will cause a overflow/underflow

- `WarningCondition` has no implementation because it is not evident how to handel errors/warnings.
