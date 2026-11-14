// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058E7F0 rf_movie_select_bink_copy_format
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, input remapping,text wrapping,Bink playback/default records,archive metadata,projection/aperture/classification and glass submission): No args. Copies physical screen width187CC94/height187CC98 to cached664760/664764. Switch current format1DAE900:23(17h) sets bitmap kind193BBD0=3,returns10;25(19h) kind5,returns8;24(18h) kind5,returns9;all other formats kind4,returns7. Numeric conversion mapping only; no capability validation,allocation or initialized-flag write.
int rf_movie_select_bink_copy_format()
{
  dword_664760 = dword_187CC94;
  dword_664764 = dword_187CC98;
  switch ( unk_1DAE900 )
  {
    case 0x17:
      unk_193BBD0 = 3;
      return 10;
    case 0x19:
      unk_193BBD0 = 5;
      return 8;
    case 0x18:
      unk_193BBD0 = 5;
      return 9;
    default:
      unk_193BBD0 = 4;
      return 7;
  }
}

