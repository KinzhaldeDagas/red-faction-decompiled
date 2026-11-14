// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00418350 rf_physical_debris_contact_response
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): Thiscall: if contact-liquid DWORD+492 is nonzero, calls 0x418390; otherwise treats result as1. Returns contact code2 for nonzero result, code0 otherwise. The current effect helper always returns AL1, so all normal paths return2. Does not clear contact state or apply an impulse here.
int __thiscall rf_physical_debris_contact_response(_DWORD *this)
{
  char v2; // [esp+7h] [ebp-1h]

  v2 = 1;
  if ( *(this + 123) )
    v2 = rf_physical_debris_contact_effect((int)this);
  if ( v2 )
    return 2;
  else
    return 0;
}

