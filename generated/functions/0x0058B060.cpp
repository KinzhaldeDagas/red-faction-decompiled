// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058B060 rf_input_remap_scan_code
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, input remapping,text wrapping,Bink playback/default records,archive metadata,projection/aperture/classification and glass submission): Cdecl one scan-code DWORD,returns remapped code. Layout selector193A0F0:1 maps86->43;4 maps0->30;2 maps16->30,17->44,30->16,39->50,44->17,50->51,51->39 via one switch(no chained remapping within layout2);3 swaps21 and44. All other codes/layouts unchanged. No queue,state/timestamp mutation or scan range validation in this helper; configured layout only,not modifier/shift or character translation. Earlier repeatable summary retained.
int __cdecl rf_input_remap_scan_code(int a1)
{
  if ( unk_193A0F0 == 1 && a1 == 86 )
    a1 = 43;
  if ( unk_193A0F0 == 4 && !a1 )
    a1 = 30;
  if ( unk_193A0F0 == 2 )
  {
    switch ( a1 )
    {
      case 16:
        a1 = 30;
        break;
      case 17:
        a1 = 44;
        break;
      case 30:
        a1 = 16;
        break;
      case 39:
        a1 = 50;
        break;
      case 44:
        a1 = 17;
        break;
      case 50:
        a1 = 51;
        break;
      case 51:
        a1 = 39;
        break;
      default:
        break;
    }
  }
  if ( unk_193A0F0 == 3 )
  {
    if ( a1 == 21 )
    {
      return 44;
    }
    else if ( a1 == 44 )
    {
      return 21;
    }
  }
  return a1;
}

