// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061276A __FF_MSGBANNER
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs banner. If firstset_error_mode(3)==1 OR
// (aSEPARATE secondquery==0 ANDglobal664D60==1), callNMSG_WRITE(252) thenNMSG_WRITE(255). Else no output. No mode mutation because3 isquery, ownexit/newline construction or cached
// route snapshot; each NMSG re-evaluates its own mode/global branch.
void _FF_MSGBANNER()
{
  if ( _set_error_mode(3) == 1 || !_set_error_mode(3) && dword_664D60 == 1 )
  {
    _NMSG_WRITE(252);
    _NMSG_WRITE(255);
  }
}

