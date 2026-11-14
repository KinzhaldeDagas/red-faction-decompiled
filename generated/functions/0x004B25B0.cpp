// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B25B0 rf_motion_sample_buffer_reset
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native buffered-motion insertion/sampling, asymmetric WORD time differences, temporary physics snapshot/restore and native list guards): ECX buffer,no stackargs. Writes count1332=0,mean interval1420=0,last arrival clock1336=-1,DWORD2300=0,flags1320=0;then3530 redundantly resetscount1332=0,last cursor clock1328=-1,and ORs flags1320 bit1. Final flags=1;returns delegated flagsEAX. Does NOT clear WORD cursor1324,timestamps1280,arrival array1340,sample vectors/parameter array1200 or the two existing curve objects. No NULL/allocation handling.
int __thiscall rf_motion_sample_buffer_reset(int this)
{
  *(_DWORD *)(this + 1332) = 0;
  *(float *)(this + 1420) = 0.0;
  *(_DWORD *)(this + 1336) = -1;
  *(_DWORD *)(this + 2300) = 0;
  *(_DWORD *)(this + 1320) = 0;
  return rf_motion_sample_buffer_mark_pending_and_empty((_DWORD *)this);
}

