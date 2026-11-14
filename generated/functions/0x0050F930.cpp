// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050F930 rf_object_model_presence_status
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile lifetime and attachments,weapon selectors,near-miss unordered branches,model and animation caches,original ECX/stack flow and PE bytes): Reads object DWORD+128: returns 0 when nonzero, otherwise -1. Status only; no NULL guard, model loading or writes.
int __cdecl rf_object_model_presence_status(int a1)
{
  if ( *(_DWORD *)(a1 + 128) )
    return 0;
  else
    return -1;
}

