// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C730 rf_record52_scalar_or_vector_deleting_destructor
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): Thiscall ECX record52 pointer plus stack flags DWORD, RET4. If flags bit1 set, invokes MSVC EH vector destructor
// iterator(base,elementSize52,count=DWORD[base-4],43C7A0), then if flags bit0 set scalar operator delete(base-4); ALWAYS returns adjusted allocation-header pointer base-4 in EAX on
// array branch, even without freeing. If bit1 clear, calls43C7A0(base) once, optionally operator delete(base) iff bit0 set, returns original base. Other flag bits ignored; no own
// NULL, count or allocation-header validation. Flags3 used by426030 destroys header-count elements and frees allocation, distinct from its fixed23/45 string pre-clear loops. No
// pointer-table nulling inside this helper.
char *__thiscall rf_record52_scalar_or_vector_deleting_destructor(char *this, char a2)
{
  if ( (a2 & 2) != 0 )
  {
    `eh vector destructor iterator'(
      this,
      0x34u,
      *((_DWORD *)this - 1),
      (void (__thiscall *)(void *))rf_record_destroy_strings0_8_and_pair24);
    if ( (a2 & 1) != 0 )
      operator delete(this - 4);
    return this - 4;
  }
  else
  {
    rf_record_destroy_strings0_8_and_pair24(this);
    if ( (a2 & 1) != 0 )
      operator delete(this);
    return this;
  }
}

