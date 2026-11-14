// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00557C80 rf_runtime_portal_construct_register
// UNREALRED VERIFIED [trigger-airlock-20261022] Allocates 0x38-byte runtime portal; room pointers at+0/+4, bounds at+8/+20, index+32. Appends portal to BOTH room lists+48 in source order. Serialized record is32bytes; allocation has additional fields not classified by this pass.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Constructs56-byte runtime room portal: vector default constructors at8/20 do nothing, so bounds remain uninitialized. Sets index32 to world portal array180 count, appends this to world180 and BOTH room arrays48, stores room pointers0/4. Other fields not initialized here. No duplicate-room or pointer checks; both room pointers equal would append twice.
_DWORD *__thiscall rf_runtime_portal_construct_register(_DWORD *this, int a2, int a3, int a4)
{
  rf_vector3_default_construct_noop(this + 2);
  rf_vector3_default_construct_noop(this + 5);
  *(this + 8) = rf_receiver_get_first_dword((void *)(a2 + 180));
  rf_pointer_array_append_dword((_DWORD *)(a2 + 180), (int)this);
  rf_pointer_array_append_dword((_DWORD *)(a3 + 48), (int)this);
  rf_pointer_array_append_dword((_DWORD *)(a4 + 48), (int)this);
  *this = a3;
  *(this + 1) = a4;
  return this;
}

