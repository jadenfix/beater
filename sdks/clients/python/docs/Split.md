# Split

Which split of the optimization substrate a [`CaseScore`] belongs to.  The RSI optimizer searches candidates against `Train`/`Val` and decides acceptance only on the held-out `Test` split (§21.4). The split assignment is the *caller's* responsibility — it owns the dataset and its train/val/test partition — so [`run_optimization_round`] never reshuffles or peeks at the split substrate; it merely routes each [`CaseScore`] to the gate by its tag.

## Enum

* `TRAIN` (value: `'train'`)

* `VAL` (value: `'val'`)

* `TEST` (value: `'test'`)

[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


