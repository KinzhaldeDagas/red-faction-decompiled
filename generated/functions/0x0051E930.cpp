// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051E930 rf_pointer_array_destroy_backing_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Thiscall wrapper calls47A3F0 on same receiver. Deletes backing pointer at+8 if nonNULL,leaves count/capacity/pointer unchanged,does not free pointed elements or receiver. No reusable reset or ownership flag logic.
void __thiscall rf_pointer_array_destroy_backing_wrapper(void **this)
{
  rf_pointer_array_destroy_backing_storage(this);
}

