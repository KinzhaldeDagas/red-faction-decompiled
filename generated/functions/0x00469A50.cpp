// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00469A50 rf_performance_options_apply_preset
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Cdecl raw presetDWORD,PE table verified. UI state
// tuple(DWORD6F7504,DWORD6F6E54,BYTE6F77A0,BYTE6F77F0,BYTE6F7550,DWORD6F6FC4):preset0=(0,0,1,1,1,0),1=(1,1,1,1,1,1),2=(1,2,0,0,0,1).3 ONLY sets chooserDWORD6F770C=3;all other inputs
// set none of tuple. EVERY input including3/invalid still stores raw preset into unchecked playerDWORD3916,then commits CURRENT
// tuple:playerBYTE3906/projected_shadows_enabled=7550;playerBYTE3907/global663F04=77F0;playerBYTE3908 and category-light
// setter=77A0;playerDWORD3924/global1C99890=7504;playerDWORD3920=6E54;bitmap reduction setter1/2 only for exact1/2 else0. Any nonzero6FC4
// ->playerBYTE3912=1,mip_filter_backend(0);zero ->BYTE0/backend(1),inverse setter boolean. No input-range/playerNULL/capability validation,save,rollback or forced tuple defaults for
// custom/invalid preset. Uses raw bytes except normalized3912;return final renderer delegate residue.
int __cdecl rf_performance_options_apply_preset(int a1)
{
  switch ( a1 )
  {
    case 0:
      unk_6F7504 = 0;
      unk_6F6E54 = 0;
      byte_6F77A0[0] = 1;
      unk_6F77F0 = 1;
      unk_6F7550 = 1;
      unk_6F6FC4 = 0;
      break;
    case 1:
      unk_6F7504 = 1;
      unk_6F6E54 = 1;
      byte_6F77A0[0] = 1;
      unk_6F77F0 = 1;
      unk_6F7550 = 1;
      unk_6F6FC4 = 1;
      break;
    case 2:
      unk_6F7504 = 1;
      unk_6F6E54 = 2;
      byte_6F77A0[0] = 0;
      unk_6F77F0 = 0;
      unk_6F7550 = 0;
      unk_6F6FC4 = 1;
      break;
    case 3:
      unk_6F770C = 3;
      break;
    default:
      break;
  }
  *(_DWORD *)(rf_local_fpgun_player + 3916) = a1;
  *(_BYTE *)(rf_local_fpgun_player + 3906) = unk_6F7550;
  rf_projected_shadows_enabled = unk_6F7550;
  *(_BYTE *)(rf_local_fpgun_player + 3907) = unk_6F77F0;
  byte_663F04 = unk_6F77F0;
  *(_BYTE *)(rf_local_fpgun_player + 3908) = byte_6F77A0[0];
  rf_renderer_set_category_light_allow_byte(byte_6F77A0[0]);
  *(_DWORD *)(rf_local_fpgun_player + 3924) = unk_6F7504;
  unk_1C99890 = unk_6F7504;
  *(_DWORD *)(rf_local_fpgun_player + 3920) = unk_6F6E54;
  if ( unk_6F6E54 == 1 )
  {
    rf_bitmap_set_global_reduction_mode(1);
  }
  else if ( unk_6F6E54 == 2 )
  {
    rf_bitmap_set_global_reduction_mode(2);
  }
  else
  {
    rf_bitmap_set_global_reduction_mode(0);
  }
  if ( unk_6F6FC4 )
  {
    *(_BYTE *)(rf_local_fpgun_player + 3912) = 1;
    return rf_renderer_set_mip_filter_backend_dispatch(0);
  }
  else
  {
    *(_BYTE *)(rf_local_fpgun_player + 3912) = 0;
    return rf_renderer_set_mip_filter_backend_dispatch(1);
  }
}

