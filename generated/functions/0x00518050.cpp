// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00518050 rf_shared_second_dword_getter_518050
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Shared thiscall getter:returns raw DWORD at receiver+4 in EAX,does nothing else;no stack args. Used by solid marker54CF00 on face-list object+112 to gate work. Receiver semantics depend on caller;does not dereference returned value,normalize tobool or mutate list. Existing library flag retained.
int __thiscall rf_shared_second_dword_getter_518050(_DWORD *this)
{
  return *(this + 1);
}

