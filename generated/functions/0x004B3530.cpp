// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B3530 rf_motion_sample_buffer_mark_pending_and_empty
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native buffered-motion insertion/sampling, asymmetric WORD time differences, temporary physics snapshot/restore and native list guards): ECX buffer,no stackargs. Sets count1332=0,last cursor clock1328=-1,ORs flags1320 with1 and returns finalflagsEAX. Preserves all other flag bits,mean1420,last arrival1336,cursor1324,curve/sample arrays. Distinct from full reset25B0. No NULL guard.
int __thiscall rf_motion_sample_buffer_mark_pending_and_empty(_DWORD *this)
{
  int result; // eax

  *(this + 333) = 0;
  *(this + 332) = -1;
  result = *(this + 330) | 1;
  *(this + 330) = result;
  return result;
}

