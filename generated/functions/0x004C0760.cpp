// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C0760 rf_bolt_emitter_release_slot_resources
// UNREALRED VERIFIED [level-lifecycle-20261028]: For each of four68-byte slots based at emitter+112+68*i, operator-deletes each pointer in array slot+8, releases array backing via0x517F40, then scalar-deletes nonnull auxiliary object slot+4 via0x4C14A0(flags1). Does not clear auxiliary pointer after deletion in this body. Slot array release clears its metadata, so later slot destructor sees null backing.
void __thiscall rf_bolt_emitter_release_slot_resources(void **this)
{
  void **v1; // eax
  void *v3; // [esp+Ch] [ebp-10h]
  int j; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]

  for ( i = 0; i < 4; ++i )
  {
    for ( j = 0; j < rf_receiver_get_first_dword(this + 17 * i + 30); ++j )
    {
      v1 = (void **)sub_552200(this + 17 * i + 30, j);
      operator delete(*v1);
    }
    rf_pointer_array_release_storage(this + 17 * i + 30);
    v3 = *(this + 17 * i + 29);
    if ( v3 )
      rf_bolt_curve_scalar_deleting_destructor(v3, 1);
  }
}

