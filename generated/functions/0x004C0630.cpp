// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C0630 rf_bolt_emitter_allocate_four_slot_geometry
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, four-slot emitter lifecycle, allocation and constructor layouts, native ordered lifetime gates, attachment transforms and paused rendering): 
// Thiscall emitter,signed requestedCount RET4. For each of four68-byte slots at112, sets life0; allocates64B curve and runs5A4540 on success (four embedded controls with pointer
// table, coordinates uninitialized), stores NULL on allocation failure. Then signed j from0 while j<32-bit(requestedCount-1), allocates12B per-point vector with NOOP ctor, appends
// pointer (including NULL on failure) to existing slot array at+8. Normal positive requestedCount yields requestedCount-1 interior vector pointers per slot; requestedCount<=1
// normally yields none, but INT_MIN subtraction wraps to INT_MAX. No clamping, storage release, rollback, array reinitialization or null-pointer rejection. Repeated call appends to
// existing arrays and overwrites/leaks prior curve pointers. Exception cleanup frees the current raw allocation if its constructor throws; no all-slot transaction.
void __thiscall rf_bolt_emitter_allocate_four_slot_geometry(float *this, int a2)
{
  void *v2; // [esp+4h] [ebp-30h]
  _DWORD *v3; // [esp+8h] [ebp-2Ch]
  void *v5; // [esp+10h] [ebp-24h]
  _DWORD *v6; // [esp+18h] [ebp-1Ch]
  int j; // [esp+20h] [ebp-14h]
  int i; // [esp+24h] [ebp-10h]

  for ( i = 0; i < 4; ++i )
  {
    *(this + 17 * i + 28) = 0.0;
    v6 = operator new(0x40u);
    if ( v6 )
      v3 = rf_cubic_bezier_construct_embedded_controls(v6);
    else
      v3 = nullptr;
    *((_DWORD *)this + 17 * i + 29) = v3;
    for ( j = 0; j < a2 - 1; ++j )
    {
      v5 = operator new(0xCu);
      if ( v5 )
        v2 = rf_vector3_default_construct_noop(v5);
      else
        v2 = nullptr;
      rf_pointer_array_append_dword((_DWORD *)this + 17 * i + 30, (int)v2);
    }
  }
}

