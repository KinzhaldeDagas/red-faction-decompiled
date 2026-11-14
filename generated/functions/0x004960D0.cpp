// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004960D0 rf_player_string_state3664_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Thiscall3664-byte prefix,returns receiver. EH vector constructor iterator on receiver12,count128,stride28,ctor496130,dtor496150. Constructs every record RFString12 only; no
// initialization of prefixFLOAT0/BYTE4/DWORD8,record numeric fields,DWORD3596 or four raw16-byte blocks3600. Unwind destroys successfully constructed strings. Constructor pointer's
// inherited SDK symbol was false application classification.
char *__thiscall rf_player_string_state3664_construct(char *this)
{
  `eh vector constructor iterator'(
    this + 12,
    0x1Cu,
    128,
    (void (__thiscall *)(void *))rf_player_string_record28_construct,
    (void (__thiscall *)(void *))rf_player_string_record28_destroy);
  return this;
}

