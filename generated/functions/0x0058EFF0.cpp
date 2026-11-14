// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058EFF0 rf_dsound_buffer_slot_clear_fields
// UNREALRED VERIFIED [dsound-buffers-20261028]: Argument slot selects44-byte record. Clears DS buffer pointer+0 and3D interface+4; sets source/sample index+8,stream slot+12,play handle+16 to-1; flags+40=0. Returns record pointer. Does not release resources or clear cached volume+20,step+32,timer+36,other floats. Caller must release before clearing.
int *__cdecl rf_dsound_buffer_slot_clear_fields(int a1)
{
  int *v2; // [esp+0h] [ebp-4h]

  v2 = &unk_1BA1820[11 * a1];
  *v2 = 0;
  v2[1] = 0;
  v2[3] = -1;
  v2[2] = -1;
  v2[4] = -1;
  v2[10] = 0;
  return v2;
}

